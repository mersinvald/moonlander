#pragma once

#include "printf.h"
#include <string.h>
#include <stdarg.h>

#define HID_APP_SUPPORT_SERVICE_ID 0

// top level methods
void hid_app_support_init(void);
bool hid_app_support_tick(void);
void hid_app_support_handler(hid_message_t* msg);

#define HID_APP_0_HANDLER hid_app_support_handler

// message handlers
void hid_app_support_handle_configuration(hid_message_t* msg);
void hid_app_support_handle_keepalive(void);

// extensions of hid_ namespace
void hid_putsn(const char* s, size_t length);
void hid_printf(const char* fmt, ...);

enum hid_app_support_in {
    SUPPORT_CONFIGURATION = 0,
    KEEPALIVE = 1,
};

enum hid_app_support_out {
    PRINT = 0,
};

enum hid_app_support_os_name {
    UNKNOWN = 0,
    LINUX = 1,
    WINDOWS = 2,
    MACOS = 3,
};


void hid_app_support_init(void) {

}

static uint16_t hid_app_support_keepalive_timeout = 0;
static uint16_t hid_app_last_keepalive_time;
extern bool hid_enabled;

bool hid_app_support_tick(void) {
    if(timer_elapsed(hid_app_last_keepalive_time) > hid_app_support_keepalive_timeout) {
        hid_enabled = false;
    }
    return false;
}

void hid_app_support_handler(hid_message_t* msg) {
    switch(msg->header.mid) {
        case SUPPORT_CONFIGURATION:
            hid_app_support_handle_configuration(msg);
            break;
        case KEEPALIVE:
            hid_app_support_handle_keepalive();
            break;
        default:
            break;
    }
}

typedef struct __attribute__ ((__packed__)) hid_app_support_configuration {
    uint16_t keepalive_timeout;
    uint8_t  os_name;
} hid_app_support_configuration;

extern bool lang_current_change_manually_set;

void hid_app_support_handle_configuration(hid_message_t* msg) {
    hid_app_support_configuration body;
    memcpy(&body, msg->data, sizeof(hid_app_support_configuration));

    #ifdef HID_DEBUG
    uprintf("app = 'support', config = { keepalive_timeout = %u, os_name = %x }\n", body.keepalive_timeout, body.os_name);
    #endif // HID_DEBUG


    hid_app_support_keepalive_timeout = body.keepalive_timeout;

    if(lang_current_change_manually_set) return;
    switch(body.os_name) {
        case LINUX:
        case MACOS:
            lang_current_change = LANG_CHANGE_CAPS;
            break;
        case WINDOWS:
            lang_current_change = LANG_CHANGE_ALT_SHIFT;
            break;
        default:
            break;
    }
}

void hid_app_support_handle_keepalive(void) {
    hid_app_last_keepalive_time = timer_read();
    hid_enabled = true;
}

void hid_putsn(const char* s, size_t length) {
    hid_message_t msg = {
        .header = { .sid = HID_APP_SUPPORT_SERVICE_ID, .mid = PRINT }
    };

    int result = length;
    int send_out = HID_MSG_DATA_LEN;
    const char* buf = s;

    while(result > 0) {
        if (result < HID_MSG_DATA_LEN) {                      // If remaining bytes are less than console epsize
            memset(&msg.data, 0, HID_MSG_DATA_LEN);  // Clear the buffer
            send_out = result;                              // Send remaining size
        }

        memcpy(&msg.data, buf, send_out);

        hid_send(&msg);

        result -= send_out;
        buf += send_out;
    }
}

#include "support_hid_printf.h"
