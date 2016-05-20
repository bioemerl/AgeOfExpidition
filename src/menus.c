#include <pebble.h>
#include "menus.h"
#include "types.h"
#include "menuhelper.h"
  
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
