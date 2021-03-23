#pragma once

#ifndef CUSTOM_SAFE_RANGE
  #error "You must specify variable CUSTOM_SAFE_RANGE for custom hotkeys keycodes."
#endif

enum custom_hotkeys_keycodes {
  CUSTOM_HOTKEYS_START = CUSTOM_SAFE_RANGE,

  CT_A_C,
  CT_A_V,
  CT_A_X,
  CT_D,
  CT_SLSH,
  CT_Y,
  CT_Z,

  MY_FLSH,

  CUSTOM_HOTKEYS_NEW_SAFE_RANGE,
  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE CUSTOM_HOTKEYS_NEW_SAFE_RANGE
};

bool process_my_hotkeys(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CT_A_C:
      if (record->event.pressed) {
        shift_activate(0);
        register_code(KC_LCTRL);
        register_code(KC_A);
        unregister_code(KC_A);
        register_code(KC_C);
        unregister_code(KC_C);
        unregister_code(KC_LCTRL);
      }
      return false;
    case CT_A_V:
      if (record->event.pressed) {
        shift_activate(0);
        register_code(KC_LCTRL);
        register_code(KC_A);
        unregister_code(KC_A);
        register_code(KC_V);
        unregister_code(KC_V);
        unregister_code(KC_LCTRL);
      }
      return false;
    case CT_A_X:
      if (record->event.pressed) {
        shift_activate(0);
        register_code(KC_LCTRL);
        register_code(KC_A);
        unregister_code(KC_A);
        register_code(KC_X);
        unregister_code(KC_X);
        unregister_code(KC_LCTRL);
      }
      return false;
    case CT_D:
      if (record->event.pressed) {
        lang_activate(0);
        register_code(KC_LCTRL);
        register_code(KC_D);
      } else {
        unregister_code(KC_D);
        unregister_code(KC_LCTRL);
      }
      return false;
    case CT_Y:
      if (record->event.pressed) {
        shift_activate(0);
        register_code(KC_LCTRL);
        register_code(KC_Y);
      } else {
        unregister_code(KC_Y);
        unregister_code(KC_LCTRL);
      }
      return false;
    case CT_Z:
      if (record->event.pressed) {
        shift_activate(0);
        register_code(KC_LCTRL);
        register_code(KC_Z);
      } else {
        unregister_code(KC_Z);
        unregister_code(KC_LCTRL);
      }
      return false;
    case CT_SLSH:
      if (record->event.pressed) {
        lang_activate(0);
        register_code(KC_LCTRL);
        register_code(KC_SLSH);
      } else {
        unregister_code(KC_SLSH);
        unregister_code(KC_LCTRL);
      }
      return false;
    case MY_FLSH:
      if(record->event.pressed) {
          lang_activate(0);
          SEND_STRING("make " KEYBOARD ":" USERNAME ":flash");
          register_code(KC_ENT);
          unregister_code(KC_ENT);
          reset_keyboard();
      }
  }
  return true;
}
