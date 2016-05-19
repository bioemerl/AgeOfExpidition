#include <pebble.h>
#include "types.h"
#include "menus.h"
#include "game.h"

static Window *window;
static TextLayer *text_layer;
static GameData gamedata;
static MenuData menudata;
static Layer *graphics_canvas_layer;

static void canvas_update_proc(Layer *this_layer, GContext *ctx){
  //draw the planet points and draw highlighting circle.
  drawmainmap(this_layer, ctx, &gamedata);
  select_menu_layers(this_layer, ctx, &menudata, &gamedata); //should check if menu is active on it's own
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(menudata.menuisactive == 0){ //activate menu if it's not active
    if(gamedata.selectedplanet == -1){
      menudata.buttonreleased = 0;
      menudata.menulayer = 0;
      menudata.menuisactive = 1;
    }
    if(gamedata.selectedplanet >= 0){
      menudata.buttonreleased = 0;
      menudata.menulayer = 1;
      menudata.menuisactive = 1;
    }
  }
  
  layer_mark_dirty(graphics_canvas_layer);
  menuselectpressproc(&menudata, &gamedata);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  layer_mark_dirty(graphics_canvas_layer);
  menuuppressproc(&menudata);
  if(menudata.menuisactive == 0)
    uppresshandler(&gamedata);
  
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  layer_mark_dirty(graphics_canvas_layer);
  menudownpressproc(&menudata);
  if(menudata.menuisactive == 0)
    downpresshandler(&gamedata);
}

static void click_release_handler(ClickRecognizerRef recognizer, void *context) {
  menubuttonreleaseproc(&menudata);
}

static void click_config_provider(void *context) {
  window_raw_click_subscribe(BUTTON_ID_UP, up_click_handler, click_release_handler, NULL);
  window_raw_click_subscribe(BUTTON_ID_DOWN, down_click_handler, click_release_handler, NULL);
  window_raw_click_subscribe(BUTTON_ID_SELECT, select_click_handler, click_release_handler, NULL);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  //create and set the update protocol for the canvas to draw on
  graphics_canvas_layer = layer_create(GRect(0,0,bounds.size.w, bounds.size.h));
  layer_add_child(window_layer, graphics_canvas_layer);
  layer_set_update_proc(graphics_canvas_layer, canvas_update_proc);

  text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_text(text_layer, "default");
  text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
  //layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
  layer_destroy(graphics_canvas_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  
  initializegame(&gamedata);
  initializemenus(&menudata);
  menudata.menuisactive = 0;
  
  /*char characterarray[100]; //initialize the first menu's data to show accurate numbers for the first planet
  snprintf(characterarray, sizeof(characterarray), 
           "Planet: %i \nAntimatter: %i\nStations:\nInventory:\nFleets:\nEvents:\n--Exit--",  
           gamedata.currentplanet.planetnumber,
           gamedata.player.inventory.antimatter
          );*/
  
  //initialize the menu layers.  Remember, ones that have to update should be updated with another function elsewhere.
  initializemenulayer(0, &menudata, 2, 1, 77, 5, 2, 0, "Error:\nYou\nShouldnot\nSeeThis");
  initializemenulayer(1, &menudata, 0, 0, 50, 3, 1, 0, "Planet #\nWarp\nEvents\nExit");
  initializemenulayer(2, &menudata, 0, 0, 50, 4, 0, 0, "Error:\nYou\nShouldnot\nSeeThis");
  initializemenulayer(3, &menudata, 0, 0, 75, 4, 0, 0, "Error:\nYou\nShouldnot\nSeeThis");
  initializemenulayer(4, &menudata, 0, 0, 50, 3, 0, 0, "Player:\nOther:\n-Back-");
  initializemenulayer(5, &menudata, 0, 0, 50, 4, 0, 0, "you\nshould\nnot\nsee\nthis"); //events layer
  
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}