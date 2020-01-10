#ifndef RTK_DECODER_H
#define RTK_DECODER_H

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__LINARO_SDK__)
#include "OMX_Types.h"
#include "OMX_Core.h"
#include "OMX_Component.h"
#include "OSAL_RTK.h"
#else
#include <media/openmax/OMX_Types.h>
#include <media/openmax/OMX_Core.h>
#include <media/openmax/OMX_Component.h>
#include <OSAL_RTK.h>
#endif

#include <basecomp.h>
#include <base/vbuffer.h>
#define CODEC_CAST_32ADDR(fmt) (((unsigned int) (fmt)) & -1U)
#define CODEC_UNUSED_WARNING(val) (void)(val)

#include "dbgmacros.h"

#define COMPONENT_NAME_VIDEO      "OMX.realtek.video.decoder"
#define COMPONENT_NAME_IMAGE      "OMX.realtek.image.decoder"
#define WRAPPER_NAME_VE1    "libdecve1wrap.so"
#define WRAPPER_NAME_VE2    "libdecve2wrap.so"
#define WRAPPER_NAME_JPG    "libdecjpgwrap.so"

#define USE_ION_ALLOC_FB
#define SUPPORT_SE
#if ! defined(__LINARO_SDK__)
#define USE_SE_SERVICE
#endif
#define ENABLE_OUTPUT_THREAD

#define MAKE_FOURCC(a,b,c,d) ( ((unsigned char)a) | ((unsigned char)b << 8) | ((unsigned char)c << 16) | ((unsigned char)d << 24) )

#define EXTRA_FB_COUNT (1+1)
#define EXTRA_FB_WTL_COUNT (0+1)
#define EXTRA_GSI_FB_COUNT (0+1)
#define EXTRA_GSI_FB_WTL_COUNT (0+0)

typedef enum BUFFER_CMD
{
    BUFFERCMD_ADD_BUF = 0,
    BUFFERCMD_REGISTER_BUF,
    BUFFERCMD_RESET_BUF,
    BUFFERCMD_CLEAR_BUF,
    BUFFERCMD_START_DECODE,
    BUFFERCMD_ADD_BUF2,
    BUFFERCMD_REGISTER_BUF2,
    BUFFERCMD_REMOVE_BUF,
} BUFFER_CMD;

typedef enum VPU_CONFIG
{
    VPUCFG_SKIP_FRAME = 0,
    VPUCFG_SET_ERR_FRAME_THRESHOLD,
    VPUCFG_SET_VP9_SCALE_MODE,
} VPU_CONFIG;

typedef enum OMX_PARAM
{
    OMX_GET_NEXT_FRAME_PA = 0,
} OMX_PARAM;

typedef struct STREAM_BUFFER
{
    OMX_U8 *bus_data;
    OSAL_BUS_WIDTH bus_address; // use this for HW
    OMX_U32 streamlen;
    OMX_U32 sliceInfoNum;
    OMX_U8 *pSliceInfo;
    OMX_U32 allocsize;
    OMX_BOOL bEOS;
    OMX_U32 nFlags;
} STREAM_BUFFER;

typedef struct STREAM_INFO
{
    OMX_COLOR_FORMATTYPE format;    // stream color format
    OMX_U32 framesize;   // framesize in bytes
    OMX_U32 width;       // picture display width
    OMX_U32 height;      // picture display height
    OMX_U32 sliceheight; // picture slice height
    OMX_U32 stride;      // picture scan line width
    OMX_U32 interlaced;  // is sequence interlaced
    OMX_U32 imageSize;   // size of image in memory
    OMX_BOOL isThumbnail;
    OMX_BOOL crop_available;       // crop information
    OMX_U32 crop_width;
    OMX_U32 crop_height;
    OMX_U32 crop_left;
    OMX_U32 crop_top;
    OMX_U32 reg_num_buffer;
    OMX_U32 nMinOutputUndequeueCount;
    double frameRate;
    OMX_BOOL isNeedVOWriteback;
#if defined(__LINARO_SDK__)
    OMX_U32 lumasize;
    OMX_U32 chromasize;
#endif
    ColorAspects mAspects;
    HDRStaticInfo mHDRInfo;
} STREAM_INFO;

