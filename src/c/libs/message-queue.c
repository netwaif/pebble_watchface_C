#include <pebble.h>
#include "message-queue.h"
#include "src/c/config.h"

#define MESSAGE_KEY_GROUP 0
#define MESSAGE_KEY_OPERATION 1
#define MESSAGE_KEY_DATA 2

#define ATTEMPT_COUNT 2

typedef struct {
  char* group;
  char* operation;
  char* data;
} Message;

typedef struct MessageQueue MessageQueue;
struct MessageQueue {
  Message* message;
  MessageQueue* next;
  uint8_t attempts_left;
};

typedef struct HandlerQueue HandlerQueue;
struct HandlerQueue {
  MessageHandler handler;
  char* group;
  HandlerQueue* next;
};

static void destroy_message_queue(MessageQueue* queue);
static void outbox_sent_callback(DictionaryIterator *iterator, void *context);
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
static void inbox_received_callback(DictionaryIterator *iterator, void *context);
static void send_next_message();
static char *translate_error(AppMessageResult result);

static MessageQueue* msg_queue = NULL;
static HandlerQueue* handler_queue = NULL;
static bool sending = false;
static bool can_send = false;
static bool s_autostart = false;

void mqueue_deinit(){
	MessageQueue* eoq = msg_queue;
  while (eoq!=NULL && eoq->next != NULL) {
		MessageQueue* next = eoq->next;
    destroy_message_queue(eoq);
		eoq = next;
  }
  destroy_message_queue(eoq);
	HandlerQueue* hq = handler_queue;
	if (hq != NULL){
  	while (hq->next != NULL) {
			HandlerQueue* next = hq->next;
    	free_safe(hq->group);
			free_safe(hq);
			hq = next;
  	}
		free_safe(hq->group);
		free_safe(hq);
	}
}

void mqueue_init(bool autostart) {
  mqueue_init_custom(autostart, DEF_MESSAGE_QUEUE_INBOX_SIZE, DEF_MESSAGE_QUEUE_OUTBOX_SIZE);
}

void mqueue_init_custom(bool autostart, uint16_t inbox_size, uint16_t outbox_size) {
  AppMessageResult result = app_message_open(inbox_size, outbox_size);
	LOG("INIT STATUS: %s, in=%dB, out=%dB", translate_error(result),inbox_size, outbox_size);
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_inbox_received(inbox_received_callback);
  s_autostart = autostart;
}

bool mqueue_add(char* group, char* operation, char* data) {
  MessageQueue* mq = malloc(sizeof(MessageQueue));
  mq->next = NULL;
  mq->attempts_left = ATTEMPT_COUNT;

  mq->message = malloc(sizeof(Message));
  mq->message->group = malloc(strlen(group) + 1);
  strcpy(mq->message->group, group);
  mq->message->operation = malloc(strlen(operation) + 1);
  strcpy(mq->message->operation, operation);
  mq->message->data = malloc(strlen(data) + 1);
  strcpy(mq->message->data, data);

  LOG("ADDING: %s, %s, %s", mq->message->group, mq->message->operation, mq->message->data);

  if (msg_queue == NULL) {
    msg_queue = mq;
  }
  else {
    MessageQueue* eoq = msg_queue;
    while (eoq->next != NULL) {
      eoq = eoq->next;
    }
    eoq->next = mq;
  }

  send_next_message();
  return true;
}

void mqueue_register_handler(char* group, MessageHandler handler) {
  HandlerQueue* hq = malloc(sizeof(HandlerQueue));
  hq->next = NULL;
  hq->group = malloc(strlen(group) + 1);
  strcpy(hq->group, group);
  hq->handler = handler;

  if (handler_queue == NULL) {
    handler_queue = hq;
  }
  else {
    HandlerQueue* eoq = handler_queue;
    while (eoq->next != NULL) {
      eoq = eoq->next;
    }
    eoq->next = hq;
  }
}

void mqueue_enable_sending(void) {
  can_send = true;
  send_next_message();
}


