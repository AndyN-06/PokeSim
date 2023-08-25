#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include <string>
#include "Trainer.h"
#include <math.h>
#include <cstdlib>

using namespace std;

//default constructor
Trainer :: Trainer() : GameObject('S'){
    speed = 5;
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    cout << "Trainer default constructed." << endl;
}

//constructor
Trainer :: Trainer(char in_code) : GameObject(in_code){
    speed = 5;
    state = STOPPED;
    display_code = in_code;
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    numpok = 0;
    cout << "Trainer constructed." << endl;
}
//constructor
Trainer :: Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : GameObject(in_loc, in_id, in_code){
    speed = in_speed;
    name = in_name;
    is_at_center = false;
    is_in_gym = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    numpok = 0;
    cout << "Trainer constructed." << endl;
}
//destructor
Trainer :: ~Trainer(){
    cout << "Trainer destructed" << endl;
}
//start move
void Trainer :: StartMoving(Point2D dest){
    this->SetupDestination(dest);
    if (state == IN_GYM && GetDistanceBetween(destination, current_gym->GetLocation())){
        current_gym->RemoveOneTrainer();
    }
    if (state = AT_CENTER && GetDistanceBetween(destination, current_center->GetLocation())){
        current_center->RemoveOneTrainer();
    }
    //if in same location
    if (GetDistanceBetween(location, dest) == 0){
        cout << display_code << " " << id_num << ": I'm already there. See?" << endl;
    } else if (state == FAINTED) //if fainted
    {
        state = MOVING;
        cout << display_code << " " << id_num << ": My pokemon have fainted. I may move but you cannot see me." << endl;
    } else { //normal
        state = MOVING;
        cout << display_code << " " << id_num << ": On my way." << endl;
    }
}

void Trainer :: StartMovingToGym(PokemonGym* gym){
    if (state == IN_GYM && GetDistanceBetween(destination, current_gym->GetLocation())){
        current_gym->RemoveOneTrainer();
    }
    if (state = AT_CENTER && GetDistanceBetween(destination, current_center->GetLocation())){
        current_center->RemoveOneTrainer();
    }
    //if at gym
    if (GetDistanceBetween(gym->GetLocation(), location) == 0){
        cout << display_code << " " << id_num << ": I'm already there. See?" << endl;
    } else if (state == FAINTED)
    {
        this->SetupDestination(gym->GetLocation());
        cout << display_code << " " << id_num << ": My pokemon have fainted. I can;t go to the Jim" << endl;
    } else {
        this->SetupDestination(gym->GetLocation());
        state = MOVING_TO_GYM;
        current_gym = gym;
        cout << display_code << " " << id_num << ": On my way to ze gym." << endl;
    }
}

void Trainer :: StartMovingToCenter(PokemonCenter* center){
    if (state == IN_GYM && GetDistanceBetween(destination, current_gym->GetLocation())){
        current_gym->RemoveOneTrainer();
    }
    if (state = AT_CENTER && GetDistanceBetween(destination, current_center->GetLocation())){
        current_center->RemoveOneTrainer();
    }
    //if at center
    if (GetDistanceBetween(center->GetLocation(), location) == 0){
        cout << display_code << " " << id_num << ": I'm already there. See?" << endl;
    } else if (state == FAINTED)
    {
        this->SetupDestination(center->GetLocation());
        cout << display_code << " " << id_num << ": My pokemon have fainted. They need healing at the center. OMW!!!" << endl;
    } else {
        this->SetupDestination(center->GetLocation());
        state = MOVING_TO_CENTER;
        current_center = center;
        cout << display_code << " " << id_num << ": On my way." << endl;
    }
}

void Trainer :: StartBattling(unsigned int num_battles){
    //if not in gym
    if (state != IN_GYM){
        cout << display_code << " " << id_num << ": I can only battle in a PokemonGym!" << endl;
    } else if (this->HasFainted()){ //if fainted
        cout << display_code << " " << id_num << ": My Pokemon have fainted so no more battles for mee..." << endl;
    } else if (current_gym->IsAbleToBattle(num_battles, PokeDollars, health) == false){ //if not enough money or health
        cout << display_code << " " << id_num << ": Not enough money for battles" << endl;
    } else if (current_gym->GetNumBattlesRemaining() == 0)
    {
        cout << display_code << " " << id_num << ": Cannot battle! This PokemonGym has no more traineres left to battle!" << endl;
    } else {
        state = BATTLING_IN_GYM;
        battles_to_buy = current_gym->TrainPokemon(num_battles);
        battles_to_buy /= current_gym->GetExp();
        cout << display_code << " " << id_num << ": Started to battle at the PokemonGym " << current_gym->GetId() << " with " << battles_to_buy << " battles" << endl;
        health -= current_gym->GetHealthCost(battles_to_buy);
        PokeDollars -= current_gym->GetPokeDollarCost(battles_to_buy);
        experience += battles_to_buy * current_gym->GetExp();
    }   
}

