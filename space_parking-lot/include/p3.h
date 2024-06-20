#ifndef P3_H

#define P3_H
#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h>
// using namespace std;
#include <GL/freeglut.h>
// angle setup
#define PI 3.14159265358979
#define DEGREE (2 * PI) / 360
typedef struct color_t
{
    float r, g, b;
    // r,g,b are all in [0,1]
} color;

class Vec
{
private:
    float x, y;

public:
    // default constructer
    Vec()
    {
        x = 0;
        y = 0;
    }

    Vec(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    float getX() { return x; }
    float getY() { return y; }
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setXY(float newX, float newY)
    {
        x = newX;
        y = newY;
    }

    void vecMove(Vec dir)
    {
        x += dir.getX();
        y += dir.getY();
    }

    void vecRotate(Vec _anchor, float angle)
    {
        // relative position
        x -= _anchor.getX();
        y -= _anchor.getY();

        // rotate
        Vec temp = Vec(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
        x = temp.getX();
        y = temp.getY();

        // actual position
        x += _anchor.getX();
        y += _anchor.getY();
    }

    Vec operator+(Vec v)
    {
        return Vec(x + v.getX(), y + v.getY());
    }
    Vec operator-(Vec v)
    {
        return Vec(x - v.getX(), y - v.getY());
    }
    Vec operator*(float k)
    {
        return Vec(x * k, y * k);
    }
    float operator*(Vec v)
    { // dot multiply
        return x * v.getX() + y * v.getY();
    }

    Vec operator<<(float angle) // counterclockwise
    {
        // (x+yi)*(cos+isin)
        return Vec(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
    }
    Vec operator>>(float angle) // clockwise
    {
        // (x+yi)*(cos-isin)
        return Vec(x * cos(angle) + y * sin(angle), y * cos(angle) - x * sin(angle));
    }
};

class Figure
{
protected:
    Vec anchor;

public:
    Figure() : anchor(0, 0) {}

    Vec getAnchor() { return anchor; }
    void setAnchor(Vec a) { anchor = a; }
    virtual void draw() {};
    virtual void move(Vec dir) {Vec v = dir;v=v+Vec(0,0);};
    virtual void rotate(float angle) {if(angle){};}; // counter-clockwise as positive direction
    virtual void zoom(float k) {if(k){};};
    // void changeAnchor(Vec newAnchor) { anchor.setXY(newAnchor.getX(), newAnchor.getY()); }
    virtual ~Figure() {}
};

class Group : public Figure
{
protected:
    std::string name;
    std::vector<Figure*> _subFigures;
    int n=0;
public:
    Group(){};
    Group(std::vector<Figure*> &subFigures, const Vec &_anchor)
    {
        for (auto &subFigure : subFigures)
        {
            //  Set the anchor of every sub-figure the anchor of the whole image
            subFigure->setAnchor(_anchor);
            _subFigures.emplace_back(subFigure);
            // std::cout<<"emplace once"<<std::endl;
        }
        anchor = _anchor;

        // std::cout<<"constructor Group"<<std::endl;
    }

    void draw()
    {
        for (auto &_subFigure : _subFigures)
        {
            _subFigure->draw();
            // std::cout<<"draw once"<<std::endl;
        }
    }

    void setName(const std::string &_name)
    {
        name = _name;
    }

    std::string getName()
    {
        return name;
    }
    void move(Vec dir)
    {
        for (auto &_subFigure : _subFigures)
        {
            _subFigure->move(dir);
        }
    }

    void rotate(float angle)
    {

        for (auto &_subFigure : _subFigures)
        {
            _subFigure->rotate(angle);
        }
    }

    void zoom(float k)
    {
        if(n<10) {if(k){}}
        else {k=1/k;}
        n=(n+1)%20;
        for (auto &_subFigure : _subFigures)
        {
            _subFigure->zoom(k);
        }
    }

    void turn() // turns right
    {

    }
    ~Group()
    {
        for (auto &_subFigure : _subFigures)
        {
            delete _subFigure;
        }
    }
};

class ColoredFig : public Figure
{
protected:
    color c;

public:
    ColoredFig(){};
    ColoredFig(color _c, Vec &_anchor) : c(_c)
    {
        anchor.setX(_anchor.getX());
        anchor.setY(_anchor.getY());
    }
    virtual void draw() = 0;
    virtual void move(Vec dir) = 0;
    virtual void rotate(float angle) = 0; // counter-clockwise as positive direction
    virtual void zoom(float k) = 0;
    virtual ~ColoredFig() {}

    void setColor(color newC)
    {
        c = newC;
    }
    void changeColor(){
        srand(time(NULL));
        float newR = (rand()%255)/255.0;
        float newG = (rand()%255)/255.0;
        float newB = (rand()%255)/255.0;
        color newC = {newR, newG, newB};
        setColor(newC);
    }
};

// Triangle
class Tri : public ColoredFig
{
private:
    Vec v1, v2, v3;

public:
    Tri(Vec v1, Vec v2, Vec v3, color c) : ColoredFig(c, v1), v1(v1), v2(v2), v3(v3){};

    void draw()
    {
        #ifndef NO_GUI
        glBegin(GL_TRIANGLES);
        glColor3f(c.r, c.g, c.b);
        glVertex2f(v1.getX(), v1.getY());
        glVertex2f(v2.getX(), v2.getY());
        glVertex2f(v3.getX(), v3.getY());
        glEnd();
        #endif
    }

    void move(Vec dir)
    {
        v1.vecMove(dir);
        v2.vecMove(dir);
        v3.vecMove(dir);
        anchor.vecMove(dir);
    }

    void rotate(float angle)
    {
        v1.vecRotate(anchor, angle);
        v2.vecRotate(anchor, angle);
        v3.vecRotate(anchor, angle);
    }

    void zoom(float k)
    {
        v1 = (v1 - anchor) * k + anchor;
        v2 = (v2 - anchor) * k + anchor;
        v3 = (v3 - anchor) * k + anchor;
    }
};

// Circle
class Cir : public ColoredFig
{
private:
    Vec center;
    float radius;

public:
    Cir(){};
    Cir(Vec center, float r, color c) : ColoredFig(c, anchor), center(center), radius(r){};
    void draw()
    {
        #ifndef NO_GUI
        glBegin(GL_POLYGON);
        glColor3f(c.r, c.g, c.b);
        for (int i = 0; i < 360; i++)
        {
            glVertex2f(center.getX() + radius * std::cos(i * DEGREE),
                       center.getY() + radius * std::sin(i * DEGREE));
        }
        glEnd();
        #endif
    }
    Vec getCenter(){
        return center;
    }

    void move(Vec dir)
    {
        center.vecMove(dir);
        anchor.vecMove(dir);
    }

    void rotate(float angle)
    {
        center.vecRotate(anchor, angle);
        //std::cout<<"anchor: " << anchor.getX() << ", "<<anchor.getY()<<std::endl;
    }

    void zoom(float k)
    {
        center = (center - anchor) * k + anchor;
        radius = radius * k;
    }
};

// Quadrilateral
class Qua : public ColoredFig
{
private:
    Vec v1, v2, v3, v4;

public:
    Qua(Vec v1, Vec v2, Vec v3, Vec v4, color c) : ColoredFig(c, v1), v1(v1), v2(v2), v3(v3), v4(v4){};

    void draw()
    {
        #ifndef NO_GUI
        glBegin(GL_QUADS);
        glColor3f(c.r, c.g, c.b);
        glVertex2f(v1.getX(), v1.getY());
        glVertex2f(v2.getX(), v2.getY());
        glVertex2f(v3.getX(), v3.getY());
        glVertex2f(v4.getX(), v4.getY());
        glEnd();
        #endif
        // std::cout<<"HERE"<<std::endl;
    }

    void move(Vec dir)
    {
        v1.vecMove(dir);
        v2.vecMove(dir);
        v3.vecMove(dir);
        v4.vecMove(dir);
        anchor.vecMove(dir);
    }

    void rotate(float angle)
    {
        v1.vecRotate(anchor, angle);
        v2.vecRotate(anchor, angle);
        v3.vecRotate(anchor, angle);
        v4.vecRotate(anchor, angle);
    }

    void zoom(float k)
    {
        v1 =Vec((v1-anchor).getX()*k,(v1-anchor).getY()*k)+anchor;
        v2 =Vec((v2-anchor).getX()*k,(v2-anchor).getY()*k)+anchor;
        v3 =Vec((v3-anchor).getX()*k,(v3-anchor).getY()*k)+anchor;
        v4 =Vec((v4-anchor).getX()*k,(v4-anchor).getY()*k)+anchor;
        //std::cout<<"anchor is "<<anchor.getX()<<" "<<anchor.getY()<<std::endl;
        //std::cout<<"v1 is "<<v1.getX()<<" "<<v1.getY()<<std::endl;
    }
    
    /*void setColor(color newC) {
        ColoredFig::setColor(newC);
    }*/
    
    void changeColor() {
        ColoredFig::changeColor();
        //std::cout<<c.b<<" in "<<c.g<<" in "<<c.r<<std::endl;
    }
};

// Parallelogram
class Par : public Qua
{
public:
    Par(Vec v1, Vec v2, Vec v3, color c) : Qua(v1, v2, v3, v2 + (v1 - v2) + (v3 - v2), c) {}
    // v1~v3 should in clockwise/counterclockwise order
};
// Rectangle (only spawn in horizontal or vertical form)
class Rec : public Qua
{
public:
    Rec(Vec v1, Vec v2, color c) : Qua(v1 + Vec(0, (v2 - v1).getY()), v1, v1 + Vec((v2 - v1).getX(), 0), v2, c) {}
    // v1, v2 are the two opposite vertices
};


Vec set_Tel(int t) { // top-left corner, teleported size 0.1*0.2
    /*
    ________________________
       | 0 | 1 | 2 | 3 | 4 |
    

         --------------
    

       | 5 | 6 | 7 | 8 | 9 |
    ________________________
    */
    if(t >= 0 && t <= 4)
        return(Vec(-0.5+0.3*t, 0.9));
    if(t >= 5 && t <= 9)
        return(Vec(-2.0+0.3*t, -0.7));
    else
    {
        std::cout<<"ERROR: t ="<<t<<std::endl;
        return Vec(0,0);
    }
}

#endif