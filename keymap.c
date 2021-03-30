#include QMK_KEYBOARD_H
#include <quantum/pointing_device.h>
#include "version.h"
#include "raw_hid.h"
#include <string.h>

#include "modules/arbitrary_keycode/include.h"

#define CUSTOM_SAFE_RANGE ML_SAFE_RANGE
#include "modules/lang_shift/include.h"
#include "modules/combo/include.h"
#include "modules/tt/include.h"
// #include "repeat/include.h"

/* ZPainting */
#include "modules/zpainting/include.h"
#include "modules/zpainting/impl.c"

/* HID apps configuration */
#include "modules/hid_client/include.h" // include definitions required for apps
#include "hid_apps.h"                   // register apps
#include "modules/hid_client/impl.c"    // hid-client implementation

extern bool mcp23018_leds[3];

enum custom_keycodes {
  KEYCODES_START = CUSTOM_SAFE_RANGE,

  // Wow, such empty

  NEW_NEW_SAFE_RANGE,
  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE NEW_NEW_SAFE_RANGE
};

#define MY_layout( \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, k16, \
    k20, k21, k22, k23, k24, k25, k26, \
    k30, k31, k32, k33, k34, k35,      \
    k40, k41, k42, k43, k44,           \
    k53, \
    k50, k51, k52, \
    \
    k60, k61, k62, k63, k64, k65, k66, \
    k70, k71, k72, k73, k74, k75, k76, \
    k80, k81, k82, k83, k84, k85, k86, \
    k91, k92, k93, k94, k95, k96, \
    ka2, ka3, ka4, ka5, ka6, \
    kb3,\
    kb4, kb5, kb6 \
) \
LAYOUT_moonlander( \
    k00, k01, k02, k03, k04, k05, k06,   k60, k61, k62, k63, k64, k65, k66, \
    k10, k11, k12, k13, k14, k15, k16,   k70, k71, k72, k73, k74, k75, k76, \
    k20, k21, k22, k23, k24, k25, k26,   k80, k81, k82, k83, k84, k85, k86, \
    k30, k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95, k96, \
    k40, k41, k42, k43, k44,      k53,   kb3,      ka2, ka3, ka4, ka5, ka6, \
                        k50, k51, k52,   kb4, kb5, kb6 \
)

// Toggle layer color
#define RGB_LYR TOGGLE_LAYER_COLOR

// Shift keys
#define SH_TAB S(KC_TAB)

// Ctrl+Shift keys
#define CS_T LCTL(S(KC_T))
#define CS_K LCTL(S(KC_K))
#define CS_M LCTL(S(KC_M))
#define CS_P LCTL(S(KC_P))

// Alt keys
#define AL_UP LALT(KC_UP)
#define AL_PSCR LALT(KC_PSCR)

// Gui keys
#define WN_1 LGUI(KC_1)
#define WN_2 LGUI(KC_2)
#define WN_3 LGUI(KC_3)
#define WN_4 LGUI(KC_4)
#define WN_5 LGUI(KC_5)
#define WN_6 LGUI(KC_6)
#define WN_7 LGUI(KC_7)
#define WN_8 LGUI(KC_8)
#define WN_9 LGUI(KC_9)
#define WN_F1 LGUI(KC_F1)
#define WN_F2 LGUI(KC_F2)
#define WN_F3 LGUI(KC_F3)
#define WN_Q LGUI(KC_Q)
#define WN_L LGUI(KC_L)

// Ctrl keys
#define CT_LEFT LCTL(KC_LEFT)
#define CT_UP LCTL(KC_UP)
#define CT_DOWN LCTL(KC_DOWN)
#define CT_RGHT LCTL(KC_RGHT)
#define CT_ENT LCTL(KC_ENT)
#define CT_BSPC LCTL(KC_BSPC)
#define CT_1 LCTL(KC_1)
#define CT_2 LCTL(KC_2)
#define CT_T LCTL(KC_T)
#define CT_W LCTL(KC_W)
#define CT_J LCTL(KC_J)
#define CT_G LCTL(KC_G)
#define CT_S LCTL(KC_S)
#define CT_F LCTL(KC_F)
#define CT_A LCTL(KC_A)
#define CT_S LCTL(KC_S)
#define CT_F5 LCTL(KC_F5)
#define CT_PGUP LCTL(KC_PGUP)
#define CT_PGDN LCTL(KC_PGDN)
#define CT_X LCTL(KC_X)
#define CT_C LCTL(KC_C)
#define CT_V LCTL(KC_V)
#define CT_PLUS LCTL(KC_EQL)
#define CT_MINS LCTL(KC_MINS)
#define CT_BSLS LCTL(KC_BSLS)

