#pragma once

#define ZP_ZONES_NUM_MAX 8

// Must be at least 1 (for background)
#define ZP_LAYERS_NUM 4

#if ZP_LAYERS_NUM < 1
  #error "ZP_LAYERS_NUM must be at least 1"
#endif

#if !defined ZP_ZONES_NUM || ZP_ZONES_NUM < 1
  #warning "ZP_ZONES_NUM is undefined or less then 1, setting it to 1"
  #define ZP_ZONES_NUM 1
  #define ZP_ZONE_0_MIN 0
  #define ZP_ZONE_0_MAX DRIVER_LED_TOTAL
#endif

#if ZP_ZONES_NUM > ZP_ZONES_NUM_MAX
  #error "ZP_ZONES_NUM must be less then " #ZP_ZONES_NUM_MAX
#endif

#define ZP_DYN_LAYERS_NUM ZP_LAYERS_NUM - 1
#define ZP_LAYER_NUM_TO_DYN_LAYER_NUM(x) x - 1

#define ZP_LAYER_BACKGROUND 0

// ZP uses RGBA to specify color
typedef struct rgba {
    uint32_t r : 8;
    uint32_t g : 8;
    uint32_t b : 8;
    uint32_t a : 8;
} rgba;

#define ZP_RGBA(R, G, B, A) { .r = R, .g = G, .b = B, .a = A }
#define ZP_RGB(R, G, B) { .r = R, .g = G, .b = B, .a = 255 }

#include "colors.h"

// ZPainting will draw the buffers in this array
// The buffer size is expected to be DRIVER_LED_TOTAL
//
// Layer indexing for this buffer is (n = n - 1),
// since the background layer is not stored
extern const rgba* zp_layers[ZP_DYN_LAYERS_NUM];

// ZPainting can skip drawing certain layer on certain zone
extern bool zp_disable_map[ZP_LAYERS_NUM][ZP_ZONES_NUM];
static const size_t zp_disable_map_size = sizeof(zp_disable_map);

// ZPainting draws everything on top of a zoned background
extern rgba zp_background[ZP_ZONES_NUM];

// Redraw flag should be set after any change
extern bool zp_repaint_flag;

inline void zp_repaint(void) {
    zp_repaint_flag = true;
}

void zp_init(void);

void zp_set_layer(uint8_t layer, const rgba* buffer);

void zp_set_background_at_zone(uint8_t zone, rgba color);
void zp_set_background(rgba color);

void zp_disable_layer_at_zone(uint8_t layer, uint8_t zone);
void zp_disable_layer(uint8_t layer);
void zp_disable_zone(uint8_t zone);

void zp_enable_layer_at_zone(uint8_t layer, uint8_t zone);
void zp_enable_layer(uint8_t layer);
void zp_enable_zone(uint8_t zone);

// Zoning utilities
uint8_t zp_led_to_zone(uint8_t led);
extern const uint8_t zp_zone_ranges[ZP_ZONES_NUM][2];
