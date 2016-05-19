#include <pebble.h>
#include "game.h"

Planet createplanet(int location){
  Planet newplanet;
  newplanet.planetnumber = location;
  newplanet.screenposx = random(location, 15, 129);
  newplanet.screenposy = random(location, 15, 153);
  newplanet.numberofstations = random(location, 0, 5);
  for(int i = 0; i < newplanet.numberofstations; i++)
    newplanet.stations[i] = createstation(location, i);
  for(int i = 0; i < 3; i++) //create events based on time, not location, so events always vary
    newplanet.events[i] = createevent(time(NULL) - location, i);
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
  newstation.stationtype = random(location + stationnumber, 0, 3);
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

int loadsavedata(GameData* gamedata){
  return 0;
}

void initializegame(GameData* gamedata){ //load the saved data after running this function
  if(loadsavedata(gamedata) == 0){
    time_t newtime = time(NULL);
    int time = (int)newtime;
    gamedata->currentplanet = createplanet( random(time, 0, MAX_16_BIT) );
    gamedata->selectedplanet = 0;
    gamedata->player.inventory = createinventory(gamedata->currentplanet.planetnumber, 1);  //eventually have default values
    
    gamedata->numberofnewplanets = random(gamedata->currentplanet.planetnumber, 2, 3);
    for(int i = 0; i < gamedata->numberofnewplanets; i++)
      gamedata->newplanets[i] = createplanet( random(gamedata->currentplanet.planetnumber * i, 0, MAX_16_BIT) ); //new planets are based on current seed.
  }
}

void warp(GameData* gamedata, int planetnumber){
  if(gamedata->player.inventory.antimatter >= 5){
    gamedata->player.inventory.antimatter -= 5;
    gamedata->selectedplanet = 0;
    gamedata->currentplanet = gamedata->newplanets[planetnumber];
    gamedata->numberofnewplanets = random(gamedata->currentplanet.planetnumber, 2, 3);
    for(int i = 0; i < gamedata->numberofnewplanets; i++)
      gamedata->newplanets[i] = createplanet( random(gamedata->currentplanet.planetnumber * i, 0, MAX_16_BIT) ); //new planets are based on current seed
  }
  else{
    //some sort of menu that says "antimatter needed" should pop up here.
  }
}

//drawing and graphics functions
void drawmainmap(Layer *this_layer, GContext *ctx, GameData* gamedata){
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(0, 0, 150, 200), 0, 0);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_draw_circle(ctx, GPoint(gamedata->currentplanet.screenposx, gamedata->currentplanet.screenposy), 10);
  graphics_fill_circle(ctx, GPoint(gamedata->currentplanet.screenposx, gamedata->currentplanet.screenposy), 3);
  if(gamedata->selectedplanet == -1){
    graphics_draw_circle(ctx, GPoint(gamedata->currentplanet.screenposx, gamedata->currentplanet.screenposy), 8);
  }
  for(int i = 0; i < gamedata->numberofnewplanets; i++){
    if(gamedata->selectedplanet == i){
      graphics_draw_circle(ctx, GPoint(gamedata->newplanets[i].screenposx, gamedata->newplanets[i].screenposy), 8);
    }
    graphics_draw_circle(ctx, GPoint(gamedata->newplanets[i].screenposx, gamedata->newplanets[i].screenposy), 10);
    graphics_draw_line(ctx, GPoint(gamedata->currentplanet.screenposx, gamedata->currentplanet.screenposy), GPoint(gamedata->newplanets[i].screenposx, gamedata->newplanets[i].screenposy));
  }
}


//game process functions
void uppresshandler(GameData* gamedata){
  if(gamedata->selectedplanet >= 0)
    gamedata->selectedplanet--;
  else{
    gamedata->selectedplanet = gamedata->numberofnewplanets - 1;
  }
}

void downpresshandler(GameData* gamedata){
  if(gamedata->selectedplanet < gamedata->numberofnewplanets - 1)
    gamedata->selectedplanet++;
  else{
    gamedata->selectedplanet = -1;
  }
}

Event createevent(int timeseed, int number){
  Event newevent;
  newevent.minuitesleft = random(timeseed + (number * 23) + 1, 10, 5000);
  newevent.eventtype = random(timeseed + (number * 23) + 2, 0, 3);
  newevent.eventduration = random(timeseed + (number * 23) + 3, 0, 300);
  time_t x = time(NULL);
  return newevent;
}