#define RGB_LYR TOGGLE_LAYER_COLOR

// Chords
// Left Index
#define CMB_CTC CMB_000
#define CMB_CTV CMB_001

// Shifted Left Index
#define CMB_CAC CMB_002
#define CMB_CAV CMB_003

// Right Index
#define CMB_CTS CMB_004
#define CMB_CMSP CMB_005

// Left Thumb
#define CMB_SFT CMB_006
#define CMB_BSP CMB_007
#define CMB_ENT CMB_008
#define CMB_CTL CMB_009

// Right Thumb
#define CMB_LAN CMB_010
#define CMB_DOT CMB_011
#define CMB_SPC CMB_012
#define CMB_ALT CMB_013

// Russian index keys on letters
#define CMS_R CMB_014
#define CMS_T CMB_015
#define CMS_S_R CMB_016
#define CMS_ST CMB_017

// Brackets on red layer, order: 1 - (), 2 - [], 3 - {}, 4 - <>
#define CMB_LB1 CMB_018
#define CMB_RB1 CMB_019
#define CMB_LB2 CMB_020
#define CMB_RB2 CMB_021
#define CMB_LB3 CMB_022
#define CMB_RB3 CMB_023
#define CMB_LB4 CMB_024
#define CMB_RB4 CMB_025

#define TT_CTJ TT_000


// Подключаем обработку кастомных кейкодов
#include "custom_lang.h"
#include "custom_hotkeys.h"
#include "gaming_hotkeys.h"
#include "moonlander_leds.h"
#include "mouse_pixel_move.h"
#include "song_keys.h"

enum Layers {
  L_EN = 0,
  L_EN_S,

  L_RU,
  L_RU_S,

  // Editing, text navigation, brackets
  L_RED,

  // Keyboard management layer
  L_YELLOW,

  // Base gaming layout
  L_GAME
};

#define TG_RED  TG(L_RED)
#define TG_YELL TG(L_YELLOW)
#define TG_GAME TG(L_GAME)

#define MO_RED  MO(L_RED)
#define MO_YELL MO(L_YELLOW)

#define TT_RED  (TT_000 + L_RED)
#define TT_YELL (TT_000 + L_YELLOW)

