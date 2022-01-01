
#include <unistd.h>
#include "ECE_Pacman.h"
#include "ECE_Ghost.h"
#include "ECE_Maze.h"
#include <thread>
#include <vector>
#include <GLUT/glut.h>
#include <random>
#include <ctime>
extern std::mutex gMtx;
extern std::condition_variable gCv;
extern std::atomic<bool> gbGameRunning;
extern std::atomic<bool> powerUpConsumed;
extern bool pacManKilled;
extern ECE_Pacman gPacman;
extern int pacmanKillTime;

GLUquadricObj* quadriticGhost = gluNewQuadric();

int walls[22][19] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//21
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},//20
        {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},//19
        {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},//18
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//17
        {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},//16
        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},//15
        {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},//14
        {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},//13
        {1,1,1,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,1},//12
        {0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},//11
        {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},//10
        {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},//9
        {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},//8
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},//7
        {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},//6
        {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},//5
        {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},//4
        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},//3
        {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},//2
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//1
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}//0
};
//draw pink ghost
void ECE_Ghost::drawPink()
{
    if(powerUpConsumed == false)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
    else if(powerUpConsumed = true)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
}
//draw red ghost
void ECE_Ghost::drawRed()
{
    if(powerUpConsumed == false)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
    else if(powerUpConsumed == true)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
}
//draw green ghost
void ECE_Ghost::drawGreen()
{
    if(powerUpConsumed == false)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
    else if(powerUpConsumed == true)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
}
//draw orange ghost
void ECE_Ghost::drawOrange()
{
    if(powerUpConsumed == false)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(colorRed,colorGreen,colorBlue);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
    else if(powerUpConsumed == true)
    {
        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glRotatef(90, 1, 0, 0);
        gluCylinder(quadriticGhost, 0.4,0.4,0.25, 32 ,32);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(ghostX, 0.05, ghostZ);
        glColor3f(1,1,1);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
}

void ECE_Ghost::updateGhostPosition()//define ghost movement
{
    if(powerUpConsumed == false)//when power up is not consumed, ghost can kill pacman
    {
        if(ghostReleased == false)//release 4 ghosts, 2 seconds each
        {
            switch((int)ghostNumber)
            {
                case (1)://red
                {
                    ghostZ = -1;
                    ghostX = 0;
                    ghostReleased = true;
                }
                case (2)://green
                {
                    ghostZ = 0;
                    ghostX = -3;
                    ghostReleased = true;
                }
                case (3)://orange
                {
                    ghostZ = 2;
                    ghostX = 3;
                    ghostReleased = true;
                }
                case (4)://pink
                {
                    ghostZ = 2;
                    ghostX = 0;
                    ghostReleased = true;
                }
            }
        }
        else if(ghostReleased == true)//movement of ghosts, ghosts can kill pacman
        {

            srand(static_cast<unsigned int>(time(0)));
            switch ((int)ghostNumber)
            {
                case 1://up
                    if (walls[(int)ghostZ + 10 - 1][(int)ghostX + 9] == 0)
                    {
                        ghostZ -= 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)
                        {
                            std::cout << "pacman is killed" << std::endl;
                            pacmanKillTime++;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                case 2://down
                    if (walls[(int)ghostZ + 10 + 1][(int)ghostX + 9] == 0)
                    {
                        ghostZ += 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)
                        {
                            std::cout << "pacman is killed" << std::endl;
                            pacmanKillTime++;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                case 3://left
                    if (walls[(int)ghostZ + 10][(int)ghostX + 9 - 1] == 0)
                    {
                        ghostX -= 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)
                        {
                            std::cout << "pacman is killed" << std::endl;
                            pacmanKillTime++;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                case 4://right
                    if (walls[(int)ghostZ + 10][(int)ghostX + 9 + 1] == 0)
                    {
                        ghostX += 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)
                        {
                            std::cout << "pacman is killed" << std::endl;
                            pacmanKillTime++;

                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                default:
                    break;
            }
        }

    } else if (powerUpConsumed == true)//when power up consumed, pacman can kill ghost
    {
        if(ghostReleased == false)//release 4 ghosts, 2 seconds each
        {
            switch((int)ghostNumber)
            {
                case (1)://red
                {
                    ghostZ = -1;
                    ghostX = 0;
                    ghostReleased = true;
                }
                case (2)://green
                {
                    ghostZ = 0;
                    ghostX = -3;
                    ghostReleased = true;
                }
                case (3)://orange
                {
                    ghostZ = 2;
                    ghostX = 3;
                    ghostReleased = true;
                }
                case (4)://pink
                {
                    ghostZ = 2;
                    ghostX = 0;
                    ghostReleased = true;
                }
            }
        }
        else if(ghostReleased == true)
        {
            srand(static_cast<unsigned int>(time(0)));
            switch ((int)ghostNumber)
            {
                case 1://up
                    if (walls[(int)ghostZ + 10 - 1][(int)ghostX + 9] == 0)
                    {
                        ghostZ -= 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)//pacman kill ghost
                        {
                            reset();//reset the ghost to the origin
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                case 2://down
                    if (walls[(int)ghostZ + 10 + 1][(int)ghostX + 9] == 0)
                    {
                        ghostZ += 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)//pacman kill ghost
                        {
                            reset();//reset the ghost to the origin
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                case 3://left
                    if (walls[(int)ghostZ + 10][(int)ghostX + 9 - 1] == 0)
                    {
                        ghostX -= 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)//pacman kill ghost
                        {
                            reset();//reset the ghost to the origin
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                case 4://right
                    if (walls[(int)ghostZ + 10][(int)ghostX + 9 + 1] == 0)
                    {
                        ghostX += 1;
                        if(ghostZ == gPacman.pacmanZ && ghostX == gPacman.pacmanX)//pacman kill ghost
                        {
                            reset();//reset the ghost to the origin
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(30));
                    }
                    else
                    {
                        int current = ghostNumber;
                        do
                        {
                            ghostNumber = (rand() % 4) + 1;
                        } while (current == (int)ghostNumber);
                    }
                    break;
                default:
                    break;
            }
        }

    }
}

void ECE_Ghost::reset()//reset the game when pacman is killed
{
    switch(ghostNumber)//back to the origin based on the color of the ghost
    {
        case(1)://reset the red ghost
        {
            ghostX = 0;
            ghostZ = -0.5;
            ghostReleased = false;
        }
        case(2)://reset green ghost
        {
            ghostX = -1;
            ghostZ = 0.5;
            ghostReleased = false;
        }
        case(3)://reset orange ghost
        {
            ghostX = 1;
            ghostZ = 0.5;
            ghostReleased = false;
        }
        case(4)://reset pink ghost
        {
            ghostX = 0;
            ghostZ = 0.5;
            ghostReleased = false;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void ECE_Ghost::escape()//when power up consumed, the ghosts should escape from pacman
{
    updateGhostPosition();
    if (ghostX == gPacman.pacmanX && ghostZ == gPacman.pacmanZ)
    {
        std::cout << "ghost is killed!" << std::endl;
    }
}

void ECE_Ghost::releaseTime()//define the time to release the ghosts, the sequence is based on the color: red, green, orange, pink
{
    if (ghostNumber == 2)//green
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    else if (ghostNumber == 3)//orange
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
    }
    else if (ghostNumber == 4)//pink
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    }
}

void ghostThread(ECE_Ghost* pGhost)
{
    //wait for game to start
    while (!gbGameRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    //Game has started
    if(pacManKilled == false)
    {
        pGhost->releaseTime();//release the ghosts sequentially
        do
        {
            //wait for next signal
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            pGhost->updateGhostPosition();
        } while (gbGameRunning);
    } else if (pacManKilled == true)
    {

        do
        {
            pGhost->reset();
        } while (gbGameRunning);

    }
}

void ghostFear()//ghost can be killed by pacman
{
    while (true)
    {
        bool flag = false;
        while (!flag)
        {
            if (powerUpConsumed)
            {
                flag = true;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        powerUpConsumed = false;//reset the flag
    }

}

ECE_Ghost::ECE_Ghost(float gX, float gZ, int gNumber, bool gReleased,float red,float green,float blue,bool gIsKilled)
{
    m_thread = std::thread(ghostThread, this);//initialize the parameters for each thread
    ghostX = gX;
    ghostZ = gZ;
    ghostNumber = gNumber;
    ghostReleased = gReleased;
    colorRed = red;
    colorGreen = green;
    colorBlue = blue;
    ghostKilled = gIsKilled;
    f_thread = std::thread(ghostFear);
}

ECE_Ghost::~ECE_Ghost()//thread interaction
{
    m_thread.join();
}



