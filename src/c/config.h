#pragma once
#include <pebble.h>

#define DEBUG 1

#define PBL_COLOR 1

#define DEF_LAYERS_MAX  7

#define DEF_LAYERS_ORDER_BUSY   0
#define DEF_LAYERS_ORDER_BG     1
#define DEF_LAYERS_ORDER_EVENTS 2
#define DEF_LAYERS_ORDER_TIME   3
#define DEF_LAYERS_ORDER_DATE   4
#define DEF_LAYERS_ORDER_BT     5
#define DEF_LAYERS_ORDER_BAT    6

#define DEF_LAYER_TIME_COLOR GColorBlack
#define DEF_LAYER_TIME_HEIGHT 43
#define DEF_LAYER_DATE_COLOR GColorBlack //GColorTiffanyBlue
#define DEF_LAYER_DATE_HEIGHT 15
#define DEF_LAYER_INDICATORS_HEIGHT 16
#define DEF_LAYER_BACKGROUND GColorClear

#define DEF_LAYER_TIME_FONT RESOURCE_ID_FONT_ROBOTO_BOLD_NUM
#define DEF_LAYER_BATTERY_FONT FONT_KEY_GOTHIC_14
#define DEF_LAYER_DATEEVENTS_FONT RESOURCE_ID_FONT_OPENSANS_BOLD

#define DEF_LAYER_BUSY_ARC_SEGMENTS 1 //number of segment per 1 Second interval
#define DEF_LAYER_BUSY_TICKER_INTERVAL 5
#define DEF_LAYER_BUSY_COLOR_AM GColorRed
#define DEF_LAYER_BUSY_COLOR_PM GColorLightGray
#define DEF_LAYER_BUSY_HAND_WIDTH 2
#define DEF_LAYER_BUSY_HAND_LENGTH 6
#define DEF_LAYER_BUSY_HAND_COLOR GColorRed
#define DEF_LAYER_BUSY_STR_LEN_MAX 256

#define DEF_LAYER_EVENTS_STR_LEN_MAX 512
#define DEF_LAYER_EVENTS_SUMMARY_LEN_MAX 64
#define DEF_LAYER_EVENTS_HEIGHT 66
#define DEF_LAYER_EVENTS_WIDTH 43
#define DEF_LAYER_EVENTS_COLOR GColorBlack
#define DEF_LAYER_EVENTS_LINES_MAX 6

#define DEF_LAYER_BG_COLOR GColorBlack
#define DEF_LAYER_BG_L_WID 3
#define DEF_LAYER_BG_L_LEN 15
#define DEF_LAYER_BG_M_WID 2
#define DEF_LAYER_BG_M_LEN 11
#define DEF_LAYER_BG_S_WID 1
#define DEF_LAYER_BG_S_LEN 7

#define DEF_MESSAGE_QUEUE_INBOX_SIZE 1024
#define DEF_MESSAGE_QUEUE_OUTBOX_SIZE 1024
#define DEF_LAYER_BUSY_MSG_GROUP "BUSY"
#define DEF_LAYER_EVENTS_MSG_GROUP "EVENTS"


#define DEF_PERSIST_BUSY_LEN_KEY 0
#define DEF_PERSIST_BUSY_ARR_KEY 1
#define DEF_PERSIST_EVENTS_LEN_KEY 2
#define DEF_PERSIST_EVENTS_ARR_KEY 3


#define free_safe(ptr) if (NULL != ptr) { LOG("free_safe: %p", ptr); free(ptr); ptr = NULL; }
#define persist_read_int_safe(key, value) (persist_exists(key) ? persist_read_int(key) : value);
#define persist_read_bool_safe(key, value) (persist_exists(key) ? persist_read_bool(key) : value);
#define persist_read_data_safe(key) (persist_exists(key) ? persist_read_bool(key) : 0);

#define MAX3(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))

#define MAX(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#define MIN(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

#if DEBUG
	#define LOG(...) APP_LOG(APP_LOG_LEVEL_DEBUG , __VA_ARGS__)
#else
	#define LOG(...) ((void)0)
#endif
