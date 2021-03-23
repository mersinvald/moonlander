#pragma once

#include "quantum/audio/song_list.h"

#ifndef CUSTOM_SAFE_RANGE
  #error "You must specify variable CUSTOM_SAFE_RANGE for songs keycodes."
#endif

enum songs_keycodes {
  SONGS_START = CUSTOM_SAFE_RANGE,

  SONGS_NEW_SAFE_RANGE,
  #undef CUSTOM_SAFE_RANGE
  #define CUSTOM_SAFE_RANGE SONGS_NEW_SAFE_RANGE
};

// Музыка обязательно должна находиться вне функции, потому что она проигрывается асинхронно...
float my_song1[][2] = SONG(QWERTY_SOUND);


// Эта функция должна находиться самой последней по приоритету
bool process_my_music_keys(uint16_t keycode, keyrecord_t *record) {
  // https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/song_list.h
  // https://docs.qmk.fm/#/feature_audio

  static bool disable_music = false;

  if (disable_music)
    return true;

  #define MUSIC_KEYCODE(FROM, TO, SONG) \
    case FROM: \
      if (record->event.pressed) { \
        PLAY_SONG(SONG); \
        disable_music = true; \
        press_arbitrary_keycode(TO, true); \
        disable_music = false; \
      } else { \
        disable_music = true; \
        press_arbitrary_keycode(TO, false); \
        disable_music = false; \
      } \
      return false; \
      break;

  switch (keycode) {
    default:
      return true;
  }
}
