#include <pebble.h>
#include "layer_bg.h"
#include <pebble-fctx/fctx.h>
#include "config.h"

static bool s_redraw_flag = true;

static void draw_hand(FContext *fctx, int center_x, int center_y, int inner_r, int outer_r, int width, int seconds, GColor color){
	int32_t second_angle = TRIG_MAX_ANGLE * seconds / 60;
	fixed_t halfwidth = INT_TO_FIXED(width)/2;
	
	fctx_begin_fill(fctx);
	fctx_set_fill_color(fctx, color);
	fctx_set_offset(fctx, FPointI(center_x,center_y));
  fctx_set_scale(fctx, FPointOne, FPointOne);
	fctx_set_rotation(fctx, second_angle);
	fctx_move_to(fctx, FPoint(INT_TO_FIXED(inner_r), -halfwidth));
	fctx_line_to(fctx, FPoint(INT_TO_FIXED(outer_r), -halfwidth));
	fctx_line_to(fctx, FPoint(INT_TO_FIXED(outer_r), halfwidth));
	fctx_line_to(fctx, FPoint(INT_TO_FIXED(inner_r), halfwidth));
	fctx_close_path(fctx);
	fctx_end_fill(fctx);
}

void layer_bg_updater(Layer *layer, GContext *ctx){
	if (!s_redraw_flag){return;} // if the flag is FALSE - we DON'T redraw - just quit
	LOG("BG layer UPDATER");
	FContext fctx;
	fctx_enable_aa(true);
  fctx_init_context(&fctx, ctx);
	
	GRect bounds = layer_get_bounds(layer);
	int l,w;
	for (int i=0;i<60;i=i+1){
		if (i==0||i==15||i==30||i==45){
			l = DEF_LAYER_BG_L_LEN;
			w = DEF_LAYER_BG_L_WID;
		}
		else if (i==5||i==10||i==20||i==25||i==35||i==40||i==50||i==55){
			l = DEF_LAYER_BG_M_LEN;
			w = DEF_LAYER_BG_M_WID;
		}
		else {
			l = DEF_LAYER_BG_S_LEN;
			w = DEF_LAYER_BG_S_WID;
		}
		draw_hand(&fctx, bounds.size.w/2, bounds.size.h/2, bounds.size.w/2-l, bounds.size.w/2, w, i , DEF_LAYER_BG_COLOR);
	}
	fctx_deinit_context(&fctx);
	s_redraw_flag = false;
}

void layer_bg_update(Layer *layer){
	s_redraw_flag = true; //explicitly set the flag to TRUE saying, that the updater callback has to erdraw the whole background
	layer_mark_dirty(layer);
}

Layer * layer_bg_create(GRect layer_bounds){
	//create the layer
	Layer * layer = layer_create(layer_bounds);
	
	//calculate the angles and other data for future usage
	
	//assign update handler for the layer
	layer_set_update_proc(layer, layer_bg_updater);
	LOG("BG layer CREATED");
	return layer;
}

void layer_bg_destroy(Layer * layer){
	if (layer != NULL){  //check if the pointer is not NULL (calling twice)
		layer_destroy(layer);
		layer = NULL;
	}
}

