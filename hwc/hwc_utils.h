#ifndef __RTK_HWC_UTILS_H_
#define __RTK_HWC_UTILS_H_
#include <hardware/hwcomposer.h>

#define HWC2_INCLUDE_STRINGIFICATION
#define HWC2_USE_CPP11
#include <hardware/hwcomposer2.h>
#undef HWC2_INCLUDE_STRINGIFICATION
#undef HWC2_USE_CPP11

#include <utils/Log.h>

#include <linux/fb.h>
#include <sys/ioctl.h>
#include <math.h>

#include <cstring>
#include <utils/String8.h>
#include <utils/Timers.h>
#include <cutils/properties.h>

#ifdef USE_RTK_VOUT_UTIL
#include <VideoRPCBaseDS_data.h>
#include <VideoRPC_System_data.h>
#include <VideoRPCBaseDS_data.h>
#include <RPCBaseDS_data.h>
#include <VoutUtil.h>
#endif

#include <sync/sync.h>
#include <sw_sync.h>

inline int WIDTH (const hwc_rect_t & rect)    { return rect.right - rect.left; }
inline int HEIGHT(const hwc_rect_t & rect)   { return rect.bottom - rect.top; }

#define DC2VO_IOC_MAGIC         'd'
#define DC2VO_WAIT_FOR_VSYNC    _IO (DC2VO_IOC_MAGIC,  0)

typedef struct {
    unsigned int enable ;
    unsigned int width ;
    unsigned int height ;
    unsigned int reserve[16-3];
} DC_BUFFER_INFO ;
#define DC2VO_SET_BUFFER_INFO            _IO    (DC2VO_IOC_MAGIC, 18)

inline float convertLuminace(int32_t cv)
{
    float temp = cv / 32;
    float luminance = 50 * pow(2, temp);
    return luminance;
}

inline float convertMinLuminace(float maxLuminance, int32_t cv)
{
    float temp = cv / 255;
    float minLuminance = maxLuminance * pow(temp, 2) / 100;
    return minLuminance;
}
#endif /* End of __RTK_HWC_UTILS_H_ */