typedef struct FRAME
{
    OMX_U8 *fb_bus_data; // pointer to DMA accesible output buffer.
    OMX_U32 fb_bus_address; // memory buffer address on the bus
    OMX_U32 fb_size;     // buffer size
    OMX_U32 size;        // output frame size in bytes
    OMX_U32 MB_err_count;   // decoding macroblock error count
    OMX_BOOL isIntra;
    OMX_BOOL isGoldenOrAlternate;
    OMX_TICKS nTimeStamp;
    OMX_U32 outputBufferType;
    OMX_BOOL isEosFrame;
    private_rtk_v1_data priv_data;
    OMX_S32 isHDR;
    VBUFFER *vbuffer;
    OMX_S32 idx;
} FRAME;

typedef struct DEC_ALLOCATOR
{
    OSAL_ALLOCATOR pIonAlloc;
    OMX_S32 nSize;
    OMX_U32 pPhyAddr;
    OMX_U8 *pVirtAddr;
} DEC_ALLOCATOR;

typedef enum ROTATION
{
    ROTATE_NONE,
    ROTATE_RIGHT_90 = 90,
    ROTATE_LEFT_90 = -90,
    ROTATE_180 = 180,
    ROTATE_FLIP_VERTICAL,
    ROTATE_FLIP_HORIZONTAL
} ROTATION;

/* Opencore specific */
/* OMX COMPONENT CAPABILITY RELATED MEMBERS */
typedef struct
    PV_OMXComponentCapabilityFlagsType
{
    OMX_BOOL iIsOMXComponentMultiThreaded;
    OMX_BOOL iOMXComponentSupportsExternalOutputBufferAlloc;
    OMX_BOOL iOMXComponentSupportsExternalInputBufferAlloc;
    OMX_BOOL iOMXComponentSupportsMovableInputBuffers;
    OMX_BOOL iOMXComponentSupportsPartialFrames;
    OMX_BOOL iOMXComponentUsesNALStartCode;
    OMX_BOOL iOMXComponentCanHandleIncompleteFrames;
    OMX_BOOL iOMXComponentUsesFullAVCFrames;
} PV_OMXComponentCapabilityFlagsType;

typedef struct PRIVATE_STRUCT
{
    OMX_BOOL bIsRTKExtractor;
    OMX_BOOL bUseOutputBeDecoded;
    OMX_U32 nFrameWidth;
    OMX_U32 nFrameHeight;
    OMX_VIDEO_WMVFORMATTYPE pWMVFormat;
    OMX_BOOL bIsRV8;
    OMX_BOOL bUseProtectBuffer;
    OMX_BOOL bLowDelayMode;
    OMX_BOOL bSetSearchIFrm;
    OMX_U32 nEnableDeInterlace;
    OMX_BOOL bEnableTunnelMode;
    OMX_BOOL bVeScaleEnable;

    /*
     * nHevcOutputMode :
     *  0: 10/8bit compressed + 8bit linear
     *  1: 10/8bit compressed + 10/8bit linear
     *  2: 10/8bit compressed only
     */
    enum {
        E_HEVC_COMPRESSED_AND_8BIT_LINEAR = 0,
        E_HEVC_COMPRESSED_AND_10BIT_LINEAR = 1,
        E_HEVC_COMPRESSED_ONLY = 2,
    } nHevcOutputMode;

    OMX_U32 nVeScaleResolution; /* width mask: 0xffff0000, height mask: 0x0000ffff */
    OMX_U32 nVeScaleFPS;
    OMX_COLOR_FORMATTYPE eColorFormat; // color format
    OMX_BOOL bIsThumbnail; // for 1295 A00 used, Need change after B00 or C00
    OMX_U32 nAVCExtMode; /* 0:AVC 1:MVC */
    OMX_BOOL nAdaptiveHoldBuf;
    OMX_BOOL nAdaptivePlaybackEnable;
    OMX_S32 nAdaptiveWidth;
    OMX_S32 nAdaptiveHeight;
    OMX_BOOL bDoviHEVC;
    OMX_U32 aVp9HdrPara[13];
    OMX_BOOL bIsDOVI;
    OMX_S32 nFullRangeFlag;
    OMX_BOOL bCombinedEnable;
    OMX_BOOL bDisplayOrder;
    OMX_BOOL bVo_writeback_disable;
    OMX_BOOL bUseReasonableOutputBuffer;
    OMX_BOOL bTurboDecodingDisable;
    OMX_BOOL bCheckBonding;
    OMX_U32 nExtBufCnt;
    OMX_U32 nExtWTLBufCnt;
} PRIVATE_STRUCT;

