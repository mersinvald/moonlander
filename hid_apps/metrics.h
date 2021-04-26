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
void hid_app_metrics_handle_configuration(hid_message_t* msg);
void hid_app_metrics_handle_metric_request(hid_message_t* msg);

// helhers
void hid_app_metrics_sync_metrics_all(void);
void hid_app_metrics_sync_metrics(uint8_t* metrics, size_t length, bool forced);
bool hid_app_metrics_sync_metric_into_msg(uint8_t metric, uint8_t pos_in_msg, hid_message_t* msg, bool forced);

enum hid_app_metrics_in {
    METRICS_CONFIGURATION = 0,
    METRIC_REQUEST = 1,
};

enum hid_app_metrics_out {
    MATRIX_EVENT = 0,
    METRIC_EVENT = 1,
    INPUT_EVENT = 2,
};

enum hid_app_metrics_metrics {
    METRIC_RANGE_START = 0,

    TICKS,

    METRIC_RANGE_END
};

#define METRICS_NUM (METRIC_RANGE_END - 1)

#if METRICS_NUM > 32
    #error "Only the maximum of 32 metrics is supported at the moment"
#endif

uint32_t hid_app_metrics_clean[METRICS_NUM];
uint32_t hid_app_metrics_dirty[METRICS_NUM];

#define METRIC_CLEAN(M) hid_app_metrics_clean[M-1]
#define METRIC_DIRTY(M) hid_app_metrics_dirty[M-1]

typedef struct __attribute__ ((__packed__)) hid_app_metrics_matrix_event {
    uint16_t keycode;
    uint16_t time;
    uint8_t col;
    uint8_t row;
    bool pressed;
    uint8_t layer;
} hid_app_metrics_matrix_event;

typedef struct __attribute__ ((__packed__)) hid_app_metrics_input_event {
    uint8_t keycode;
    bool pressed;
    uint16_t time;
} hid_app_metrics_input_event;

typedef struct __attribute__ ((__packed__)) hid_app_metrics_metric_event {
    uint8_t metric;
    uint32_t value;
} hid_app_metrics_metric_event;

typedef struct __attribute__ ((__packed__)) hid_app_metrics_configuration {
    uint8_t config;
    uint32_t metrics;
} hid_app_metrics_configuration;

#define MAX_METRICS_IN_MSG (HID_MSG_DATA_LEN / sizeof(hid_app_metrics_metric_event))

static uint8_t hid_app_metrics_config = 0;
static uint32_t hid_app_metrics_config_push = 0;

#define TELEMETRY_SNIFF_MATRIX (hid_app_metrics_config & 1)
#define TELEMETRY_SNIFF_LAYER ((hid_app_metrics_config >> 1) & 1)
#define TELEMETRY_SNIFF_INPUT ((hid_app_metrics_config >> 0x2) & 1)
#define TELEMETRY_PUSH_ALL ((hid_app_metrics_config >> 0x7) & 1)
#define TELEMETRY_PUSH_METRIC(M) ((hid_app_metrics_config_push >> M) & 1)

void hid_app_metrics_init(void) {
    memset(hid_app_metrics_clean, 0, METRICS_NUM * sizeof(uint32_t));
    memset(hid_app_metrics_dirty, 0, METRICS_NUM * sizeof(uint32_t));
}

bool hid_app_metrics_tick(void) {
    METRIC_DIRTY(TICKS) += 1;

    hid_app_metrics_sync_metrics_all();

    return false;
}

void hid_app_metrics_handler(hid_message_t* msg) {
    switch(msg->header.mid) {
        case METRICS_CONFIGURATION:
            hid_app_metrics_handle_configuration(msg);
            break;
        case METRIC_REQUEST:
            hid_app_metrics_handle_metric_request(msg);
            break;
        default:
            break;
    }
}

void hid_app_metrics_handle_configuration(hid_message_t* msg) {
    hid_app_metrics_configuration body;
    memcpy(&body, msg->data, sizeof(hid_app_metrics_configuration));

    hid_app_metrics_config = body.config;
    hid_app_metrics_config_push = body.metrics;

    #ifdef HID_DEBUG
    uprintf(
        "app = 'metrics', config = { "
        "sniff_matrix = %x, "
        "sniff_layer = %x, "
        "sniff_input = %x, "
        "push_all = %x, "
        "push_mask = %x",
        TELEMETRY_SNIFF_MATRIX,
        TELEMETRY_SNIFF_LAYER,
        TELEMETRY_SNIFF_INPUT,
        TELEMETRY_PUSH_ALL,
        hid_app_metrics_config_push
    );

    for(int i = METRIC_RANGE_START + 1; i < METRIC_RANGE_END; i++) {
        uprintf(", push_metric_%x = %s", i, TELEMETRY_PUSH_METRIC(i) ? "true" : "false");
    }

    uprintf(" }\n");
    #endif // HID_DEBUG
}

