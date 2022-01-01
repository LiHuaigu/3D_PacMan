
#ifndef FINAL_PROJECT_ECE_PACMAN_H
#define FINAL_PROJECT_ECE_PACMAN_H
#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>
class ECE_Pacman {
public:
    float pacmanX = 0 ;
    float pacmanZ = 6;
    bool isKilled{false};
    int timeKilled{0};
    int score{0};
    int life{3};
    void draw();
    void coin();
    void powerUp();
    void reset();
    bool checkCoins();
    void setDesiredDirection(int key);
    void setCurrentDirection(int key);
    int coins[22][19] ={

            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//21
            {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},//20
            {1,2,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,2,1},//19
            {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},//18
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//17
            {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},//16
            {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},//15
            {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1},//14
            {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1},//13
            {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1},//12
            {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1},//11
            {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1},//10
            {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1},//9
            {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1},//8
            {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},//7
            {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},//6
            {1,2,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,2,1},//5
            {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},//4
            {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},//3
            {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},//2
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//1
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}//0
    };
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
            {1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1},//12
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

};


#endif //FINAL_PROJECT_ECE_PACMAN_H