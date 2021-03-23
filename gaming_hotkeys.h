#pragma once

#ifndef CUSTOM_SAFE_RANGE
  #error "You must specify variable CUSTOM_SAFE_RANGE for custom hotkeys keycodes."
#endif

enum gaming_hotkeys_keycodes {
  GAMING_HOTKEYS_START = CUSTOM_SAFE_RANGE,

  GAMING_HOTKEYS_NEW_SAFE_RANGE,
  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE GAMING_HOTKEYS_NEW_SAFE_RANGE
};

bool process_gaming_hotkeys(uint16_t keycode, keyrecord_t *record) {
  return true;
}
