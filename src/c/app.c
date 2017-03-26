#include <pebble.h>
#include "src/c/libs/message-queue.h"
#include "layers/layer_time.h"
#include "layers/layer_date.h"
#include "layers/layer_battery.h"
#include "layers/layer_bluetooth.h"
#include "layers/layer_bg.h"
#include "layers/layer_busy.h"
#include "layers/layer_events.h"
#include "config.h"

static Layer  *s_layers_pointers[DEF_LAYERS_MAX];
static Window *s_main_window;
void NULL_CALLBACK(){}

void tick_handler(struct tm *tick_time, TimeUnits units_changed){

	#if DEBUG
		if (SECOND_UNIT & units_changed){
			if (tick_time->tm_sec % DEF_LAYER_BUSY_TICKER_INTERVAL==0){
				LOG("TICK TICKER_INTERVAL (%d)!",DEF_LAYER_BUSY_TICKER_INTERVAL);
				layer_bg_update(s_layers_pointers[DEF_LAYERS_ORDER_BG]);  //explicitely request update of background (sets redraw flag to TRUE)
				layer_busy_update(s_layers_pointers[DEF_LAYERS_ORDER_BUSY],tick_time);
	//			layer_events_update(s_layers_pointers[DEF_LAYERS_ORDER_EVENTS],tick_time);
				//layer_busy_events_update(); //explicitly request new data from phone
				//bluetooth_refresh();  //explicitly request update of bluetooth status
				//battery_bar_refresh(); //explicitly request update of battery charge
			}
			layer_date_update_date(tick_time, s_layers_pointers[DEF_LAYERS_ORDER_DATE]); //requesting DATE redraw
			layer_time_update_time(tick_time, s_layers_pointers[DEF_LAYERS_ORDER_TIME]); //reqeusting TIME redraw
		}
	#endif
	
	if (MINUTE_UNIT & units_changed){
		if (tick_time->tm_min % DEF_LAYER_BUSY_TICKER_INTERVAL==0){
			layer_bg_update(s_layers_pointers[DEF_LAYERS_ORDER_BG]);  //explicitely request update of background (sets redraw flag to TRUE)
			layer_busy_update(s_layers_pointers[DEF_LAYERS_ORDER_BUSY],tick_time);
	//		layer_events_update(s_layers_pointers[DEF_LAYERS_ORDER_EVENTS], tick_time);
		}
		layer_date_update_date(tick_time, s_layers_pointers[DEF_LAYERS_ORDER_DATE]); //requesting DATE redraw
		layer_time_update_time(tick_time, s_layers_pointers[DEF_LAYERS_ORDER_TIME]);	  //reqeusting TIME redraw
		//bluetooth_refresh();  //explicitly request update of bluetooth status
		//battery_bar_refresh(); //explicitly request update of battery charge
	}

	if (DAY_UNIT & units_changed){
		layer_bg_update(s_layers_pointers[DEF_LAYERS_ORDER_BG]);  //explicitely request update of background (sets redraw flag to TRUE)
		layer_date_update_date(tick_time, s_layers_pointers[DEF_LAYERS_ORDER_DATE]); //requesting DATE redraw
	}
}

