#ifndef PARKINGLOT_H

#define PARKINGLOT_H

#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "p3.h"


#define dir_downwards 0
#define dir_right 1
#define dir_left 2
#define dir_upwards 3

class door : Group // parking lot gate
{
    public: door(){
        Figure* all=new Qua(Vec(-0.975,-0.8),Vec(-0.975,-0.77),Vec(-0.7,-0.77),Vec(-0.7,-0.8),color{0,0,0});
        _subFigures.push_back(all);
    }
    void draw(){
        #ifndef NO_GUI
        Group::draw();
        #endif
    }
    void move(Vec dir){
        Group::move(dir);
    }
    void rotate(float angle){
        Group::rotate(angle);
    }
};
// assume safety bubble size 0.2*0.3 (x,y)

// the anchor is the bottom-left corner of the parking lot
void DrawParkingLot() 
{
    #ifndef NO_GUI
    // 10 spaces in total, 5 on each side
    for(int i = 0; i <= 5; i++)
    {
        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0); // black
        glVertex2f(0.9-0.3*i,-1); // parking space length = 0.4
        glVertex2f(0.9-0.3*i,-0.6); // parking space width = 0.3
        glEnd();
    }
    for(int i = 0; i <= 5; i++)
    {
        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(0.9-0.3*i,0.6);
        glVertex2f(0.9-0.3*i,1);
        glEnd();
    }
    // wall in the middle
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0); // black
    glVertex2f(-1,0);
    glVertex2f(0.5,0);
    glEnd();
    #endif
}

#endif