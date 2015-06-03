#include <pebble.h>
#include "menus.h"
 
//prototypes
void layeroneupdate(MenuData* menudata, GameData* gamedata);

void update_menu_layer(MenuData* menudata, GameData* gamedata){
  switch(menudata->menulayer){
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
  }
}

void layeroneupdate(MenuData* menudata, GameData* gamedata){
  if(menudata->selectpressed == 1 && menudata->currentmenu[0] == 0){
    
  }
}

void updatemenuselection(MenuData* menudata){
  if(menudata->downpressed == 1 && menudata->uppressed == 0 && menudata->buttonreleased == 1){
      menudata->currentmenu[menudata->menulayer] = ((menudata->currentmenu[menudata->menulayer] + 1) % menudata->layerdata[menudata->menulayer].numberofitems);
      menudata->buttonreleased = 0;
  }
  //UP PRESSED
  if(menudata->downpressed == 0 && menudata->uppressed == 1 && menudata->buttonreleased == 1){
    menudata->currentmenu[menudata->menulayer] = ((menudata->currentmenu[menudata->menulayer] - 1) % menudata->layerdata[menudata->menulayer].numberofitems);
    menudata->buttonreleased = 0;
    if(menudata->currentmenu[menudata->menulayer] < 0)
      menudata->currentmenu[menudata->menulayer] = menudata->layerdata[menudata->menulayer].numberofitems - 1;
  }
}


void select_menu_layers(Layer *this_layer, GContext *ctx, MenuData* menudata, int layernumber){
  //always draw the base menu
  if(menudata->menulayer == 0 || menudata->menulayer == 1 || menudata->menulayer == 2)
    draw_menu_layer(this_layer, ctx, menudata, 0); //the base menu layer
    draw_menu_layer(this_layer, ctx, menudata, 1);
    draw_menu_layer(this_layer, ctx, menudata, 2);
  if(menudata->menulayer == 1)//buysellmenu
    draw_menu_layer(this_layer, ctx, menudata, 1);
}


void draw_menu_layer(Layer *this_layer, GContext *ctx, MenuData* menudata, int menulayernumber){
  drawmenuandbox(this_layer, ctx, menudata->currentmenu[menulayernumber], menudata->layerdata[menulayernumber].issquarelayer, menulayernumber, menudata->layerdata[menulayernumber].numberoftitles, menudata->layerdata[menulayernumber].xpos, menudata->layerdata[0].ypos, menudata->layerdata[menulayernumber].boxwidth, menudata->layerdata[menulayernumber].numberoftitles, menudata->layerdata[menulayernumber].layertext);
  switch(menulayernumber){
    case 1: //special things that need to be drawn in a layer will go here
      break;
    case 2: //special things that need to be drawn in a layer will go here
      break;
  }
}

//the reason for passing so many variables despite also passing the container is lazyness and legacy code.
void drawmenuandbox(Layer *this_layer, GContext *ctx, int currentposition, int issquarelayer, int layernumber, int itemscount, int x, int y, int xdiff, int offset, char text[100]){
  itemscount = itemscount + offset;
  GRect layertext;
  GRect highlightbox;
  if(issquarelayer == 0){
    highlightbox = (GRect(x, 2 + y+(currentposition + offset)*15 - currentposition, xdiff, 15 )); //highlighting box
    layertext = GRect(x, y, xdiff, 4 + y+(itemscount - 1)*15 - itemscount);
  }
  else if(issquarelayer == 1){ //if you want to draw a number of boxes
    if((currentposition%(itemscount - offset - 1)) == 0 && currentposition != 0){ //draw the last box as large, if number of items is odd
      highlightbox = (GRect(x, 2 + y+((currentposition + offset)/ 2)*15 - (currentposition/2), xdiff, 15 )); //highlighting box
    }
    else if(((currentposition + 1)%2) == 0) //draw box around the second colm of entries
      highlightbox = (GRect(x  + (xdiff/2), 2 + y+((currentposition + offset) / 2)*15 - (currentposition/2), (xdiff / 2), 15 ));
    else if(((currentposition + 1)%2 != 0)) //draw box around the first colm of entires
      highlightbox = (GRect(x, 2 + y+((currentposition + offset) / 2)*15 - (currentposition/2), (xdiff / 2), 15 ));
    layertext = GRect(x, y, xdiff, 4 + y+((itemscount/2 + 1) - 1)*15 - (itemscount/2));
  }
  graphics_fill_rect(ctx, layertext, 0, GCornerNone); //background box
  graphics_draw_rect(ctx, highlightbox); //the box around selected area
  graphics_draw_text(ctx, text, fonts_get_system_font(FONT_KEY_FONT_FALLBACK), layertext, GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
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
}
void menubuttonreleaseproc(MenuData* menudata){
  menudata->buttonreleased = 1;
  if(menudata->menuisactive == 1)
    updatemenuselection(menudata);
}
