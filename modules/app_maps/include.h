#pragma once

#ifndef CUSTOM_SAFE_RANGE
  #error "You must specify variable CUSTOM_SAFE_RANGE for color extension."
#endif

#ifndef APP_KEYS_COUNT
  #define APP_KEYS_COUNT 30
#endif

enum app_keycodes {
  APP_START = CUSTOM_SAFE_RANGE,

  #include "keycodes.h"

  APP_SAFE_RANGE,

  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE APP_SAFE_RANGE
}

