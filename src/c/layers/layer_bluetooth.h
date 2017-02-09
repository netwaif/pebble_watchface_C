#pragma once
#include <pebble.h>

Layer* layer_bluetooth_create(GRect root_bounds);
void bluetooth_layer_destroy(Layer *bluetooth_layer);
void bluetooth_vibe_disconnect(bool vibe);
void bluetooth_vibe_connect(bool vibe);
void bluetooth_set_colors(GColor connected_circle, GColor connected_icon, GColor disconnected_circle, GColor disconnected_icon);
void bluetooth_set_position(GPoint position);
void bluetooth_refresh();