// Этот макрос нужен, чтобы задавать одинаковые слои (в том числе и шифтовый слой) для английского и русского языка. В итоге их отличия будут только в буквах.
#define LANG_TWO_LAYERS(\
  L_DEFAULT, L_SHIFT,\
  \
  /* Left hand */ \
       LU1, LU2, LU3, LU4, LU5, \
       LH1, LH2, LH3, LH4, LH5, \
       LD1, LD2, LD3, LD4, LD5, \
  /* Right hand */ \
  RU1, RU2, RU3, RU4, RU5, \
  RH1, RH2, RH3, RH4, RH5, RH6, \
  RD1, RD2, RD3, RD4, RD5, RD6, \
  \
  /* ---------------------------- Shift layer ---------------------------- */ \
  /* Left hand */ \
        SLU1, SLU2, SLU3, SLU4, SLU5, \
        SLH1, SLH2, SLH3, SLH4, SLH5, \
        SLD1, SLD2, SLD3, SLD4, SLD5, \
  /* Right hand */ \
  SRU1, SRU2, SRU3, SRU4, SRU5, \
  SRH1, SRH2, SRH3, SRH4, SRH5, SRH6, \
  SRD1, SRD2, SRD3, SRD4, SRD5, SRD6 \
) \
  /*-------------------------------------------------------------------------*/ \
  [L_DEFAULT] = MY_layout( \
    /* LEFT HALF */ \
    KC_ESC,  AG_PLUS, AG_SCLN, EN_GRV,  AG_COLN, AG_EQL,  EN_AT, \
    AG_UNDS, LU1,     LU2,     LU3,     LU4,     LU5,     CMB_CTC, \
    AG_DQUO, LH1,     LH2,     LH3,     LH4,     LH5,     CMB_CTV, \
    EN_QUOT, LD1,     LD2,     LD3,     LD4,     LD5, \
    CT_J,    TT_YELL, CT_SLSH, XXXXXXX, XXXXXXX, \
    CMB_CTL, /* LEFT RED THUMB KEY */ \
    CMB_SFT, CMB_BSP, CMB_ENT, /* LEFT THUMB KEYS */ \
    \
    /* RIGHT HALF */ \
    CT_D,    AG_ASTR, AG_EXCL, AG_QUES, EN_HASH, AG_SLSH, CT_Z, \
    CMB_CTS, RU1,     RU2,     RU3,     RU4,     RU5,     AG_MINS, \
    CMB_CMSP,RH1,     RH2,     RH3,     RH4,     RH5,     RH6, \
             RD1,     RD2,     RD3,     RD4,     RD5,     RD6, \
                      TT_RED,  AG_BSLS, XXXXXXX, TG_GAME, XXXXXXX, \
                      CMB_ALT, /* RIGHT RED THUMB KEY */ \
                      CMB_LAN, CMB_DOT, CMB_SPC /* RIGHT THUMB KEYS */ \
  ), \
  \
  /*-------------------------------------------------------------------------*/ \
  [L_SHIFT] = MY_layout( \
    /* LEFT HALF */ \
    _______, AG_7,    AG_5,    AG_3,    AG_1,    AG_9,    EN_CIRC, \
    _______, SLU1,    SLU2,    SLU3,    SLU4,    SLU5,    CMB_CAC, \
    EN_AMPR, SLH1,    SLH2,    SLH3,    SLH4,    SLH5,    CMB_CAV, \
    EN_PIPE, SLD1,    SLD2,    SLD3,    SLD4,    SLD5, \
    _______, _______, _______, _______, _______, \
    _______, /* LEFT RED THUMB KEY */ \
    _______, _______, _______, /* LEFT THUMB KEYS */ \
    \
    /* RIGHT HALF */ \
    RU_NUME, AG_0,    AG_2,    AG_4,    AG_6,    AG_8,    CT_Y, \
    _______, SRU1,    SRU2,    SRU3,    SRU4,    SRU5,    _______, \
    _______, SRH1,    SRH2,    SRH3,    SRH4,    SRH5,    SRH6, \
             SRD1,    SRD2,    SRD3,    SRD4,    SRD5,    SRD6, \
                      _______, AG_PERC, _______, _______, _______, \
                      _______, /* RIGHT RED THUMB KEY */ \
                      _______, _______, _______ /* RIGHT THUMB KEYS */ \
  ),

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //---------------------------------------------------------------------------
  LANG_TWO_LAYERS(
    L_EN, L_EN_S,

    /* Left hand */
             KC_GRV,  EN_X,    EN_Y,    EN_P,    EN_S_I,
             EN_A,    EN_O,    EN_E,    EN_U,    EN_I,
             XXXXXXX, EN_Q,    EN_J,    EN_K,    KC_CIRC,

    /* Right hand */
    EN_F,    EN_G,    EN_C,    EN_R,    EN_L,
    EN_D,    EN_H,    EN_T,    EN_N,    EN_S,    AG_SLSH,
    EN_B,    EN_M,    EN_W,    EN_V,    EN_Z,    KC_TILD,

    /* ---------------------------- Shift layer ---------------------------- */
    /* Left hand */
             KC_GRV,   EN_S_X,  EN_S_Y,  EN_S_P,  EN_S_I,
             EN_S_A,   EN_S_O,  EN_S_E,  EN_S_U,  EN_S_I,
             _______,  EN_S_Q,  EN_S_J,  EN_S_K,  KC_CIRC,

    /* Right hand */
    EN_S_F,  EN_S_G,  EN_S_C,  EN_S_R,  EN_S_L,
    EN_S_D,  EN_S_H,  EN_S_T,  EN_S_N,  EN_S_S,  _______,
    EN_S_B,  EN_S_M,  EN_S_W,  EN_S_V,  EN_S_Z,  _______
  )

  //---------------------------------------------------------------------------
  LANG_TWO_LAYERS(
    L_RU, L_RU_S,

    /* Left hand */
             RU_J,    RU_TS,   RU_U,    RU_K,    RU_JE,
             RU_F,    RU_Y,    RU_V,    RU_A,    RU_P,
             RU_JA,   RU_CH,   RU_S,    RU_M,    RU_I,

    /* Right hand */
    RU_N,    RU_G,    RU_SH,   RU_SC,   RU_Z,
    CMS_R,   RU_O,    RU_L,    RU_D,    RU_ZH,   RU_E,
    CMS_T,   RU_SF,   RU_B,    RU_JU,   RU_H,    RU_JO,

    /* ---------------------------- Shift layer ---------------------------- */
    /* Left hand */
             RU_S_J,  RU_S_TS, RU_S_U,  RU_S_K, RU_S_JE,
             RU_S_F,  RU_S_Y,  RU_S_V,  RU_S_A,  RU_S_P,
             RU_S_JA, RU_S_CH, RU_S_S,  RU_S_M,  RU_S_I,

    /* Right hand */
    RU_S_N,  RU_S_G,  RU_S_SH, RU_S_SC, RU_S_Z,
    CMS_S_R, RU_S_O,  RU_S_L,  RU_S_D,  RU_S_ZH, RU_S_E,
    CMS_ST,  RU_S_SF, RU_S_B,  RU_S_JU, RU_S_H,  RU_S_JO
  )

  //---------------------------------------------------------------------------
  [L_YELLOW] = MY_layout(
    // LEFT HALF
    _______, RGB_HUI, RGB_SAI, ZP_VAI,  RGB_SPI, RGB_MOD, RGB_TOG,
    _______, RGB_HUD, RGB_SAD, ZP_VAD,  RGB_SPD, RGB_RMOD,RGB_LYR,
    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
    _______, _______, AU_TOG,  MU_TOG,  MU_MOD,
    _______, // LEFT RED THUMB KEY
    _______,   _______,   _______, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, _______, _______, _______, RESET,   MY_FLSH,
    _______, _______, _______, _______, _______, _______, _______,
    _______, LED_1,   LED_2,   LED_3,   LED_4,   LED_5,   LED_6,
             _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),
  //---------------------------------------------------------------------------
  [L_RED] = MY_layout(
    _______, _______, _______, _______, _______, _______, _______,
    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
    _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    _______, CT_LEFT, CT_DOWN, CT_UP,   CT_RGHT, CT_F,
    _______, _______, _______, _______, _______,
    _______, // LEFT RED THUMB KEY
    _______, _______, _______, // LEFT THUMB KEYS

    // RIGHT HALF
    _______, _______, _______, _______, _______, _______, _______,
    CT_PLUS, EN_MACR, CMB_LB2, CMB_RB2, EN_ARR2, EN_ARR1, CT_ENT,
    CT_MINS, KC_TAB,  CMB_LB1, CMB_RB1, CMB_LB4, CMB_RB4, SH_TAB,
             EN_FISH, CMB_LB3, CMB_RB3, EN_LTEQ, EN_GTEQ, _______,
                      _______, _______, _______, _______, _______,
                      _______, // RIGHT RED THUMB KEY
                      _______, _______, _______ // RIGHT THUMB KEYS
  ),
  //---------------------------------------------------------------------------
  [L_GAME] = MY_layout(
    // LEFT HALF
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_7,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_8,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS, KC_DEL,
    KC_LGUI, // LEFT RED THUMB KEY
    KC_SPC,  KC_LALT, KC_ENT, // LEFT THUMB KEYS

    // RIGHT HALF
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG_GAME,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, // RIGHT RED THUMB KEY
                      XXXXXXX, XXXXXXX, XXXXXXX // RIGHT THUMB KEYxxxxx
  )
};

