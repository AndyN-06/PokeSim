#include <iostream>
#include "GameCommand.h"
#include "Model.h"
#include "Point2D.h"
#include "View.h"
#include "Input_Handling.h"

using namespace std;

void DoMoveCommand(Model& model, int trainer_id, Point2D p1){
    if (model.GetTrainerPtr(trainer_id)->GetId() == 0){
        throw Invalid_Input("Not a valid trainer id");
    } 
    cout << "Moving " << model.GetTrainerPtr(trainer_id)->GetName() << " to " << p1 << endl;
    model.GetTrainerPtr(trainer_id)->StartMoving(p1);
}

void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id){
    if (model.GetTrainerPtr(trainer_id)->GetId() == 0 || model.GetPokemonGymPtr(center_id)->GetId() == center_id){
        throw Invalid_Input("Not a valid id");
    } 
    cout << "Moving " << model.GetTrainerPtr(trainer_id)->GetName() << " to pokemon center" << center_id << endl;
    model.GetTrainerPtr(trainer_id)->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
}

void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id){
    if (model.GetTrainerPtr(trainer_id)->GetId() == 0 || model.GetPokemonGymPtr(gym_id)->GetId() == gym_id){
        throw Invalid_Input("Not a valid id");
    } 
    cout << "Moving " << model.GetTrainerPtr(trainer_id)->GetName() << " to gym" << gym_id << endl;
    model.GetTrainerPtr(trainer_id)->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
}

void DoStopCommand(Model& model, int trainer_id){
    if (model.GetTrainerPtr(trainer_id)->GetId() == 0){
        throw Invalid_Input("Not a valid trainer id");
    } 
    cout << "Stopping " << model.GetTrainerPtr(trainer_id)->GetName() << endl;
    model.GetTrainerPtr(trainer_id)->Stop();
}

void DoBattleCommand(Model& model, int trainer_id, unsigned int battles){
    if (model.GetTrainerPtr(trainer_id)->GetId() == 0){
        throw Invalid_Input("Not a valid trainer id");
    } 
    cout << model.GetTrainerPtr(trainer_id)->GetName() << " is battling" << endl;
    model.GetTrainerPtr(trainer_id)->StartBattling(battles);
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed){
    if (model.GetTrainerPtr(trainer_id)->GetId() == 0){
        throw Invalid_Input("Not a valid trainer id");
    } 
    cout << "Recovering " << model.GetTrainerPtr(trainer_id)->GetName() << "'s Pokemon's health" << endl;
    model.GetTrainerPtr(trainer_id)->StartRecoveringHealth(potions_needed);
}

void DoAdvanceCommand(Model& model, View& view){
    cout << "Advancing one tick." << endl;
    bool y = model.Update();
}

void DoRunCommand(Model& model, View& view){
    cout << "Advancing to next event." << endl;
    while(true){
        if(model.Update()){
            break;
        }
    }
}