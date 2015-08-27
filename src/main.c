#include <pebble.h>
#include "types.h"
#include "menus.h"
#include "game.h"

static Window *window;
static TextLayer *text_layer;
static GameData gamedata;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  static char characterarray[200];
  snprintf(characterarray, sizeof(characterarray), 
           "Newplanets is %i \nPlanetnumber is %i \ncurrentstations is %i \nplayermetal is %i \nplanetfleet is %i \nplanet ship 1 hp %i", 
           gamedata.numberofnewplanets, 
           gamedata.currentplanet.planetnumber,
           gamedata.currentplanet.numberofstations,
           gamedata.player.inventory.metal,
           gamedata.currentplanet.fleet.numberofships,
           gamedata.currentplanet.fleet.ships[0].health
          );
  text_layer_set_text(text_layer, characterarray);
  warp(&gamedata, 1);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_text(text_layer, "default");
  text_layer_set_text_alignment(text_layer, GTextAlignmentLeft);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  initializegame(&gamedata);
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}