const ComboWithKeycode combos[] PROGMEM = {
  // Left Index
  CHORD(CT_C,    /* <- */ CMB_CTC),
  CHORD(CT_V,    /* <- */ CMB_CTV),
  CHORD(CT_X,    /* <- */ CMB_CTC, CMB_CTV),

  // Shifted Left Index
  CHORD(CT_A_C,  /* <- */ CMB_CAC),
  CHORD(CT_A_V,  /* <- */ CMB_CAV),
  CHORD(CT_A_X,  /* <- */ CMB_CAC, CMB_CAV),

  // -------------------------------------------------------------------------
  // Right Index
  CHORD(CT_S,    /* <- */ CMB_CTS),
  CHORD(AG_CMSP, /* <- */ CMB_CMSP),
  CHORD(AG_COMM, /* <- */ CMB_CTS, CMB_CMSP),

  // -------------------------------------------------------------------------
  // Left Thumb
  IMMEDIATE_CHORD(SFT_N, SFT_N,     /* <-! */ CMB_SFT),
  CHORD(KC_BSPC, /* <- */ CMB_BSP),
  CHORD(KC_ENT,  /* <- */ CMB_ENT),
  IMMEDIATE_CHORD(CTRL_EN, CTRL_EN, /* <-! */ CMB_CTL),
  CHORD(CT_A,    /* <- */ CMB_SFT, CMB_CTL),
  CHORD(SFT_N_O, /* <- */ CMB_SFT, CMB_BSP),
  CHORD(KC_DEL,  /* <- */ CMB_BSP, CMB_CTL),
  CHORD(CT_BSPC, /* <- */ CMB_BSP, CMB_ENT),
  CHORD(CTSH_EN, /* <- */ CMB_SFT, CMB_BSP, CMB_CTL),
  // TODO: screenshot
 //  CHORD(MY_SCRN,  /* <- */ CMB_BSP, CMB_ENT, CMB_CTL),

  // Right Thumb
  CHORD(LA_CHNG, /* <- */ CMB_LAN),
  CHORD(AG_DOT,  /* <- */ CMB_DOT),
  CHORD(KC_SPC,  /* <- */ CMB_SPC),
  CHORD(ALT_EN,  /* <- */ CMB_ALT),
  CHORD(AG_SDOT, /* <- */ CMB_DOT, CMB_SPC),
  CHORD(LA_SYNC, /* <- */ CMB_LAN, CMB_DOT),
  CHORD(CTAL_EN, /* <- */ CMB_SPC, CMB_ALT),
  CHORD(SHAL_EN, /* <- */ CMB_DOT, CMB_ALT),
  CHORD(WIN_EN,  /* <- */ CMB_SPC, CMB_DOT, CMB_ALT),
  // TODO: locking
//   CHORD(MU_WNL,  /* <- */ CMB_LAN, CMB_DOT, CMB_ALT),

  // -------------------------------------------------------------------------
  // Russian combos on letters
  CHORD(RU_R,    /* <- */ CMS_R),
  CHORD(RU_T,    /* <- */ CMS_T),
  CHORD(RU_HD,   /* <- */ CMS_R, CMS_T),
  CHORD(RU_S_R,  /* <- */ CMS_S_R),
  CHORD(RU_S_T,  /* <- */ CMS_ST),
  CHORD(RU_S_HD, /* <- */ CMS_S_R, CMS_ST),

  // -------------------------------------------------------------------------
  // Arrows on the red layer
  CHORD(AG_LPRN, /* <- */ CMB_LB1),
  CHORD(AG_RPRN, /* <- */ CMB_RB1),
  CHORD(EN_LBRC, /* <- */ CMB_LB2),
  CHORD(EN_RBRC, /* <- */ CMB_RB2),
  CHORD(EN_LCBR, /* <- */ CMB_LB3),
  CHORD(EN_RCBR, /* <- */ CMB_RB3),
  CHORD(EN_LT,   /* <- */ CMB_LB4),
  CHORD(EN_GT,   /* <- */ CMB_RB4),
  CHORD(AG_2B1,  /* <- */ CMB_LB1, CMB_RB1),
  CHORD(EN_2B2,  /* <- */ CMB_LB2, CMB_RB2),
  CHORD(EN_2B3,  /* <- */ CMB_LB3, CMB_RB3),
  CHORD(EN_2B4,  /* <- */ CMB_LB4, CMB_RB4),
};
const uint8_t combos_size = sizeof(combos)/sizeof(ComboWithKeycode);

