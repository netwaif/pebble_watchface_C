#pragma once
#include <pebble.h>

void layer_bg_update(Layer *layer);

Layer * layer_bg_create(GRect layer_bounds);

void layer_bg_destroy(Layer * layer);

void layer_bg_updater(Layer *layer, GContext *ctx);