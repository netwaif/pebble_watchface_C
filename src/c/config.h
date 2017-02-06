#pragma once
#include <pebble.h>

#define DEBUG 1

#if DEBUG
	#define LOG(...) APP_LOG(APP_LOG_LEVEL_DEBUG , __VA_ARGS__)
#else
	#define LOG(...) ((void)0)
#endif

#define DEF_LAYERS_MAX  7
#define DEF_LAYERS_ORDER_BG     0
#define DEF_LAYERS_ORDER_BUSY   1
#define DEF_LAYERS_ORDER_TIME   2
#define DEF_LAYERS_ORDER_DATE   3
#define DEF_LAYERS_ORDER_EVENTS 4
#define DEF_LAYERS_ORDER_BT     5
#define DEF_LAYERS_ORDER_BAT    6

#define DEF_LAYER_TIME_FONT FONT_KEY_BITHAM_42_MEDIUM_NUMBERS
#define DEF_LAYER_TIME_COLOR GColorBlack
#define DEF_LAYER_TIME_BACKGROUND GColorClear