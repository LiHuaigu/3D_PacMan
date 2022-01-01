
#include "ECE_Pacman.h"
#include "ECE_Maze.h"
#include <GLUT/glut.h>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
extern std::atomic<bool> gbGameRunning;
extern std::atomic<bool> powerUpConsumed;
extern int score;
extern std::atomic<bool> gameEnd;
extern bool pacManKilled;
extern int pacmanKillTime;

GLUquadricObj* quadriticPac = gluNewQuadric();

void ECE_Pacman::draw()//draw pacman
{
    glPushMatrix();
    glColor3f(0.93, 0.93, 0);
    glTranslatef(pacmanX, 0.0, pacmanZ);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();
}
void ECE_Pacman::coin()//draw coins
{
    //set light refelct and color
    GLfloat color[] = { 0.82f, 0.82f, 0.82f, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
    //set quadric
    GLUquadricObj* quadricObj = gluNewQuadric();
    gluQuadricDrawStyle(quadricObj, GLU_SMOOTH);
    //draw the coins
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (coins[i][j]==0)
            {
                glPushMatrix();
                glTranslatef((float)j - 9 , 0, (float)i - 10);
                glColor3f(0.82,0.82,0.82);
                gluSphere(quadricObj, 0.12, 10, 10);
                glPopMatrix();
            }
        }
    }
}
void ECE_Pacman::powerUp()//draw power ups
{
    GLfloat color[] = { 0.97,0.84,0, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
    //set quadric
    GLUquadricObj* quadricObj = gluNewQuadric();
    gluQuadricDrawStyle(quadricObj, GLU_SMOOTH);
    //draw the powerups
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (coins[i][j] == 2)//draw power ups
            {

                glPushMatrix();
                glTranslatef((float)j - 9 , 0, (float)i - 10);
                glColor3f(0.97,0.84,0);
                glRotatef(90, 1, 0, 0.0f);
                gluCylinder(quadriticPac, 0.2,0.2,0.1, 32 ,32);
                glPopMatrix();

                glPushMatrix();
                glTranslatef((float)j - 9 , 0, (float)i - 10);
                glColor3f(0.97,0.84,0);
                glRotatef(90, 1, 0, 0.0f);
                gluDisk(quadriticPac,0,0.2,32,32);
                glPopMatrix();
            }
        }
    }
}

void ECE_Pacman::reset()
{
    pacmanX = 0;
    pacmanZ = 6;
    sleep(2);
    pacManKilled == false;
}

void ECE_Pacman::setDesiredDirection(int key)

{

    if(score == 156)
    {
        std::cout << "You Win" << std::endl;
        exit(0);
    }

    if(pacmanKillTime > 2)//if the pacman died for 3 times, end the game
    {
        std::cout << "Game Over" << std::endl;
        exit(0);
    }

    if(pacManKilled == false)
    {

        switch(key)
        {
            case(GLUT_KEY_UP):
            {
                if (walls[(int)pacmanZ + 10 - 1][(int)pacmanX + 9] == 0)
                {
                    pacmanZ--;
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 0)//consume normal coin
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;
                        score++;
                    }
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 2)//consume power up
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;

                        powerUpConsumed = true;//power up consumed
                        score++;
                    }
                    glutPostRedisplay();

                }
                break;
            }
            case(GLUT_KEY_LEFT):
            {
                if (walls[(int)pacmanZ + 10][(int)pacmanX + 9 - 1]==0)
                {
                    pacmanX--;
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 0)//consume normal coin
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;
                        score++;

                    }
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 2)//consume power up
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;
                        powerUpConsumed = true;//power up consumed
                        score++;
                    }

                    glutPostRedisplay();
                }
                break;
            }
            case(GLUT_KEY_DOWN):
            {

                if (walls[(int)pacmanZ  + 10 + 1][(int)pacmanX + 9 ] == 0)
                {
                    pacmanZ++;
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 0)//consume normal coin
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;
                        score++;

                    }
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 2)//consume power up
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;
                        powerUpConsumed = true;//power up consumed
                        score++;
                    }
                    glutPostRedisplay();


                }
                break;
            }
            case(GLUT_KEY_RIGHT):
            {
                if(walls[(int)pacmanZ + 10][(int)pacmanX + 9 + 1] == 0)
                {
                    pacmanX++;
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 0)//consume normal coin
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;
                        score++;

                    }
                    if(coins[(int)pacmanZ + 10][(int)pacmanX + 9] == 2)//consume power up
                    {
                        coins[(int)pacmanZ + 10][(int)pacmanX + 9] = 1;
                        powerUpConsumed = true;//power up consumed
                        score++;
                    }
                    glutPostRedisplay();
                }
                break;

            }
            default:
            {
                break;
            }
        }
    }


}