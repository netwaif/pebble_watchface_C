#pragma once
#include <pebble.h>
#include <pebble-fctx/fctx.h>


static FFont *s_dateevents_font;

void draw_hand(FContext *fctx, int center_x, int center_y, int inner_r, int outer_r, int width, int seconds, GColor color);

void draw_arc(FContext *fctx, int center_x, int center_y, int inner_r, int outer_r, int seconds_start, int seconds_end, GColor color);

uint32_t my_sqrt(uint32_t n);

int32_t int32_sqrt(int32_t inValue);