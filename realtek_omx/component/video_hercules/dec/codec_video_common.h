#ifndef RTK_VIDEO_COMMON_H
#define RTK_VIDEO_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <OMX_Types.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OSAL_RTK.h>

#include "codec.h"
#include "codec_HEVCHdrParameterParser.h"
#include "vo_writeback/codec_VORPC.h"
#include "vpuapi.h"

#ifdef SUPPORT_SE
#ifdef USE_SE_SERVICE
#include "RtkIpc/SeOp.h"
#else
#include "SeAPI.h"
#endif
#endif

#ifdef ENABLE_TEE_DRM_FLOW
#include "tee_client_api.h"
#include "tee_api.h"
#endif

#include <system/SystemMemory.h>
#include <allocator/Allocator.h>
#include <allocator/IonAllocator.h>
#include <allocator/MallocAllocator.h>
#include <system_mem.h>
#include "utils/BWControl.h"
#include "utils/PWControl.h"

#if defined(__LINARO_SDK__)
#include <stdbool.h>
#endif

#ifdef OMX_DECODER_DOVI
#include "dolby/codec_metadata_parser.h"
#endif
#ifdef ANDROID
#ifdef OMX_DECODER_VE1
#define ENABLE_TURBO_DECODING
#endif
#endif
#define DISABLE_DROP_B_FRAME //Because it is not accurate

#define RTK_4K_ES_SIZE  (9<<20) // 9MB

#ifdef PRODUCT_1GB_1080P
#define RTK_ES_SIZE     (2<<20) // 2MB
#define VP9_ES_SIZE     (1<<20) // 1MB
#define NUM_BS_BUF      3
#else
#define RTK_ES_SIZE     (4<<20) // 4MB
#define VP9_ES_SIZE     (3<<20) // 3MB
#define NUM_BS_BUF      5
#endif

#define IS_OVER_1440P(x)        (x >= (2560 * 1440))
#define IS_OVER_1080P(x)        (x >= (1920 * 1080))
#define IS_OVER_SPEC(x)         (x >= (4096 * 2304))

#define CSD_NUM 2

//#define DEBUG_VDEC
#ifdef DEBUG_VDEC
#ifdef ANDROID
#define TRACE_PRINT(fmt, args...) ALOGD(fmt, ##args)
#else
#define TRACE_PRINT(fmt, args...) printf(fmt, ##args)
#endif
#else
#define TRACE_PRINT(fmt, args...)   do{ }while(0)
#endif
#define TEST_SEQUENCE_CHANGE_BY_HOST


#define RTK_OMXDECODE_HEVCPERFORMANCEMODE   "vendor.omx.hevc_performance_mode"

#define codec_show_pts(pts) ((double)(pts/1E6))
#define CHK_OVER_1080P(width, height) ((width * height) > (1920 * 1088))
#define CHK_GREATER_1080P(width, height) ((width * height) >= (1920 * 1088))
#define DECODING_THRESHOLD(nRN, nRD) \
    ((nRN == 0 || nRD == 0 || (double)nRN/(double)nRD < 29) ? (double)0.041 : \
    (((double)nRN/(double)nRD < 48) ? (double)0.0315 : \
    (((double)nRN/(double)nRD < 55) ? (double)0.025 : 0.0155)))

#define MAX_RETRIES 1000
#define INTERVAL_TIME (10*90000)
#define MAX_BITSTREAM_BUFFER_COUNT 16
#define MAX_NATIVE_BUFFER_NUM 32
#define MAX_PPU_SRC_NUM 2
#define MAX_CHUNK_HEADER_SIZE	 256*1024 //DEFAULT_STREAMBUFFER_SIZE //Fuchun 20131225 don't need big size
#define ENOUGH_CHUNK_SIZE 0x20000//(1024+VPU_GBU_SIZE*2)
#define EMPTY_BUFFER_REFILL_SIZE  (512) //(1024+VPU_GBU_SIZE*2)
#define VPU_WAIT_TIME_OUT 10 //should be less than normal decoding time to give a chance to fill stream. if this value happens some problem. we should fix VPU_WaitInterrupt function
#define VPU_WAIT_TIME_OUT_CQ 1
#define EXTRA_FRAME_BUFFER_NUM 3
#define MAX_TIME_QUEUE 256
#define MAX_BUFCMD_QUEUE 64
#define VPU_WAIT_TIME_OUT_IN_FLUSH 100
#define TEMP_QUEUE_CNT 30
#define SKIP_B_COUNT 2

