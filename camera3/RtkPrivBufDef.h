#ifndef _RTK_PRIV_BUF_DEF
#define _RTK_PRIV_BUF_DEF

#include "hwc/volayer/hwlayer/utils/GraphicBufferInfo.h"

// copied from device/realtek/frameworks/native/services/sideband/Display/VOLayer/hwlayer/video/VideoBuffer.h
// bad workaround, fix me later
typedef enum
{
    INTERLEAVED_TOP_FIELD = 0,  /* top    field data stored in even lines of a frame buffer */
    INTERLEAVED_BOT_FIELD,      /* bottom field data stored in odd  lines of a frame buffer */
    CONSECUTIVE_TOP_FIELD,      /* top    field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_BOT_FIELD,      /* bottom field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_FRAME,           /* progressive frame data stored consecutlively in all lines of a frame buffer */
    INTERLEAVED_TOP_FIELD_422,  /* top    field data stored in even lines of a frame buffer */
    INTERLEAVED_BOT_FIELD_422,      /* bottom field data stored in odd  lines of a frame buffer */
    CONSECUTIVE_TOP_FIELD_422,      /* top    field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_BOT_FIELD_422,      /* bottom field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_FRAME_422,        /* progressive frame with 4:2:2 chroma */
    TOP_BOTTOM_FRAME,            /* top field in the 0~height/2-1, bottom field in the height/2~height-1 in the frame */
    INTERLEAVED_TOP_BOT_FIELD,   /* one frame buffer contains one top and one bot field */
    INTERLEAVED_BOT_TOP_FIELD,   /* one frame buffer contains one bot and one top field */
    MPEG2_PIC_MODE_NOT_PROG,     /*yllin: for MPEG2 check pic mode usage */
    SOFTWARE_DEINTERLACED     /* frame data is calculated by software deinterlace */

} VP_PICTURE_MODE ;

#endif

