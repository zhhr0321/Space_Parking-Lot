#ifndef VEHICLE_H

#define VEHICLE_H
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

class Car : Group
{
public:
    Car()
    {
        Vec theAnchor = Vec(-0.922,-0.925);
        auto initSubFigure = [&](Figure* A){
            A->setAnchor(theAnchor);
            _subFigures.push_back(A);
        };
        Figure* body = new Qua(Vec(-0.928,-0.88),Vec(-0.928,-0.97), Vec(-0.904, -0.97),Vec(-0.904,-0.88), color{0.517,0.439,0.933});
        Figure* top = new Qua(Vec(-0.928,-0.958), Vec(-0.946,-0.94), Vec(-0.946,-0.91), Vec(-0.928,-0.88), color{0.686,0.933,0.933});
        Figure* wheel_front = new Cir(Vec(-0.904,-0.94), 0.01, color{1.0,0,0}); //1.0,0.965,0.561
        Figure* wheel_back = new Cir(Vec(-0.904,-0.91), 0.01, color{1.0,0,0});
        initSubFigure(body);
        initSubFigure(top);
        initSubFigure(wheel_front);
        initSubFigure(wheel_back);
        setName("Car");
    };

    Vec getDirection(){
        return ((Cir*)(_subFigures[3]))->getCenter() - ((Cir*)(_subFigures[2]))->getCenter();
    };

    void draw(){
        Group::draw();
    };

    void move(Vec dir){
        Group::move(dir);
    }

    void rotate(float k){
        Group::rotate(k);
    }
    void zoom(float k){
        Group::zoom(k);
    }
    std::string getName(){
        return Group::getName();
    }
};

class UFO : Group
{
public:
    UFO()
    {

        Vec theAnchor = Vec(-0.925,-0.925);

        auto initSubFigure = [&](Figure* A){
            A->setAnchor(theAnchor);
            _subFigures.push_back(A);
        };
        Figure* body1 = new Qua( Vec(-0.916,-0.91), Vec(-0.97,-0.955), Vec(-0.955,-0.925), Vec(-0.934,-0.91),color{0.0,0.0,0.8});
        Figure* body2 = new Qua( Vec(-0.895, -0.925), Vec(-0.97,-0.955), Vec(-0.916,-0.91), Vec(-0.88, -0.955),color{0.0,0.0,0.8});
        Figure* wheel_back = new Qua(Vec(-0.955,-0.95), Vec(-0.955,-0.96), Vec(-0.94,-0.96), Vec(-0.94, -0.95), color{0.0,0.841,0.8});
        Figure* wheel_front = new Qua(Vec(-0.90,-0.95), Vec(-0.90,-0.96),Vec(-0.895, -0.96), Vec(-0.895, -0.95), color{0.0,0.841,0.8});
        std::vector<Figure*> temp;
        temp.push_back(body1);
        temp.push_back(body2);
        temp.push_back(wheel_back);
        temp.push_back(wheel_front);
        for(auto &A : temp){
            initSubFigure(A);
        }
        setName("UFO");
    }

    void draw(){
        Group::draw();
    }

    void move(Vec dir){
        Group::move(dir);
    }

    void rotate(float k){
        Group::rotate(k);
    }
    void zoom(float k){
        Group::zoom(k);
    }
    std::string getName(){
        return Group::getName();
    }
};

class Spacecraft : Group
{
public:
    Spacecraft()
    {
        Vec theAnchor = Vec(-0.925,-0.94);

        auto initSubFigure = [&](Figure* A){
            A->setAnchor(theAnchor);
            _subFigures.push_back(A);
        };
        Figure* body = new Qua(Vec(-0.94,-0.91), Vec(-0.94,-0.97), Vec(-0.91,-0.97), Vec(-0.91,-0.91), color{0.545,0.102,0.102});
        Figure* top = new Tri(Vec(-0.94,-0.91), Vec(-0.91,-0.91), Vec(-0.925,-0.88), color{0.803,0.149,0.149});
        Figure* wing_left = new Tri(Vec(-0.94,-0.94), Vec(-0.94,-0.955), Vec(-0.955,-0.955), color{1.0,0.251,0.251});
        Figure* wing_right = new Tri(Vec(-0.91,-0.94), Vec(-0.91,-0.955), Vec(-0.895, -0.955), color{1.0,0.251,0.251});
        std::vector<Figure*> temp;
        temp.push_back(body);
        temp.push_back(top);
        temp.push_back(wing_left);
        temp.push_back(wing_right);

        for(auto &A : temp){
            initSubFigure(A);
        }
        setName("Spa");
    }

    void draw(){
        Group::draw();
    }

    void move(Vec dir){
        Group::move(dir);
    }

    void rotate(float k){
        Group::rotate(k);
    }

    std::string getName(){
        return Group::getName();
    }
    void zoom(float k){
        Group::zoom(k);
    }
};

#endif