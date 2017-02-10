#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include "layer_busy.h"
#include "src/c/modules/graphics.h"
#include "src/c/config.h"

static bool s_redraw_flag = true;
static struct tm s_current_time;
	
typedef struct events {
   int start;
   int end;
} event;

static struct events free_busy[50]={
	{-5,4},{8,15},{24,35},{47,68},{80,98},{104,135}
};

static int free_busy_length = 6;

void layer_busy_updater(Layer *layer, GContext *ctx){
	if (!s_redraw_flag){return;}else{s_redraw_flag = false;} // if the flag is FALSE - we DON'T redraw - just quit
	LOG("BUSY layer UPDATER");
	FContext fctx;
	fctx_enable_aa(true);
  fctx_init_context(&fctx, ctx);
	
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, DEF_LAYER_BACKGROUND);
	graphics_fill_rect(ctx, bounds, 0, GCornersAll);
	
	int center_x = bounds.size.w/2;
	int center_y = bounds.size.h/2;
	int innerRadius = bounds.size.w/2-DEF_LAYER_BG_L_LEN;
	int outerRadius = bounds.size.w/2-DEF_LAYER_BG_S_LEN;
	int angle;
	
	#if DEBUG
		angle = s_current_time.tm_sec;
	#else
		angle = (s_current_time.tm_hour*60.0+s_current_time.tm_min)/12.0;
	#endif
	
	//draw_arc(&fctx, bounds.size.w/2, bounds.size.h/2, bounds.size.w/2-DEF_LAYER_BG_L_LEN, bounds.size.w/2-DEF_LAYER_BG_S_LEN, 12, 34 , DEF_LAYER_BUSY_COLOR_AM);
	//draw_arc(&fctx, bounds.size.w/2, bounds.size.h/2, bounds.size.w/2-DEF_LAYER_BG_L_LEN, bounds.size.w/2-DEF_LAYER_BG_S_LEN, 42, 64 , DEF_LAYER_BUSY_COLOR_PM);
	
	for (int i=0;i<free_busy_length;i=i+1){
		//CanvasRenderingContext2D.rockyFillRadial(x, y, innerRadius, outerRadius, startAngle, endAngle)
		
		if (free_busy[i].end < 60){
			draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(angle,MAX(0,free_busy[i].start)),  free_busy[i].end, DEF_LAYER_BUSY_COLOR_AM);
		}else if(free_busy[i].start < 120){
			if (free_busy[i].start < 60){
				draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(free_busy[i].start, angle), 60, DEF_LAYER_BUSY_COLOR_AM);
			}
			draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(60,free_busy[i].start),  MIN(free_busy[i].end , angle+60), DEF_LAYER_BUSY_COLOR_PM);
		}
	}
	
	draw_hand(&fctx, center_x, center_y, innerRadius-DEF_LAYER_BUSY_HAND_LENGTH, outerRadius, DEF_LAYER_BUSY_HAND_WIDTH, angle, DEF_LAYER_BUSY_HAND_COLOR);
	
	fctx_deinit_context(&fctx);
}

void layer_busy_update(Layer *layer, struct tm *tick_time){
	s_redraw_flag = true; //explicitly set the flag to TRUE saying, that the updater callback has to erdraw the whole background
	s_current_time = *tick_time;
	layer_mark_dirty(layer);
}

Layer * layer_busy_create(GRect layer_bounds){
	//create the layer
	Layer * layer = layer_create(layer_bounds);
	
	//calculate the angles and other data for future usage
	
	//initially current time in layer's data for the first drawing
	time_t start = time(NULL);
	s_current_time = *localtime(&start);
	
	//assign update handler for the layer
	layer_set_update_proc(layer, layer_busy_updater);
	LOG("BUSY layer CREATED");
	return layer;
}

void layer_busy_destroy(Layer * layer){
	if (layer != NULL){  //check if the pointer is not NULL (calling twice)
		layer_destroy(layer);
		layer = NULL;
	}
}