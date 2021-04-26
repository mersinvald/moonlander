#pragma once

#if HID_APP_SUPPORT_ENABLE == true
    #include "hid_apps/support.h"
#endif
#if HID_APP_COLOR_ENABLE == true
    #include "hid_apps/color.h"
#endif
#if HID_APP_TELEMETRY_ENABLE == true
    #include "hid_apps/telemetry.h"
#endif

void hid_apps_init(void) {
#if HID_APP_SUPPORT_ENABLE == true
    hid_app_support_init();
#endif
#if HID_APP_COLOR_ENABLE == true
    hid_app_color_init();
#endif
#if HID_APP_TELEMETRY_ENABLE == true
    hid_app_telemetry_init();
#endif
}

void hid_apps_tick(void) {
#if HID_APP_SUPPORT_ENABLE == true
    if(hid_app_support_tick()) return;
#endif
#if HID_APP_COLOR_ENABLE == true
    if(hid_app_color_tick()) return;
#endif
#if HID_APP_TELEMETRY_ENABLE == true
    if(hid_app_telemetry_tick()) return;
#endif
}
