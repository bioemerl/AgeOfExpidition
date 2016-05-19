#include <pebble.h>
#include "menus.h"
#include "types.h"
#include "game.h"
#define STATIONTRADER 0
#define STATIONCIVILIAN 1
#define STATIONMILITARY 2
#define STATIONWARP 3
#define EVENTSALE 0
#define EVENTWAR 1
#define EVENTRAID 2
#define EVENTPLAUGE 3
  
  
  
//prototypes
void layerzeroupdate(MenuData* menudata, GameData* gamedata);
void layeroneupdate(MenuData* menudata, GameData* gamedata);
void layertwoupdate(MenuData* menudata, GameData* gamedata);
void layerthreeupdate(MenuData* menudata, GameData* gamedata);
void layerfourupdate(MenuData* menudata, GameData* gamedata);
void layerfiveupdate(MenuData* menudata, GameData* gamedata);

void initializemenus(MenuData* menudata){
  menudata->menulayer = 0;
  menudata->buttonreleased = 1;
  for(int i = 0; i < NUMBER_OF_LAYERS; i++) //initialize the current cursor to 0 for all layers
    menudata->currentmenu[i] = 0;
}

void initializemenulayer(int menulayer, MenuData* menudata, int xpos, int ypos, int width, int numberofitems, int numberoftitles, int issquarelayer, char layertext[MAX_LAYER_TEXT]){
  snprintf(menudata->layerdata[menulayer].layertext, sizeof(menudata->layerdata[menulayer].layertext), layertext);
  menudata->layerdata[menulayer].xpos = xpos;
  menudata->layerdata[menulayer].ypos = ypos;
  menudata->layerdata[menulayer].boxwidth = width;
  menudata->layerdata[menulayer].numberofitems = numberofitems;
  menudata->layerdata[menulayer].numberoftitles = numberoftitles;
  menudata->layerdata[menulayer].issquarelayer = issquarelayer;
}

void setmenulayertext(int menulayer, MenuData* menudata, char layertext[MAX_LAYER_TEXT]){
  snprintf(menudata->layerdata[menulayer].layertext, sizeof(menudata->layerdata[menulayer].layertext), layertext);
}

void update_menu_layer(MenuData* menudata, GameData* gamedata){ //run on click
  switch(menudata->menulayer){
    case 0:
      layerzeroupdate(menudata, gamedata);
      break;
    case 1:
      layeroneupdate(menudata, gamedata);
      break;
    case 2:
      layertwoupdate(menudata, gamedata);
      break;
    case 3:
      layerthreeupdate(menudata, gamedata);
      break;
    case 4:
      layerfourupdate(menudata, gamedata);
      break;
    case 5:
      layerfiveupdate(menudata, gamedata);
      break;
  }
}

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
    
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[5] == 1){
    
  }
  if(menudata->selectpressed == 1 && menudata->currentmenu[5] == 2){
    
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
  
  
  
}

void updatemenuselection(MenuData* menudata){
  APP_LOG(APP_LOG_LEVEL_INFO, "box %i, buttonreleased is %i", menudata->currentmenu[menudata->menulayer], menudata->buttonreleased);
  if(menudata->downpressed == 1 && menudata->uppressed == 0 && menudata->buttonreleased == 1){
      APP_LOG(APP_LOG_LEVEL_INFO, "run");
      menudata->currentmenu[menudata->menulayer] = ((menudata->currentmenu[menudata->menulayer] + 1) % (menudata->layerdata[menudata->menulayer].numberofitems));
  }
  //UP PRESSED
  if(menudata->downpressed == 0 && menudata->uppressed == 1 && menudata->buttonreleased == 1){
    menudata->currentmenu[menudata->menulayer] = ((menudata->currentmenu[menudata->menulayer] - 1));
    if(menudata->currentmenu[menudata->menulayer] < 0)
      menudata->currentmenu[menudata->menulayer] = menudata->layerdata[menudata->menulayer].numberofitems - 1;
  }
  menudata->buttonreleased = 0;
}