void main_window_load(Window *window){ 
	LOG("main_window_load");
		
	Layer *root_layer = window_get_root_layer(window);
	GRect root_bounds = layer_get_bounds(root_layer);
	//creating a time layer DEF_LAYER_TIME_HEIGHT
	GRect layer_time_bounds = GRect(root_bounds.origin.x
								   ,root_bounds.origin.y+root_bounds.size.h/2-DEF_LAYER_TIME_HEIGHT
								   ,root_bounds.size.w
								   ,DEF_LAYER_TIME_HEIGHT);
	//creating a DATE layer DEF_LAYER_DATE_HEIGHT
	GRect layer_date_bounds = GRect(root_bounds.origin.x
								   ,layer_time_bounds.origin.y-DEF_LAYER_DATE_HEIGHT+5
								   ,root_bounds.size.w
								   ,DEF_LAYER_DATE_HEIGHT);
	// creating indicators layer (same bounds are used for battery and bluetooth indicators)
	GRect layer_indicators_bounds = GRect(root_bounds.size.w/3
										 ,layer_date_bounds.origin.y-DEF_LAYER_INDICATORS_HEIGHT
										 ,root_bounds.size.w/3
										 ,DEF_LAYER_INDICATORS_HEIGHT);
	//creating bounds for events layer
	GRect layer_events_bounds = GRect(root_bounds.origin.x
									 ,root_bounds.origin.y+root_bounds.size.h/2 + DEF_LAYER_EVENTS_MARGIN
									 ,root_bounds.size.w
									 ,DEF_LAYER_EVENTS_HEIGHT);

	s_layers_pointers[DEF_LAYERS_ORDER_TIME] = layer_time_create(layer_time_bounds);
	s_layers_pointers[DEF_LAYERS_ORDER_DATE] = layer_date_create(layer_date_bounds);
	s_layers_pointers[DEF_LAYERS_ORDER_BT] = layer_bluetooth_create(layer_indicators_bounds); 	//creating a bluetooth icon layer
	s_layers_pointers[DEF_LAYERS_ORDER_BAT] = layer_battery_create(layer_indicators_bounds); 	//creating a battery icon layer
	s_layers_pointers[DEF_LAYERS_ORDER_BG] = layer_bg_create(root_bounds); //creating the background
	s_layers_pointers[DEF_LAYERS_ORDER_BUSY] = layer_busy_create(root_bounds); //creating the layer for free/busy arcs
//	s_layers_pointers[DEF_LAYERS_ORDER_EVENTS] = layer_events_create(layer_events_bounds); //creating the events layer
	
	for (int i = 0; i < DEF_LAYERS_MAX; i = i + 1){					//adding all created layers to the main window root layer
		if (s_layers_pointers[i]!=NULL){											//in the order defined by #define contstants
			layer_add_child(root_layer, s_layers_pointers[i]); 
		}
	}
}

void main_window_unload(Window *window){ 	
	LOG("main_window_unload");
	//special distructors for layers
	bluetooth_layer_destroy(s_layers_pointers[DEF_LAYERS_ORDER_BT]);
	battery_bar_layer_destroy(s_layers_pointers[DEF_LAYERS_ORDER_BAT]);
	layer_time_destroy(s_layers_pointers[DEF_LAYERS_ORDER_TIME]);
	layer_date_destroy(s_layers_pointers[DEF_LAYERS_ORDER_DATE]);
	layer_bg_destroy(s_layers_pointers[DEF_LAYERS_ORDER_BG]);
	layer_busy_destroy(s_layers_pointers[DEF_LAYERS_ORDER_BUSY]);
//	layer_events_destroy(s_layers_pointers[DEF_LAYERS_ORDER_EVENTS]);
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

void appmessage_sys_handler(char* operation, char* data){
	if (strcmp(operation, "INIT") == 0) {
		LOG("SYS msg handler: got INIT msg with data=%s", data);
		layer_busy_events_update(); //as soon as the connection is up - request the updated free/busy from phone
		layer_events_events_update(); //as soon as BT is up - request updated EVENTS data from the phone
  }
  else{
    LOG("SYS msg handler: unknown OPERATION!");
  }
}

void system_init(void) {
  LOG("system_init START");
	for (char i = 1; i <= DEF_LAYERS_MAX; i = i + 1){
		s_layers_pointers[i-1] = NULL;
	}
	s_main_window = main_window_init();
	#if !DEBUG //subscribe to MINUTE tick for production mode
		tick_timer_service_subscribe(DAY_UNIT+MINUTE_UNIT, tick_handler);		
	#elif DEBUG //subscribe for SECOND event for faster debug ticking
		tick_timer_service_subscribe(DAY_UNIT+MINUTE_UNIT+SECOND_UNIT, tick_handler);
		LOG("subscribed to DAY+MINUTE+SECOND_UNIT");
	#endif

	mqueue_init(true);
	mqueue_register_handler("SYS", appmessage_sys_handler);
	
	LOG("system_init END");
}

void system_deinit(void) {
  LOG("system_DEinit START");
	app_message_deregister_callbacks();
	tick_timer_service_unsubscribe();
	mqueue_deinit();
	window_destroy(s_main_window);
	LOG("system_DEinit END");
}

int main(void) {
	LOG("APP START");
  system_init();
	LOG("entering APP_EVENT_LOOP!");
	app_event_loop();
	LOG("exiting APP_EVENT_LOOP!");
	system_deinit();
	LOG("APP END");
}
