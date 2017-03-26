#pragma once
#include <pebble.h>

void layer_events_update(Layer *layer, struct tm *tick_time);

Layer * layer_events_create(GRect layer_bounds);

void layer_events_destroy(Layer * layer);

void layer_events_updater(Layer *layer, GContext *ctx);

void layer_events_events_update();

