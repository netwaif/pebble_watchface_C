#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include <pebble-fctx/ffont.h>
#include "src/c/config.h"
#include "layer_events.h"
#include "src/c/libs/data-processor.h"
#include "src/c/libs/message-queue.h"
#include "src/c/modules/graphics.h"

#define DEF_LAYER_EVENTS_STR_LEN_MAX 256
#define DEF_LAYER_EVENTS_MSG_GROUP "BUSY"
#define DEF_PERSIST_BUSY_LEN_KEY 0
#define DEF_PERSIST_BUSY_ARR_KEY 1

static bool s_redraw_flag = true;
static struct tm s_current_time;
	
typedef struct _event {
   int start;
   int end;
} event;

static event* s_events = NULL;
static int    s_events_length = 0;

static void layer_events_msg_handler(char* operation, char* data){
	if (strcmp(operation, "UPDATE") == 0) {
    		
  }
  else{
    LOG("unknown OPERATION!");
  }
}

static void* layer_events_events_destory_safe(event *arr, int *len){
	if (NULL==arr){*len=0;return NULL;}
	//for (uint8_t d = 0; d < *len; d += 1) {
    //free_safe(arr[d]->start);
		//free_safe(arr[d]->end);
    //free_safe(arr[d]);
  //}
  free_safe(arr);
  *len = 0;
	return NULL;
}

static event* layer_events_events_init_safe(int *len){
	event* arr = malloc(*len * sizeof(event));
	LOG("allocated %dB at %d",(*len * sizeof(event)),arr);
	//for (uint8_t d = 0; d < *len; d += 1) {
    //arr[d] = malloc(sizeof(event));
		//e->start = malloc(sizeof(int));
		//e->end = malloc(sizeof(int));
		//arr[d] = e;
  //}
	return arr;
}