#pragma once

#ifndef CUSTOM_SAFE_RANGE
  #error "You must specify variable CUSTOM_SAFE_RANGE for custom lang keycodes."
#endif

enum custom_lang_keycodes {
  CUSTOM_LANG_START = CUSTOM_SAFE_RANGE,

  EN_LTEQ, // <=
  EN_GTEQ, // >=
  EN_ARR1, // ->
  EN_ARR2, // =>
  AG_2B1,  // ()◀️
  EN_2B2,  // []◀️
  EN_2B3,  // {}◀️
  EN_2B4,  // <>◀️

  CUSTOM_LANG_NEW_SAFE_RANGE,
  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE CUSTOM_LANG_NEW_SAFE_RANGE
};

bool process_my_lang_keys(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EN_LTEQ:
      if (record->event.pressed) {
        lang_shift_tap_key(EN_LT);
        lang_shift_tap_key(AG_EQL);
      }
      return false;
      break;
    case EN_GTEQ:
      if (record->event.pressed) {
        lang_shift_tap_key(EN_GT);
        lang_shift_tap_key(AG_EQL);
      }
      return false;
      break;
    case EN_ARR1:
      if (record->event.pressed) {
        lang_shift_tap_key(AG_MINS);
        lang_shift_tap_key(EN_GT);
      }
      return false;
      break;
    case EN_ARR2:
      if (record->event.pressed) {
        lang_shift_tap_key(AG_EQL);
        lang_shift_tap_key(EN_GT);
      }
      return false;
      break;
    case AG_2B1:
      if (record->event.pressed) {
        lang_shift_tap_key(AG_LPRN);
        lang_shift_tap_key(AG_RPRN);
        register_code(KC_LEFT); unregister_code(KC_LEFT);
      }
      return false;
      break;
    case EN_2B2:
      if (record->event.pressed) {
        lang_shift_tap_key(EN_LBRC);
        lang_shift_tap_key(EN_RBRC);
        register_code(KC_LEFT); unregister_code(KC_LEFT);
      }
      return false;
      break;
    case EN_2B3:
      if (record->event.pressed) {
        lang_shift_tap_key(EN_LCBR);
        lang_shift_tap_key(EN_RCBR);
        register_code(KC_LEFT); unregister_code(KC_LEFT);
      }
      return false;
      break;
    case EN_2B4:
      if (record->event.pressed) {
        lang_shift_tap_key(EN_LT);
        lang_shift_tap_key(EN_GT);
        register_code(KC_LEFT); unregister_code(KC_LEFT);
      }
      return false;
      break;
  }
  return true;
}


