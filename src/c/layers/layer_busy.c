#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include "src/c/config.h"
#include "layer_busy.h"
#include "src/c/libs/data-processor.h"
#include "src/c/libs/message-queue.h"
#include "src/c/modules/graphics.h"

#define DEF_LAYER_BUSY_STR_LEN_MAX 256
#define DEF_LAYER_BUSY_MSG_GROUP "BUSY"
#define DEF_PERSIST_BUSY_LEN_KEY 0
#define DEF_PERSIST_BUSY_ARR_KEY 1

static Layer* s_layer_busy = NULL;
static bool s_redraw_flag = true;
static bool s_requested_update = false;
static struct tm s_current_time;

typedef struct _event {
   int start;
   int end;
} event;

static event* s_events = NULL;
static int    s_events_length = 0;

static void* layer_busy_events_destory_safe(event *arr, int *len){
	if (NULL==arr){*len=0;return NULL;}
  free_safe(arr);
  *len = 0;
	return NULL;
}

static event* layer_busy_events_init_safe(int *len){
	event* arr = malloc(*len * sizeof(event));
	LOG("allocated %dB at %d",(*len * sizeof(event)),arr);
	return arr;
}

void layer_busy_msg_handler(char* operation, char* data){
	if (strcmp(operation, "UPDATE") == 0) {
  	s_events = layer_busy_events_destory_safe(s_events, &s_events_length);
		ProcessingState* parser = data_processor_create(data, '|');
		s_events_length = data_processor_get_int(parser);
		s_events = layer_busy_events_init_safe(&s_events_length);
		persist_write_int(DEF_PERSIST_BUSY_LEN_KEY, s_events_length);
		persist_write_string(DEF_PERSIST_BUSY_ARR_KEY, data);
		LOG("parse_string: START parsing of %d from %s", s_events_length, data);
		for (int i=0; i<s_events_length; i+=1){
			int s = data_processor_get_int(parser);
			int e = data_processor_get_int(parser);
			//LOG("parsed: s=%d, e=%d",s,e);
			s_events[i].start = s;
			s_events[i].end = e;
		}
		LOG("parse_string: parsing END, parsed %d of %d", 2*s_events_length, data_processor_count(parser)-1);
		data_processor_destroy(parser);
		layer_mark_dirty(s_layer_busy);
  }
  else{
    LOG("unknown OPERATION!");
  }
	s_requested_update = false;
}


void layer_busy_events_update(){
	//requests the new data from mobile
	if (!s_requested_update && connection_service_peek_pebble_app_connection()){
		mqueue_add(DEF_LAYER_BUSY_MSG_GROUP, "REQUEST", "");
		s_requested_update = true;
	}
}

static void layer_busy_events_parse_string(char *str, event *arr, int *len){
	ProcessingState* parser = data_processor_create(str, '|');
	int l = data_processor_get_int(parser);
	LOG("parse_string: START parsing of %d/%d from %s", l, *len, str);
	if (l!=*len){*len = l;}
	for (int i=0; i<l; i+=1){
		int s = data_processor_get_int(parser);
		int e = data_processor_get_int(parser);
		//LOG("parsed: s=%d, e=%d",s,e);
		arr[i].start = s;
		arr[i].end = e;
	}
	LOG("parse_string: parsing END, parsed %d of %d", 2*l, data_processor_count(parser)-1);
	data_processor_destroy(parser);
}

void layer_busy_persist_load(event *arr, int *len){
	if (persist_exists(DEF_PERSIST_BUSY_LEN_KEY)&&persist_exists(DEF_PERSIST_BUSY_ARR_KEY)){
		if (*len!=0 || NULL!=s_events){
			s_events = layer_busy_events_destory_safe(arr,len);
		}
		*len = persist_read_int_safe(DEF_PERSIST_BUSY_LEN_KEY,0);
		if (*len!=0){		
			s_events = layer_busy_events_init_safe(len);
			char *buff = malloc(DEF_LAYER_BUSY_STR_LEN_MAX);
			int res = persist_read_string(DEF_PERSIST_BUSY_ARR_KEY, buff, DEF_LAYER_BUSY_STR_LEN_MAX);
			LOG("layer_busy_persist_load: read=%dB", res);
			layer_busy_events_parse_string(buff, s_events, len);
			free(buff);
		}
	}
}

