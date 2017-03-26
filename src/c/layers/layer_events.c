#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include <pebble-fctx/ffont.h>
#include "src/c/config.h"
#include "layer_events.h"
#include "src/c/libs/data-processor.h"
#include "src/c/libs/message-queue.h"
#include "src/c/modules/graphics.h"


static Layer* s_layer_events = NULL;
static FFont *s_events_font;
static bool s_redraw_flag = true;
static bool s_requested_update = false;
static struct tm s_current_time;

typedef struct _event {
   struct tm start;
   struct tm end;
   char *summary;
} event;

static event* s_events = NULL;
static int    s_events_length = 0;

static void* layer_events_events_destory_safe(event *arr, int *len){
	if (NULL==arr){*len=0;return NULL;}
	for (int i=0; i<*len;i=i+1){
		free_safe(arr[i].summary);
	}
	free_safe(arr);
	*len = 0;
	return NULL;
}

static event* layer_events_events_init_safe(int *len){
	event* arr = malloc(*len * sizeof(event));
	//for (int i=0; i<*len;i=i+1){
		//arr[i].summary = malloc(DEF_LAYER_EVENTS_SUMMARY_LEN_MAX);
	//}

	LOG("allocated %dB at %d",(*len * sizeof(event))+*len * DEF_LAYER_EVENTS_SUMMARY_LEN_MAX,arr);
	return arr;
}

static void layer_events_events_parse_string(char *str, event *arr, int *len){
	ProcessingState* parser = data_processor_create(str, '|');
	int l = data_processor_get_int(parser);
	LOG("parse_string: START parsing of %d/%d from %s", l, *len, str);
	if (l!=*len){*len = l;}
	for (int i=0; i<l; i+=1){
		time_t s = (time_t)data_processor_get_uint(parser);
		s_events[i].start = *localtime(&s);
		time_t e = (time_t)data_processor_get_uint(parser);
		s_events[i].end = *localtime(&e);
		//LOG("parsed: s=%d, e=%d",s_events[i].start,s_events[i].end);
		arr[i].summary = data_processor_get_string(parser);
	}
	LOG("parse_string: parsing END, parsed %d of %d", 3*l, data_processor_count(parser)-1);
	data_processor_destroy(parser);
}

void layer_events_msg_handler(char* operation, char* data){
	if (strcmp(operation, "UPDATE") == 0) {
		s_events = layer_events_events_destory_safe(s_events, &s_events_length);
		ProcessingState* parser = data_processor_create(data, '|');
		s_events_length = data_processor_get_int(parser);
		data_processor_destroy(parser);
		s_events = layer_events_events_init_safe(&s_events_length);
		persist_write_int(DEF_PERSIST_EVENTS_LEN_KEY, s_events_length);
		persist_write_string(DEF_PERSIST_EVENTS_ARR_KEY, data);
		layer_events_events_parse_string(data, s_events, &s_events_length);

		layer_mark_dirty(s_layer_events);
  }
  else{
    LOG("unknown OPERATION!");
  }
	s_requested_update = false;
}

void layer_events_events_update(){
	//requests the new data from mobile
	if (!s_requested_update && connection_service_peek_pebble_app_connection()){
		mqueue_add(DEF_LAYER_EVENTS_MSG_GROUP, "REQUEST", "");
		s_requested_update = true;
	}
}

void layer_events_persist_load(event *arr, int *len){
	if (persist_exists(DEF_PERSIST_EVENTS_LEN_KEY) && persist_exists(DEF_PERSIST_EVENTS_ARR_KEY)){
		if (*len!=0 || NULL!=s_events){
			s_events = layer_events_events_destory_safe(arr,len);
		}
		*len = persist_read_int_safe(DEF_PERSIST_EVENTS_LEN_KEY,0);
		if (*len!=0){
			s_events = layer_events_events_init_safe(len);
			char *buff = malloc(DEF_LAYER_EVENTS_STR_LEN_MAX);
			int res = persist_read_string(DEF_PERSIST_EVENTS_ARR_KEY, buff, DEF_LAYER_EVENTS_STR_LEN_MAX);
			LOG("layer_events_persist_load: read=%dB", res);
			layer_events_events_parse_string(buff, s_events, len);
			free(buff);
		}
	}
}

