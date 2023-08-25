#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
using namespace std;

class Vector2D{
    public:
        //member vars
        double x;
        double y;
        //conostructors
        Vector2D();
        Vector2D(double, double);
};

//overloaded operators
Vector2D operator* (Vector2D, double);
Vector2D operator/ (Vector2D, double);
ostream &operator<< (ostream&, Vector2D);

#endif