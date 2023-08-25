#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Building.h"
#include "View.h"
#include "WildPokemon.h"
#include <list>

using namespace std;

class Model{
    private:
        int time;
        list<GameObject*> object_ptrs;
        list<GameObject*> active_ptrs;
        list<Trainer*> trainer_ptrs;
        list<WildPokemon*> poke_ptrs;
        list<PokemonGym*> gym_ptrs;
        list<PokemonCenter*> center_ptrs;
    
    public:
        Model();
        ~Model();

        Trainer* GetTrainerPtr(int);
        PokemonCenter* GetPokemonCenterPtr(int);
        PokemonGym* GetPokemonGymPtr(int);
        bool Update();
        void Display(View&);
        void ShowStatus();
        int GetNumObj();
        int GetNumTrain();
        int GetNumCen();
        int GetNumGym();
        void MakeNew(char, int, double, double);
};

#endif