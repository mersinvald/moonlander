RGB_MATRIX_EFFECT(ZPAINTING)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "include.h"

// TODO: make some benchmarks, find out if z-culling is needed
// TODO: fade-in-like animation for color shift

extern uint8_t zp_led_hits;

static rgba zp_effect_buffer[DRIVER_LED_TOTAL];

#define ZP_MATRIX_ZONE_LIMITS(rgb_min, rgb_max, zone, min, max) \
    uint8_t min = zp_zone_ranges[zone][0]; \
    uint8_t max = zp_zone_ranges[zone][1]; \
    if(rgb_min > min) min = rgb_min; \
    if(rgb_max < max) max = rgb_max;


void zp_effect_draw_background(uint8_t led_min, uint8_t led_max) {
    const float BRIGTNESS_FACTOR = (float) zp_background_val / 255.0;
    const rgba off = ZP_OFF;

    for(int zone = 0; zone < ZP_ZONES_NUM; zone++) {
        ZP_MATRIX_ZONE_LIMITS(led_min, led_max, zone, min, max);

        // If zone starts higher, then the led_max limit
        if(min > max) continue;

        rgba color = zp_background[zone];
        color.r *= BRIGTNESS_FACTOR;
        color.g *= BRIGTNESS_FACTOR;
        color.b *= BRIGTNESS_FACTOR;

        if(zp_disable_map[ZP_LAYER_BACKGROUND][zone]) {
            color = off;
        }

        rgba* it = zp_effect_buffer + min;
        rgba* end = zp_effect_buffer + max;

        for(; it != end; ++it) {
            *it = color;
        }
    }
}

static inline void zp_effect_draw_pixel(uint8_t led, const rgba* layer) {
    rgba bg = zp_effect_buffer[led];
    rgba fg = layer[led];
    rgba out;

    float alpha = (float) fg.a / 255;
    float oneminusalpha = 1.0 - alpha;

    out.r = (fg.r * alpha) + (oneminusalpha * bg.r);
    out.g = (fg.g * alpha) + (oneminusalpha * bg.g);
    out.b = (fg.b * alpha) + (oneminusalpha * bg.b);

    zp_effect_buffer[led] = out;
}

void zp_effect_draw_layer(uint8_t led_min, uint8_t led_max, int dyn_lid) {
    int lid = dyn_lid + 1;

    const rgba* layer = zp_layers[dyn_lid];
    if(layer == NULL) return;

    for(int zone = 0; zone < ZP_ZONES_NUM; zone++) {
        if(zp_disable_map[lid][zone]) continue;

        ZP_MATRIX_ZONE_LIMITS(led_min, led_max, zone, min, max);

        // If zone starts higher, then the led_max limit
        if(min > max) continue;

        for(uint8_t i = min; i < max; i++) {
            zp_effect_draw_pixel(i, layer);
        }
    }
}

void zp_effect_init(void) {
    memset(zp_effect_buffer, 0, DRIVER_LED_TOTAL * sizeof(rgba));
    zp_repaint();
}

bool ZPAINTING(effect_params_t* params) { 
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if(params->init) {
        zp_effect_init();
    }

    if(zp_repaint_flag) {
        zp_led_hits += led_max - led_min;
        zp_effect_draw_background(led_min, led_max);
        for(int layer = 0; layer < ZP_DYN_LAYERS_NUM; layer++) {
            zp_effect_draw_layer(led_min, led_max, layer);
        }
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        rgba c = zp_effect_buffer[i];
        float f = (float) rgb_matrix_config.hsv.v / 255;
        rgb_matrix_set_color(i, c.r * f, c.g * f, c.b * f);
    }

    // Shutdown the repaint job when all LEDs been painted
    if(zp_led_hits >= DRIVER_LED_TOTAL) {
        zp_repaint_flag = false;
    }

    return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
