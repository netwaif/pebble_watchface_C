#include <pebble.h>
#include "src/c/libs/fctx.h"
#include "src/c/libs/fpath.h"
#include "src/c/config.h"
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
	if (seconds_start >= seconds_end){
		//LOG("NOT drawing arc: seconds_start=%d < seconds_end=%d",seconds_start,seconds_end);
		return;
	}
	int steps = DEF_LAYER_BUSY_ARC_SEGMENTS * (seconds_end-seconds_start);  //dividing into more steps for better quality rendering
	int32_t angle_step = TRIG_MAX_ANGLE / (60 * DEF_LAYER_BUSY_ARC_SEGMENTS); //use half-step for smoothness
	int32_t curr_angle = TRIG_MAX_ANGLE * (seconds_start-15) / 60; //offsetting for Pi/2
		
	//LOG("drawing arc: seconds_start=%d  seconds_end=%d",seconds_start,seconds_end);
	//LOG("drawing arc: curr_angle=%d steps=%d angle_step=%d",curr_angle,steps,angle_step);
		
	fctx_begin_fill(fctx);
	fctx_set_fill_color(fctx, color);
	fctx_set_offset(fctx, FPointI(center_x,center_y));
 	fctx_set_scale(fctx, FPointOne, FPointOne);
	
	fctx_set_rotation(fctx, curr_angle);
	fctx_move_to(fctx, FPoint(INT_TO_FIXED(inner_r), 0));
	fctx_line_to(fctx, FPoint(INT_TO_FIXED(outer_r), 0));
	for (int i = 0; i < steps; i=i+1){ //draw outer arc
		curr_angle += angle_step;
		fctx_set_rotation(fctx, curr_angle);
		fctx_line_to(fctx, FPoint(INT_TO_FIXED(outer_r), 0));
	}
	fctx_line_to(fctx, FPoint(INT_TO_FIXED(inner_r), 0)); //go to drawing inner arc
	for (int i = 0; i < steps; i=i+1){ //draw inner arc
		curr_angle -= angle_step;
		fctx_set_rotation(fctx, curr_angle);
		fctx_line_to(fctx, FPoint(INT_TO_FIXED(inner_r), 0));
	}
	fctx_close_path(fctx);
	fctx_end_fill(fctx);
}