const uint16_t tt_keys[][3] = {
  { TT_CTJ,  CT_J,    CT_BSLS }, // Убийство программы, если нажать три раза, то выдаёт Ctrl+\, что убивает безоговорочно.
  { TT_RED,  MO_RED,  TG_RED  },
  { TT_YELL, MO_YELL, TG_YELL },
};
const uint8_t tt_size = sizeof(tt_keys)/(sizeof(uint16_t) * 3);

// TODO make progmem?
static const rgba layer_bg_map[] = {
  [L_EN] = ZP_RGB(255, 255, 255),
  [L_EN_S] = ZP_RGB(204, 204, 204),

  [L_RU] = ZP_RGB(50, 50, 255),
  [L_RU_S] = ZP_RGB(41, 41, 204),

  [L_RED] = ZP_RGB(255, 50, 50),
  [L_YELLOW] = ZP_RGB(255, 255, 0),
  [L_GAME] = ZP_RGB(255, 0, 255)
};
const uint8_t layer_bg_map_size = sizeof(layer_bg_map)/(sizeof(rgba));

bool initted_for_layer_state = false;
layer_state_t layer_state_set_user(layer_state_t state) {
  if (initted_for_layer_state) {
    // Выключаем все леды, потому что они только просвечивают своим некрасивым цветом через прозрачные кейкапы, а для чего их использовать можно я не придумал
    ML_LED_1(false);
    ML_LED_2(false);
    ML_LED_3(false);
    ML_LED_4(false);
    ML_LED_5(false);
    ML_LED_6(false);

    uint8_t layer = get_highest_layer(state);

    zp_set_background(layer_bg_map[layer]);
  }

  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  initted_for_layer_state = true;

  uint8_t layer = biton32(layer_state);

  // === GAMING MODE START ===
  // Handle only the separate set of the gaming-specific hotkeys
  // to reduce the input lag
  if (layer >= L_GAME) {
    if (!process_gaming_hotkeys(keycode, record)) {
      return false;
    }

    return true;
  }
  // === GAMING MODE END ===

  if (!process_my_music_keys(keycode, record)) {
    return false;
  }

  if (!combo_process_record(keycode, record)) {
    return false;
  }

  if (!tt_process_record(keycode, record)) {
    return false;
  }

  if(!zp_process_record(keycode, record)) {
    return false;
  }

//   if (!rp_process_record(keycode, record)) {
//     return false;
//   }

  if (!process_my_lang_keys(keycode, record)) {
    return false;
  }

  if (!lang_shift_process_record(keycode, record)) {
    return false;
  }

  if (!process_my_hotkeys(keycode, record)) {
    return false;
  }

  if (!process_moonlander_leds(keycode, record)) {
    return false;
  }

  if (!process_mouse_pixel_move(keycode, record)) {
    return false;
  }

  

  return true;
}

