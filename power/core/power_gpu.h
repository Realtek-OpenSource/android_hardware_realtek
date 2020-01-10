#ifndef __RTK_POWER_HAL_POWER_GPU_H__
#define __RTK_POWER_HAL_POWER_GPU_H__

#include "power_base.h"

class PowerGPU : public PowerBase {
public:
    PowerGPU();
    virtual ~PowerGPU();
    virtual int         operate(enum POWER_DEVICE_CMD cmd, int data);
private:
    virtual int Performance_cb(bool enable);
};

#endif /* End of __RTK_POWER_HAL_POWER_GPU_H__ */
