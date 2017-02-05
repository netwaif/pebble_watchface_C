#include <pebble.h>

static Window *s_main_window;
static TextLayer *text_layer;

void root_layer_fill(Window *window){
	Layer *window_root_layer = window_get_root_layer(window);
	GRect window_bounds = layer_get_bounds(window_root_layer);
	text_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(58, 52), window_bounds.size.w, 50));
	text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_text_color(text_layer, GColorBlack);
  text_layer_set_text(text_layer, "00:00");
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	layer_add_child(window_root_layer, text_layer_get_layer(text_layer));
}
	
void main_window_load(Window *window){
//	root_layer_fill(window);
	
}

void main_window_unload(Window *window){
//	text_layer_destroy(text_layer);
}

void main_window_appear(Window *window){
	
}

void main_window_disappear(Window *window){
	
}

Window* main_window_init(Window *window){
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers){
		.load = main_window_load,
		.unload = main_window_unload,
		.appear = main_window_appear,
		.disappear = main_window_disappear
	});
	
}

void system_init(void) {
  
//	main_window_init(s_main_window);
	
	s_main_window = window_create();
	
	
	window_stack_push(s_main_window, true);
}

void system_deinit(void) {
	
	window_destroy(s_main_window);
}

int main(void) {
  system_init();
	
	app_event_loop();
  
	system_deinit();
}
