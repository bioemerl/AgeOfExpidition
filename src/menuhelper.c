#include <pebble.h>
#include "menuhelper.h"

#define STATIONTRADER 0
#define STATIONCIVILIAN 1
#define STATIONMILITARY 2
#define STATIONWARP 3
#define EVENTSALE 0
#define EVENTWAR 1
#define EVENTRAID 2
#define EVENTPLAUGE 3

void layerzeroupdate(MenuData* menudata, GameData* gamedata){ //self planet menu
  char characterarray[MAX_LAYER_TEXT];
  snprintf(characterarray, sizeof(characterarray), //update the text of the layer
           "Planet: %i \nAntimatter: %i\nStations:\nInventory:\nFleets:\nEvents:\n--Exit--",  
           gamedata->currentplanet.planetnumber,
           gamedata->player.inventory.antimatter
          );
  setmenulayertext(0, menudata, characterarray);
  if(menudata->selectpressed == 1 && menudata->currentmenu[0] == 0 && menudata->buttonreleased == 1){
    menudata->currentmenu[0] = 0;
    menudata->menulayer = 2;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[0] == 1){
    menudata->currentmenu[0] = 0;
    menudata->menulayer = 3;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[0] == 2){
    menudata->currentmenu[0] = 0;
    menudata->menulayer = 4;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[0] == 3){
    menudata->currentmenu[0] = 0;
    menudata->menulayer = 5;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[0] == 4){
    menudata->currentmenu[0] = 0;
    menudata->menuisactive = 0;
  }
}

void layeroneupdate(MenuData* menudata, GameData* gamedata){ //other planet menu
  //--
  //Update the menu
  //--
    char characterarray[MAX_LAYER_TEXT];
  snprintf(characterarray, sizeof(characterarray), //update the text of the layer
           "%i\nWarp\nEvents:\n--Exit--",  
           gamedata->newplanets[gamedata->selectedplanet].planetnumber
          );
  setmenulayertext(1, menudata, characterarray);
  //--
  if(menudata->selectpressed == 1 && menudata->currentmenu[1] == 0 && menudata->buttonreleased == 1){
    warp(gamedata, gamedata->selectedplanet);
    menudata->currentmenu[1] = 0;
    menudata->menuisactive = 0;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[1] == 1){
    menudata->currentmenu[1] = 0;
    menudata->menulayer = 5;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[1] == 2){
    menudata->currentmenu[1] = 0;
    menudata->menuisactive = 0;
  }
}

void layertwoupdate(MenuData* menudata, GameData* gamedata){ //stations menu
  //---
  //update the text, size, and so on, of the layer, to show the correct # of stations
  //---
  menudata->layerdata[2].numberofitems = gamedata->currentplanet.numberofstations + 1;
  char stationnames[gamedata->currentplanet.numberofstations][10];
  for(int i = 0; i < gamedata->currentplanet.numberofstations; i++){ //create a list of names to populate the menu with
    if(gamedata->currentplanet.stations[i].stationtype == STATIONTRADER){
      snprintf(stationnames[i], sizeof(stationnames[i]), "Trader\n");
    }
    if(gamedata->currentplanet.stations[i].stationtype == STATIONCIVILIAN){
      snprintf(stationnames[i], sizeof(stationnames[i]), "Civilian\n");
    }
    if(gamedata->currentplanet.stations[i].stationtype == STATIONMILITARY){
      snprintf(stationnames[i], sizeof(stationnames[i]), "Military\n");
    }
    if(gamedata->currentplanet.stations[i].stationtype == STATIONWARP){
      snprintf(stationnames[i], sizeof(stationnames[i]), "Warp\n");
    }
  }
  char menutext[60] = {}; //the full menu text
  for(int i = 0; i < gamedata->currentplanet.numberofstations; i++){
    strcat(menutext, stationnames[i]);
  }
  strcat(menutext, "-Back-");
  setmenulayertext(2, menudata, menutext);
  
  //---
  //the actual button code
  //---
  if(menudata->selectpressed == 1 && menudata->currentmenu[2] == 0 && menudata->buttonreleased ==1){ //the first button needs release protections
    APP_LOG(APP_LOG_LEVEL_INFO, "GOTO STATION MENU");
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[2] >= 1 && menudata->currentmenu[2] < gamedata->currentplanet.numberofstations){ //should do same as first button
    APP_LOG(APP_LOG_LEVEL_INFO, "GOTO STATION MENU");
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[2] == gamedata->currentplanet.numberofstations){
    menudata->currentmenu[2] = 0;
    menudata->menulayer = 0;
  }
}

