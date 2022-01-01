
#include <iostream>
//#include <glew.h>
#include <unistd.h>
#include <GLUT/glut.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <mutex>
#include <math.h>
#include <stdlib.h> // standard definitions
#include <atomic>
#include "ECE_Pacman.h"
#include "ECE_Maze.h"
#include "ECE_Ghost.h"
std::mutex gMtx;//mutex
std::condition_variable gCv;//condition variable
std::atomic<bool> gbGameRunning = {false};//whether game start running
std::atomic<bool> powerUpConsumed = {false};//whether power up consumed
bool pacManKilled = {false};//whether pacman is killed
std::atomic<bool> resetAll = {false};//reset ghosts and pacman to the origin
std::atomic<bool> gameEnd = {false};//whether game is ended
int pacmanKillTime = 0;//how many times pacman has been killed
ECE_Pacman gPacman;//create pacman
int score;//total score earned
ECE_Maze gMaze;//create the maze
//create four ghosts
ECE_Ghost gGhosts[4] = {
        {0, -0.5 ,1, false, 255, 0, 0, 0},
        {-1, 0.5, 2, false, 0, 0.8, 0.81, 0},
        {1, 0.5, 3, false, 1, 0.7, 0, 0},
        {0, 0.5, 4, false, 1, 0.4, 0.7, 0}
};
GLUquadricObj* quadritic = gluNewQuadric();

void display();

void quitGame();

void init(void)//initialization
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 20.0, 20.0, 20.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_DEPTH_TEST);
    if(!quadritic)
    {
        quadritic = gluNewQuadric();
    }
}
void display(void)//display all the stuff
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    gMaze.wall();//draw wall
    gPacman.coin();//draw coin
    gPacman.powerUp();//draw power up
    gPacman.draw();//draw pacman
    //draw four ghosts
    gGhosts[0].drawRed();
    gGhosts[1].drawGreen();
    gGhosts[2].drawOrange();
    gGhosts[3].drawPink();
    glutSwapBuffers();
}



void reshape(int w, int h)//reshape the scene
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, (GLfloat)w / (GLfloat)h, 1.0, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 15, 25, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void normalKeys(unsigned char key, int x, int y)//normal keys, starting of exiting the game
{
    gbGameRunning = true;
    if(key == 'q' || key == 'Q')
    {
        std::cout << "Quit Game" << std::endl;
        quitGame();
    }
}

void timerFunction(int ID)//control time
{
    display();
    gCv.notify_all();
    glutTimerFunc(300, timerFunction, 0);
}

void quitGame()//quit game
{
    exit(0);
}

void pressSpecialKey(int key, int x, int y)//special key, control the movement of pacman
{
    gbGameRunning = true;
    switch (key)
    {
        case GLUT_KEY_UP: gPacman.setDesiredDirection(GLUT_KEY_UP); break;
        case GLUT_KEY_LEFT: gPacman.setDesiredDirection(GLUT_KEY_LEFT); break;
        case GLUT_KEY_DOWN: gPacman.setDesiredDirection(GLUT_KEY_DOWN); break;
        case GLUT_KEY_RIGHT: gPacman.setDesiredDirection(GLUT_KEY_RIGHT); break;
    }
}

int main(int argc, char** argv)//main function
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutSpecialFunc(pressSpecialKey);
    glutKeyboardFunc(normalKeys);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void wall()//draw the wall of maze
{
    glPushMatrix();
    glTranslatef(0, 0.0, -10);
    glColor3f(0.0, 0.5, 0.9);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12, 0.12, 9, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, -10);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-9, 0.0, -10);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, -10);
    glColor3f(0.0, 0.5, 0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12, 0.12, 9, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9, 0.0, -10);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,7, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9, 0.0, -10);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,7, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, -10);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,3, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -3);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 100,100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-9, 0.0, -3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -3);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 100,100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, -3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(0, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    //rectangle one
    glPushMatrix();
    glTranslatef(-2, 0.0, -8);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    //rectangle two
    glPushMatrix();
    glTranslatef(2, 0.0, -8);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    //square one
    glPushMatrix();
    glTranslatef(-6, 0.0, -8);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-7, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-7, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    //square two
    glPushMatrix();
    glTranslatef(6, 0.0, -8);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(7, 0.0, -8);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(7, 0.0, -7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -5);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,4, 100,100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, -5);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(0, 0.0, -3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -5);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-7, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -5);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(7, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,4, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,4, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, -5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -3);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, -3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -3);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, -3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, -3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-9, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, -3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,4, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, 1);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,4, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, 1);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-9, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, 1);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(0, 0.0, 9);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, 1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, 1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, 3);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-9, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, 3);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,3, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 0.0, 1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0.0, 1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, 3);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,4, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, 3);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(0, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, 5);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, 5);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, 7);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,4, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, 7);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, 5);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-7, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, 5);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(7, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, 5);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, 5);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, 5);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(6, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9, 0.0, 3);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,8, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9, 0.0, 3);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,8, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-9, 0.0, 11);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, 11);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9, 0.0, 11);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,18, 200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8, 0.0, 7);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-8, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8, 0.0, 7);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,1, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(8, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, 9);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,5, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-2, 0.0, 9);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-7, 0.0, 9);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, 9);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadritic, 0.12,0.12,5, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(2, 0.0, 9);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(7, 0.0, 9);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 0.0, 7);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0.0, 7);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadritic, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();
}