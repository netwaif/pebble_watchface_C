#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include "config.h"
#include "graphics.h"

void draw_hand(FContext *fctx, int center_x, int center_y, int inner_r, int outer_r, int width, int seconds, GColor color){
	int32_t second_angle = TRIG_MAX_ANGLE * (seconds-15) / 60; //offsetting because angles start at 15 seconds mark
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

void draw_arc(FContext *fctx, int center_x, int center_y, int inner_r, int outer_r, int seconds_start, int seconds_end, GColor color){
	seconds_start -= 15;  //offsetting because angles start at 15 seconds mark
	seconds_end -= 15;
	int32_t angle_step = TRIG_MAX_ANGLE / 120; //use half-step for smoothness
	fctx_begin_fill(fctx);
	fctx_set_fill_color(fctx, color);
	fctx_set_offset(fctx, FPointI(center_x,center_y));
 	fctx_set_scale(fctx, FPointOne, FPointOne);
	for (int i = seconds_start; i < seconds_end; i=i+1){
		int32_t curr_angle = TRIG_MAX_ANGLE * i / 60;
		fctx_set_rotation(fctx, curr_angle);
		fctx_move_to(fctx, FPoint(INT_TO_FIXED(inner_r), 0));
		fctx_line_to(fctx, FPoint(INT_TO_FIXED(outer_r), 0));
		fctx_set_rotation(fctx, curr_angle+angle_step);
		fctx_line_to(fctx, FPoint(INT_TO_FIXED(outer_r), 0));
		fctx_set_rotation(fctx, curr_angle+2*angle_step);
		fctx_line_to(fctx, FPoint(INT_TO_FIXED(outer_r), 0));
		fctx_line_to(fctx, FPoint(INT_TO_FIXED(inner_r), 0));
		fctx_set_rotation(fctx, curr_angle+angle_step);
		fctx_line_to(fctx, FPoint(INT_TO_FIXED(inner_r), 0));
		fctx_close_path(fctx);
	}
	fctx_end_fill(fctx);
}