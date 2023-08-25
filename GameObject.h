#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include "Point2D.h"

using namespace std;

class GameObject{
    protected:
        //variables
        Point2D location;
        int id_num;
        char display_code;
        char state;
    
    public:
        //constructors
        GameObject(char);
        GameObject(Point2D, int, char);
        virtual ~GameObject();

        //functions
        Point2D GetLocation();
        int GetId();
        char GetState();
        virtual void ShowStatus();
        virtual bool Update() = 0;
        virtual bool ShouldBeVisible() = 0;
        void DrawSelf(char*);
};

#endif