#ifndef CAM_BUF_DEF_H
#define CAM_BUF_DEF_H

#include <system/window.h>
#include <utils/Timers.h>
#include <libRTKAllocator/include/allocator/Allocator.h>
#include "RtkPrivBufDef.h"

namespace android {

typedef enum {
    BUF_STATE_UNDEF,
    BUF_STATE_OK,
    BUF_STATE_NA
} BUF_STATE;

/**
 * Memory info passed from Hal
 */
typedef struct gralloc_buf_info {
    uint32_t phyAddr;
    void *vAddr;
    void *cb;
    void *cr;
    int size;
    int format;
    int w;
    int h;
    private_rtk_data rtkData;
    private_rtk_data rtkDataReturn;
    buffer_handle_t *pHandle;
    BUF_STATE bufState;
    //bool hasRtkPrivData;
} gralloc_buf_info_t;

/**
 * Memory info of ION buffers allocated inside V4L2Device
 */
typedef struct allocator_info {
    int index;
    AllocatorDef *allocator;
    void *vAddr;
    void *phyAddr;
    int size;
    int width_aligned;      // 16 byte aligned if necessary
    int height_aligned;     // 16 byte aligned
    nsecs_t timeStamp;
    int width;
    int height;
    bool is16Aligned;
    uint32_t bytesused;
    int32_t mShareFd;       // for DMA buffer mode

    // Following are the extension for VOWB
    uint32_t pLockAddr;    // used in VOWB, only valid to a YUV buffer that is using VOWB deinterlace
    int64_t yAddr;
    int64_t uAddr;

    int8_t *pLockVAddr;
    int8_t *pRecvVAddr;
} allocator_info_t;

}; // namespace android


#endif
