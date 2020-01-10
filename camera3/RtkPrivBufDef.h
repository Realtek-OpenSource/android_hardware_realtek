#ifndef _RTK_PRIV_BUF_DEF
#define _RTK_PRIV_BUF_DEF

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

// pass mode to firmware
typedef struct _private_rtk_data
{
    unsigned int        yuv_mode;
    unsigned long long  pts[2];
    int                 delay_mode;
    int                 delay_depth;
    unsigned int        IsForceDIBobMode; //force deinterlace bob mode
    int                 init_frame;
    int                 deintflag; // 0:AUTODEINT 1:FORCEDEINT 2:FORCEPROGRESSIVE
    int                 ssid;
    unsigned int        lumaOffTblAddr;     /* legacy */
    unsigned int        chromaOffTblAddr;   /* legacy */
    unsigned int        lumaOffTblAddrR;    /* legacy */
    unsigned int        chromaOffTblAddrR;  /* legacy */
    unsigned int        bufBitDepth;
    unsigned int        bufFormat;
    unsigned int        transferCharacteristics;
    unsigned int        display_primaries_x0;
    unsigned int        display_primaries_y0;
    unsigned int        display_primaries_x1;
    unsigned int        display_primaries_y1;
    unsigned int        display_primaries_x2;
    unsigned int        display_primaries_y2;
    unsigned int        white_point_x;
    unsigned int        white_point_y;
    unsigned int        max_display_mastering_luminance;
    unsigned int        min_display_mastering_luminance;
    unsigned int        display_width;
    unsigned int        display_height;
    unsigned int        hdmi_flag; // bit[0] : HDCP
    unsigned long long  hdmi_hdcp_key;
    unsigned long long  hdmi_hdcp_key_response;
    unsigned int        reserve[64-35];

#if 0
    unsigned int yuv_mode;
    unsigned long long  pts[2];
    int delay_mode;
    int delay_depth;
    unsigned int IsForceDIBobMode;
#endif

} private_rtk_data;

#endif

