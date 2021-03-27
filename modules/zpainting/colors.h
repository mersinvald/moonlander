#pragma once

#include "include.h"

#define ZP_WHITE       ZP_RGB(0xFF, 0xFF, 0xFF)
#define ZP_RED         ZP_RGB(0xFF, 0x00, 0x00)
#define ZP_CORAL       ZP_RGB(0xFF, 0x7C, 0x4D)
#define ZP_ORANGE      ZP_RGB(0xFF, 0x80, 0x00)
#define ZP_GLDNROD     ZP_RGB(0xD9, 0xA5, 0x21)
#define ZP_GOLD        ZP_RGB(0xFF, 0xD9, 0x00)
#define ZP_YELLOW      ZP_RGB(0xFF, 0xFF, 0x00)
#define ZP_CHRTRSE     ZP_RGB(0x80, 0xFF, 0x00)
#define ZP_GREEN       ZP_RGB(0x00, 0xFF, 0x00)
#define ZP_LGREEN      ZP_RGB(0x00, 0xFF, 0x80)
#define ZP_TRQSE       ZP_RGB(0x47, 0x6E, 0x6A)
#define ZP_TEAL        ZP_RGB(0x00, 0x80, 0x80)
#define ZP_CYAN        ZP_RGB(0x00, 0xFF, 0xFF)
#define ZP_AZURE       ZP_RGB(0x99, 0xf5, 0xFF)
#define ZP_BLUE        ZP_RGB(0x00, 0x00, 0xFF)
#define ZP_PURPLE      ZP_RGB(0x7A, 0x00, 0xFF)
#define ZP_MGNTA       ZP_RGB(0xFF, 0x00, 0xFF)
#define ZP_PINK        ZP_RGB(0xFF, 0x80, 0xBF)
#define ZP_BLACK       ZP_RGB(0x00, 0x00, 0x00)
#define ZP_OFF         ZP_BLACK

static inline rgba zp_with_alpha(rgba x, uint8_t alpha) {
    x.a = alpha;
    return x;
}

#define ZP_TRANS   ZP_RGBA(0, 0, 0, 0)
#define __________ ZP_TRANS


