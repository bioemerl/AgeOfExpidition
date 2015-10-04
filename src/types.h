#pragma once
  
extern const int MAX_16_BIT;
  
typedef struct{
  int metal;
  int food;
  int antimatter;
} Inventory;

typedef struct{
  Inventory inventory;
} Station;

typedef struct{
  int health;
  int type;
} Ship;

typedef struct{
  int numberofships;
  Ship ships[10];
} Fleet;

typedef struct{
  int planetnumber; //used as location seed
  int screenposx;
  int screenposy;
  int numberofstations;
  Station stations[5];
  Fleet fleet;
} Planet;

typedef struct{
  Inventory inventory;
  Fleet fleet;
} Player;

typedef struct{
  Player player;
  Planet currentplanet;
  int selectedplanet; //-1 is the current planet, 0 to x are the other planets.
  int numberofnewplanets; //a number between 1 and 3
  Planet newplanets[3];
} GameData;



//what to do
//start game in main menu, allow for restart game, load game, and resume game, also settings (on-off if app auto-starts in events)
//game begins with a seed for the random number gen, this seed creates a level that should be consistent
//enter game
//background is black with randomly generated white stars.  There are X number of stars highlighted.
//player is at the main star, can access menu
  
//can do ship ops
//see resource counts, and convert between resources.
//access information screen
//equip or de-equip ships with modules
//move crew around to different ships
  
//can do planet ops
//attack/interact with things in system
//access quest system
//purchase ships, modules for ships

//can access navigation ops
//select next planet and warp
//see info about one planet

//player can look through information that exists currently.  They can speak to NPC's and so on, shop, trade
//player can turn off app and game will schedule next event.  If event is scheduled then it will wake up the game during the event
//events will cause things to happen, trigger battles, make shops cheaper, allow purchase of ships.
  
//game resources
//ship:
//(string) ship type, which will determine max number of modules
//(strings) ship modules (reactor, command station, etc, just names that change how the ship does things)
//(object) ship captain
  
//planet:
//scheduled events
//stations
//armies
  
//Captain
//(strings/ints) modifier
//(string) affinity (alike captains work iffy, different captains can reduce or increase stats)

//Events:
//(string) eventtype
//(time) eventstart
//(time) eventend
//(int) eventstrength

//Stations:
//(string) stationtype
//(object) stationinventory
  
//Armies:
//(string) faction
//(object) fleet
  
//Inventory:
//(string/int) resource/amount
//repeat as necessary for all in game resources

//Fleet:
//(object) Ship
//repeat as necessary for max number of ships
  
//Ship:
//ship class (can be changed in menu by player)
//max # of modules
//(string) module
//repeat as needed for max possible # of modules.
  
//stored data:
//player fleet, captains, resources, location
//seed of current run
//schedule soonest event of current planet
//current ship armies/station, anything the player has the ability to effect directly.

