#pragma once
#include <pebble.h>

Layer* layer_battery_create(GRect root_bounds);
void battery_bar_layer_destroy(Layer *battery_bar_layer);
void battery_bar_set_percent_hidden(bool hidden);
void battery_bar_set_icon_hidden(bool hidden);
void battery_bar_set_colors(GColor normal, GColor warning, GColor danger, GColor charging);
void battery_bar_set_position(GPoint position);
void battery_bar_refresh();