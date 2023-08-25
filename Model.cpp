#include <iostream>
#include <stdlib.h>
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Building.h"
#include "View.h"
#include "Model.h"
#include "WildPokemon.h"
#include "Input_Handling.h"
#include <string>

using namespace std;

Model :: Model(){
    time = 0;
    PokemonCenter* C1 = new PokemonCenter(1,1,100,Point2D(1,20));
    object_ptrs.push_back(C1);
    center_ptrs.push_back(C1);
    active_ptrs.push_back(C1);
    PokemonCenter* C2 = new PokemonCenter(2,2,200,Point2D(10,20));
    object_ptrs.push_back(C2);
    center_ptrs.push_back(C2);
    active_ptrs.push_back(C2);
    Trainer* T1 = new Trainer("George Lopez",1,'T',2,Point2D(5,1));
    object_ptrs.push_back(T1);
    trainer_ptrs.push_back(T1);
    active_ptrs.push_back(T1);
    Trainer* T2 = new Trainer("Bob The Builder",2,'T',1,Point2D(10,1));
    object_ptrs.push_back(T2);
    trainer_ptrs.push_back(T2);
    active_ptrs.push_back(T2);
    PokemonGym* G1 = new PokemonGym(10,1,2,3,1,Point2D(0,0));
    object_ptrs.push_back(G1);
    gym_ptrs.push_back(G1);
    active_ptrs.push_back(G1);
    PokemonGym* G2 = new PokemonGym(20,5,7.5,4,2,Point2D(5,5));
    object_ptrs.push_back(G2);
    gym_ptrs.push_back(G2);
    active_ptrs.push_back(G2);
    WildPokemon* W1 = new WildPokemon(Point2D(10,12), 1);
    object_ptrs.push_back(W1);
    poke_ptrs.push_back(W1);
    active_ptrs.push_back(W1);
    WildPokemon* W2 = new WildPokemon(Point2D(15,5), 2);
    object_ptrs.push_back(W2);
    poke_ptrs.push_back(W2);
    active_ptrs.push_back(W2);
    cout << "Model default constructed" << endl;
}

Model :: ~Model(){
    for(list <GameObject*> :: iterator it = object_ptrs.begin(); it != object_ptrs.end(); it++){
        delete *it;
    }
    cout << "Model destructed" << endl;
}

Trainer* Model :: GetTrainerPtr(int id){
    for (list <Trainer*> :: iterator it = trainer_ptrs.begin(); it != trainer_ptrs.end(); it++){
        if ((*it)->GetId() == id){
            return *it;
        }
    }

    return nullptr;
}

PokemonCenter* Model :: GetPokemonCenterPtr(int id){
    for(list <PokemonCenter*> :: iterator it = center_ptrs.begin(); it != center_ptrs.end(); it++){
        if((*it)->GetId() == id){
            return *it;
        }
    }
    return nullptr;
}

PokemonGym* Model :: GetPokemonGymPtr(int id){
    for(list <PokemonGym*> :: iterator iter1 = gym_ptrs.begin(); iter1 != gym_ptrs.end(); iter1++){
        if((*iter1)->GetId() == id){
            return *iter1; 
        }
    }
    return nullptr;
}

bool Model :: Update(){
    time++;
    int up = 0;
    int def = 0;
    int hel = 0;
    list <GameObject*> :: iterator itG;
    for(itG = active_ptrs.begin(); itG != active_ptrs.end(); itG++){
        if((*itG)->Update()){
            up++;
        }
    }
    for(list <GameObject*> :: iterator itG = active_ptrs.begin(); itG != active_ptrs.end(); itG++){
        if(!(*itG)->ShouldBeVisible()){
            active_ptrs.erase(itG);
            cout << "Dead object removed" << endl;
            break;
        }
    }
    list <PokemonGym*> :: iterator itP;
    for(itP = gym_ptrs.begin(); itP != gym_ptrs.end(); itP++){
        if((*itP)->GetNumBattlesRemaining() <= 0){
            def++;
        }
    }
    if (def == gym_ptrs.size()){
        cout << "GAME OVER: You win! All battles done!" << endl;
        exit(0);
    }
    list<Trainer*> :: iterator itT;
    for(itT = trainer_ptrs.begin(); itT != trainer_ptrs.end(); itT++){
        if((*itT)->HasFainted()){
            hel++;
        }
    }
    if(hel == trainer_ptrs.size()){
        cout << "GAME OVER: You lose! All of your Trainers have lost!" << endl;
        exit(0);
    }
    if(up > 0){
        return true;
    }
    return false;
}

void Model :: Display(View& view){
    for ( list<GameObject*> :: iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++){
        view.Plot(*it);
    }
    view.Draw();
}

void Model :: ShowStatus(){
    cout << "time: " << time << endl;
    for(list<GameObject*> :: iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++ ){
        (*it)->ShowStatus();
    }
}

void Model :: MakeNew(char type, int in_id, double x, double y){
    switch(type){
        case 'c':{
            for(list <PokemonCenter*> :: iterator itP = center_ptrs.begin(); itP != center_ptrs.end(); itP++){
                if(in_id == (*itP)->GetId()){
                    throw Invalid_Input("Center ID exists already");
                }  
            }
            PokemonCenter* C = new PokemonCenter(in_id, 1, 1, Point2D(x,y));
            cout << "Pokemon Center " << in_id << " created" << endl;
            object_ptrs.push_back(C);
            active_ptrs.push_back(C);
            center_ptrs.push_back(C);
            break;
        }
        case 'g':{
            for(list <PokemonGym*> :: iterator itG = gym_ptrs.begin(); itG != gym_ptrs.end(); itG++){
                if(in_id == (*itG)->GetId())
                throw Invalid_Input("Gym ID exists already");
            }
            PokemonGym* G = new PokemonGym(1, 1, 1, 1, in_id, Point2D(x,y));
            cout << "Pokemon Gym " << in_id << " created" << endl;
            object_ptrs.push_back(G);
            active_ptrs.push_back(G);
            gym_ptrs.push_back(G);
            break;
        }
        case 't':{
            for(list <Trainer*> :: iterator itT = trainer_ptrs.begin(); itT != trainer_ptrs.end(); itT++){
                if(in_id == (*itT)->GetId())
                throw Invalid_Input("Trainer ID exists already");
            }
            Trainer* T = new Trainer("Brosky", in_id ,'T', 1 , Point2D(x,y));
            cout << "Trainer " << in_id << " created" << endl;
            object_ptrs.push_back(T);
            active_ptrs.push_back(T);
            trainer_ptrs.push_back(T);
            break;
        }
        default:
            throw Invalid_Input("Invalid arguments");
    }
}