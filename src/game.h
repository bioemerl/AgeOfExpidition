#pragma once
#include "types.h"

//random generators for the different objects in the game
Planet createplanet(int location);
Fleet createfleet(int location); //called by create planet
Station createstation(int location, int stationnumber);
Inventory createinventory(int location, int inventorynumber); //called by createstation
Ship createship(int location, int shipnumber); //called by createfleet, or by createstation

//function that regens world based on current planet, and moves from the current planet to a new planet
void warp(GameData* gamedata, int planetnumber);

int random(int seed, int min, int max);

void initializegame(GameData* gamedata);

//drawing and graphics functions
void drawmainmap(Layer *this_layer, GContext *ctx, GameData* gamedata);

//game process functions
void uppresshandler(GameData* gamedata);
void downpresshandler(GameData* gamedata);