Layer * layer_events_create(GRect layer_bounds){
	//create the layer
	s_layer_events = layer_create(layer_bounds);

	#if DEBUG
		char *debug_str = "1|10000|20000|testtest";
		persist_write_int(DEF_PERSIST_EVENTS_LEN_KEY, 1);
		persist_write_string(DEF_PERSIST_EVENTS_ARR_KEY, debug_str);
	#endif

	//restore the data from persitant storage into the memory
	layer_events_persist_load(s_events, &s_events_length);

	//initially current time in layer's data for the first drawing
	time_t start = time(NULL);
	s_current_time = *localtime(&start);

	//load the font for events display
	if (s_dateevents_font == NULL){
		s_dateevents_font = ffont_create_from_resource(DEF_LAYER_DATEEVENTS_FONT);
	}
	s_events_font = s_dateevents_font;

	//assign update handler for the layer
	layer_set_update_proc(s_layer_events, layer_events_updater);
	LOG("EVENTS layer CREATED");

	//assign message handler for the layer
	mqueue_register_handler(DEF_LAYER_EVENTS_MSG_GROUP, layer_events_msg_handler);

	return s_layer_events;
}

void layer_events_destroy(Layer * layer){
	if (layer != NULL){  //check if the pointer is not NULL (calling twice)
		layer_destroy(layer);
		layer = NULL;
	}
	s_events = layer_events_events_destory_safe(s_events,&s_events_length);
	if (s_events_font != NULL) {
		ffont_destroy(s_events_font);
	}
}

void layer_events_updater(Layer *layer, GContext *ctx){
	if (!s_redraw_flag){return;}else{s_redraw_flag = false;} // if the flag is FALSE - we DON'T redraw - just quit
	LOG("EVENTS layer UPDATER");

	//init FCTX context
	FContext fctx;
	fctx_enable_aa(true);
	fctx_init_context(&fctx, ctx);

	//calculate the text width based on layer's height
	GRect layer_bounds = layer_get_bounds(layer);
	graphics_context_set_fill_color(ctx, DEF_LAYER_BACKGROUND);
	graphics_fill_rect(ctx, layer_bounds, 0, GCornersAll);

	char *buffer = malloc(32);
	for (int i=0;i<MIN(s_events_length,DEF_LAYER_EVENTS_LINES_MAX);i=i+1){
		strncpy(buffer,s_events[i].summary,30);
		
		fctx_set_text_em_height(&fctx, s_events_font, layer_bounds.size.h/MIN(s_events_length,DEF_LAYER_EVENTS_LINES_MAX));
		fixed_t text_width = fctx_string_width(&fctx, buffer, s_events_font);
		//get the text bounds based on text size and align it within layer_bounds
		GRect text_bounds = GRect(layer_bounds.size.w/2-FIXED_TO_INT(text_width/2)
				,i*layer_bounds.size.h/MIN(s_events_length,DEF_LAYER_EVENTS_LINES_MAX)
				,FIXED_TO_INT(text_width)
				,layer_bounds.size.h/MIN(s_events_length,DEF_LAYER_EVENTS_LINES_MAX));
		//clearing the text area based on text_bounds
		//graphics_fill_rect(ctx, text_bounds, 0, GCornersAll);
		//getting the anchor point from local coords into FPoint coords for fctx
		GPoint gAbsOffset = layer_convert_point_to_screen(layer, GPoint(text_bounds.origin.x+text_bounds.size.w/2 , text_bounds.origin.y+text_bounds.size.h-1));
		FPoint fAbsOffset = FPoint(INT_TO_FIXED(gAbsOffset.x),INT_TO_FIXED(gAbsOffset.y));
		fctx_set_offset(&fctx, fAbsOffset);
		//draw the text.. finally...
		fctx_begin_fill(&fctx);
		fctx_set_fill_color(&fctx, DEF_LAYER_DATE_COLOR);
		fctx_draw_string(&fctx, buffer, s_events_font, GTextAlignmentCenter, FTextAnchorBaseline);
		fctx_end_fill(&fctx); //!!!!!!!!!!
		#if DEBUG
			//graphics_draw_rect(ctx, text_bounds);
		#endif
	}

	//deinit the fctx context
	fctx_deinit_context(&fctx);

	#if DEBUG  //drawing the outline boarder of layer and text area according to its size
		graphics_context_set_stroke_width(ctx, 1);
		graphics_context_set_stroke_color(ctx, GColorRed);
		graphics_draw_rect(ctx, layer_bounds);
		graphics_context_set_stroke_color(ctx, GColorGreen);
	#endif

	free_safe(buffer);
	LOG("EVENTS layer UPDATER done!");
}

void layer_events_update(Layer *layer, struct tm *tick_time){
	s_redraw_flag = true; //explicitly set the flag to TRUE saying, that the updater callback has to erdraw the whole background
	s_current_time = *tick_time;
	layer_mark_dirty(layer);
}
