#include <string.h>

#include "include.h"
#include "keys.h"

const rgba* zp_layers[ZP_DYN_LAYERS_NUM];
bool zp_disable_map[ZP_LAYERS_NUM][ZP_ZONES_NUM];
rgba zp_background[ZP_ZONES_NUM];
bool zp_repaint_flag = true;

void zp_init(void) {
    for(int i = 0; i < ZP_DYN_LAYERS_NUM; i++) {
        zp_layers[i] = NULL;
    }
    memset(zp_disable_map, 0, zp_disable_map_size);
    zp_repaint();
}

void zp_set_layer(uint8_t layer, const rgba* buffer) {
    uint8_t dyn = ZP_LAYER_NUM_TO_DYN_LAYER_NUM(layer);

    if(dyn > layer) {
        uprintf("Cannot set Z_LAYER buffer for Z_LAYER_0: " \
                "user z_layers must start with Z_LAYER_1\n");
    }

    if(dyn >= ZP_DYN_LAYERS_NUM) {
        uprintf("ZP_LAYER INDEX OVERFLOW\n");
    }

    zp_layers[dyn] = buffer;
    zp_repaint();
}

void zp_set_background_at_zone(uint8_t zone, rgba color) {
    zp_background[zone] = color;
    zp_repaint();
}

void zp_set_background(rgba color) {
    for(int i = 0; i < ZP_ZONES_NUM; i++) {
        zp_set_background_at_zone(i, color);
    }
    zp_repaint();
}

void zp_disable_layer_at_zone(uint8_t layer, uint8_t zone) {
    zp_disable_map[layer][zone] = true;
    zp_repaint();
}

void zp_disable_layer(uint8_t layer) {
    memset(zp_disable_map[layer], true, ZP_ZONES_NUM);
    zp_repaint();
}

void zp_disable_zone(uint8_t zone) {
    for(int i = 0; i < ZP_LAYERS_NUM; i++) {
        zp_disable_map[i][zone] = true;
    }
    zp_repaint();
}

void zp_enable_layer_at_zone(uint8_t layer, uint8_t zone) {
    zp_disable_map[layer][zone] = false;
    zp_repaint();
}

void zp_enable_layer(uint8_t layer) {
    memset(zp_disable_map[layer], false, ZP_ZONES_NUM);
    zp_repaint();
}

void zp_enable_zone(uint8_t zone) {
    for(int i = 0; i < ZP_LAYERS_NUM; i++) {
        zp_disable_map[i][zone] = false;
    }
    zp_repaint();
}

uint8_t zp_led_to_zone(uint8_t led) {
    #if ZP_ZONES_NUM >= 1
    if(led >= ZP_ZONE_0_MIN && led < ZP_ZONE_0_MAX) return 0;
    #endif

    #if ZP_ZONES_NUM >= 2
    if(led >= ZP_ZONE_1_MIN && led < ZP_ZONE_1_MAX) return 1;
    #endif

    #if ZP_ZONES_NUM >= 3
    if(led >= ZP_ZONE_2_MIN && led < ZP_ZONE_2_MAX) return 2;
    #endif

    #if ZP_ZONES_NUM >= 4
    if(led >= ZP_ZONE_3_MIN && led < ZP_ZONE_3_MAX) return 3;
    #endif

    #if ZP_ZONES_NUM >= 5
    if(led >= ZP_ZONE_4_MIN && led < ZP_ZONE_4_MAX) return 4;
    #endif

    #if ZP_ZONES_NUM >= 6
    if(led >= ZP_ZONE_5_MIN && led < ZP_ZONE_5_MAX) return 5;
    #endif

    #if ZP_ZONES_NUM >= 7
    if(led >= ZP_ZONE_6_MIN && led < ZP_ZONE_6_MAX) return 6;
    #endif

    #if ZP_ZONES_NUM >= 8
    if(led >= ZP_ZONE_7_MIN && led < ZP_ZONE_7_MAX) return 7;
    #endif

    // fallback to zone 0
    return 0;
}

const uint8_t zp_zone_ranges[ZP_ZONES_NUM][2] = {
#if ZP_ZONES_NUM >= 1
    { ZP_ZONE_0_MIN, ZP_ZONE_0_MAX },
#endif
#if ZP_ZONES_NUM >= 2
    { ZP_ZONE_1_MIN, ZP_ZONE_1_MAX },
#endif
#if ZP_ZONES_NUM >= 3
    { ZP_ZONE_2_MIN, ZP_ZONE_2_MAX },
#endif
#if ZP_ZONES_NUM >= 4
    { ZP_ZONE_3_MIN, ZP_ZONE_3_MAX },
#endif
#if ZP_ZONES_NUM >= 5
    { ZP_ZONE_3_MIN, ZP_ZONE_3_MAX },
#endif
#if ZP_ZONES_NUM >= 6
    { ZP_ZONE_3_MIN, ZP_ZONE_3_MAX },
#endif
#if ZP_ZONES_NUM >= 7
    { ZP_ZONE_3_MIN, ZP_ZONE_3_MAX },
#endif
#if ZP_ZONES_NUM >= 8
    { ZP_ZONE_3_MIN, ZP_ZONE_3_MAX },
#endif
};
