#ifndef __HWC_CALLBACKS_H__
#define __HWC_CALLBACKS_H__

#define HWC2_INCLUDE_STRINGIFICATION
#define HWC2_USE_CPP11
#include <hardware/hwcomposer2.h>
#undef HWC2_INCLUDE_STRINGIFICATION
#undef HWC2_USE_CPP11

class HWCCallbacks {
public:
    void hotplug(hwc2_display_t display, HWC2::Connection state);
    void refresh(hwc2_display_t display);
    void vsync(hwc2_display_t display, int64_t timestamp);
    HWC2::Error registerCallbacks(HWC2::Callback, hwc2_callback_data_t callback_data,
        hwc2_function_pointer_t pointer);
private:
    hwc2_callback_data_t mHotplugData = nullptr;
    hwc2_callback_data_t mRefreshData = nullptr;
    hwc2_callback_data_t mVsyncData = nullptr;

    HWC2_PFN_HOTPLUG mHotplug = nullptr;
    HWC2_PFN_REFRESH mRefresh = nullptr;
    HWC2_PFN_VSYNC mVsync = nullptr;
};

#endif  // __HWC_CALLBACKS_H__
