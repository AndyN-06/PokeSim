#include <iostream>
#include "GameObject.h"
#include "Point2D.h"

using namespace std;

//constructors
GameObject :: GameObject(char in_code){
    display_code = in_code;
    id_num = 1;
    state = 0;
    cout << "GameObject constructed" << endl;
}

GameObject :: GameObject(Point2D in_loc, int in_id, char in_code){
    display_code = in_code;
    id_num = in_id;
    location = in_loc;
    state = 0;
    cout << "GameObject constructed" << endl;
}
//destructor
GameObject :: ~GameObject(){
    cout << "GameObject destructed" << endl;
}

//functions
Point2D GameObject :: GetLocation(){
    return location;
}

int GameObject :: GetId(){
    return id_num;
}

void GameObject :: ShowStatus(){
    cout << display_code << " " << id_num << " at " << location << endl;
}

void GameObject :: DrawSelf(char* ptr){
    //put code at ptr location
    *ptr = display_code;
    //put id next to that location
    *(ptr + 1) = (id_num + '0');
}