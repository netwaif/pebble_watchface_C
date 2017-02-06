#include <pebble.h>
#include <pebble-helpers/pebble-helpers.h>
#include <pebble-events/pebble-events.h>
#include <pebble-packet/pebble-packet.h>
#include "layer_time.h"
#include "layer_battery.h"
#include "layer_bluetooth.h"
#include "config.h"

static void NULL_CALLBACK(){}
static Layer  *s_layers_pointers[DEF_LAYERS_MAX];
static Window *s_main_window;
static EventHandle s_minutetick_eventhandle;
static EventHandle s_secondtick_eventhandle;

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
	LOG("TICK!");
	layer_time_update_time(tick_time, s_layers_pointers[DEF_LAYERS_ORDER_TIME]);
}

void main_window_load(Window *window){ 
	LOG("main_window_load");
	
	Layer *root_layer = window_get_root_layer(window);
  GRect root_bounds = layer_get_bounds(root_layer);
	//13 + 39 = 52 
	s_layers_pointers[DEF_LAYERS_ORDER_TIME] = layer_time_create(root_bounds); 	//creating a time layer
	s_layers_pointers[DEF_LAYERS_ORDER_BT] = layer_bluetooth_create(GRect(root_bounds.size.w/2-54/2,root_bounds.size.h/5-13,13,13)); 	//creating a bluetooth icon layer
	s_layers_pointers[DEF_LAYERS_ORDER_BAT] = layer_battery_create(GRect(root_bounds.size.w/2-54/2+13+2,root_bounds.size.h/5-10,39,10)); 	//creating a battery icon layer
	
	for (int i = 0; i < DEF_LAYERS_MAX; i = i + 1){					//adding all created layers to the main window root layer
		if (s_layers_pointers[i]!=NULL){											//in the order defined by #define contstants
			layer_add_child(root_layer, s_layers_pointers[i]); 
		}
	}
}

void main_window_unload(Window *window){ 	
	LOG("main_window_unload");
	
	//special destructors for bluetooth and battery layers
	bluetooth_layer_destroy(s_layers_pointers[DEF_LAYERS_ORDER_BT]);
	battery_bar_layer_destroy(s_layers_pointers[DEF_LAYERS_ORDER_BAT]);
	//safely destroy the rest of the layers
	for (int i = 0; i < DEF_LAYERS_MAX; i = i + 1){
		layer_destroy_safe(s_layers_pointers[i]);
	}
}

void main_window_appear(Window *window){
	LOG("main_window_appear");
}

void main_window_disappear(Window *window){
	LOG("main_window_disappear");
}

Window *main_window_init(void){
	Window *window = window_create();
	window_set_background_color(window,GColorClear);
	window_set_window_handlers(window, (WindowHandlers){
		.load = main_window_load,
		.unload = main_window_unload,
		.appear = main_window_appear,
		.disappear = main_window_disappear
	});
	
	Layer *root_layer = window_get_root_layer(window);
	layer_set_update_proc(root_layer, NULL_CALLBACK);
	
	window_stack_push(window, false);
	return window;
}

void system_init(void) {
  LOG("system_init START");
	
	for (char i = 1; i <= DEF_LAYERS_MAX; i = i + 1){
		s_layers_pointers[i-1] = NULL;
	}
	
	s_main_window = main_window_init();
	
	s_minutetick_eventhandle = events_tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	
	#if DEBUG //subscribe to SECOND tick for debug info
  	s_secondtick_eventhandle = events_tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
	#endif
	
	LOG("system_init END");
}

void system_deinit(void) {
  LOG("system_DEinit START");	
	
	events_tick_timer_service_unsubscribe(s_minutetick_eventhandle);
	
	#if DEBUG //unsibscribe from SECOND tick handler in case of debug
		events_tick_timer_service_unsubscribe(s_secondtick_eventhandle);
	#endif
	
	window_destroy(s_main_window);
	
	LOG("system_DEinit END");
}

int main(void) {
  system_init();
	app_event_loop();
	system_deinit();
}
