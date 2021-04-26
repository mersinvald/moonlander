/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#pragma once

#define ORYX_CONFIGURATOR
#define RGB_MATRIX_STARTUP_SPD 60

#define LANG_CHANGE_DEFAULT LANG_CHANGE_CAPS

#define COMBO_KEYS_COUNT 50
#define COMBO_MAX_SIZE 4
#define COMBO_STACK_MAX_SIZE 5
#define COMBO_WAIT_TIME 100

#define COLOR_PICTURE_DEFAULT 2

#define DISABLE_DEFAULT_ML_LEDS_LOGIC

#define KEYBOARD "moonlander"
#define USERNAME "mersinvald"
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

/* HID Apps */
#define HID_DEBUG
//#define HID_TRACE

#define HID_APP_SUPPORT_ENABLE true
#define HID_APP_COLOR_ENABLE true
#define HID_APP_METRICS_ENABLE true

/* RGB Lighting */
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_VAL_STEP 16

#include "config_zpainting.h"
