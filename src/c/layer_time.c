#include <pebble.h>
#include "layer_time.h"
#include "config.h"

void layer_time_update_time(struct tm *tick_time, Layer *layer){
	layer_updater_time_data * data = layer_get_data(layer);
	data->curr_time = *tick_time;
	layer_mark_dirty(layer);
}

Layer * layer_time_create(GRect root_bounds){
	//calculate area within root bounds
	GRect bounds = GRect(root_bounds.origin.x, root_bounds.size.h/5, root_bounds.size.w, root_bounds.size.h/2-root_bounds.size.h/5);
	//create the layer
	Layer * layer = layer_create_with_data(bounds,sizeof(layer_updater_time_data));
	//get the pointer to layer's data
	layer_updater_time_data * data = layer_get_data(layer);
	//initially store bounds and current time in layer's data for the first drawing
	data->prev_bounds = bounds;
	time_t start = time(NULL);
	data->curr_time = *localtime(&start);
	//assign update handler for the layer
	layer_set_update_proc(layer, layer_time_updater);
	return layer;
}

void layer_time_updater(Layer *layer, GContext *ctx){

	GRect layer_bounds = layer_get_bounds(layer);
	
	#if DEBUG	//draw the layer outline bound
		graphics_context_set_stroke_width(ctx, 1);
		graphics_context_set_stroke_color(ctx, GColorRed);
		graphics_draw_rect(ctx, layer_bounds);
	#endif
	
	//extracting the data from layer_data
	layer_updater_time_data * data = layer_get_data(layer);
	GRect prev_bounds = data->prev_bounds;
	struct tm * curr_time = &data->curr_time;
	
	//clearing the text area of PREVIOUS BOUND size
	graphics_context_set_fill_color(ctx, DEF_LAYER_TIME_BACKGROUND);
	graphics_fill_rect(ctx, prev_bounds, 0, GCornersAll);
	
	//prepare the text to be displayed
	char s_buffer[7];
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", curr_time);
	#if DEBUG //display seconds in both fields for debug purpose
		strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%S:%S" : "%S:%S", curr_time);
	#endif
	
	GFont font = fonts_get_system_font(DEF_LAYER_TIME_FONT);
	GSize text_size = graphics_text_layout_get_content_size(s_buffer, font, layer_bounds, GTextOverflowModeWordWrap, GTextAlignmentCenter);
	
	//get the text bounds based on text size and align it within layer_bounds
	GRect bounds = GRect(layer_bounds.origin.x+layer_bounds.size.w/2-text_size.w/2-2, layer_bounds.origin.y+layer_bounds.size.h-text_size.h, text_size.w+5, text_size.h);
	//store bounds in layer data for next tick
	data->prev_bounds = bounds;
	
	#if DEBUG //drawing the outline boarder of text area according to its size
		graphics_context_set_stroke_width(ctx, 1);
		graphics_context_set_stroke_color(ctx, GColorGreen);
		graphics_draw_rect(ctx, bounds);
	#endif
	
	//rendering text
	graphics_context_set_text_color(ctx, DEF_LAYER_TIME_COLOR);
	graphics_draw_text(ctx, s_buffer, font, bounds, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
}
