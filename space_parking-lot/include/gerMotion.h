#ifndef GERMOTION_H

#define GERMOTION_H
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "p3.h"
#include "vehicle.h"
#include "parkingLot.h"

#define dir_downwards 0
#define dir_right 1
#define dir_left 2
#define dir_upwards 3


typedef struct motion_t{
    Vec move_dir;
    float rotate_angle;
} motion;


void TimeStep(int n) {
if(n){}
#ifndef NO_GUI
    glutTimerFunc(n, TimeStep, n); glutPostRedisplay();
#endif
}


std::vector<motion> generateTurn1(float radius, int n, float theta) // n is the number of steps, theta is the total rotation needed
{
    std::vector<motion> res;
    for(int i = 0; i < n; i++)
    {
        motion m;
        m.rotate_angle = (float)(-theta/n);
        m.move_dir = Vec(sin(i*theta/n)*radius,cos(i*theta/n)*radius);
        res.push_back(m);
    }
    return res;
}

std::vector<motion> generateTurn2(float radius, int n, float theta) // n is the number of steps, theta is the total rotation needed
{
    std::vector<motion> res;
    for(int i = 0; i < n; i++)
    {
        motion m;
        m.rotate_angle = (float)(theta/n);
        m.move_dir = Vec(cos(i*theta/n)*radius,sin(i*theta/n)*radius);
        res.push_back(m);
    }
    return res;
}

std::vector<motion> generateTurn3(float radius, int n, float theta) // n is the number of steps, theta is the total rotation needed
{
    std::vector<motion> res;
    for(int i = 0; i < n; i++)
    {
        motion m;
        m.rotate_angle = (float)(theta/n);
        m.move_dir = Vec(-sin(i*theta/n)*radius,cos(i*theta/n)*radius);
        res.push_back(m);
    }
    return res;
}
std::vector<motion> generateTurn4(float radius, int n, float theta) // n is the number of steps, theta is the total rotation needed
{
    std::vector<motion> res;
    for(int i = 0; i < n; i++)
    {
        motion m;
        m.rotate_angle = (float)(theta/n);
        m.move_dir = Vec(-cos(i*theta/n)*radius,-sin(i*theta/n)*radius);
        res.push_back(m);
    }
    return res;
}

void addMotions(std::queue<motion> &original, motion step, int times) // put multiple same motions into queue
{
    for(int i = 0; i < times; i++)
        original.push(step);
}

void addMotionList(std::queue<motion> &original, std::vector<motion> insert) // put a pre-designed set of motions into queue
{
    for(int i = 0; i < (int)insert.size(); i++)
    {
        original.push(insert[i]);
    }
}

// get motion operations according to parking spot index
std::queue<motion> getmotion(int index)
{
    std::queue<motion> result;
    static motion rightwords = {Vec(0.01,0),0};
    static motion leftwords = {Vec(-0.01,0),0};
    static motion upwords = {Vec(0,0.01),0};
    static motion downwords = {Vec(0,-0.01),0};


    static std::vector<motion> turn_left, turn_right;

    // commom motion while entering
    addMotions(result, upwords, 40); // straight part
    // std::vector<motion> starting_turn = generateTurn(Vec(-0.))

    static std::vector<motion> R; // 倒车入库
    /*
    ________________________
       | 0 | 1 | 2 | 3 | 4 |
    

         --------------
    

       | 5 | 6 | 7 | 8 | 9 |
    ________________________
    */
    
    switch(index)
    {
        case 0:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 160);
            addMotionList(result,generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,60);
            addMotionList(result,generateTurn3(0.01,10,90*DEGREE));
            addMotions(result,leftwords,130);
            addMotionList(result, generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,50);
            break;
        case 1:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 160);
            addMotionList(result,generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,60);
            addMotionList(result,generateTurn3(0.01,10,90*DEGREE));
            addMotions(result,leftwords,100);
            addMotionList(result, generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,50);
            break;
        case 2:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 160);
            addMotionList(result,generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,60);
            addMotionList(result,generateTurn3(0.01,10,90*DEGREE));
            addMotions(result,leftwords,70);
            addMotionList(result, generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,50);
            break;
        case 3:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 160);
            addMotionList(result,generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,60);
            addMotionList(result,generateTurn3(0.01,10,90*DEGREE));
            addMotions(result,leftwords,40);
            addMotionList(result, generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,50);
            break;
        case 4:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 160);
            addMotionList(result,generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,60);
            addMotionList(result,generateTurn3(0.01,10,90*DEGREE));
            addMotions(result,leftwords,10);
            addMotionList(result, generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,upwords,50);
            break;
        case 9:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 155);
            addMotionList(result,generateTurn2(0.01,10,90*DEGREE));
            addMotions(result,downwords,30);
            break;
        case 8:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 140);
            addMotionList(result,generateTurn4(0.01,10,90*DEGREE));
            addMotions(result,downwords,30);
            break;
        case 7:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 110);
            addMotionList(result,generateTurn4(0.01,10,90*DEGREE));
            addMotions(result,downwords,30);
            break;
        case 6:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 80);
            addMotionList(result,generateTurn4(0.01,10,90*DEGREE));
            addMotions(result,downwords,30);
            break;
        case 5:
            addMotionList(result, generateTurn1(0.01,10,90*DEGREE));
            addMotions(result, rightwords, 50);
            addMotionList(result,generateTurn4(0.01,10,90*DEGREE));
            addMotions(result,downwords,40);
            break;
        
    }

    std::cout<<"motion steps: "<<result.size()<<std::endl;
    return result;
}

#endif