void Trainer :: StartRecoveringHealth(unsigned int num_potions){
    if (state != AT_CENTER){
        cout << display_code << " " << id_num << ": I can only recover health at a Pokemon Center" << endl;
    } else if (current_center->GetNumPotionRemaining() < 1){
        cout << display_code << " " << id_num << ": Cannot recover! No potion remaining in this Pokemon Center" << endl;
    } else if (!(current_center->CanAffordPotion(num_potions, PokeDollars))){
        cout << display_code << " " << id_num << ": Not enough money to recover health." << endl;
    } else {
        state = RECOVERING_HEALTH;
        potions_to_buy = current_center->DistributePotion(num_potions);
        PokeDollars -= current_center->GetPokeDollarCost(potions_to_buy);
        health += 5 * potions_to_buy;
        cout << display_code << " " << id_num << ": Started recovering " << potions_to_buy << " potions at Pokemon Center " << current_center->GetId() << endl;
    }
}

void Trainer :: Stop(){
    state = STOPPED;
    cout << display_code << " " << id_num << ": Stopping.." << endl;
}

bool Trainer :: HasFainted(){
    if (health == 0){
        state = FAINTED;
        return true;
    } else {
        return false;
    }
}

bool Trainer :: ShouldBeVisible(){
    if (this->HasFainted()){
        return false;
    } else {
        return true;
    }
}

void Trainer :: ShowStatus(){
    cout << name << " status: " << endl;
    GameObject :: ShowStatus();
    switch(state){
        case STOPPED:
            cout << "stopped" << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
        case MOVING:
            cout << "moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << "." << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
        case MOVING_TO_GYM:
            cout << "heading to PokemonGym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
        case MOVING_TO_CENTER:
            cout << "heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
        case IN_GYM:
            cout << "inside PokemonGym " << current_gym->GetId() << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
        case AT_CENTER:
            cout << "inside Pokemon Center " << current_center->GetId() << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
        case BATTLING_IN_GYM:
            cout << "battling in PokemonGym " << current_gym->GetId() << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
        case RECOVERING_HEALTH:
            cout << "recovering health in Pokemon Center " << current_center->GetId() << endl;
            cout << "Health: " << health << endl << "PokeDollars: " << PokeDollars << endl << "Experience: " << experience << endl;
            break;
    }
}

bool Trainer :: UpdateLocation(){
    if (fabs((destination - location).x) <= fabs(delta.x) && fabs((destination - location).y) <= fabs(delta.y)){
        location = destination;
        cout << "arrived" << endl;
        return true;
    } else {
        location = location + delta;
        cout << "moved" << endl;
        return false;
    }
}

bool Trainer :: Update(){
    if (this->HasFainted()){
        this->Stop();
        if (state != FAINTED){
            state = FAINTED;
            cout << name << " is out of health and can't move" << endl;
            return true;
        }
        return false;
    }
    switch(state){
        case STOPPED:
            return false;
        case MOVING:
            health -= 1;
            PokeDollars += GetRandomAmountOfPokeDollars();
            if (this->UpdateLocation()){
                state = STOPPED;
                return true;
            } else {
                return false;
            }
        case MOVING_TO_GYM:
            health -= 1;
            PokeDollars += GetRandomAmountOfPokeDollars();
            if (this->UpdateLocation()){
                state = IN_GYM;
                current_gym->AddOneTrainer();
                return true;
            } else{
                return false;
            }
        case MOVING_TO_CENTER:
            health -= 1;
            PokeDollars += GetRandomAmountOfPokeDollars();
            if (this->UpdateLocation()){
                state = AT_CENTER;
                current_center->AddOneTrainer();
                return true;
            } else{
                return false;
            }
        case IN_GYM:
            return false;
        case AT_CENTER:
            return false;
        case BATTLING_IN_GYM:
            cout << "** " << name << " completed " << battles_to_buy << " battle(s)! **" << endl;
            cout << "** " << name << " gained " << current_gym->TrainPokemon(battles_to_buy) << " experience! **" << endl;
            state = IN_GYM;
            return true;
        case RECOVERING_HEALTH:
            cout << "** " << name << " recovered " << 5 * potions_to_buy << " health! **" << endl;
            cout << "** " << name << " bought " << potions_to_buy << " potion(s)! **" << endl;
            state = AT_CENTER;
            return true;
        default:
            return false;
    }
}

void Trainer :: SetupDestination(Point2D dest){
    destination = dest;
    delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
}

double GetRandomAmountOfPokeDollars(){
    srand(time(NULL));
    double p = (double)rand()/RAND_MAX;
    return p * (2.0-0.0);
}

string Trainer :: GetName(){
    return name;
}

int Trainer :: GetHealth(){
    return health;
}

void Trainer :: GetPoke(){
    numpok += 1;
    this->HasPoke = true;
}

void Trainer :: addHealth(unsigned int h){
    health += h;
}