void select_menu_layers(Layer *this_layer, GContext *ctx, MenuData* menudata, GameData* gamedata){
  update_menu_layer(menudata, gamedata); //first update the layers, to ensure they draw with proper info.
  if(menudata->menuisactive == 1){
    //always draw the base menu
    if(menudata->menulayer == 0)
      draw_menu_layer(this_layer, ctx, menudata, 0);
    if(menudata->menulayer == 1)
      draw_menu_layer(this_layer, ctx, menudata, 1);
    if(menudata->menulayer == 2)
      draw_menu_layer(this_layer, ctx, menudata, 2);
    if(menudata->menulayer == 3)
      draw_menu_layer(this_layer, ctx, menudata, 3);
    if(menudata->menulayer == 4)
      draw_menu_layer(this_layer, ctx, menudata, 4);
    if(menudata->menulayer == 5)
      draw_menu_layer(this_layer, ctx, menudata, 5);

  }
}


void draw_menu_layer(Layer *this_layer, GContext *ctx, MenuData* menudata, int menulayernumber){
  layer_mark_dirty(this_layer);
  drawmenuandbox(this_layer, ctx, menudata->currentmenu[menulayernumber], menudata->layerdata[menulayernumber].issquarelayer, menulayernumber, menudata->layerdata[menulayernumber].numberofitems, menudata->layerdata[menulayernumber].xpos, menudata->layerdata[0].ypos, menudata->layerdata[menulayernumber].boxwidth, menudata->layerdata[menulayernumber].numberoftitles, menudata->layerdata[menulayernumber].layertext);
  switch(menulayernumber){
    case 0:
      break;
    case 1: //special things that need to be drawn in a layer will go here
      break;
    case 2: //special things that need to be drawn in a layer will go here
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
  }
}

//the reason for passing so many variables despite also passing the container is lazyness and legacy code.
void drawmenuandbox(Layer *this_layer, GContext *ctx, int currentposition, int issquarelayer, int layernumber, int itemscount, int x, int y, int xdiff, int offset, char text[MAX_LAYER_TEXT]){
  graphics_context_set_fill_color(ctx, GColorBlack);
  itemscount = itemscount + offset;
  GRect layertext;
  GRect highlightbox;
  GRect backgroundbox;
  if(issquarelayer == 0){
    highlightbox = (GRect(x, 2 + y+(currentposition + offset)*15 - currentposition, xdiff, 15 )); //highlighting box
    layertext = GRect(x + 2, y, xdiff - 2, 4 + y+(itemscount)*15 - itemscount);
    backgroundbox = GRect(x-1, y, xdiff + 2, 4 + y+(itemscount)*15 - itemscount);
  }
  else if(issquarelayer == 1){ //if you want to draw a number of boxes
    if((currentposition%(itemscount - offset - 1)) == 0 && currentposition != 0){ //draw the last box as large, if number of items is odd
      highlightbox = (GRect(x, 2 + y+((currentposition + offset)/ 2)*15 - (currentposition/2), xdiff, 15 )); //highlighting box
    }
    else if(((currentposition + 1)%2) == 0) //draw box around the second colm of entries
      highlightbox = (GRect(x  + (xdiff/2), 2 + y+((currentposition + offset) / 2)*15 - (currentposition/2), (xdiff / 2), 15 ));
    else if(((currentposition + 1)%2 != 0)) //draw box around the first colm of entires
      highlightbox = (GRect(x, 2 + y+((currentposition + offset) / 2)*15 - (currentposition/2), (xdiff / 2), 15 ));
    backgroundbox = GRect(x - 1, y, xdiff+2, 4 + y+((itemscount/2 + 1))*15 - (itemscount/2));
    layertext = GRect(x + 2, y, xdiff - 2, 4 + y+((itemscount/2 + 1))*15 - (itemscount/2));
  }
  graphics_fill_rect(ctx, backgroundbox, 0, GCornerNone); //background box
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_draw_text(ctx, text, fonts_get_system_font(FONT_KEY_GOTHIC_14), layertext, GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  graphics_draw_rect(ctx, highlightbox); //the box around selected area
}

void menudownpressproc(MenuData* menudata){
  menudata->downpressed = 1;
  if(menudata->menuisactive == 1)
    updatemenuselection(menudata);
}
void menuuppressproc(MenuData* menudata){
  menudata->uppressed = 1;
  if(menudata->menuisactive == 1)
    updatemenuselection(menudata);
}
void menuselectpressproc(MenuData* menudata, GameData* gamedata){
  menudata->selectpressed = 1;
  if(menudata->menuisactive == 1)
    update_menu_layer(menudata, gamedata);
  menudata->selectpressed = 0;
}
void menubuttonreleaseproc(MenuData* menudata){
  menudata->uppressed = 0;
  menudata->downpressed = 0;
  menudata->selectpressed = 0;
  menudata->buttonreleased = 1;
}