void hid_app_metrics_handle_metric_request(hid_message_t* msg) {
    uint8_t requests[HID_MSG_DATA_LEN];
    memcpy(&requests, &msg->data, HID_MSG_DATA_LEN);
    hid_app_metrics_sync_metrics(requests, HID_MSG_DATA_LEN, true);
}

void hid_send_matrix_event(uint16_t keycode, keyrecord_t *record, uint8_t layer) {
    hid_app_metrics_matrix_event event = {0};

    // If record exists, that's a matrix event,
    // Otherwise, the layer change event
    if(record != NULL) {
        if(!TELEMETRY_SNIFF_MATRIX) {
            return;
        }

        event.keycode = keycode;
        event.time = record->event.time;
        event.col = record->event.key.col;
        event.row = record->event.key.row;
        event.pressed = record->event.pressed;
    } else {
        if(!TELEMETRY_SNIFF_LAYER) {
            return;
        }
    }

    event.layer = layer;

    hid_message_t msg = {
        .header = { .sid = HID_APP_METRICS_SERVICE_ID, .mid = MATRIX_EVENT }
    };

    memset(&msg.data, 0, HID_MSG_DATA_LEN);
    memcpy(&msg.data, &event, sizeof(hid_app_metrics_matrix_event));

    hid_send(&msg);
}

void hid_send_layer_change_event(uint8_t layer) {
    hid_send_matrix_event(0, NULL, layer);
}

void hid_send_input_event(uint8_t keycode, bool pressed) {
    if(!TELEMETRY_SNIFF_INPUT) {
        return;
    }

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
    hid_send_input_event(keycode, true);
}

void hid_unregister_code(uint8_t keycode) {
    hid_send_input_event(keycode, false);
}

void hid_app_metrics_sync_metrics_all(void) {
    hid_app_metrics_sync_metrics(NULL, 0, TELEMETRY_PUSH_ALL);
}

void hid_app_metrics_sync_metrics(uint8_t* metrics, size_t length, bool forced) {
    hid_message_t msg = {
        .header = { .sid = HID_APP_METRICS_SERVICE_ID, .mid = METRIC_EVENT },
        .data = {0}
    };

    uint8_t pos_in_msg = 0;

    int start = 0;
    if(metrics == NULL) {
        length = METRIC_RANGE_END;
        start = METRIC_RANGE_START + 1;
    }

    for(int i = start; i < length; i++) {
        uint8_t metric = i;

        if(metrics != NULL) {
            metric = metrics[i];
        }

        // Skip if metric id is zero
        if(metric == METRIC_RANGE_START) {
            continue;
        }

        if(!TELEMETRY_PUSH_METRIC(metric) && !forced) {
            continue;
        }

        if(hid_app_metrics_sync_metric_into_msg(metric, pos_in_msg, &msg, forced)) {
            pos_in_msg++;
        }

        if(pos_in_msg == MAX_METRICS_IN_MSG) {
            hid_send(&msg);
            memset(&msg.data, 0, HID_MSG_DATA_LEN);
            pos_in_msg = 0;
        }
    }

    if(pos_in_msg != 0) {
        hid_send(&msg);
    }
}

bool hid_app_metrics_sync_metric_into_msg(uint8_t metric, uint8_t pos_in_msg, hid_message_t* msg, bool forced) {
    uint32_t value = METRIC_DIRTY(metric);
    if(value == METRIC_CLEAN(metric) && !forced) {
        return false;
    }

    hid_app_metrics_metric_event ev = {
        .metric = metric,
        .value = value
    };

    hid_app_metrics_metric_event* dst = ((hid_app_metrics_metric_event*) msg->data) + pos_in_msg;
    memcpy(dst, &ev, sizeof(hid_app_metrics_metric_event));

    METRIC_CLEAN(metric) = value;
    return true;
}
