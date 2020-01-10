#ifndef _HWM_H_
#define _HWM_H_

#include <hardware/hardware.h>

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>


typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

#define EFUSE_BIT_SECURE_BOOT	(1<<0)
#define EFUSE_BIT_BOOT_ENC		(1<<1)
#define EFUSE_BIT_HWCHK_FIRST	(1<<2)
#define EFUSE_BIT_HWCHK_LATER	(1<<3)

#define OTP_ERR_OPEN_DEV -1
#define OTP_ERR_MODULE -2
#define OTP_ERR_START_ADDR -3
#define OTP_ERR_LEN -4
#define OTP_ERR_WRITE_CHECK -5

/**
 *  * The id of this module
 *   */
#define HWM_HARDWARE_MODULE_ID "rtk_hwm"
#define HWM_HARDWARE_E         "HWM_E"

/**
 *  * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 *   * and the fields of this data structure must begin with hw_module_t
 *    * followed by module specific information.
 *     */
struct hwm_module_t {
    struct hw_module_t common;
};

/**
 *  * Every device data structure must begin with hw_device_t
 *   * followed by module specific public methods and attributes.
 *    */
struct hwm_device_t {
    struct hw_device_t common;
    int (*test) (struct hwm_device_t *dev, char* pMsg);
    int (*uuid_read) (struct hwm_device_t *dev, UINT8* buf, unsigned int length, unsigned int start_addr);
    int (*uuid_write) (struct hwm_device_t *dev, UINT8* buf, int length, int start_addr);
    int (*emmc_flash_id_read) (struct hwm_device_t *dev, UINT8* buf);
    int (*chip_id_read) (struct hwm_device_t *dev, UINT8* buf);
};

/** convenience API for opening and closing a device */

static inline int hwm_dev_open(const struct hw_module_t* module, const char* name, struct hwm_device_t** device) {
    return module->methods->open(module,
            name, (struct hw_device_t**)device);
}

static inline int hwm_dev_close(struct hwm_device_t* device) {
    return device->common.close(&device->common);
}


/***************************************************/
/* Definition                                                                       */
/***************************************************/

int otp_init(void);
int otp_uninit(void);

#endif // _HWM_H_
