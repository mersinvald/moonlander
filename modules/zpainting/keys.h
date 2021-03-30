#pragma once

#ifndef CUSTOM_SAFE_RANGE
  #error "You must specify variable CUSTOM_SAFE_RANGE for color extension."
#endif

enum zp_keys {
    ZP_START = CUSTOM_SAFE_RANGE,

	ZP_VAI,
    ZP_VAD,

	ZP_NEW_SAFE_RANGE,
	#undef CUSTOM_SAFE_RANGE
	#define CUSTOM_SAFE_RANGE ZP_NEW_SAFE_RANGE
};

bool zp_process_record(uint16_t key, keyrecord_t *record);