#ifndef __RTK_POWER_HAL_POWER_CPU_H__
#define __RTK_POWER_HAL_POWER_CPU_H__

#include "power_base.h"

class PowerCPU : public PowerBase {
public:
    PowerCPU();
    virtual ~PowerCPU();
private:
    virtual int Performance_cb(bool enable);
    int Performance_freq(bool enable);
    int Performance_spif(bool enable);
    enum {
        VERSION_FREQ,
        VERSION_SPIF,
    } mVersion;
};

#endif /* End of __RTK_POWER_HAL_POWER_CPU_H__ */
