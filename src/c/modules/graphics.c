#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include <pebble-fctx/fpath.h>
#include <pebble-fctx/ffont.h>
#include "src/c/config.h"
#include "graphics.h"

int32_t int32_sqrt(int32_t inValue)
{
	uint8_t  neg = (inValue < 0);
	uint32_t num = (neg ? -inValue : inValue);
	uint32_t result = 0;
	uint32_t bit;
	uint8_t  n;
	
	// Many numbers will be less than 15, so
	// this gives a good balance between time spent
	// in if vs. time spent in the while loop
	// when searching for the starting value.
	if (num & 0xFFF00000)
		bit = (uint32_t)1 << 30;
	else
		bit = (uint32_t)1 << 18;
	
	while (bit > num) bit >>= 2;
	
	// The main part is executed twice, in order to avoid
	// using 64 bit values in computations.
	for (n = 0; n < 2; n++)
	{
		// First we get the top 24 bits of the answer.
		while (bit)
		{
			if (num >= result + bit)
			{
				num -= result + bit;
				result = (result >> 1) + bit;
			}
			else
			{
				result = (result >> 1);
			}
			bit >>= 2;
		}
		
		if (n == 0)
		{
			// Then process it again to get the lowest 8 bits.
			if (num > 65535)
			{
				// The remainder 'num' is too large to be shifted left
				// by 16, so we have to add 1 to result manually and
				// adjust 'num' accordingly.
				// num = a - (result + 0.5)^2
				//	 = num + result^2 - (result + 0.5)^2
				//	 = num - result - 0.5
				num -= result;
				num = (num << 16) - 0x8000;
				result = (result << 16) + 0x8000;
			}
			else
			{
				num <<= 16;
				result <<= 16;
			}
			
			bit = 1 << 14;
		}
	}

#ifndef FIXMATH_NO_ROUNDING
	// Finally, if next bit would have been 1, round the result upwards.
	if (num > result)
	{
		result++;
	}
#endif
	
	return (neg ? -result : result);
}

#define iter1(N) try = root + (1 << (N)); if (n >= try << (N)) { n -= try << (N); root |= 2 << (N); }
uint32_t my_sqrt(uint32_t n)
{
    uint32_t root = 0, try;
    iter1 (15); iter1 (14); iter1 (13); iter1 (12); iter1 (11);
    iter1 (10); iter1 ( 9); iter1 ( 8); iter1 ( 7); iter1 ( 6);
    iter1 ( 5); iter1 ( 4); iter1 ( 3); iter1 ( 2); iter1 ( 1); iter1 ( 0);
    return root >> 1;
}

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
