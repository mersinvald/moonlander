#pragma once

#if HID_APP_SUPPORT_ENABLE == true
    #include "hid_apps/support.h"
#endif

void hid_apps_init(void) {
#if HID_APP_SUPPORT_ENABLE == true
    hid_app_support_init();
#endif
}

void hid_apps_tick(void) {
#if HID_APP_SUPPORT_ENABLE == true
    if(hid_app_support_tick()) return;
#endif
}
