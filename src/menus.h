#pragma once
#include "types.h"
  
#define NUMBER_OF_LAYERS 1;

//games can run one of two ways
//turn based-update per press of the button
//active, with a loop that doesn't ever end
//turn based will run procedures, then run the update right after
//update based will run procedures, then run the update inside the loop that updates constantly


typedef struct{
  char layertext[100];
  int xpos, ypos, boxwidth;
  int numberofitems;
  int numberoftitles;
  int issquarelayer;
} LayerInfo;

typedef struct{
  int8_t menuisactive;
  int8_t currentmenu[1]; //THE TOTAL NUMBER OF LAYERS IS ARRAY SIZE
  LayerInfo layerdata[1]; //CANT USE THE DEFINE FOR SOME ODD REASON, COMPILER WILL GIVE ERROR
  int8_t menulayer;
  int8_t uppressed;
  int8_t downpressed;
  int8_t selectpressed;
  int8_t buttonreleased;
} MenuData;

//TODO: make an initializemenus fucntion that sets things to zero;

//how this works:
//0: ensure menudata.menuisactive is equal to 1 rather than a 0.  If it is a 0, nothing will draw or update.
//1: ensure the procedure fuctions are run in the functions that are triggered when the buttons are pressed
//2: ensure updatemenuselection is run after/when a button is pressed
//3: ensure that every time the screen is cleared, select_menu_layers is called
//4: ensure that every time a button is pressed, update_menu_layer is called

//how will I make a menu layer?
//1: change numberofitems constant to +1
//2: define somewhere in your code a function that initializes all the variables inside of the LayerInfo
//   structure inside of the MenuData structure
//3: define inside of the update_menu_layer somewhere that sets the menudata.menulayer value to the number your layer is
//   that number is the "number of menu layers -1"
//4: define inside of update_menu_layer all the code needed to update the menu items of your new layer

//run as block 1
//block 1.1
void update_menu_layer(MenuData* menudata, GameData* gamedata); //runs all the code for what buttonpresses do in the menus.
//block 1.2
void select_menu_layers(Layer *this_layer, GContext *ctx, MenuData* menudata, int layernumber); //calls draw_menu_layers where needed for menus that have many stacked layers that all need to show up
void draw_menu_layer(Layer *this_layer, GContext *ctx, MenuData* menudata, int menulayernumber); //draws the menu layer with paramaters given  draws layers using drawmenuandbox
void drawmenuandbox(Layer *this_layer, GContext *ctx, int currentposition, int issquarelayer, int layernumber, int itemscount, int x, int y, int xdiff, int offset, char text[100]); //actually draws menus


//run  as block 2
void menudownpressproc(MenuData* menudata); //run on the main trigger for down button press
void menuuppressproc(MenuData* menudata);  //run on the main trigger for up button press
void menuselectpressproc(MenuData* menudata, GameData* gamedata);  //run on the main trigger for select button press
void menubuttonreleaseproc(MenuData* menudata);  //run on the main trigger for any button release
//updatemenuselection will be run only when the procs are run above.
//void updatemenuselection(GameData* gamedata, int menulayer, int layeritemscount); //updates the selected item on the active layer




