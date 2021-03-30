#include "include.h"

void hid_send(hid_message_t* msg) {
    raw_hid_send((uint8_t*) msg, sizeof(hid_message_t));
}

void hid_receive(hid_message_t* msg) {
    #ifdef HID_DEBUG
    uprintf("hid_receive: sid=%x, mid=%x\n", msg->header.sid, msg->header.mid);
    #endif

    uint8_t sid = msg->header.sid;
    if(sid >= HID_APP_COUNT) {
        uprintf("sid(%x) is out of bounds(0..%x)\n", sid, HID_APP_COUNT);
        return;
    }

    switch(sid) {
        #ifdef HID_APP_0_HANDLER
        case 0:
            HID_APP_0_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_1_HANDLER
        case 1:
            HID_APP_1_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_2_HANDLER
        case 2:
            HID_APP_2_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_3_HANDLER
        case 3:
            HID_APP_3_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_4_HANDLER
        case 4:
            HID_APP_4_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_4_HANDLER
        case 4:
            HID_APP_4_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_4_HANDLER
        case 4:
            HID_APP_4_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_5_HANDLER
        case 5:
            HID_APP_5_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_6_HANDLER
        case 6:
            HID_APP_6_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_7_HANDLER
        case 7:
            HID_APP_7_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_8_HANDLER
        case 8:
            HID_APP_8_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_9_HANDLER
        case 9:
            HID_APP_9_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_10_HANDLER
        case 10:
            HID_APP_10_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_11_HANDLER
        case 11:
            HID_APP_11_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_12_HANDLER
        case 12:
            HID_APP_12_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_13_HANDLER
        case 13:
            HID_APP_13_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_14_HANDLER
        case 14:
            HID_APP_14_HANDLER(msg);
            break;
        #endif
        #ifdef HID_APP_15_HANDLER
        case 15:
            HID_APP_15_HANDLER(msg);
            break;
        #endif
        default:
            uprintf("no app to handle sid=%x\n", sid);
            break;
    }
}
