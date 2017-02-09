#pragma once
#include <pebble.h>

typedef struct _layer_updater_time_data{
	struct tm curr_time;

} layer_updater_time_data;

void layer_time_update_time(struct tm *tick_time, Layer * layer);

Layer * layer_time_create(GRect layer_bounds);

void layer_time_destroy(Layer * layer);

void layer_time_updater(Layer *layer, GContext *ctx);