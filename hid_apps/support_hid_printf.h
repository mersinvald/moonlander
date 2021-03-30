#pragma once

#include "printf.h"
#include <string.h>
#include <stdarg.h>

#define HID_PRINTBUF_SIZE 512

void hid_printf(const char *fmt, ...) {
    static char buf[HID_PRINTBUF_SIZE];

    va_list va;
    va_start(va, fmt);
    size_t length = vsnprintf(buf, HID_PRINTBUF_SIZE, fmt, va);
    va_end(va);

    hid_putsn(buf, length);
}
