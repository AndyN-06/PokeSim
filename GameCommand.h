#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

#include <iostream>
#include "Model.h"
#include "Point2D.h"
#include "View.h"

using namespace std;

void DoMoveCommand(Model&, int, Point2D);
void DoMoveToCenterCommand(Model&, int, int);
void DoMoveToGymCommand(Model&, int, int);
void DoStopCommand(Model&, int);
void DoBattleCommand(Model&, int, unsigned int);
void DoRecoverInCenterCommand(Model&, int, unsigned int);
void DoAdvanceCommand(Model&, View&);
void DoRunCommand(Model&, View&);

#endif