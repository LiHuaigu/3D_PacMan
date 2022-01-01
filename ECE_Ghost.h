
#ifndef FINAL_PROJECT_ECE_GHOST_H
#define FINAL_PROJECT_ECE_GHOST_H
#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <list>
#include <vector>
//array：ghostX, ghostZ, ghostNumber, ghostReleased, colorRed, colorGreen, colorBlue， ghostIsKilled
static float originRedArr[] = {0, -0.5 ,1, 0, 255, 0, 0, 1};
static float originGreenArr[] = {-1, 0.5, 2, 0, 0, 0.8, 0.81, 1};
static float originOrangeArr[] = {1, 0.5, 3, 0, 1, 0.7, 0, 1};
static float originPinkArr[] = {0, 0.5, 4, 0, 1, 0.4, 0.7, 1};

class ECE_Ghost {
private:
    std::thread m_thread;
    std::thread f_thread;
    bool ghostKilled{false};
    bool ghostReleased{false};
    int ghostNumber;
    float ghostX, ghostZ, colorRed, colorGreen, colorBlue;
public:
    void drawRed();

    void reset();

    void drawGreen();

    void drawPink();

    void drawOrange();

    void ghostDie();

    void escape();

    void updateGhostPosition();

    void releaseTime();

    int shortestPath[1000];

    ECE_Ghost(float ghostX, float ghostZ, int ghostNumber, bool ghostReleased, float colorRed, float colorGreen,
              float colorBlue, bool ghostIsKilled);

    ~ECE_Ghost();

    int walls[22][19] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//21
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},//20
            {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},//19
            {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},//18
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//17
            {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},//16
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},//15
            {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},//14
            {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},//13
            {1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1},//12
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},//11
            {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},//10
            {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},//9
            {1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1},//8
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},//7
            {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1},//6
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},//5
            {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},//4
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},//3
            {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},//2
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//1
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}//0
    };

};


#endif //FINAL_PROJECT_ECE_GHOST_H