#define USE_BIT_INTERNAL_BUF        1
#define USE_IP_INTERNAL_BUF         1
#define USE_DBKY_INTERNAL_BUF       1
#define USE_DBKC_INTERNAL_BUF       1
#define USE_OVL_INTERNAL_BUF        1
#define USE_BTP_INTERNAL_BUF        1
#define USE_ME_INTERNAL_BUF         1

/* WAVE410 only */
#define USE_BPU_INTERNAL_BUF        1
#define USE_VCE_IP_INTERNAL_BUF     1
#define USE_VCE_LF_ROW_INTERNAL_BUF 1
#define USE_SCALAR_ENABLE_BUF       1
#define USE_SCAL_PACKED_MODE_BUF    1

#define SEQ_HEADER_VC1              36
#define SEQ_HEADER_VC1_ADVANCED     128
#define SEQ_HEADER_DIV3             32
#define SEQ_HEADER_VP8              32

#define PIC_HEADER_VC1              8
#define PIC_HEADER_VC1_ADVANCED     4
#define PIC_HEADER_DIV3             12
#define PIC_HEADER_VP8              12

#define ABS(a)	   (((a) < 0) ? -(a) : (a))
#define GET_QUEUE_ELEMENT_SIZE(rp,wp,size)  ((wp-rp+size)%size)
#define QUEUE_IS_FULL(rp,wp,size)  (((wp+1)%size)==rp)
#define QUEUE_IS_EMPTY(rp,wp)  (wp==rp)

// fps should be almost  23.98, 24, 24.98, 25, 29.97, 30, 50, 59.94, 60
#define FPS_IS_REASONABLE(fps) ((fps > 23.5 && fps < 25.5) || (fps > 29.4 && fps < 30.5) || (fps > 49.5 && fps < 50.5) || (fps > 59.5 && fps < 60.5))

#define MIN_UNDEQUEUED_BUFFERS_COUNT 6 //should depend on GPU setting

#define RTK_LM_VIDEO_MEMORY_SIZE (56 << 20) //56MB

#define RTK_PTS_QUEUE_START_FNUM_LOWDELAY 1 // ptsQStart
#define RTK_PTS_QUEUE_START_FNUM 2 // ptsQStart
#define RTK_PTS_QUEUE_START_FNUM_KODI_ZERO 15 // ptsQStart
#define RTK_PTS_QUEUE_LIMIT 5

#define DEF_33BIT_REVERSE_MARGIN 0X989680ll // 10sec
#define DEF_WEBCAM_32BIT_REVERSE 0xFFFFFFFFll
#define DEF_TS_FILE_33BIT_REVERSE ((0x1FFFFFFFFll/90000)*1000000)
#define SEQ_INIT_TIMEOUT_LIMIT 1000
#if defined(__LINARO_SDK__) && defined(VPU_GET_CC)
#define MPEG2_CC_REG_FRAME_MAX  20 // the maximum of VPU register frames
#define MPEG2_CC_RINGBUF_SIZE 2048
#define RTK_CC_SYNC 0x52744B63  // RtKc
#define RTK_CC_HEADER_SIZE 16

typedef struct  {
    unsigned long base;
    unsigned long limit;
    unsigned long wp;
    unsigned long rp;
} RVSD_RINGBUF;
#endif //defined(__LINARO_SDK__) && defined(VPU_GET_CC)
typedef struct PRIVATE_INFO
{
    OMX_U32 infoId;
    OMX_U8  *addr;
} PRIVATE_INFO;

typedef struct OMX_RV_SEGMENT_INFO
{
    OMX_U32 isValid;
    OMX_U32 offset;
} OMX_RV_SEGMENT_INFO;

typedef struct OMX_RV_FRAME_INFO
{
    OMX_U32 numSegments;
    OMX_U32 cntSegments;
    OMX_U32 pTargetAddr;
    OMX_RV_SEGMENT_INFO segment[128];
} OMX_RV_FRAME_INFO;

