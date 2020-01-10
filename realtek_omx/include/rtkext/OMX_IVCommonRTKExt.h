#ifndef OMX_IVCommonRTKExt_h
#define OMX_IVCommonRTKExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <OMX_Core.h>

/**
 *  * nCount             : Count the FILLDONE time, 100 per life cycle
 *  * nInputBufferAtTop  : Count if current input buffer count = total number - 1
 *  * nOutputBufferAtTop : Count if current output buffer count = total number - undequeue buffer number
 *  */
typedef struct OMX_VIDEO_PERFORMANCE_CHECK {
    OMX_U32 nCount;
    OMX_U32 nInputBufferAtTop;
    OMX_U32 nOutputBufferAtTop;
} OMX_VIDEO_PERFORMANCE_CHECK;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/* File EOF */
