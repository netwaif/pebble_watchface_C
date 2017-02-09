#pragma once
#include <pebble.h>

void layer_busy_update(Layer *layer, struct tm *tick_time);

Layer * layer_busy_create(GRect layer_bounds);

void layer_busy_destroy(Layer * layer);

void layer_busy_updater(Layer *layer, GContext *ctx);