float error_song1[][2] = SONG(MUSIC_OFF_SOUND);
void combo_max_count_error(void) {
  PLAY_SONG(error_song1);
  uprintf("COMBO ERROR: MAX COMBOS COUNT HAS REACHED\n");
}

float error_song2[][2] = SONG(VOICE_CHANGE_SOUND);
void combo_max_size_error(void) {
  PLAY_SONG(error_song2);
  uprintf("COMBO ERROR: MAX COMBO SIZE HAS REACHED\n");
}

void repeated_key_error(void) {
  PLAY_SONG(error_song2);
  uprintf("REPEATED KEY ERROR\n");
}

void user_timer(void) {
  combo_user_timer();
  lang_shift_user_timer();
  // rp_timer();
}

void matrix_scan_user(void) {
  user_timer();
  hid_apps_tick();
}

void rgb_matrix_indicators_user(void) {

}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
  audio_on();

  zp_init();
  hid_apps_init();

  zp_set_background(layer_bg_map[0]);
  rgb_matrix_mode(RGB_MATRIX_CUSTOM_ZPAINTING);
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
  if(length != sizeof(hid_message_t)) {
    uprintf("invalid hid packet length, expected %x, got %x\n", sizeof(hid_message_t), length);
    return;
  }

  hid_receive((hid_message_t*) data);
}
