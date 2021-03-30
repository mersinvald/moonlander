#pragma once
#include "raw_hid.h"

#define HID_APP_COUNT 16
#define HID_MSG_ID_LIMIT 16
#define HID_MSG_BUF_SIZE 8

#define HID_MSG_DATA_LEN RAW_EPSIZE - sizeof(hid_header_t)

#pragma pack(push, 1)
typedef struct header {
    uint8_t mid : 4;
    uint8_t sid : 4;
} hid_header_t;

typedef struct message {
    hid_header_t header;
    uint8_t data[HID_MSG_DATA_LEN];
} hid_message_t;
#pragma pack(pop)

void hid_send(hid_message_t* msg);
void hid_receive(hid_message_t* msg);
