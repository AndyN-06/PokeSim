#include <iostream>
#include "WildPokemon.h"
#include "GameObject.h"
#include <string.h>
#include "Trainer.h"
#include "Point2D.h"

using namespace std;

WildPokemon :: WildPokemon(Point2D in_loc, int id) : GameObject(in_loc, id, 'W'){
    attack = 5;
    health = 2;
    variant = false;
    in_combat = false;
}

WildPokemon :: WildPokemon(string n, double at, double h, bool var, int id, Point2D in_loc) : GameObject(in_loc, id, 'W'){
    attack = at;
    health = h;
    variant = var;
    state = IN_ENVIRONMENT;
}

void WildPokemon :: follow(Trainer* t){
    current_trainer = t;
    state = IN_TRAINER;
    //change information about trainer here
    t->GetPoke();
    t->addHealth(this->get_health());
}

bool WildPokemon :: get_variant(){
    return variant;
}

double WildPokemon :: get_attack(){
    return attack;
}

double WildPokemon :: get_health(){
    return health;
}

bool WildPokemon :: get_in_combat(){
    return in_combat;
}

bool WildPokemon :: Update(){
    if (!(this->IsAlive())){
        return true; // maybe change here
    } else if (state == IN_ENVIRONMENT){
        return false;
    } else {
        this->SetLoco(current_trainer);
        return false;
    }
}

void WildPokemon :: ShowStatus(){
    cout << "Wild Pokemon status: ";
    GameObject :: ShowStatus();
    //add more info here
}

bool WildPokemon :: IsAlive(){
    if (health > 0){
        return true;
    } else {
        state = DEAD;
        return false;
    }
}

bool WildPokemon :: ShouldBeVisible(){
    if(state == DEAD || state == IN_TRAINER){
        return false;
    } else {
        return true;
    }
}

void WildPokemon :: SetLoco(Trainer* t){
    this->location = current_trainer->GetLocation();
}