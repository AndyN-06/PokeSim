#include <iostream>
#include "Point2D.h"
#include <math.h>
using namespace std;

class Vector2D;

//default constructor sets to origin
Point2D :: Point2D(){
    x = 0.0;
    y - 0.0;
}
//constructor
Point2D :: Point2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}
//function
double GetDistanceBetween(Point2D p1, Point2D p2){
    //use distance formula
    double x2 = pow(p2.x - p1.x, 2);
    double y2 = pow(p2.y - p1.y, 2);
    return sqrt(x2 + y2);
}
//overloaded operators
ostream &operator<< (ostream& out, Point2D p1){
    out << "(" << p1.x << ", " << p1.y << ")";
    return out;
}

Point2D operator+ (Point2D p1, Vector2D v1){
    return Point2D(p1.x + v1.x, p1.y + v1.y);
}

Vector2D operator- (Point2D p1, Point2D p2){
    return Vector2D(p1.x - p2.x, p1.y - p2.y);
}