static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  sending = false;
  MessageQueue* sent = msg_queue;
  LOG("SENT: %s, %s, %s", sent->message->group, sent->message->operation, sent->message->data);
  msg_queue = msg_queue->next;
  destroy_message_queue(sent);
  send_next_message();
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  sending = false;
  LOG("ERROR: %s, %s, %s", msg_queue->message->group, msg_queue->message->operation, msg_queue->message->data);
  LOG("%s", translate_error(reason));
  send_next_message();
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  LOG("!received smth!");
	char* group = dict_find(iterator, MESSAGE_KEY_GROUP)->value->cstring;
  char* operation = dict_find(iterator, MESSAGE_KEY_OPERATION)->value->cstring;
  char* data = dict_find(iterator, MESSAGE_KEY_DATA)->value->cstring;
	
  HandlerQueue* hq = handler_queue;
  while (hq != NULL) {
    if (strcmp(group, hq->group) == 0) {
      hq->handler(operation, data);
    }
    hq = hq->next;
  }

  if (! can_send && s_autostart) {
    mqueue_enable_sending();
  }
}

static void destroy_message_queue(MessageQueue* queue) {
  if (queue!=NULL){
		if (queue->message!=NULL){
			free_safe(queue->message->group);
  		free_safe(queue->message->operation);
  		free_safe(queue->message->data);
			free_safe(queue->message);
		}
		free_safe(queue);
	}
}

static void send_next_message() {
  if (! can_send) {
    return;
  }

  MessageQueue* mq = msg_queue;
  if (! mq) {
    return;
  }

  LOG("SENDING: %s, %s, %s", mq->message->group, mq->message->operation, mq->message->data);

  if (mq->attempts_left <= 0) {
    msg_queue = mq->next;
    destroy_message_queue(mq);
    send_next_message();
    return;
  }

  if (sending) {
    return;
  }
  sending = true;


  DictionaryIterator* dict;
  app_message_outbox_begin(&dict);
  dict_write_cstring(dict, MESSAGE_KEY_GROUP, mq->message->group);
  dict_write_cstring(dict, MESSAGE_KEY_OPERATION, mq->message->operation);
	dict_write_cstring(dict, MESSAGE_KEY_DATA, mq->message->data);
  AppMessageResult result = app_message_outbox_send();
  LOG("%s", translate_error(result));
  mq->attempts_left -= 1;
}

static char *translate_error(AppMessageResult result) {
  switch (result) {
    case APP_MSG_OK: return "APP_MSG_OK";
    case APP_MSG_SEND_TIMEOUT: return "APP_MSG_SEND_TIMEOUT";
    case APP_MSG_SEND_REJECTED: return "APP_MSG_SEND_REJECTED";
    case APP_MSG_NOT_CONNECTED: return "APP_MSG_NOT_CONNECTED";
    case APP_MSG_APP_NOT_RUNNING: return "APP_MSG_APP_NOT_RUNNING";
    case APP_MSG_INVALID_ARGS: return "APP_MSG_INVALID_ARGS";
    case APP_MSG_BUSY: return "APP_MSG_BUSY";
    case APP_MSG_BUFFER_OVERFLOW: return "APP_MSG_BUFFER_OVERFLOW";
    case APP_MSG_ALREADY_RELEASED: return "APP_MSG_ALREADY_RELEASED";
    case APP_MSG_CALLBACK_ALREADY_REGISTERED: return "APP_MSG_CALLBACK_ALREADY_REGISTERED";
    case APP_MSG_CALLBACK_NOT_REGISTERED: return "APP_MSG_CALLBACK_NOT_REGISTERED";
    case APP_MSG_OUT_OF_MEMORY: return "APP_MSG_OUT_OF_MEMORY";
    case APP_MSG_CLOSED: return "APP_MSG_CLOSED";
    case APP_MSG_INTERNAL_ERROR: return "APP_MSG_INTERNAL_ERROR";
    default: return "UNKNOWN ERROR";
  }
}
