#ifndef RTK_INCLUDE_HARDWARE_POWER_H
#define RTK_INCLUDE_HARDWARE_POWER_H
#include <hardware/hardware.h>
#include <hardware/power.h>

#define RTK_POWER_SERVICE_VERSION 1

#define POWER_PERFORMANCE_TIMEOUT_MS           "persist.vendor.power.wdt.ms"

#ifndef RTK_POWER_HINT_PERFORMANCE_WDT
#define RTK_POWER_HINT_PERFORMANCE_WDT          (0x10000001)
#endif

typedef enum rtk_power_hint_t {
    RTK_POWER_HINT_DEVICE_OPERATE = RTK_POWER_HINT_PERFORMANCE_WDT + 1,
} rtk_power_hint_t;

enum POWER_DEVICE_ID {
    DEVICE_CPU,
    DEVICE_GPU,
};

enum POWER_DEVICE_CMD {
    SET_CORES_ENABLE,
    SET_FULL_CORES_ENABLE,
    SET_MAX_FREQ,
    SET_MIN_FREQ,
    SPECIAL_CASE_0,
    SPECIAL_CASE_1,
    SPECIAL_CASE_2,
    SPECIAL_CASE_3,
};

typedef union {
    int data;
    struct {
        unsigned int            magic:2;
        enum POWER_DEVICE_ID    id:8;
        enum POWER_DEVICE_CMD   cmd:8;
        unsigned int            extData:14;
    } info;
} POWER_DEVICE_OPERATE;

#define power_device_operate_prepare(operate)    {(operate).info.magic = (sizeof(POWER_DEVICE_OPERATE)&0x3);}

#define power_device_operate_prepare_data(operate, i_id, i_cmd, i_data) {    \
    power_device_operate_prepare(operate);   \
    (operate).info.id      = (i_id);             \
    (operate).info.cmd     = (i_cmd);            \
    (operate).info.extData = (unsigned int) (i_data);  \
}

#define power_device_operate_conform(operate)    ((operate).info.magic == (sizeof(POWER_DEVICE_OPERATE)&0x3))

#endif /* RTK_INCLUDE_HARDWARE_POWER_H */
