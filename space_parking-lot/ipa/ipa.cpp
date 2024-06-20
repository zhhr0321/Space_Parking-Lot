#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include "p3.h"
#include "vehicle.h"
#include "parkingLot.h"
#include "gerMotion.h"
#include "gerMotion.h"

#define dir_downwards 0
#define dir_right 1
#define dir_left 2
#define dir_upwards 3

void glDraw() {
    static int frame=0,num_car=0;
    static int flag_cin=0;
    static int all=0;
    if(flag_cin==0){
        flag_cin=1;
        std::cout<<"input a number between 7 and 10: ";
        std::cin>>all;
    }
    frame++;

    int index=rand()%all;

    static door Door;
    static std::vector<Figure*> vehicle;
    
    //static int num_te=0;
    static std::vector<std::queue<motion>> vehicle_motion;
    static std::vector<bool> isparked(10);// initialize as false
    //num_te=1;


    static int tele_needed = 1;
    static Qua* Tele=nullptr;
    if(tele_needed)
    {
        tele_needed = 0;
        //std::cout<<index<<"space"<<std::endl;
        Vec tele_point = set_Tel(index);
        Tele = new Qua(tele_point, tele_point + Vec(0.0, -0.2), tele_point + Vec(0.1, -0.2), tele_point + Vec(0.1, 0.0), color{0,0,0});
        isparked[index] = 1; // marked space as occupied
    }
    
    if(frame%60 == 1)
    {
        Tele->changeColor();
    }
    
    
    // draw gate
    if(frame%120 >= 2 && frame%120 <= 11) Door.rotate(9*DEGREE);
    if(frame%120 >= 62 && frame%120 <= 71) Door.rotate(-9*DEGREE);
    if(frame%120 == 15 && num_car < 10) // a new vehicle comes in
    {
        int n=rand()%3;
        Figure* new_vehicle;
        switch(n)
        {
            case 0: new_vehicle = (Figure*)(new Car());
                    num_car++;
                    break;
            case 1: new_vehicle = (Figure*)(new UFO());
                    num_car++;
                    break;
            case 2: new_vehicle = (Figure*)(new Spacecraft());
                    num_car++;
                    break;
            default:
                    break;
        }
        if(num_car >= all)
        {
            std::cout<<"The parking lot is full!"<< std::endl;
        }
        else{
            vehicle.push_back(new_vehicle);

            // assign parking space
            index = rand()%all;
            while(isparked[index]==true)
                {index = (index+1)%all;}
            // determine motion and store
            std::queue<motion> new_motion = getmotion(index);
            vehicle_motion.push_back(new_motion);
            isparked[index] = true; // taken
            //std::cout<<vehicle.size()<<std::endl;
        }
    }

    for(int i = 0; i < (int)vehicle.size(); i++)
    {

        if(((Group*)vehicle[i])->getName() == "Spa"){
            vehicle[i]->zoom(1.1);
        }
        else if(((Group*)vehicle[i])->getName() == "UFO"){
            vehicle[i]->rotate(5*DEGREE);
        }
        if(vehicle_motion[i].empty())
            continue;
        else
        {
            motion current_motion = vehicle_motion[i].front();
            vehicle_motion[i].pop(); // delete
            vehicle[i]->rotate(current_motion.rotate_angle);
            vehicle[i]->move(current_motion.move_dir);
        }
    }


    #ifndef NO_GUI
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawParkingLot();
    Door.draw();
    // draw vehicles
    Tele->draw();
    for(int i=0;i<num_car;i++){
        vehicle[i]->draw();
        // std::cout<<"draw func called"<<std::endl;
    }
    glutSwapBuffers();
    glFlush();
    #endif
}



int main (int argc, char *argv[]) { 
if(argc){}
if(*argv){}
#ifndef NO_GUI
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Test");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw);
    glutTimerFunc(400, TimeStep, 25);
    glutMainLoop();
#endif
}

