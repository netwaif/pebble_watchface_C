#include <pebble.h>
#include "layer_date.h"
#include "pebble-fctx/ffont.h"
#include "config.h"

static FFont *s_date_font;

void layer_date_update_date(struct tm *tick_time, Layer *layer){
	layer_updater_date_data * data = layer_get_data(layer);
	data->curr_time = *tick_time;
	layer_mark_dirty(layer);
}

void layer_date_updater(Layer *layer, GContext *ctx){
	LOG("date layer UPDATER");
	//extracting the data from layer_data
	layer_updater_date_data * data = layer_get_data(layer);
	//GRect prev_bounds = data->prev_bounds;
	struct tm * curr_time = &data->curr_time;
	//prepare the text to be displayed
	char s_buffer[7];
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", curr_time);
	#if DEBUG //display seconds in both fields for debug purpose
		strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%S:%S" : "%S:%S", curr_time);
	#endif
	
	//init FCTX context
	FContext fctx;
	fctx_enable_aa(true);
  fctx_init_context(&fctx, ctx);
	//calculate the text width based on it's height
	fctx_set_text_em_height(&fctx, s_date_font, DEF_LAYER_DATE_HEIGHT);
	fixed_t text_width = fctx_string_width(&fctx, s_buffer, s_date_font);
	//get the text bounds based on text size and align it within layer_bounds
	GRect layer_bounds = layer_get_bounds(layer);
	GRect text_bounds = GRect(layer_bounds.size.w/2-FIXED_TO_INT(text_width/2),0,FIXED_TO_INT(text_width),layer_bounds.size.h);
	//clearing the text area based on text_bounds
	graphics_context_set_fill_color(ctx, DEF_LAYER_BACKGROUND);
	graphics_fill_rect(ctx, text_bounds, 0, GCornersAll);
	//getting the anchor point from local coords into FPoint coords for fctx
	GPoint gAbsOffset = layer_convert_point_to_screen(layer, GPoint(text_bounds.origin.x+text_bounds.size.w/2 , text_bounds.origin.y+text_bounds.size.h-1));
	FPoint fAbsOffset = FPoint(INT_TO_FIXED(gAbsOffset.x),INT_TO_FIXED(gAbsOffset.y));
	fctx_set_offset(&fctx, fAbsOffset); 
	//draw the text.. finally...
	fctx_begin_fill(&fctx);
	fctx_set_fill_color(&fctx, DEF_LAYER_DATE_COLOR);
	fctx_draw_string(&fctx, s_buffer, s_date_font, GTextAlignmentCenter, FTextAnchorBaseline);
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

Layer * layer_date_create(GRect layer_bounds){
	//create the layer
	Layer * layer = layer_create_with_data(layer_bounds,sizeof(layer_updater_date_data));
	//get the pointer to layer's data
	layer_updater_date_data * data = layer_get_data(layer);
	//initially current time in layer's data for the first drawing
	time_t start = time(NULL);
	data->curr_time = *localtime(&start);
	//load the font for time display
	s_date_font = ffont_create_from_resource(RESOURCE_ID_DATE_FONT);
	//assign update handler for the layer
	layer_set_update_proc(layer, layer_date_updater);
	LOG("time layer CREATED");
	return layer;
}

void layer_date_destroy(Layer * layer){
	if (layer != NULL){  //check if the pointer is not NULL (calling twice)
		ffont_destroy(s_date_font);	//freeing memory fron the font
		layer_destroy(layer);
		layer = NULL;
	}
}