typedef enum THREAD_STATE
{
    THREAD_RUN       = 0,
    THREAD_PAUSE,
    THREAD_STOP,
    THREAD_DONE,
} THREAD_STATE;
struct OMX_BUFCMD
{
    OMX_U32 phyAddress;
    OMX_U8 *virtAddress;
    OMX_U32 nSize;
    BUFFER_CMD command;
};
typedef struct OMX_DEC_THREAD
{
    pthread_t pThread;
    pthread_cond_t pThreadCond;
    pthread_mutex_t pThreadMtx;
    volatile THREAD_STATE pThreadRun;
    volatile CODEC_STATE nDecState;
    volatile OMX_BOOL bThreadStop;
    OMX_HANDLETYPE ts_mutex;
    OMX_HANDLETYPE ptr_mutex;
    OMX_HANDLETYPE start_state_mutex;
} OMX_DEC_THREAD;
typedef struct OMX_BUFCMD_THREAD
{
    pthread_t pThread;
    pthread_cond_t pThreadCond;
    pthread_mutex_t pThreadMtx;
    volatile THREAD_STATE pThreadRun;
    volatile int nRdPtr;
    volatile int nWrPtr;
    volatile struct OMX_BUFCMD pBufCmd[MAX_BUFCMD_QUEUE];
} OMX_BUFCMD_THREAD;

typedef struct {
    vpu_buffer_t    buf;
    SystemMemory    *smem;
    Uint32          size;
} OMXESBuf;

enum {
    RTK_HEVC_8BIT_LINEAR = 0,
    RTK_HEVC_10BIT_LINEAR = 1,
    RTK_HEVC_ONLY_COMPRESSED = 2,
    RTK_HEVC_8BIT_COMBIND = 3,
    RTK_HEVC_10BIT_COMBIND = 4,
    RTK_HEVC_ONLY_COMPRESSED_VO_WB = 5,
};

typedef struct dec_config_t
{
    OMX_S32 bitFormat;
    OMX_S32 rotAngle;
    OMX_S32 mirDir;
    OMX_S32 useRot;
    OMX_S32 useDering;
    OMX_S32 outNum;
    OMX_S32 checkeos;
    OMX_S32 mp4DeblkEnable;
    OMX_S32 iframeSearchEnable;
    OMX_S32 dynamicAllocEnable;
    OMX_S32 reorder;
    OMX_S32 mpeg4Class;
    OMX_S32 mapType;
    OMX_S32 tiled2LinearEnable;
    OMX_S32 seqInitMode;
    OMX_S32 dispMixerDirect;
    OMX_S32 wtlEnable;
    OMX_S32 wtlMode;	// 1: frame 2: field
    LowDelayInfo lowDelayInfo;

    OMX_S32 FrameCacheBypass   ;
    OMX_S32 FrameCacheBurst    ;
    OMX_S32 FrameCacheMerge    ;
    OMX_S32 FrameCacheWayShape ;

    OMX_S32 skipframeMode;
    OMX_BOOL bLowMemory;
    OMX_BOOL bRenderToV1;
    OMX_BOOL bOnlyCompressed;
    OMX_BOOL bDcSysDebug;

    OMX_S32 scale_width;
    OMX_S32 scale_height;
    OMX_S32 scale_fps;
    OMX_BOOL scale_enable;
    OMX_BOOL bForce8Bit;

    OMX_S32 nHevcOutputType;
    OMX_S32 nRegCountForReset;
    OMX_S32 regFbCountForReset;
    OMX_S32 wtlEnableForReset;
} dec_config_t;

struct TimeStruct
{
    OMX_U32     wPtr;
    OMX_TICKS   nTimeStamp;
    OMX_U32     dStusFlg;
};

struct FrameStruct
{
    long              picType;
    int               errorBlock;
    int               POC;
    signed char       repeatFirstField;//for mpeg2 pts inc calculation
    signed char       mvcViewIdx;
    signed char       topFieldFirst;
    char              pairedFldFrm;
    char              stillVOBU;
    char              reSend;
    signed short      mvcPairIdx;

