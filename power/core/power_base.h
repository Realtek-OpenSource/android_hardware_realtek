#ifndef __RTK_POWER_HAL_POWER_BASE_H__
#define __RTK_POWER_HAL_POWER_BASE_H__

#include "power.h"

class PowerBase {
public:
    PowerBase(enum POWER_DEVICE_ID id);
    virtual ~PowerBase();
    virtual enum POWER_DEVICE_ID getDeviceId(void) {return mDeviceId;};
    virtual int         setPerformance(bool enable);
    virtual int         setPerformanceTimeout(int64_t timeout_ms);
    virtual int         operate(enum POWER_DEVICE_CMD /*cmd*/, int /* ppData */) {return -1;};

private:
    virtual int         Performance_cb(bool enable) = 0;

    int                 updateState();
    static void *       Loop (void * data);
    enum POWER_DEVICE_ID mDeviceId;
    bool                mPerformanceForce;
    bool                mPerformanceStore;
    int64_t             mPerformanceTimeout;
    bool                mEOS;
    pthread_t           mThread;
    pthread_mutex_t     mLock;
    pthread_cond_t      mCond;
};

#endif /* End of __RTK_POWER_HAL_POWER_BASE_H__ */
