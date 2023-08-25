#include <iostream>
#include "PokemonCenter.h"
#include "Building.h"
#include "Point2D.h"

using namespace std;

PokemonCenter :: PokemonCenter(){
    display_code = 'C';
    potion_capacity = 100;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter default constructed" << endl;
}

PokemonCenter :: PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc){
    id_num = in_id;
    location = in_loc;
    pokedollar_cost_per_potion = potion_cost;
    potion_capacity = potion_cap;
    display_code = 'C';
    num_potions_remaining = potion_capacity;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter constructed" << endl;
}

PokemonCenter :: ~PokemonCenter(){
    cout << "PokemonCenter destructed" << endl;
}

bool PokemonCenter :: HasPotions(){
    if (num_potions_remaining > 0){
        return true;
    } else {
        return false;
    }
}

unsigned int PokemonCenter :: GetNumPotionRemaining(){
    return num_potions_remaining;
}

bool PokemonCenter :: CanAffordPotion(unsigned int potion, double budget){
    if (potion * pokedollar_cost_per_potion <= budget){
        return true;
    } else {
        return false;
    }
}

double PokemonCenter :: GetPokeDollarCost(unsigned int potion){
    return pokedollar_cost_per_potion;
}

unsigned int PokemonCenter :: DistributePotion(unsigned int potion_needed){
    if (num_potions_remaining >= potion_needed){
        num_potions_remaining -= potion_needed;
        return potion_needed;
    } else {
        unsigned int temp = num_potions_remaining;
        num_potions_remaining = 0;
        return temp;
    }
}

bool PokemonCenter :: Update(){
    if (num_potions_remaining == 0){
        state = NO_POTIONS_AVAILABLE;
        display_code = 'c';
        cout << "PokemonCenter " << id_num << " has ran out of potions." << endl;
        return true;
    } else {
        return false;
    }
}

void PokemonCenter :: ShowStatus(){
    cout << "PokemonCenter Status: ";
    Building :: ShowStatus();
    cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << endl;
    if (num_potions_remaining == 1){
        cout << "has " << num_potions_remaining << " potion remaining." << endl;
    } else {
        cout << "has " << num_potions_remaining << " potions remaining." << endl;
    }
}