    VP_PICTURE_MODE_t picMode;
    char              forceFieldMode;

    int               video_full_range_flag;
};

typedef enum QueueEnum
{
    RECEIVE_QUEUE       = 0,
    TIMESTAMP_QUEUE,
    DROP_FROM_RECEIVE_QUEUE,
    DROP_FROM_TIMESTAMP_QUEUE,
} QueEnum;

struct TmeOffStSrt
{
    OMX_TICKS   nTimeStamp;
    OMX_U32     nIdx;
    OMX_U32     nQueIdx;
    OMX_TICKS   nDiffTick;
    OMX_U32     dStusFlg;
};//TimeOffSetStruct

struct StreamProtect
{
    OSAL_ALLOCATOR  alloc;
    OMX_U32         nAllocSize;
    OMX_U32         pBusAddress;
    OMX_U8          *pBusDataAddress;
};

typedef struct RTKALLOCATOR_MEM {
    OSAL_S32    mSize;
    OSAL_U8     *mVirAddr;
    OSAL_U32    mPhyAddr;
    SystemMemory *mBufferMemory;
} RTKALLOCATOR_MEM;

typedef struct VOwbFrmInfo
{

    OMX_S32         dInterlaceQueneNum;
    DecOutputInfo   InterlaceInfo;
    DecOutputInfo   NewInterlaceInfo;
    OMX_U32         pLockAddr[2];
    OMX_U32         pReceivedAddr[2];

    OMX_U32         pLockNextAddr[2];
    OMX_U32         pReceivedNextAddr[2];
    DataQueue       *DecClr_queue;
} VOwbFrmInfo;

typedef struct CalRetInfo
{
    OMX_TICKS    nTimeStamp;
    OMX_TICKS    nEstTime;
    OMX_U32      dStusFlg;
} CalRetInfo;

typedef struct VP92_HDR {
    unsigned int hdr_vp92;

    unsigned int hdr_matrix_coefficients;
    unsigned int hdr_transferCharacteristics;
    unsigned int hdr_display_primaries_x0;
    unsigned int hdr_display_primaries_x1;
    unsigned int hdr_display_primaries_x2;
    unsigned int hdr_display_primaries_y0;
    unsigned int hdr_display_primaries_y1;
    unsigned int hdr_display_primaries_y2;
    unsigned int hdr_white_point_x;
    unsigned int hdr_white_point_y;
    unsigned int hdr_min_mastering_luminance;
    unsigned int hdr_max_mastering_luminance;
} VP92_HDR;

typedef struct AdaptiveHoldBuffer {
    OMX_BOOL            enable;
    OMX_S32             minframeCount;

    struct {
        int             wtlEnable;
        OMX_S32         width;
        OMX_S32         height;
        OMX_S32         stride;
    } info;

    struct {
        OMX_S32         width;
        OMX_S32         height;
        OMX_S32         stride;
    } linear_info;

} AdaptiveHoldBuffer;

typedef struct AdaptivePlayback {
    OMX_BOOL            enable;
    struct {
        OMX_S32         width;
        OMX_S32         height;
    } info;
} AdaptivePlayback;

typedef struct SyncWait {
    pthread_mutex_t     pThreadMtx;
    pthread_cond_t      pThreadCond;
    OMX_S32             sThreadWaitTimeoutMs;
    OMX_S32             sThreadWaitCount;
    OMX_S32             sNumOfWaits;
} SyncWait;

typedef struct DecCount {
    OMX_U32 nFillCount;
    OMX_U32 nQueueCount;
    OMX_U32 nOutputCount;
    OMX_U32 nDispFrameCount;
} DecCount;

void    SyncWait_init       (SyncWait * pInfo, OMX_S32 wait_timeout_ms, OMX_S32 num_of_waits);
void    SyncWait_destroy    (SyncWait * pInfo);
void    SyncWait_lock       (SyncWait * pInfo);
int     SyncWait_sync       (SyncWait * pInfo);
void    SyncWait_unlock     (SyncWait * pInfo);

enum
{
    DBS_INITIALIZED = -1,
    DBS_COMPONENT = 0,
    DBS_NATIVE_WINDOW = 1
};