typedef enum CODEC_STATE
{
    CODEC_NEED_MORE,
    CODEC_HAS_FRAME,
    CODEC_HAS_INFO,
    CODEC_HAS_INFO_DATA,
    CODEC_OK,
    CODEC_NOT_HAS_RESOURCE,
    CODEC_DECODE_FINISH,
    CODEC_ERROR_HW_TIMEOUT = -1,
    CODEC_ERROR_HW_BUS_ERROR = -2,
    CODEC_ERROR_SYS = -3,
    CODEC_ERROR_DWL = -4,
    CODEC_ERROR_UNSPECIFIED = -5,
    CODEC_ERROR_STREAM = -6,
    CODEC_ERROR_INVALID_ARGUMENT = -7,
    CODEC_ERROR_NOT_INITIALIZED = -8,
    CODEC_ERROR_INITFAIL = -9,
    CODEC_ERROR_HW_RESERVED = -10,
    CODEC_ERROR_MEMFAIL = -11,
    CODEC_ERROR_STREAM_NOT_SUPPORTED = -12,
    CODEC_ERROR_FORMAT_NOT_SUPPORTED = -13
} CODEC_STATE;

typedef enum
{
    INTERLEAVED_TOP_FIELD = 0,  /* top    field data stored in even lines of a frame buffer */
    INTERLEAVED_BOT_FIELD,      /* bottom field data stored in odd  lines of a frame buffer */
    CONSECUTIVE_TOP_FIELD,      /* top    field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_BOT_FIELD,      /* bottom field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_FRAME,          /* progressive frame data stored consecutlively in all lines of a frame buffer */
    INTERLEAVED_TOP_FIELD_422,  /* top    field data stored in even lines of a frame buffer */
    INTERLEAVED_BOT_FIELD_422,  /* bottom field data stored in odd  lines of a frame buffer */
    CONSECUTIVE_TOP_FIELD_422,  /* top    field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_BOT_FIELD_422,  /* bottom field data stored consecutlively in all lines of a field buffer */
    CONSECUTIVE_FRAME_422,      /* progressive frame with 4:2:2 chroma */
    TOP_BOTTOM_FRAME,           /* top field in the 0~height/2-1, bottom field in the height/2~height-1 in the frame */
    INTERLEAVED_TOP_BOT_FIELD,  /* one frame buffer contains one top and one bot field, top field first */
    INTERLEAVED_BOT_TOP_FIELD,  /* one frame buffer contains one bot and one top field, bot field first */

    MPEG2_PIC_MODE_NOT_PROG     /* yllin: for MPEG2 check pic mode usage */

} VP_PICTURE_MODE_t ;

struct OutTimeStruct
{
    OMX_TICKS   nTimeStamp;
    OMX_TICKS   nTimeTick;
    OMX_TICKS   nEstTime;
    OMX_U32     dStusFlg;
    OMX_S32     dIdx;
    OMX_S32     dDispIdx;
};

enum {
    CAL_TIME_NONE = 0,
    CAL_TIME_REPEAT,
    CAL_TIME_NOT_FIND,
    CAL_TIME_SEQ_CHANGE,
    CAL_TIME_KODI_ZERO,
};

enum {
    RTK_AUTODEINT = 0,
    RTK_FORCEDEINT,
    RTK_FORCEPROGRESSIVE,
};

