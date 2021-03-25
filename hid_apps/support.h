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
void hid_app_support_handle_os_name(uint8_t desc);

// extensions of hid_ namespace
void hid_putsn(const char* s, size_t length);
void hid_printf(const char* fmt, ...);

enum hid_app_support_in {
    OS_NAME = 0,
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

bool hid_app_support_tick(void) {
    return false;
}

void hid_app_support_handler(hid_message_t* msg) {
    switch(msg->header.mid) {
        case PRINT:
            hid_app_support_handle_os_name(msg->data[0]);
            break;
        default:
            break;
    }
}

void hid_app_support_handle_os_name(uint8_t desc) {
    if(lang_current_change_manually_set) return;
    switch(desc) {
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