typedef struct CODEC_VDEC
{
    CODEC_PROTOTYPE base;
    DecHandle       handle;
    DecOpenParam    decOP;
    DecInitialInfo  initialInfo;
    DecOutputInfo   outputInfo;
    DecParam        decParam;
    SecAxiUse       secAxiUse;
    MaverickCacheConfig decCacheConfig;
    DRAMConfig      dramCfg;
    FrameBufferAllocInfo fbAllocInfo;
    FrameBuffer     fbPPU[MAX_PPU_SRC_NUM];
    FrameBuffer     fbUser[MAX_REG_FRAME];
    vpu_buffer_t    vbStream;
    vpu_buffer_t    vbStreamVp9[NUM_BS_BUF];
    OMXESBuf        *pStreamBuf;
    OMXESBuf        *pStreamBufReuse;
    OMX_S32         fbWidth;
    OMX_S32         fbHeight;
    OMX_S32         fbStride;
    OMX_S32         fbLinearStride; //For HEVC
    FrameBufferFormat fbFormat;
    FrameBufferFormat wtlFormat;
    OMX_S32         rotStride;
    OMX_S32         regFbCount;
    OMX_S32         seqInited;
    OMX_S32         ppuEnable;
    OMX_S32         frameIdx;
    OMX_S32         decodedIdx;
    OMX_S32         decodefinish;
    OMX_S32         int_reason;
    OMX_S32         totalNumofErrMbs;
    OMX_S32         needFrameBufCount;
    OMX_S32         instIdx;
    OMX_S32         coreIdx;
    OMX_S32         mapType;
    TiledMapConfig  mapCfg;
    OMX_S32         chunkReuseRequired;
    /** @param extradata pointer to extradata*/
    OMX_U8              *tempHeader; //for MKV HEVC check
    /** @param extradata_size extradata size*/
    OMX_S32         seqHeaderSize;
    OMX_S32         picHeaderSize;
    OMX_S32         tempAllocateSize;
    OMX_S32         ppIdx;
    DataQueue       *disp_queue;
    DataQueue       *streamFreeQ;             /*<< This variable is used when bsmode is PIC_END */
    DataQueue       *streamUsingQ;             /*<< This variable is used when bsmode is PIC_END */
    DataQueue       *streamDecodingQ;             /*<< This variable is used when bsmode is PIC_END */

    OMX_S32         bufferEmptyFlag;        // for bug 41710
    OMX_S32         bufferEmptySize;        // for bug 41710
    OMX_S32         bufferEmptyReciPtsWPtr;

    OMX_U32                 framesize;
    OMX_TICKS               lastTimestamp;
    OMX_TICKS               outTimestamp;
    OMX_S32                 nFrameCycle[TEMP_QUEUE_CNT];
    OMX_S32                 nSkipBCount;
    OMX_U32                 nClkRate;
    struct OutTimeStruct    timestampQueue[MAX_TIME_QUEUE];
    struct TimeStruct       reciveTimestamp[MAX_TIME_QUEUE];
    struct FrameStruct      frameQueue[MAX_TIME_QUEUE];
    OMX_U32                 nFrameWidth;
    OMX_U32                 nFrameHeight;
    OMX_U32                 codecProfile;
    OMX_U32                 nGarbageSize;
    OMX_U32                 nFrameCnt;
    OMX_TICKS               nTimeTick;

//RTK param
    OMX_BOOL            bIsTS; // for pts order
    OMX_U32             nReciPtsWPtr;
    OMX_U32             nReciPtsRPtr;
    OMX_U32             nNotFoundPTSFlg;
    OMX_U32             nTimeoutCount;
    SyncWait            sFlushWait;
    OMX_S32             extraFbNum;
    unsigned long       mSeHandle;
#ifdef TEST_SEQUENCE_CHANGE_BY_HOST
    OMX_S32             seqChangeRequest;
    OMX_S32             seqChangedStreamEndFlag;
    PhysicalAddress     seqChangedRdPtr;
    PhysicalAddress     seqChangedWrPtr;
    OMX_BOOL            bKeepDecode;
    OMX_S32             oldWidth;
    OMX_S32             oldHeight;
#endif
#ifdef USE_ION_ALLOC_FB
    RTKALLOCATOR_MEM   *pIonFb[MAX_REG_FRAME];
    RTKALLOCATOR_MEM   *pIonFbPPU[MAX_REG_FRAME];
#endif
    OMX_S32             startOneFrm;
    OMX_S32             startInitSeq;
    OMX_S32             ptsQStart;
    OMX_S32             bIsDisplay[MAX_REG_FRAME];

    //ENABLE_OUTPUT_BE_DECODE_BUFFER
    OMX_BOOL            bIsRegisterDone;
    OMX_S32             nRegCount;

    OMX_BOOL            bIsMp4Container;
    OMX_BOOL            bIsMkvContainer;
    OMX_BOOL            bIsFirstPacket;
    OMX_RV_FRAME_INFO   pRVHdr;
    OMX_U32             slen;
    OMX_BOOL            bSearchIFrm;
    OMX_BOOL            bWaitDispIFrm;
    OMX_S32             nWaitDispIFrmIdx;
    OMX_S32             nWaitEosFrmIdx;
    OMX_U32             nFrameStartPtr;
    OMX_U32             nUseFrameStartPtr;
    OMX_U32             pPtsSync;
    OMX_BOOL            bStopThumbnailDecode;
    OMX_BOOL            bResetWave4;
    OMX_BOOL            bIsForceInterlaceType;
#ifdef ENABLE_TEE_DRM_FLOW
    TEEC_Context        ctx;
    TEEC_Session        sess;
    RTK_TEEC_Session    rtk_sess;
#endif
    dec_config_t        s_dec_config;
    OMX_HANDLETYPE      ts_mutex;
    OMX_HANDLETYPE      disp_mutex;
    OMX_U32             nPtsCount;
    OMX_BOOL            bNeedDeinterlace;
    OMX_U32             frmIdxInDPB;
#if defined(__LINARO_SDK__) && defined(VPU_GET_CC)
    FILE                *pFifo;
    unsigned long       m_CCDecodeOrderWp[MPEG2_CC_REG_FRAME_MAX];//keeping write pointer by decoder's frame order
    RVSD_RINGBUF        m_RingBuf; // local ring buffer infomation
    void*               m_pBuf; //real local ring buffer, should free if no more used
#endif
    //OMX_HEVC_10BIT_HDR_SUPPORT
    HdrParameterParser  pHdr;
    OMX_BOOL            bCombinedEnable;
    OMX_BOOL            bCombineddLinearCompressed;
    OMX_S32             nCompressedTotalSize;
    OMX_S32             nLinearTotalSize;
    OMX_S32             nFbcYTblSize;
    OMX_S32             nFbcCTblSize;
    vpu_buffer_t        extFbcYTbls[MAX_GDI_IDX];
    vpu_buffer_t        extFbcCTbls[MAX_GDI_IDX];

    ScalerInfo          sclInfo;

    VORPCGlobal         *pVORPC;
    VORPCGlobal         *pVORPC_SeqChg;
    DataQueue           *vowb_queue;
    OMX_BOOL            vo_writeback_enable;
    OMX_BOOL            vo_writeback_close_flg;
    OMX_S32             dIsInterlaceFrm;
    VOwbFrmInfo         stFrmInfo;

    OMX_TICKS           nNextTimePTS;
    OMX_TICKS           nPreTimePTS;
    SystemMemory        *mBSMemory;
    SystemMemory        *mBSMemoryVp9[NUM_BS_BUF];
    SystemMemory        *mSeqHeaderMemory;
    SystemMemory        *mPicHeaderMemory;
    OMX_BOOL            bBSBufUseLargeSizeFlg;
    OMX_BOOL            bCalPTSSkipFlg;
    OMX_TICKS           nCalSkipPTS;
    OMX_U8              nDropFrameThreshold; //percentage
    OMX_U32             nDropFrameIdx;
    OMX_U8              PrevPicRepeatFirstField;//for mpeg2dec pts_inc calculation.
    OMX_U32             useHdrFrmRate;// for mpeg2 pts inc calculation.
    OMX_BOOL            mIsPTSreverseFlg;
    OMX_BOOL            mTimeQueSeqChangeFlg;
    PRIVATE_STRUCT      pRtkInfo;
#ifdef ENABLE_TURBO_DECODING
    OMX_DEC_THREAD      pThreadDec;
    OMX_BOOL            mEnbTurboDecFlg;
#endif
    OMX_U32             checkPTSOffSetEnbCnt;
    OMX_U32             checkPTSOffSetTotalCnt;
    OMX_U32             nCQUsingCnt;
    OMX_BOOL            bBufferFull;
    VP92_HDR            pVP9HDR;
    AdaptiveHoldBuffer  mAdaptiveHoldBuf;
    AdaptivePlayback    mAdaptivePlayback;
#ifdef OMX_DECODER_DOVI
    RTKALLOCATOR_MEM   *pIonVoRegister[MAX_REG_FRAME];
    rtk_hdr_10_infoframe_t m_hdr_info_frame;
    OMX_U32             bCtrPathValid;
#endif
    OMX_BOOL            bNotHasResource;
    OMX_U32             nReciPtsRPtrChk;
    OMX_BOOL            bFlushBfSeqInited;
    RTKALLOCATOR_MEM    *pIonCSD[CSD_NUM];
    OMX_HANDLETYPE      flush_mutex;
    BWControl  *        mGpuBwControl;
    PWControl  *        mCpuPowerControl;
    OMX_U32             frames_sizes[8];//For VP9 super frames
    OMX_U32             frames_this_pts;
    OMX_U32             frames_count;
    OMX_HANDLETYPE      register_mutex;
    OMX_BUFCMD_THREAD   pThreadBufCmd;
    OMX_U32             nSeqInitTimeoutCount;
    OMX_U32             lastWidth;
    OMX_U32             lastHeight;
    OMX_BOOL            EnbKodiZeroFlw;
    OMX_S32             mPTSZeroCnt;
    OMX_TICKS           mSeqChgTimeUs;
    OMX_U32             nCombindFrameWidth;
    OMX_U32             nCombindFrameHeight;
    DecCount            pDecCount;
} CODEC_VDEC;

