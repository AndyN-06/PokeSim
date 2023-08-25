#include <iostream>
#include "Building.h"
#include "GameObject.h"
#include "Point2D.h"

Building :: Building(): GameObject('B'){
    trainer_count = 0;
    cout << "Building default constructed" << endl;
}

Building :: Building(char in_code, int in_id, Point2D in_loc): GameObject(in_code){
    id_num = in_id;
    display_code = in_code;
    location = in_loc;
    trainer_count = 0;
    state = 0;
    cout << "Building constructed" << endl;
}

void Building :: AddOneTrainer(){
    trainer_count++;
}

void Building :: RemoveOneTrainer(){
    trainer_count--;
}

void Building :: ShowStatus(){
    cout << display_code << " " << id_num << " located at " << location << endl;
    if (trainer_count == 1){
        cout << trainer_count << " trainer is in this building" << endl;
    } else {
        cout << trainer_count << " trainers are in this building" << endl;
    }
}

bool Building :: ShouldBeVisible(){
    return true;
}