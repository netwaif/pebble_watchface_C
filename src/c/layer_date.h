#pragma once
#include <pebble.h>

typedef struct _layer_updater_date_data{
	struct tm curr_time;

} layer_updater_date_data;

void layer_date_update_date(struct tm *tick_time, Layer * layer);

Layer * layer_date_create(GRect layer_bounds);

void layer_date_destroy(Layer * layer);

void layer_date_updater(Layer *layer, GContext *ctx);