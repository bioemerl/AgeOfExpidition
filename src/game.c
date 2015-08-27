#include <pebble.h>
#include "game.h"

Planet createplanet(int location){
  Planet newplanet;
  newplanet.planetnumber = location;
  newplanet.screenposx = random(location, 0, 400);
  newplanet.screenposy = random(location, 0, 300);
  newplanet.numberofstations = random(location, 0, 5);
  for(int i = 0; i < newplanet.numberofstations; i++)
    newplanet.stations[i] = createstation(location, i);
  newplanet.fleet = createfleet(location);
  return newplanet;
}

Fleet createfleet(int location){
  Fleet newfleet;
  newfleet.numberofships = random(location, 1, 5);
  for(int i = 0; i < newfleet.numberofships; i++)
    newfleet.ships[i] = createship(location, i);
  return newfleet;
}

Station createstation(int location, int stationnumber){
  Station newstation;
  newstation.inventory = createinventory(location, stationnumber);
  return newstation;
}

Inventory createinventory(int location, int inventorynumber){
  Inventory newinventory; 
  //the random functions must vary as they would return the same number for each
  newinventory.metal = random((location + inventorynumber)*inventorynumber, 0, 100);
  newinventory.food = random((location - inventorynumber)*inventorynumber, 1, 99);
  newinventory.antimatter = random((location - inventorynumber), 0, 101);
  return newinventory;
}

Ship createship(int location, int shipnumber){
  Ship newship;
  newship.health = random(location + shipnumber, 50, 100);
  newship.type = random(location + shipnumber, 1, 2);
  return newship;
} 

int random(int seed, int min, int max){ 
  if(max == 0)
    return 0;
  static long baseseed = 100;
  baseseed = (((seed * 214013L + 2531011L) >> 16) & 32767);
  seed = ((baseseed % (max+1)));
  if(seed < min)
    seed = seed + min;
  return seed;
}

void initializegame(GameData* gamedata){ //load the saved data after running this function
  int time = 1008;
  gamedata->currentplanet = createplanet( random(time, 0, MAX_16_BIT) );
  
  gamedata->player.inventory = createinventory(gamedata->currentplanet.planetnumber, 1);  //eventually have default values
  
  gamedata->numberofnewplanets = random(gamedata->currentplanet.planetnumber, 2, 3);
  for(int i = 0; i < gamedata->numberofnewplanets; i++)
    gamedata->newplanets[i] = createplanet( random(gamedata->currentplanet.planetnumber * i, 0, MAX_16_BIT) ); //new planets are based on current seed.
}


void warp(GameData* gamedata, int planetnumber){
  gamedata->currentplanet = gamedata->newplanets[planetnumber];
  gamedata->numberofnewplanets = random(gamedata->currentplanet.planetnumber, 2, 3);
  for(int i = 0; i < gamedata->numberofnewplanets; i++)
    gamedata->newplanets[i] = createplanet( random(gamedata->currentplanet.planetnumber * i, 0, MAX_16_BIT) ); //new planets are based on current seed.
}