Layer * layer_busy_create(GRect layer_bounds){
	//create the layer
	s_layer_busy = layer_create(layer_bounds);
	
	#if DEBUG
		char *debug_str = "24|0|1|5|6|10|11|15|16|20|21|25|26|30|31|35|36|40|41|45|46|50|51|55|56|60|61|65|66|70|71|75|76|80|81|85|86|90|91|95|96|100|101|105|106|110|111|115|116";
		persist_write_int(DEF_PERSIST_BUSY_LEN_KEY, 24);
		persist_write_string(DEF_PERSIST_BUSY_ARR_KEY, debug_str);
	#endif
	
	//restore the data from persitant storage into the memory
	layer_busy_persist_load(s_events, &s_events_length);
	
	//initially current time in layer's data for the first drawing
	time_t start = time(NULL);
	s_current_time = *localtime(&start);
	
	//assign update handler for the layer
	layer_set_update_proc(s_layer_busy, layer_busy_updater);
	LOG("BUSY layer CREATED");
	
	//assign message handler for the layer
	mqueue_register_handler(DEF_LAYER_BUSY_MSG_GROUP, layer_busy_msg_handler);
	
	return s_layer_busy;
}

void layer_busy_destroy(Layer * layer){
	if (layer != NULL){  //check if the pointer is not NULL (calling twice)
		layer_destroy(layer);
		layer = NULL;
	}
	s_events = layer_busy_events_destory_safe(s_events,&s_events_length);
}

void layer_busy_updater(Layer *layer, GContext *ctx){
	if (!s_redraw_flag){return;}else{s_redraw_flag = false;} // if the flag is FALSE - we DON'T redraw - just quit
	LOG("BUSY layer UPDATER");
	FContext fctx;
	fctx_enable_aa(true);
  fctx_init_context(&fctx, ctx);
	
	GRect bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, DEF_LAYER_BACKGROUND);
	graphics_fill_rect(ctx, bounds, 0, GCornersAll);
	
	int center_x = bounds.size.w/2;
	int center_y = bounds.size.h/2;
	int innerRadius = bounds.size.w/2-DEF_LAYER_BG_L_LEN;
	int outerRadius = bounds.size.w/2-DEF_LAYER_BG_S_LEN;
	int angle;
	
	#if DEBUG
		angle = s_current_time.tm_sec;
	#else
		angle = (s_current_time.tm_hour*60.0+s_current_time.tm_min)/12.0;
	#endif
	
	for (int i=0;i<s_events_length;i=i+1){
		//LOG("start drawing from %d s=%d,e=%d", s_events, s_events[i].start, s_events[i].end);
		if (s_events[i].end < 60){
			draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(angle,s_events[i].start),  s_events[i].end, DEF_LAYER_BUSY_COLOR_AM);
		}else if(s_events[i].start < 120){
			if (s_events[i].start < 60){
				draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(s_events[i].start, angle), 60, DEF_LAYER_BUSY_COLOR_AM);
			}
			draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(60,s_events[i].start),  MIN(s_events[i].end , angle+60), DEF_LAYER_BUSY_COLOR_PM);
		}
	}
	draw_hand(&fctx, center_x, center_y, innerRadius-DEF_LAYER_BUSY_HAND_LENGTH, outerRadius, DEF_LAYER_BUSY_HAND_WIDTH, angle, DEF_LAYER_BUSY_HAND_COLOR);
	
	fctx_deinit_context(&fctx);
	LOG("BUSY layer UPDATER done!");
}

void layer_busy_update(Layer *layer, struct tm *tick_time){
	s_redraw_flag = true; //explicitly set the flag to TRUE saying, that the updater callback has to erdraw the whole background
	s_current_time = *tick_time;
	layer_mark_dirty(layer);
}