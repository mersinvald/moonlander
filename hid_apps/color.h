#pragma once

#include <string.h>

#include "../modules/zpainting/include.h"
#include "../config.h"

#define HID_APP_COLOR_SERVICE_ID 1

// top level methods
void hid_app_color_init(void);
bool hid_app_color_tick(void);
void hid_app_color_handler(hid_message_t* msg);

#define HID_APP_1_HANDLER hid_app_color_handler

// message handlers
void hid_app_color_handle_set_key_colors(hid_message_t* msg);
void hid_app_color_handle_clear(hid_message_t* msg);

enum hid_app_color_in {
    SET_KEY_COLORS = 0,
    COLOR_CLEAR = 1,
};

typedef struct __attribute__ ((__packed__)) key_color {
    uint8_t led;
    rgba color;
} key_color;

typedef struct __attribute__ ((__packed__)) set_key_colors {
    uint8_t length;
    key_color updates[6];
} set_key_colors;

static rgba hid_app_color_led_buffer[DRIVER_LED_TOTAL] = { ZP_TRANS };

void hid_app_color_init(void) {
    zp_set_layer(ZP_LAYER_HOST, (const rgba*) &hid_app_color_led_buffer);
}

bool hid_app_color_tick(void) {
    return false;
}

void hid_app_color_handler(hid_message_t* msg) {
    switch(msg->header.mid) {
        case SET_KEY_COLORS:
            hid_app_color_handle_set_key_colors(msg);
            break;
        case COLOR_CLEAR:
            hid_app_color_handle_clear(msg);
            break;
        default:
            break;
    }
}

void hid_app_color_handle_set_key_colors(hid_message_t* msg) {
    set_key_colors body;
    memcpy(&body, msg->data, sizeof(set_key_colors));

    for(uint8_t i = 0; i < body.length; i++) {
        key_color update = body.updates[i];
        uint8_t led = update.led;
        rgba color = update.color;
        //uprintf("color: led %x = rgba(%x, %x, %x, %x)\n", led, color.r, color.g, color.b, color.a);
        hid_app_color_led_buffer[led] = color;
    }

    zp_repaint();
}

void hid_app_color_handle_clear(hid_message_t* msg) {
    rgba color;
    memcpy(&color, msg->data, sizeof(rgba));

    for(int i = 0; i < DRIVER_LED_TOTAL; i++) {
        hid_app_color_led_buffer[i] = color;
    }

    zp_repaint();
}