enum
{
    SKIP_FRM_OFF = 0,
    SKIP_EXCEPT_IDR_FRM = 1,
    SKIP_NON_REF_FRM = 2
};

enum
{
    PTS_UNINIT = 0, //initial state,
    PTS_DEC_SYNC = 1, //got pts info at dec stage.
    PTS_DISP_SYNC = 2 //got pts info at display stage.
};


OMX_S32 codec_vowb_SendBuftoVO(
    CODEC_VDEC *pVpu,
    DecOutputInfo *outputInfo,
    OMX_TICKS nTimeStamp,
    struct OutTimeStruct CalRet
);

OMX_S32 codec_sample_fps(
    CODEC_VDEC *pVpu,
    DecOutputInfo *outputInfo,
    struct OutTimeStruct decFmeInfo
);

OMX_S32 codec_vo_IsDataQueueFull(
    CODEC_VDEC *pVpu
);

OMX_S32 codec_vo_IsVOWBQueueFull(
    CODEC_VDEC *pVpu
);

OMX_U8 *codec_get_FBVirAddr(
    CODEC_VDEC *pVpu,
    OMX_U32 dispFramePhyAddr,
    OMX_S32 *Idx
);

CODEC_STATE codec_vo_ClearWBBufByInterlaceFlw(
    CODEC_VDEC *pVpu,
    OMX_U32 phyAddress,
    OMX_S32 dEOSFlw,
    OMX_S32 dFlushFlw
);

