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
    MATRIX_EVENT = 0,
    METRIC_EVENT = 1,
    INPUT_EVENT = 2,
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

#pragma pack(push, 1)
typedef struct hid_app_metrics_matrix_event {
    uint16_t keycode;
    uint16_t time;
    uint8_t col;
    uint8_t row;
    bool pressed;
    uint8_t layer;
} hid_app_metrics_matrix_event; 

typedef struct hid_app_metrics_input_event {
    uint8_t keycode;
    bool pressed;
    uint16_t time;
} hid_app_metrics_input_event;
#pragma pack(pop)

void hid_send_record(uint16_t keycode, keyrecord_t *record, uint8_t layer) {
    hid_app_metrics_matrix_event event = {0};

    if(record != NULL) {
        event.keycode = keycode;
        event.time = record->event.time;
        event.col = record->event.key.col;
        event.row = record->event.key.row;
        event.pressed = record->event.pressed;
    }
    
    event.layer = layer;

    hid_message_t msg = {
        .header = { .sid = HID_APP_METRICS_SERVICE_ID, .mid = MATRIX_EVENT }
    };

    memset(&msg.data, 0, HID_MSG_DATA_LEN);
    memcpy(&msg.data, &event, sizeof(hid_app_metrics_matrix_event));

    hid_send(&msg);
}

void hid_app_metrics_send_input_event(uint8_t keycode, bool pressed) {
    hid_app_metrics_input_event event = {
        .keycode = keycode,
        .pressed = pressed,
        .time = timer_read(),
    };

    hid_message_t msg = {
        .header = { .sid = HID_APP_METRICS_SERVICE_ID, .mid = INPUT_EVENT }
    };

    memset(&msg.data, 0, HID_MSG_DATA_LEN);
    memcpy(&msg.data, &event, sizeof(hid_app_metrics_input_event));

    hid_send(&msg);
}

void hid_register_code(uint8_t keycode) {
    hid_app_metrics_send_input_event(keycode, true);
}

void hid_unregister_code(uint8_t keycode) {
    hid_app_metrics_send_input_event(keycode, false);
}
