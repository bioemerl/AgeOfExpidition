#pragma once

  
typedef struct{
  extern const int8_t MENUITEMSCNT;
  int8_t currentmenu[20];
  int8_t menulayer;
  int8_t uppressed;
  int8_t downpressed;
  int8_t selectpressed;
  int8_t buttonreleased;
} MenuData;

void update_menu(GameData* gamedata);
void update_menu_layer(MenuData* menudata);
void updatemenuselection(GameData* gamedata, int menulayer, int layeritemscount);
void draw_menu_layer(MenuData* menudata);
void draw_menu_layer(Layer *this_layer, GContext *ctx, int menulayernumber, int x, int y);
void drawmenuandbox(Layer *this_layer, GContext *ctx, int issquarelayer, int layernumber, int itemscount, int x, int y, int xdiff, int offset, char text[100]);
void menudownpressproc();
void menuuppressproc();
void menuselectpressproc();
void menubuttonreleaseproc();