CODEC_STATE codec_InterpolationPTS(
    CODEC_VDEC *pVpu
);

void codec_CleartimeQueueByIdx(
    CODEC_VDEC *pVpu,
    OMX_S32 dIdx
);

void codec_DeltimeQueueByIdx(
    CODEC_VDEC *pVpu,
    OMX_S32 dIdx
);

CODEC_STATE codec_ChkNeedAddCalPTS(
    CODEC_VDEC *pVpu
);

OMX_S32 codec_addPTSInTimeQueue(
    CODEC_VDEC *pVpu,
    OMX_TICKS nTimeStamp,
    OMX_BOOL Isvowbflow,
    struct OutTimeStruct *CalRet
);

CODEC_STATE codec_checkPTSOffSet(
    CODEC_VDEC *pVpu
);

void OMXWriteState(
    OMX_S32 *state,
    OMX_S32 value,
    OMX_HANDLETYPE mutex
);

RetCode OMX_DecGetBitstreamBuffer(
    CODEC_VDEC *pVpu,
    DecHandle handle,
    PhysicalAddress* prdPtr,
    PhysicalAddress* pwrPtr,
    Uint32* size
);

RetCode OMX_DecUpdateBitstreamBuffer(
    CODEC_VDEC *pVpu,
    DecHandle handle,
    Uint32 size
);

