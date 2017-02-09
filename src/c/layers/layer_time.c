#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include <pebble-fctx/ffont.h>
#include "layer_time.h"
#include "src/c/_config.h"

static FFont *s_time_font;
static char s_buffer[7]="00:00";

void layer_time_update_time(struct tm *tick_time, Layer *layer){
	layer_updater_time_data * data = layer_get_data(layer);
	data->curr_time = *tick_time;
	layer_mark_dirty(layer);
}

void layer_time_updater(Layer *layer, GContext *ctx){
	LOG("time layer UPDATER");
	//extracting the data from layer_data
	layer_updater_time_data * data = layer_get_data(layer);
	struct tm * curr_time = &data->curr_time;
	
	//init FCTX context
	FContext fctx;
	fctx_enable_aa(true);
  fctx_init_context(&fctx, ctx);
	//calculate the text width based on layer's height
	GRect layer_bounds = layer_get_bounds(layer);
	fctx_set_text_em_height(&fctx, s_time_font, layer_bounds.size.h);
	fixed_t text_width = fctx_string_width(&fctx, s_buffer, s_time_font);
	//get the text bounds based on text size and align it within layer_bounds
	GRect text_bounds = GRect(layer_bounds.size.w/2-FIXED_TO_INT(text_width/2),0,FIXED_TO_INT(text_width),layer_bounds.size.h);
	
	//getting the anchor point from local coords into FPoint coords for fctx
	GPoint gAbsOffset = layer_convert_point_to_screen(layer, GPoint(text_bounds.origin.x+text_bounds.size.w/2 , text_bounds.origin.y+text_bounds.size.h-1));
	FPoint fAbsOffset = FPoint(INT_TO_FIXED(gAbsOffset.x),INT_TO_FIXED(gAbsOffset.y));
	fctx_set_offset(&fctx, fAbsOffset); 	
	
	//clearing the text area based on previous numbers
	fctx_begin_fill(&fctx);
	fctx_set_fill_color(&fctx, GColorWhite);
	fctx_set_color_bias(&fctx, 8);
	fctx_draw_string(&fctx, s_buffer, s_time_font, GTextAlignmentCenter, FTextAnchorBaseline);
	fctx_end_fill(&fctx);
	
	//prepare the text to be displayed
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", curr_time);
	#if DEBUG //display seconds in both fields for debug purpose
		strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%S:%S" : "%S:%S", curr_time);
	#endif
	
	//draw the text.. finally...
	fctx_begin_fill(&fctx);
	fctx_set_fill_color(&fctx, DEF_LAYER_TIME_COLOR);
	fctx_set_color_bias(&fctx, 0);
	fctx_draw_string(&fctx, s_buffer, s_time_font, GTextAlignmentCenter, FTextAnchorBaseline);
	fctx_end_fill(&fctx);
	//deinit the fctx context
	fctx_deinit_context(&fctx);
	
	#if DEBUG  //drawing the outline boarder of layer and text area according to its size
		graphics_context_set_stroke_width(ctx, 1);
		graphics_context_set_stroke_color(ctx, GColorRed);
		graphics_draw_rect(ctx, layer_bounds);
		graphics_context_set_stroke_color(ctx, GColorGreen);
		graphics_draw_rect(ctx, text_bounds);
	#endif
}

Layer * layer_time_create(GRect layer_bounds){
	//create the layer
	Layer * layer = layer_create_with_data(layer_bounds,sizeof(layer_updater_time_data));
	//get the pointer to layer's data
	layer_updater_time_data * data = layer_get_data(layer);
	//initially current time in layer's data for the first drawing
	time_t start = time(NULL);
	data->curr_time = *localtime(&start);
	//load the font for time display
	s_time_font = ffont_create_from_resource(DEF_LAYER_TIME_FONT);
	//assign update handler for the layer
	layer_set_update_proc(layer, layer_time_updater);
	LOG("time layer CREATED");
	return layer;
}

void layer_time_destroy(Layer * layer){
	if (layer != NULL){  //check if the pointer is not NULL (calling twice)
		ffont_destroy(s_time_font);	//freeing memory fron the font
		layer_destroy(layer);
		layer = NULL;
	}
}
