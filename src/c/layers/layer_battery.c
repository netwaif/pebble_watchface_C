#include <pebble.h>
#include <pebble-fctx/fctx.h>
#include "layer_battery.h"
#include "src/c/config.h"

typedef struct BatteryBarSettings {
  bool is_charging;
  bool hide_percent;
  bool hide_icon;
  uint8_t charge_percent;
  GFont percent_font;
  GRect percent_layer_rect;
  GRect icon_layer_rect;
  GColor color_normal;
  GColor color_warning;
  GColor color_danger;
  GColor color_charging;
  GColor color_state;
} BatteryBarSettings;

static Layer *s_battery_container_layer, *s_battery_icon_layer, *s_battery_bolt_layer;
static TextLayer *s_battery_percent_layer;

static GPath *s_battery_bolt_path_ptr = NULL;

static GPathInfo s_battery_bolt_path_info = {
  .num_points = 13,
  .points = (GPoint []) {{4,4},{6,4},{6,3},{8,3},{8,2},{8,4},{12,4},{10,4},{10,5},{8,5},{8,6},{8,4},{11,4}}
};

// Check current battery level, change colors and set percentage level.
static void battery_bar_battery_update(BatteryChargeState charge_state) {
  LOG("battery updater: charge = %d\%, state = %d",charge_state.charge_percent,charge_state.is_charging);
	
	BatteryBarSettings *data = layer_get_data(s_battery_container_layer);
	data->charge_percent = charge_state.charge_percent;
  data->is_charging = charge_state.is_charging;
  if(data->charge_percent == 0) {
    data->charge_percent = 1;
  }
	
	//change the BlueTooth sniff interval if the power changes
	SniffInterval sniff_int = app_comm_get_sniff_interval();
	if ( (sniff_int==SNIFF_INTERVAL_NORMAL) && (data->charge_percent <= 30) ){
		app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
	}else if ((sniff_int==SNIFF_INTERVAL_REDUCED) && (data->charge_percent  > 30) ){
		app_comm_set_sniff_interval(SNIFF_INTERVAL_NORMAL);
	}

	//change icon color based on the charge
  if(data->charge_percent < 20) {
    data->color_state = data->color_danger;
  } else if(data->charge_percent <= 30) {
    data->color_state = data->color_warning;
  } else {
    data->color_state = data->color_normal;
  }
	
	//prepare the text of charge
	static char s_txt[5];
  snprintf(s_txt, sizeof(s_txt), "%u%%", data->charge_percent);
  text_layer_set_text(s_battery_percent_layer, s_txt);
  text_layer_set_text_color(s_battery_percent_layer, data->color_state);

  layer_set_hidden(text_layer_get_layer(s_battery_percent_layer), data->hide_percent);
  layer_set_hidden(s_battery_icon_layer, data->hide_icon);
	
	layer_mark_dirty(s_battery_container_layer);
  layer_mark_dirty(s_battery_icon_layer);
}

static void battery_container_layer_update_callback(Layer *container_layer, GContext* ctx){
	graphics_context_set_antialiased(ctx,true);
	GRect bounds = layer_get_bounds(container_layer);
	
	graphics_context_set_fill_color(ctx, DEF_LAYER_BACKGROUND);
	graphics_fill_rect(ctx, bounds, 0, GCornerNone);
	#if DEBUG
		graphics_context_set_stroke_color(ctx, GColorRed);
		graphics_draw_rect(ctx, bounds);
	#endif
}

// Draw the battery icon and charging indicator.
static void battery_bar_layer_update_callback(Layer *icon_layer, GContext* ctx) {
	graphics_context_set_antialiased(ctx,true);
  BatteryBarSettings *data = layer_get_data(s_battery_container_layer);
	
  graphics_context_set_stroke_color(ctx, data->color_state);
  graphics_draw_rect(ctx, GRect(0, 0, 16, 9));
  graphics_draw_rect(ctx, GRect(15, 2, 2, 5));

  graphics_context_set_stroke_color(ctx, data->color_state);
  graphics_context_set_fill_color(ctx, data->color_state);

  if(data->is_charging) {
    graphics_context_set_stroke_color(ctx, data->color_charging);
    gpath_draw_outline(ctx, s_battery_bolt_path_ptr);
  } else {
    uint8_t width = ((data->charge_percent / 100.0) * 11.0);
    if(width < 12) {
      width++;
    }
    graphics_fill_rect(ctx, GRect(2, 2, width, 5), 0, GCornerNone);
  }
}

