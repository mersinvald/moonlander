#include <string.h>
#include <lib/lib8tion/lib8tion.h>

#include "config.h"
#include "include.h"
#include "keys.h"

const rgba* zp_layers[ZP_DYN_LAYERS_NUM];
bool zp_disable_map[ZP_LAYERS_NUM][ZP_ZONES_NUM];
rgba zp_background[ZP_ZONES_NUM];
bool zp_repaint_flag = true;
uint8_t zp_led_hits = 0;
uint8_t zp_background_val = ZP_BACKGROUND_VAL;

void zp_init(void) {
    for(int i = 0; i < ZP_DYN_LAYERS_NUM; i++) {
        zp_layers[i] = NULL;
    }
    memset(zp_disable_map, 0, zp_disable_map_size);
    zp_repaint();
}

void zp_repaint(void) {
    zp_repaint_flag = true;
    zp_led_hits = 0;
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

void zp_background_increase_val(void) {
    zp_background_val = qadd8(zp_background_val, RGB_MATRIX_VAL_STEP);
    zp_repaint();
}

void zp_background_decrease_val(void) {
    zp_background_val = qsub8(zp_background_val, RGB_MATRIX_VAL_STEP);
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

bool zp_process_record(uint16_t key, keyrecord_t *record) {
    bool shifted = get_mods() & MOD_MASK_SHIFT;

    switch (key) {
    case ZP_VAI:
        if (!record->event.pressed) {
            if(shifted) {
                rgb_matrix_increase_val();
            } else {
                zp_background_increase_val();
            }
        }
        return false;
        break;
    case ZP_VAD:
        if (!record->event.pressed) {
            if(shifted) {
                rgb_matrix_decrease_val();
            } else {
                zp_background_decrease_val();
            }
        }
        return false;
        break;
    default:
        break;
   }
   return true;
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