void layerthreeupdate(MenuData* menudata, GameData* gamedata){ //self inventory check menu
  //---
  //update the menu
  //---
  char menutext[100];
  snprintf(menutext, sizeof(menutext), "Metal: %i\nFood: %i\nAntimatter: %i\n-Back-", gamedata->player.inventory.metal, gamedata->player.inventory.food, gamedata->player.inventory.antimatter); //update this later with real resources
  setmenulayertext(3, menudata, menutext);
  //---
  //The button code
  //---
  if(menudata->selectpressed == 1 && menudata->currentmenu[3] == 0 && menudata->buttonreleased == 1){
    
  } 
  if(menudata->selectpressed == 1 && menudata->currentmenu[3] == 1){
    
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[3] == 3){
    menudata->currentmenu[3] = 0;
    menudata->menulayer = 0;
  } 
}

void layerfourupdate(MenuData* menudata, GameData* gamedata){  //fleets menu
  //first option "player"
  //second option "other"
  //third option "back"
  if(menudata->selectpressed == 1 && menudata->currentmenu[4] == 0 && menudata->buttonreleased == 1){
    
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[4] == 2){
    menudata->currentmenu[4] = 0;
    menudata->menulayer = 0;
  }
}

void layerfiveupdate(MenuData* menudata, GameData* gamedata){ //events menu
  //initialize the events
  Event events[3];
  if(gamedata->selectedplanet == -1){
    for(int i = 0; i < 3; i++)
      events[i] = gamedata->currentplanet.events[i];
  }
  else{
    for(int i = 0; i < 3; i++)
      events[i] = gamedata->newplanets[gamedata->selectedplanet].events[i];
  }
  
  //selectedplanet
  //-1 is current planet, 0 to 3 are the others
  char eventnames[3][10];
  for(int i = 0; i < 3; i++){
    if(events[i].eventtype == EVENTSALE)
      snprintf(eventnames[i], sizeof(eventnames[i]), "Sale\n");
    else if(events[i].eventtype == EVENTWAR)
      snprintf(eventnames[i], sizeof(eventnames[i]), "War\n");
    else if(events[i].eventtype == EVENTRAID)
      snprintf(eventnames[i], sizeof(eventnames[i]), "Raid\n");
    else if(events[i].eventtype == EVENTPLAUGE)
      snprintf(eventnames[i], sizeof(eventnames[i]), "Plague\n");
    else
      snprintf(eventnames[i], sizeof(eventnames[i]), "Err\n");
  }
  char menu[40] = {};
  for(int i = 0; i < 3; i++){
    strcat(menu, eventnames[i]);
  }
  strcat(menu, "-Back-");
  setmenulayertext(5, menudata, menu);
  
  if(menudata->selectpressed == 1 && menudata->currentmenu[5] == 0 && menudata->buttonreleased == 1){
    menudata->menulayer = 6;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[5] == 1){
    menudata->menulayer = 6;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[5] == 2){
    menudata->menulayer = 6;
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[5] == 3){
    //if selected planet is -1 return to current planet menu
    //else return to other planet menu
    if(gamedata->selectedplanet == -1){
      menudata->currentmenu[5] = 0;
      menudata->menulayer = 0;
    }
    else{
      menudata->currentmenu[5] = 0;
      menudata->menulayer = 1;
    }
  }
  
  
}

void layersixupdate(MenuData* menudata, GameData* gamedata){ //events info menu
  //show the name of event as title
  //time until event starts in hours/mins
  //time the event will last in hours/mins
  
  //"Title\nStarts:\nH: hours M: mins"
  //or
  //"TITLE\nEnds:\nH: hours M: mins"
  Event event;
  int eventnum = menudata->currentmenu[5];
  //get the event to display
  if(gamedata->selectedplanet == -1){
      event = gamedata->currentplanet.events[eventnum];
  }
  else{
      event = gamedata->newplanets[gamedata->selectedplanet].events[eventnum];
  }
  
  //organize the information
  char lines[10][3];
  snprintf(lines[0], sizeof(lines), "%i", event.minuitesleft);
  
  
}
