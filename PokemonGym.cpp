#include <iostream>
#include "Building.h"
#include "PokemonGym.h"
#include "Point2D.h"

using namespace std;

PokemonGym :: PokemonGym(){
    display_code = 'G';
    state = NOT_DEFEATED;
    max_number_of_battles = 10;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = 1;
    pokedollar_cost_per_battle = 1.0;
    experience_per_battle = 2;
    cout << "PokemonGym default constructed" << endl;
}

PokemonGym :: PokemonGym(unsigned int max_battle, unsigned int health_loss, double pokedollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc){
    id_num = in_id;
    max_number_of_battles = max_battle;
    health_cost_per_battle = health_loss;
    experience_per_battle = exp_per_battle;
    pokedollar_cost_per_battle = pokedollar_cost;
    location = in_loc;
    display_code = 'G';
    state = NOT_DEFEATED;
    num_battle_remaining = max_number_of_battles;
    cout << "PokemonGym constructed" << endl;
}

PokemonGym :: ~PokemonGym(){
    cout << "PokemonGym destructed" << endl;
}

double PokemonGym :: GetPokeDollarCost(unsigned int battle_qty){
    return pokedollar_cost_per_battle * battle_qty;
}

unsigned int PokemonGym :: GetHealthCost(unsigned int battle_qty){
    return health_cost_per_battle * battle_qty;
}

unsigned int PokemonGym :: GetNumBattlesRemaining(){
    return num_battle_remaining;
}

bool PokemonGym :: IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health){
    if ((battle_qty * pokedollar_cost_per_battle <= budget) && (battle_qty * health_cost_per_battle <= health)){
        return true;
    } else {
        return false;
    }
}

unsigned int PokemonGym :: TrainPokemon(unsigned int battle_units){
    if (num_battle_remaining >= battle_units){
        num_battle_remaining -= battle_units;
        return battle_units * experience_per_battle;
    } else {
        unsigned int temp = num_battle_remaining;
        num_battle_remaining = 0;
        return temp * experience_per_battle;
    }
}

bool PokemonGym :: Update(){
    if (num_battle_remaining == 0){
        state = DEFEATED;
        display_code = 'g';
        cout << display_code << " " << id_num << " has been beaten" << endl;
        return true;
    } else {
        return false;
    }
}

bool PokemonGym :: passed(){
    if (num_battle_remaining == 0){
        return true;
    } else {
        return false;
    }
}

void PokemonGym :: ShowStatus(){
    cout << "PokemonGymStatus: ";
    Building :: ShowStatus();
    cout << "Max number of battles: " << max_number_of_battles << endl;
    cout << "Health cost per battle: " << health_cost_per_battle << endl;
    cout << "PokeDollar per battle: " << pokedollar_cost_per_battle << endl;
    cout << "Experience per battle: " << experience_per_battle << endl;
    if (num_battle_remaining == 1){
        cout << num_battle_remaining << " battle is remaining for this PokemonGym" << endl;
    } else {
        cout << num_battle_remaining << " battles are remaining for this PokemonGym" << endl;
    }
}

unsigned int PokemonGym :: GetExp(){
    return experience_per_battle;
}