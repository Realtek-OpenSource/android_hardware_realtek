#ifndef RTK_DEC_COMMON_H
#define RTK_DEC_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <OMX_Types.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OSAL_RTK.h>

#include "dbgmacros.h"

#ifdef PLATFORM_P
#define RTK_OMXDECODE_HEVCPERFORMANCEMODE   "vendor.omx.hevc_performance_mode"
#define RTK_OMXDECODE_VIDEOMAXACQCNT        "persist.vendor.rtk.video.maxAcqCnt"
#define RTK_OMXDECODE_HWCDISABLEVOWRITEBACK "vendor.hwc.disable.vo.writeback"
#define RTK_OMXDECODE_DCSYSDEBUG            "vendor.dc.sys.debug"
#define RTK_OMXDECODE_HWCSUPPORTV1FLIP      "vendor.hwc.support.v1.flip"
#else
#define RTK_OMXDECODE_HEVCPERFORMANCEMODE   "rtk.omx.hevc_performance_mode"
#define RTK_OMXDECODE_VIDEOMAXACQCNT        "persist.rtk.video.maxAcqCnt"
#define RTK_OMXDECODE_HWCDISABLEVOWRITEBACK "rtk.hwc.disable.vo.writeback"
#define RTK_OMXDECODE_DCSYSDEBUG            "rtk.dc.sys.debug"
#define RTK_OMXDECODE_HWCSUPPORTV1FLIP      "rtk.hwc.support.v1.flip"
#endif


/* Common function */
/************************************************************************/
/* Queue                                                                                                                */
/************************************************************************/
typedef struct {
    uint8_t*    buffer;
    uint32_t    size;
    uint32_t    itemSize;
    uint32_t    count;
    uint32_t    front;
    uint32_t    rear;
} DataQueue;

DataQueue* DataQueue_Create(
    uint32_t    itemCount,
    uint32_t    itemSize
);

void DataQueue_Destroy(
    DataQueue*  queue
);

/**
 * \brief       Enqueue with deep copy
 */
int DataQueue_Enqueue(
    DataQueue*  queue,
    void*       data
);

/**
 * \brief       Caller has responsibility for releasing the returned data
 */
void* DataQueue_Dequeue(
    DataQueue*  queue
);

void DataQueue_Flush(
    DataQueue*  queue
);

void* DataQueue_Peek(
    DataQueue*  queue
);

/**
 * \brief       @dstQ is NULL, it allocates Queue structure and then copy from @srcQ.
 */
DataQueue* DataQueue_Copy(
    DataQueue*  dstQ,
    DataQueue*  srcQ
);

int DataQueue_Count(
    DataQueue*  queue
);


void SendOneFrameToVO(
    private_rtk_v1_data *priv, // It points to accessible address, but NO data.
    OMX_S32             fbWidth,
    OMX_S32             fbHeight,
    VP_PICTURE_MODE_t   picMode,
    OMX_S8              pairedFldFrm,
    OMX_S8              forceFieldMode,
    OMX_U32             nEnableDeInterlace,
    OMX_BOOL            *bNeedDeinterlace,
    OMX_BOOL            bEnableTunnelMode,
    OMX_TICKS           outTimestamp,
    OMX_TICKS           nTimeTick,
    OMX_BOOL            bDisplayOrder
);

#ifdef __cplusplus
}
#endif
#endif                       // RTK_DEC_COMMON_H
