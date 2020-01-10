#ifndef ANDROID_HARDWARE_POWER_V1_0_POWER_H
#define ANDROID_HARDWARE_POWER_V1_0_POWER_H

#include <android/hardware/power/1.0/IPower.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <hardware/power.h>

namespace android {
namespace hardware {
namespace power {
namespace V1_0 {
namespace implementation {

using ::android::hardware::power::V1_0::Feature;
using ::android::hardware::power::V1_0::PowerHint;
using ::android::hardware::power::V1_0::IPower;
using ::android::hardware::Return;
using ::android::hardware::Void;

struct Power : public IPower {
    Power();
    Return<void> setInteractive             (bool interactive)                      override;
    Return<void> powerHint                  (PowerHint hint, int32_t data)          override;
    Return<void> setFeature                 (Feature feature, bool activate)        override;
    Return<void> getPlatformLowPowerStats   (getPlatformLowPowerStats_cb _hidl_cb)  override;
};

} // namespace implementation
} // namespace V1_1
} // namespace power
} // namespace hardware
} // namespace android
#endif /* End of ANDROID_HARDWARE_POWER_V1_0_POWER_H */
