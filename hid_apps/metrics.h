#pragma once

#include "printf.h"
#include <string.h>
#include <stdarg.h>

#define HID_APP_METRICS_SERVICE_ID 2

// top level methods
void hid_app_metrics_init(void);
bool hid_app_metrics_tick(void);
void hid_app_metrics_handler(hid_message_t* msg);

#define HID_APP_2_HANDLER hid_app_metrics_handler

// message handlers

enum hid_app_metrics_in {
    CONFIGURATION = 0,
    METRIC_REQUEST = 1,
};

enum hid_app_metrics_out {
    KEYBOARD_EVENT = 0,
    METRIC_EVENT = 1,
};


void hid_app_metrics_init(void) {

}

bool hid_app_metrics_tick(void) {
    return false;
}

void hid_app_metrics_handler(hid_message_t* msg) {
    switch(msg->header.mid) {
        case PRINT:
            hid_app_support_handle_os_name(msg->data[0]);
            break;
        default:
            break;
    }
}

typedef struct hid_app_metrics_keyboard_event {
    uint16_t keycode;
    uint16_t time;
    uint8_t col;
    uint8_t row;
    bool pressed;
    uint8_t layer;
} hid_app_metrics_keyboard_event; 

void hid_send_record(uint16_t keycode, keyrecord_t *record, uint8_t layer) {
    hid_app_metrics_keyboard_event event = {0};

    if(record != NULL) {
        event.keycode = keycode;
        event.time = record->event.time;
        event.col = record->event.key.col;
        event.row = record->event.key.row;
        event.pressed = record->event.pressed;
    }
    
    event.layer = layer;

    hid_message_t msg = {
        .header = { .sid = HID_APP_METRICS_SERVICE_ID, .mid = KEYBOARD_EVENT }
    };

    memset(&msg.data, 0, HID_MSG_DATA_LEN);
    memcpy(&msg.data, &event, sizeof(hid_app_metrics_keyboard_event));

    hid_send(&msg);
}
