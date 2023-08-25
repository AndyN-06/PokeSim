#ifndef POINT2D_H
#define POINT2D_H

#include<iostream>
#include "Vector2D.h"
using namespace std;

class Point2D{
    public:
        //member variables
        double x;
        double y;

        //constructors
        Point2D();
        Point2D(double, double);
};

//nonmember function
double GetDistanceBetween(Point2D, Point2D);

//overloading operators
ostream &operator<< (ostream&, Point2D);
Point2D operator+ (Point2D, Vector2D);
Vector2D operator- (Point2D, Point2D);

#endif