// Force the battery bar to update and redraw.
void battery_bar_refresh() {
  battery_bar_battery_update(battery_state_service_peek());
}

// Create a set of default settings.
static void battery_bar_set_defaults(BatteryBarSettings *data) {
  data->percent_font = fonts_get_system_font(DEF_LAYER_BATTERY_FONT);
  data->percent_layer_rect = GRect(0, -1, 30, DEF_LAYER_INDICATORS_HEIGHT);
  data->icon_layer_rect = GRect(31, 4, 17, DEF_LAYER_INDICATORS_HEIGHT);
  data->hide_percent = false;
  data->hide_icon = false;
  #ifdef PBL_COLOR
    data->color_normal = GColorBlack;
    data->color_warning = GColorOrange;
    data->color_danger = GColorRed;
    data->color_charging = GColorYellow;
  #else
    data->color_normal = GColorBlack;
    data->color_warning = GColorBlack;
    data->color_danger = GColorBlack;
    data->color_charging = GColorBlack;
  #endif
}

// Create a new battery bar layer and start monitoring.
Layer* layer_battery_create(GRect root_bounds) {
  s_battery_container_layer = layer_create_with_data(GRect(root_bounds.origin.x+root_bounds.size.w-48, root_bounds.origin.y+root_bounds.size.h-DEF_LAYER_INDICATORS_HEIGHT, 48, DEF_LAYER_INDICATORS_HEIGHT), sizeof(BatteryBarSettings));
	layer_set_update_proc(s_battery_container_layer, battery_container_layer_update_callback);
  BatteryBarSettings *data = layer_get_data(s_battery_container_layer);
  battery_bar_set_defaults(data);

  s_battery_percent_layer = text_layer_create(data->percent_layer_rect);
  text_layer_set_background_color(s_battery_percent_layer, GColorClear);
  text_layer_set_text_color(s_battery_percent_layer, data->color_normal);
  text_layer_set_text_alignment(s_battery_percent_layer, GTextAlignmentRight);
  text_layer_set_font(s_battery_percent_layer, data->percent_font);
  layer_add_child(s_battery_container_layer, text_layer_get_layer(s_battery_percent_layer));

  s_battery_bolt_path_ptr = gpath_create(&s_battery_bolt_path_info);

  s_battery_icon_layer = layer_create(data->icon_layer_rect);
  layer_set_update_proc(s_battery_icon_layer, battery_bar_layer_update_callback);
  layer_add_child(s_battery_container_layer, s_battery_icon_layer);

  battery_bar_refresh();
  battery_state_service_subscribe(battery_bar_battery_update);

  return s_battery_container_layer;
}

// Destroy the layer and its contents.
void battery_bar_layer_destroy(Layer *battery_bar_layer) {
  battery_state_service_unsubscribe();

  gpath_destroy(s_battery_bolt_path_ptr);
  s_battery_bolt_path_ptr = NULL;

  text_layer_destroy(s_battery_percent_layer);

  layer_remove_from_parent(s_battery_bolt_layer);
  layer_remove_from_parent(s_battery_icon_layer);
  layer_remove_from_parent(s_battery_container_layer);

  layer_destroy(s_battery_bolt_layer);
  layer_destroy(s_battery_icon_layer);
  layer_destroy(s_battery_container_layer);
}

// Hide the percentage label.
void battery_bar_set_percent_hidden(bool hidden) {
  BatteryBarSettings *data = layer_get_data(s_battery_container_layer);
  data->hide_percent = hidden;
  battery_bar_refresh();
}

// Hide the battery icon.
void battery_bar_set_icon_hidden(bool hidden) {
  BatteryBarSettings *data = layer_get_data(s_battery_container_layer);
  data->hide_icon = hidden;
  battery_bar_refresh();
}

// Adjust the colors of the various battery level states.
void battery_bar_set_colors(GColor normal, GColor warning, GColor danger, GColor charging) {
  BatteryBarSettings *data = layer_get_data(s_battery_container_layer);
  data->color_normal = normal;
  data->color_warning = warning;
  data->color_danger = danger;
  data->color_charging = charging;
  battery_bar_refresh();
}

// Move the battery bar position on screen (x, y).
void battery_bar_set_position(GPoint position) {
  GRect frame = layer_get_frame(s_battery_container_layer);
  frame.origin = position;
  layer_set_frame(s_battery_container_layer, frame);
}
