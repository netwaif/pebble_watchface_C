#include <pebble.h>
#include "src/c/libs/fctx.h"
#include "src/c/libs/data-processor.h"
#include "src/c/libs/message-queue.h"
#include "layer_busy.h"
#include "src/c/modules/graphics.h"
#include "src/c/config.h"

#define DEF_LAYER_BUSY_ARR_LEN_MAX 50
#define DEF_LAYER_BUSY_MSG_GROUP "BUSY"
#define DEF_PERSIST_BUSY_LEN_KEY 0
#define DEF_PERSIST_BUSY_ARR_KEY 1


static bool s_redraw_flag = true;
static struct tm s_current_time;
	
typedef struct event {
   int* start;
   int* end;
} _event;

static struct event** s_events = NULL;
static int s_events_length = 0;

void layer_busy_msg_handler(char* operation, char* data){
	if (strcmp(operation, "UPDATE") == 0) {
    data_processor_init(data, '|');
		
  }
  else{
    LOG("unknown OPERATION!");
  }
}

static void layer_busy_events_destory_safe(struct event **arr, int *len){
	if (NULL==arr){*len=0;return;}
	for (uint8_t d = 0; d < *len; d += 1) {
    free_safe(arr[d]->start);
		free_safe(arr[d]->end);
    free_safe(arr[d]);
  }
  free_safe(arr);
  *len = 0;
}

static void layer_busy_events_init_safe(struct event **arr, int *len){
	arr = malloc(*len * sizeof(_event*));
	for (uint8_t d = 0; d < *len; d += 1) {
    _event* e = malloc(sizeof(_event));
		e->start = malloc(sizeof(int));
		e->end = malloc(sizeof(int));
		arr[d] = e;
  }
}

static void layer_busy_events_parse_string(char *str[], struct event **arr, int *len){
	
}

void layer_busy_persist_load(struct event **arr, int *len){
	if (persist_exists(DEF_PERSIST_BUSY_LEN_KEY)&&persist_exists(DEF_PERSIST_BUSY_ARR_KEY)){
		if (*len!=0 || NULL!=s_events){layer_busy_events_destroy_safe(arr,len);}
		*len = persist_read_int_safe(DEF_PERSIST_BUSY_LEN_KEY,0);
		if (*len!=0){			
			layer_busy_events_init_safe(arr,len);
			char buff[];
			int res = persist_read_data(DEF_PERSIST_BUSY_ARR_KEY, buff, MIN(DEF_LAYER_BUSY_ARR_LEN_MAX,*len)*sizeof(_event));
			LOG("layer_busy_persist_load: read=%dB supposed=%dB", res,(*len)*sizeof(_event));
		}
	}
}

void layer_busy_persist_save(struct event **arr, int *len){
	int res = persist_write_int(DEF_PERSIST_BUSY_LEN_KEY, *len);
	res = persist_write_data(DEF_PERSIST_BUSY_ARR_KEY, arr, MIN(DEF_LAYER_BUSY_ARR_LEN_MAX,*len)*sizeof(_event));
	LOG("layer_busy_persist_save: saved=%dB supposed=%dB", res,(*len)*sizeof(_event));
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
	
	//draw_arc(&fctx, bounds.size.w/2, bounds.size.h/2, bounds.size.w/2-DEF_LAYER_BG_L_LEN, bounds.size.w/2-DEF_LAYER_BG_S_LEN, 12, 34 , DEF_LAYER_BUSY_COLOR_AM);
	//draw_arc(&fctx, bounds.size.w/2, bounds.size.h/2, bounds.size.w/2-DEF_LAYER_BG_L_LEN, bounds.size.w/2-DEF_LAYER_BG_S_LEN, 42, 64 , DEF_LAYER_BUSY_COLOR_PM);
	
	for (int i=0;i<events_length;i=i+1){
		//CanvasRenderingContext2D.rockyFillRadial(x, y, innerRadius, outerRadius, startAngle, endAngle)
		
		if (*events[i]->end < 60){
			draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(angle,MAX(0,*events[i]->start)),  *events[i]->end, DEF_LAYER_BUSY_COLOR_AM);
		}else if(*events[i]->start < 120){
			if (*events[i]->start < 60){
				draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(*events[i]->start, angle), 60, DEF_LAYER_BUSY_COLOR_AM);
			}
			draw_arc(&fctx, center_x , center_y , innerRadius , outerRadius, MAX(60,*events[i]->start),  MIN(*events[i]->end , angle+60), DEF_LAYER_BUSY_COLOR_PM);
		}
	}
	
	draw_hand(&fctx, center_x, center_y, innerRadius-DEF_LAYER_BUSY_HAND_LENGTH, outerRadius, DEF_LAYER_BUSY_HAND_WIDTH, angle, DEF_LAYER_BUSY_HAND_COLOR);
	
	fctx_deinit_context(&fctx);
}

void layer_busy_update(Layer *layer, struct tm *tick_time){
	s_redraw_flag = true; //explicitly set the flag to TRUE saying, that the updater callback has to erdraw the whole background
	s_current_time = *tick_time;
	layer_mark_dirty(layer);
}

Layer * layer_busy_create(GRect layer_bounds){
	//create the layer
	Layer * layer = layer_create(layer_bounds);
	
	#if DEBUG
		//{	{-5,4},{8,15},{24,35},{47,68},{80,98},{104,135} };
	#endif
	
	//restore the data from persitant storage into the memory
	layer_busy_persist_load(events, &events_length);
	
	//initially current time in layer's data for the first drawing
	time_t start = time(NULL);
	s_current_time = *localtime(&start);
	
	//assign update handler for the layer
	layer_set_update_proc(layer, layer_busy_updater);
	LOG("BUSY layer CREATED");
	
	//assign message handler for the layer
	mqueue_register_handler(DEF_LAYER_BUSY_MSG_GROUP, layer_busy_msg_handler);
	
	return layer;
}

void layer_busy_destroy(Layer * layer){
	if (layer != NULL){  //check if the pointer is not NULL (calling twice)
		layer_destroy(layer);
		layer = NULL;
	}
}