typedef enum DECODER_PORT_CHANGE_STATE
{
    OMX_PORT_CHANGE_READY,
    OMX_PORT_CHANGE_SETTING_RECEIVED,
    OMX_PORT_CHANGE_BUFFER_RETURNED,
} DECODER_PORT_CHANGE_STATE;

typedef struct CODEC_PROTOTYPE CODEC_PROTOTYPE;

// internal CODEC interface, which wraps up Hantro API
struct CODEC_PROTOTYPE
{
    //
    // Destroy the codec instance
    //
    void (*destroy) (CODEC_PROTOTYPE *);
    //
    // Decode n bytes of data given in the stream buffer object.
    // On return consumed should indicate how many bytes were consumed from the buffer.
    //
    // The function should return one of following:
    //
    //    CODEC_NEED_MORE  - nothing happened, codec needs more data.
    //    CODEC_HAS_INFO   - headers were parsed and information about stream is ready.
    //    CODEC_HAS_FRAME  - codec has one or more headers ready
    //    less than zero   - one of the enumerated error values
    //
    // Parameters:
    //
    //    CODEC_PROTOTYPE  - this codec instance
    //    STREAM_BUFFER    - data to be decoded
    //    OMX_U32          - pointer to an integer that should on return indicate how many bytes were used from the input buffer
    //    FRAME            - where to store any frames that are ready immediately
    CODEC_STATE(*decode) (CODEC_PROTOTYPE *, STREAM_BUFFER *, OMX_U32 *,
                          FRAME *);

    //
    // Get info about the current stream. On return stream information is stored in STREAM_INFO object.
    //
    // The function should return one of the following:
    //
    //   CODEC_OK         - got information succesfully
    //   less than zero   - one of the enumerated error values
    //
    CODEC_STATE(*getinfo) (CODEC_PROTOTYPE *, STREAM_INFO *);

    //
    // Get a frame from the decoder. On return the FRAME object contains the frame data. If codec does internal
    // buffering this means that codec needs to copy the data into the specied buffer. Otherwise it might be
    // possible for a codec implementation to store the frame directly into the frame's buffer.
    //
    // The function should return one of the following:
    //
    //  CODEC_OK         - everything OK but no frame was available.
    //  CODEC_HAS_FRAME  - got frame ok.
    //  less than zero   - one of the enumerated error values
    //
    // Parameters:
    //
    //  CODEC_PROTOTYPE  - this codec instance
    //  FRAME            - location where frame data is to be written
    //  OMX_BOOL         - end of stream (EOS) flag
    //
    CODEC_STATE(*getframe) (CODEC_PROTOTYPE *, FRAME *, OMX_BOOL);

    //
    // Scan for complete frames in the stream buffer. First should be made to
    // give an offset to the first frame within the buffer starting from the start
    // of the buffer. Respectively last should be made to give an offset to the
    // start of the last frame in the buffer.
    //
    // Note that this does not tell whether the last frame is complete or not. Just that
    // complete frames possibly exists between first and last offsets.
    //
    // The function should return one of the following.
    //
    //   -1             - no frames found. Value of first and last undefined.
    //    1             - frames were found.
    //
    // Parameters:
    //
    //  CODEC_PROTOTYPE - this codec instance
    //  STREAM_BUFFER   - frame data pointer
    //  OMX_U32         - first offset pointer
    //  OMX_U32         - last offset pointer
    //
    OMX_S32 (*scanframe) (CODEC_PROTOTYPE *, STREAM_BUFFER *, OMX_U32 * first,
                          OMX_U32 * last);
    //
    // Flush the input and output data
    //
    void (*flush) (CODEC_PROTOTYPE *, OMX_U32);
    //
    // Command for buffer handling
    //
    CODEC_STATE (*bufcmd) (CODEC_PROTOTYPE *, OMX_U32, OMX_U8 *, OMX_U32, BUFFER_CMD);
    //
    // Set config during runtime
    //
    void (*setconfig) (CODEC_PROTOTYPE *, VPU_CONFIG, OMX_U32);
    void (*getparam) (CODEC_PROTOTYPE *, OMX_PARAM, void *);
};

#ifdef __cplusplus
}
#endif
#endif                       // RTK_DECODER_H
