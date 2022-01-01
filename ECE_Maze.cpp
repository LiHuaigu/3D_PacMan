#include "ECE_Maze.h"
#include <GLUT/glut.h>
#include <mutex>

GLUquadricObj* quadriticMaze = gluNewQuadric();
extern std::mutex gMtx;
extern std::condition_variable gCv;
extern std::atomic<bool> gbGameRunning;


void ECE_Maze::wall()
{
    glPushMatrix();
    glTranslatef(0, 0.0, -10);
    glColor3f(0.0, 0.5, 0.9);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12, 0.12, 9, 100, 100);
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
    gluCylinder(quadriticMaze, 0.12, 0.12, 9, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-9, 0.0, -10);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,7, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9, 0.0, -10);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,7, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, -10);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,3, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -3);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,3, 100,100);
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
    gluCylinder(quadriticMaze, 0.12,0.12,3, 100,100);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
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
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
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
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 100,100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7, 0.0, -7);
    glColor3f(0,0.5,0.9);
    glRotatef(-180, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,4, 100,100);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,1, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,1, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,4, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,4, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,3, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 200,200);
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
    gluCylinder(quadriticMaze, 0.12,0.12,3, 200,200);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, -1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 0.0, -1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, -1);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,4, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2, 0.0, 1);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,4, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,3, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,3, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, 1);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, 1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,3, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,3, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(9, 0.0, 3);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 0.0, 1);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,4, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,4, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6, 0.0, 5);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,1, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-6, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 0.0, 5);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,8, 32 ,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9, 0.0, 3);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,8, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,18, 200,200);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8, 0.0, 7);
    glColor3f(0,0.5,0.9);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadriticMaze, 0.12,0.12,1, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,1, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,5, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,5, 32 ,32);
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
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(-4, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0.0, 7);
    glColor3f(0,0.5,0.9);
    gluCylinder(quadriticMaze, 0.12,0.12,2, 32 ,32);
    glPopMatrix();

    glPushMatrix();//fix corner
    glColor3f(0.0, 0.5, 0.9);
    glTranslatef(4, 0.0, 7);
    glutSolidSphere(0.12, 100, 100);
    glPopMatrix();
}