#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include "layer_busy.h"
#include "config.h"

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