OMX_S32 BuildOmxSeqHeader(
    CODEC_VDEC *pVpu,
    OMX_U8* pInputBuffer,
    OMX_U32 pInputBufferLen,
    OMX_BOOL bIsCodecConfig
);

OMX_S32 BuildOmxPicHeader(
    CODEC_VDEC *pVpu,
    OMX_U8* pInputBuffer,
    OMX_U32 pInputBufferLen
);

void VDecAdjustDecOpenParam(
    DecOpenParam* p,
    int mapType,
    OMX_COLOR_FORMATTYPE eColorFormat
);

OMX_S32 HandleDecInitSequenceError(
    DecHandle handle,
    OMX_U32 productId,
    DecOpenParam* openParam,
    DecInitialInfo* seqInfo,
    RetCode apiErrorCode
);

OMX_ERRORTYPE CreateVideoDecoder(
    CODEC_VDEC *pVpu
);

void DestroyVideoDecoder(
    CODEC_VDEC *pVpu
);

void SetVDecConfig(
    CODEC_VDEC *pVpu
);

OMX_TICKS CalculatePTS(
    CODEC_VDEC *pVpu,
    OMX_U32 rdPtr,
    OMX_S32 error,
    struct OutTimeStruct *CalRet
);

int GetSkipFrmMode(
    CODEC_VDEC *pVpu
);

int DropAndWaitDispIFrm(
    CODEC_VDEC *pVpu,
    int frmIdx
);

CODEC_STATE FillInputBuf(
    CODEC_VDEC *pVpu,
    vpu_buffer_t vbStream,
    OMX_U8 *pStreamData,
    OMX_U32 nStreamLen,
    OMX_TICKS nTimeStamp,
    OMX_U32 nFlags
);

CODEC_STATE FillInputBuf_protected(
    CODEC_VDEC *pVpu,
    vpu_buffer_t vbStream,
    OMX_U32 bus_address,
    OMX_U32 nStreamLen,
    OMX_TICKS nTimeStamp,
    OMX_U32 nFlags
);

OMX_BOOL VDecCheckFrameIsFull(
    CODEC_VDEC *pVpu
);

char CheckIfPairedFldFrm(
    CODEC_VDEC *pVpu,
    DecOutputInfo* info,
    VP_PICTURE_MODE_t picMode,
    int curIdx
);

OMX_U32 GetDispQNum(
    CODEC_VDEC *pVpu
);

CODEC_STATE codec_sortPTSOffSetTbl(
CODEC_VDEC *pVpu,
struct TmeOffStSrt OffsetQueue[MAX_TIME_QUEUE],
OMX_S32 *dTimeCnt
);

CODEC_STATE codec_ChkKODIZeroIssue(
    CODEC_VDEC *pVpu
);
CODEC_STATE UpdateRecQueueInfo(
    CODEC_VDEC *pVpu,
    OMX_U32 bIsDecodeFlow
);

CODEC_STATE UpdateRecQueueInfo2(
    CODEC_VDEC *pVpu,
    OMX_U32 bIsDecodeFlow
);

#ifdef OMX_DECODER_DOVI
rtk_dv_vo_register* decoder_get_dolby_vo_register(
    CODEC_VDEC *pVpu,
    DolbyMetadataItem *p_metadata,
    DecOutputInfo *p_bl_display_info
);
#endif

void GetPicType(
    CodStd bitstreamFormat,
    int indexFrameDecoded,
    int picType,
    char *pPicType
);


#ifdef __cplusplus
}
#endif
#endif                       // RTK_VIDEO_COMMON_H

