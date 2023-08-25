#include <iostream>
#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "View.h"
#include "Model.h"
#include <stdlib.h>
#include "GameCommand.h"
#include "Input_Handling.h"
#include "WildPokemon.h"

using namespace std;

int main(){
    View v1;
    Model m1;
    char com;
    int a1, a2, a3;
    char a4;
    double a5, a6;
    while (true){
        com = '0';
        v1.Clear();
        m1.ShowStatus();
        m1.Display(v1);
        cout << "Enter command: ";
        cin >> com;
        try{
        switch (com){
            case 'm':
                cin >> a1 >> a2 >> a3;
                DoMoveCommand(m1, a1, Point2D(a2, a3));
                break;
            case 'c':
                cin >> a1 >> a2; 
                DoMoveToCenterCommand(m1, a1, a2);
                break;
            case 'g':
                cin >> a1 >> a2;
                DoMoveToGymCommand(m1, a1, a2);
                break;
            case 's':
                cin >> a1;
                DoStopCommand(m1, a1);
                break;
            case 'p':
                cin >> a1 >> a2;
                DoRecoverInCenterCommand(m1, a1, a2);
                break;
            case 'b':
                cin >> a1 >> a2;
                DoBattleCommand(m1, a1, a2);
                break;
            case 'a':
                DoAdvanceCommand(m1, v1);
                break;
            case 'r':
                DoRunCommand(m1, v1);
                break;
            case 'q':
                return 0;
            case 'n':
                cin >> a4 >> a1 >> a5 >> a6;
                m1.MakeNew(a4, a1, a5, a6);
        }
        }
        catch(Invalid_Input& except){
            cout << "Invalid Input - " << except.msg_ptr << endl;
            cout << "Enter valid command" << endl;
        }
    }
}