#pragma once

#include "config.h"

#ifndef CUSTOM_SAFE_RANGE
  #error "You must specify variable CUSTOM_SAFE_RANGE for custom hotkeys keycodes."
#endif

enum gaming_hotkeys_keycodes {
  GAMING_HOTKEYS_START = CUSTOM_SAFE_RANGE,

  BNRD_0,
  BNRD_1,
  BNRD_2,
  BNRD_3,
  BNRD_4,
  BNRD_5,
  BNRD_6,
  BNRD_7,
  BNRD_8,
  BNRD_TAB,
  BNRD_SPD,
  BNRD_RTS,

  GAMING_HOTKEYS_NEW_SAFE_RANGE,
  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE GAMING_HOTKEYS_NEW_SAFE_RANGE
};

static void tap_mod_shifted_key(uint8_t mod, uint8_t kc) {
  bool shifted = (get_mods() & MOD_BIT(mod)) > 0;
  if(shifted) unregister_code(mod);
  register_code(kc);
  unregister_code(kc);
  if(shifted) register_code(mod);
}

static bool bnrd_rts_mode = false;

bool process_gaming_hotkeys(uint16_t key, keyrecord_t *record) {
  bool alt = (get_mods() & MOD_MASK_ALT) > 0;
  uint8_t kc = 0;
  
  if(key >= BNRD_1 && key <= BNRD_8) {
    uint8_t offset = key - BNRD_1;
    uint8_t kc_num = KC_1 + offset;
    uint8_t kc_fun = KC_F1 + offset;
    kc = alt ? kc_fun : kc_num;

    if(record->event.pressed) {
      tap_mod_shifted_key(KC_LALT, kc);
    }
    
    return false;
  }

  switch (key) {
    case BNRD_0:
      kc = alt ? KC_F9 : KC_0;
      if(record->event.pressed) {
        tap_mod_shifted_key(KC_LALT, kc);
      }  
      return false;
      break;
    case BNRD_TAB:
      kc = alt ? KC_ESC : KC_TAB;
      if(alt && record->event.pressed) {
        tap_mod_shifted_key(KC_LALT, KC_ESC);
      } else if(record->event.pressed) {
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      return false;
      break;
    case BNRD_SPD:
      // ' -- toggle slow mo
      // [ -- toggle stop time
      kc = alt ? KC_QUOT : KC_LBRC;
      if(record->event.pressed) {
        tap_mod_shifted_key(KC_LALT, kc);
      }
      return false;
      break;
    case BNRD_RTS:
      // ] -- toggle free camera
      if(record->event.pressed) {
        if(bnrd_rts_mode) {
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
        } else {
          register_code(KC_RBRC);
          unregister_code(KC_RBRC);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
        }
      }
      return false;
      break;
  }

  return true;
}
