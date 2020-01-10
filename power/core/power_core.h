#ifndef __RTK_POWER_HAL_POWER_CORE_H__
#define __RTK_POWER_HAL_POWER_CORE_H__

#include <hardware/power.h>
#include <utils/Vector.h>
#include <core/power_base.h>

class PowerCore {
public:
    PowerCore();
    virtual ~PowerCore();
    virtual void    setInteractive      (bool interactive);
    virtual void    powerHint           (power_hint_t hint, int32_t data);
    virtual void    setFeature          (feature_t feature, bool activate);
private:
    void        power_performance               (bool enable);
    void        power_performance_timeout_ms    (int64_t timeout_ms);
    void        power_device_operate            (int data);
    bool                            mPerformance;
    pthread_mutex_t                 mLock;
    android::Vector<PowerBase *>    mModeleList;
};

#endif /* End of __RTK_POWER_HAL_POWER_CORE_H__ */
