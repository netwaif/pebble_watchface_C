#pragma once
#include <pebble.h>
#include <pebble-fctx/fctx.h>

void draw_hand(FContext *fctx, int center_x, int center_y, int inner_r, int outer_r, int width, int seconds, GColor color);

void draw_arc(FContext *fctx, int center_x, int center_y, int inner_r, int outer_r, int seconds_start, int seconds_end, GColor color);