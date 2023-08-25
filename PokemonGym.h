#ifndef POKEMONGYM_H
#define POKEMONGYM_H

#include <iostream>
#include "Building.h"
#include "Point2D.h"

using namespace std;

class PokemonGym: public Building{
    private:
        unsigned int num_battle_remaining;
        unsigned int max_number_of_battles;
        unsigned int health_cost_per_battle;
        double pokedollar_cost_per_battle;
        unsigned int experience_per_battle;
    
    public:
        PokemonGym();
        PokemonGym(unsigned int, unsigned int, double, unsigned int, int, Point2D);
        ~PokemonGym();

        double GetPokeDollarCost(unsigned int);
        unsigned int GetHealthCost(unsigned int);
        unsigned int GetNumBattlesRemaining();
        bool IsAbleToBattle(unsigned int, double, unsigned int);
        unsigned int TrainPokemon(unsigned int);
        bool Update();
        bool passed();
        void ShowStatus();
        unsigned int GetExp();
};

enum PokemonGymStates{
    NOT_DEFEATED = 0,
    DEFEATED = 1
};

#endif