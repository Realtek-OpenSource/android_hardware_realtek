#ifndef CODEC_RTK_H
#define CODEC_RTK_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "hresult.h"
#include "AudioInbandAPI.h"
#include "audio_common.h"
#include "AudioRPC_System.h"
#include <system/RingBuffer.h>

#include "codec.h"
#include "EType.h"

#ifdef ENABLE_TEE_DRM_FLOW
#include "tee_client_api.h"
#include "tee_api.h"
#endif

//#ifndef __LINARO_SDK__
#define ENABLE_GLOBAL_PP
//#endif
#define ENABLE_RAWAAC_LOW_THRESHOLD_DECODE_MODE
//#define Write_PCM //store .pcm file for testing

#define DEFAULT_COUNT                100
#define DEFAULT_SLEEP_TIME           1000

#ifndef UNUSED_PARAMETER
#define UNUSED_PARAMETER(x) (void)(x)
#endif

#ifndef bool
#define bool unsigned char
#endif

#ifdef __LINARO_SDK__
#define AUDIO_DEC_INPUT_BUF_SIZE         (256*1024)
#define AUDIO_DEC_OUTPUT_BUF_SIZE        (64*1024)
#define AUDIO_DEC_ICQ_BUF_SIZE           (64*1024)
#define AUDIO_PP_OUT_BUF_SIZE            (64*1024)
#define AUDIO_DEC_PTS_BUF_SIZE           (64*1024)
#define AUDIO_DEC_RAWOUTINFO_BUF_SIZE    (16*1024)
#else
#define AUDIO_DEC_INPUT_BUF_SIZE         (36*1024)
#define AUDIO_DEC_OUTPUT_BUF_SIZE        (32*1024)
#define AUDIO_DEC_ICQ_BUF_SIZE           (16*1024)
#define AUDIO_PP_OUT_BUF_SIZE            (64*1024)
#define AUDIO_DEC_PTS_BUF_SIZE           (16*1024)
#define AUDIO_DEC_RAWOUTINFO_BUF_SIZE    (16*1024)
#endif
#ifdef AUDIO_READER
#define AUDIO_READER_BUF_SIZE            (32*1024)
#define AUDIO_DEFAULT_OUTPUT_CHANNEL     2
#endif

#define MAX_INPUT_BUFFER_SIZE            (128*1024)
#define AUDIO_DEC_TMP_BUF_SIZE           (36*1024)
#define AUDIO_DEC_TMP_BUF_SIZE_2         (2*1024)

#define AUDIO_RTKEXT_DEC_INPUT_BUF_SIZE  (256*1024)
#define AUDIO_RTKEXT_DEC_OUTPUT_BUF_SIZE (74*1024)
#define AUDIO_RTKEXT_DEC_ICQ_BUF_SIZE    (64*1024)
#define AUDIO_RTKEXT_PP_OUT_BUF_SIZE     (64*1024)
#define AUDIO_RTKEXT_DEC_PTS_BUF_SIZE    (64*1024)

#define AUDIO_DEC_OUTPIN             8
#define APP_MAX_INPIN_NUM            4
#define APP_OUTPIN_ID                APP_MAX_INPIN_NUM
#define AUDIO_DMX_OUTPIN             2

#define INBAND_PTS_INFO_SIZE    sizeof(AUDIO_DEC_PTS_INFO)
#define INBAND_PCM_SIZE         sizeof(AUDIO_INFO_PCM_FORMAT)
#define INBAND_EOS_SIZE         sizeof(AUDIO_DEC_EOS)
#define INBAND_INDEX_SIZE       sizeof(AUDIO_INFO_CHANNEL_INDEX_NEW)
#define INBAND_INFO_SIZE        sizeof(AUDIO_INBAND_PRIVATE_INFO)
#define INBAND_NEW_FMT_SIZE     sizeof(AUDIO_DEC_NEW_FORMAT)
#define INBAND_DEMUX_INFO_SIZE  sizeof(AUDIO_DEMUX_BUFFER_INFO)
#define INBAND_NONPCM_SIZE      sizeof(AUDIO_INFO_SPDIF_NONPCM_CFG)
#define AUDIO_START_THRES    (INBAND_PCM_SIZE + INBAND_INDEX_SIZE + (2 * INBAND_INFO_SIZE))

#ifdef AUDIO_ON_SCPU_MS12
#define INBAND_INDEX_SIZE_MS12  sizeof(AUDIO_INFO_CHANNEL_INDEX_MS12)
#define AUDIO_START_THRES_MS12    (INBAND_PCM_SIZE + INBAND_INDEX_SIZE_MS12 + (2 * INBAND_INFO_SIZE))
#endif

#define NEW_CHANNEL_INDEX_INFO_SIZE  sizeof(AUDIO_INFO_CHANNEL_INDEX_NEW)
#define OLD_CHANNEL_INDEX_INFO_SIZE  sizeof(AUDIO_INFO_CHANNEL_INDEX_OLD)

#define DEC_BYTE_SWAP(_dst, value) \
    _dst = (long)((value & 0x000000ff) << 24) | (long)(((value & 0x0000ff00) >> 8) << 16) | (long)(((value & 0x00ff0000) >> 16) << 8) | (long)((value & 0xff000000) >> 24);

#define AUDIO_SYNC_WORD              0x62773030
#define RAWAAC_SYNC_WORD             0x4d773030

typedef enum
{
    ENUM_AUDIO_PCM_FORMAT,                              //0
    ENUM_AUDIO_FRAME_SIZE,
    ENUM_AUDIO_FRAME_BOUNDARY,
    ENUM_AUDIO_DEC_EXT_BS,
    ENUM_AUDIO_DEC_CFG,
    ENUM_AUDIO_CS_DATA,
    ENUM_AUDIO_AI_STATE,
    ENUM_AUDIO_SPDIF_BS_INFO,
    ENUM_AUDIO_DEMUX_BUFFER_INIT,
    ENUM_AUDIO_CHANNEL_INDEX,                           //9
    ENUM_AUDIO_ECHO_INFO,
// add by ny /////////////////////////////////
    ENUM_AUDIO_ENC_CFG,
// add end ///////////////////////////////////
    ENUM_AUDIO_REFRESH_RBUFPTR,
    ENUM_AUDIO_SWITCH_FOCUS,                            //d
    ENUM_AIN_SWITCH_FOCUS,
    ENUM_AUDIO_CHANNEL_SOURCE,      //obsolete
    ENUM_AUDIO_SPDIF_NONPCM_CFG,
    ENUM_AOUT_MUTE_INFO,
    ENUM_AOUT_VOLUME_LEVEL,
    ENUM_AOUT_SPDIF_SOURCE_SELECT,
    ENUM_AOUT_KARAOKE_CONTROL,
    ENUM_AOUT_SPDIF_DIFF,
    ENUM_AUDIO_CHANGE_PP_OUT_SAMPLERATE,
    ENUM_APP_NIGHT_MODE_CFG,  // old version
    ENUM_APP_REINIT_PIN,
    ENUM_AUDIO_BS_ERR,
    ENUM_AUDIO_PTS_TEST,
    ENUM_AOUT_DROP_PTS,
    ENUM_APP_NIGHT_MODE_INFO, // for night mode global var
    ENUM_AUDIO_MPEG_TYPE,
    ENUM_AUDIO_NOISE_INFO,
    ENUM_AUDIO_SOUND_EVENT,
    ENUM_AUDIO_PRIVATE_CGMS_INFO,                       //21
// add by taro for inband /////////////////////////////////
    ENUM_AUDIO_INBAND_EOS_INFO,
    ENUM_AUDIO_INBAND_PTS_INFO,
//    ENUM_AUDIO_INBAND_PRIVATE_INFO,
    ENUM_AUDIO_INBAND_NEWFORMAT_INFO,
// end add by taro for inband /////////////////////////////////
    ENUM_AUDIO_DEC_GET_FORMAT,
// for trans-encoder, add by isometry
    ENUM_AUDIO_TRANSENC_BS_INFO,
    ENUM_AUDIO_TRANSENC_BUFFER_INIT,
    ENUM_AUDIO_TRANSENC_NONPCM_CFG,
    ENUM_AUDIO_SRC_CHANGE,
// end for trans-encoder
// send aac raw out info
    ENUM_AUDIO_AAC_RAW_OUT_INFO,
    ENUM_AUDIO_FLASH_AO,
    ENUM_AUDIO_IN_DATA_MEASURE,
    ENUM_AUDIO_DECODER_NEWFORMAT,
    ENUM_AUDIO_PASSTHROUGH_MODE,
    ENUM_AUDIO_DTS_DOWNMIX,
    ENUM_AUDIO_AAC_DOWNMIX,
    ENUM_AUDIO_KARAOKE_INFO, // for Karaoke mixer, add by Chris
#ifdef AUDIO_RAW_OUT_MORE_BYTES
    ENUM_AUDIO_DECODER_EOS,      // for raw out, decoder inform AO to raw out more 64 bytes.
#endif
    ENUM_AUDIO_GET_FLASH_PINID,
    ENUM_AUDIO_RELEASE_FLASH_PINID,
    ENUM_AUDIO_CONTROL_FLASH_VOLUME,
    ENUM_AUDIO_DEC_SUPPORT_RATE,
#ifdef AUDIO_TV_PLATFORM
    ENUM_AUDIO_SPDIF_OUT_CS_INFO,
    ENUM_AUDIO_DEC_DELAY_RP,
    ENUM_AUDIO_ANALOG_INPUT_CLOCK_INFO,
    ENUM_AIN_ATV_SET_CLOCK,
    ENUM_AIN_INOUT_CH_SELECT,
    ENUM_AIN_SET_FS_CLOCKSRC,
    ENUM_AIN_SET_PATH_DATA_OUT,
    ENUM_AIN_SET_INTERLEAVE_OUT,
#ifdef SUPPORT_GLOBAL_AI
    ENUM_AIN_SET_OUT_FMT,
#endif // SUPPORT_GLOBAL_AI
#endif // AUDIO_TV_PLATFORM
    ENUM_APP_AGC_MODE_CONFIG,
    ENUM_AO_LOW_DELAY_PARAMETERS,
    ENUM_AIN_CONNECT_ALSA
} ENUM_AUDIO_INFO_TYPE;

typedef struct
{
    ENUM_AUDIO_INFO_TYPE    infoType;
    AUDIO_PCM_FORMAT        pcmFormat;
    long                    start_addr;
    int                     max_bit_rate;
} AUDIO_INFO_PCM_FORMAT;

//#ifdef NEW_CHANNEL_INDEX_TYPE//AUDIO_ON_SCPU  // should be 4 bytes field for easy endian change
typedef struct
{
    ENUM_AUDIO_INFO_TYPE    infoType;
    long channel_index[8];
    long start_addr;
    long dual_mono_flag;
} AUDIO_INFO_CHANNEL_INDEX_NEW;

typedef struct
{
    ENUM_AUDIO_INFO_TYPE    infoType;
    char channel_index[8];
    long start_addr;
    char dual_mono_flag;
} AUDIO_INFO_CHANNEL_INDEX_OLD;

#ifdef AUDIO_ON_SCPU_MS12
typedef struct
{
    ENUM_AUDIO_INFO_TYPE    infoType;
    long channel_index[8];
    long start_addr;
    long dual_mono_flag;
} AUDIO_INFO_CHANNEL_INDEX_MS12;
#endif

typedef struct
{
    ENUM_AUDIO_INFO_TYPE    infoType;
    long*   rp_addr; // non pcm rp addr
    long    base;
    long    limit;
    long*   wp_addr; // demux wp addr
    long*   cp_addr; // demux rp addr, add for bug 25179, when decoder decode very fast to demux wp, if call _AO_set_non_pcm_param() after _AO_flush_non_pcm_info_queue() ,it blocked
    long    pinID;   // APP add this info for AO
} AUDIO_DEMUX_BUFFER_INFO;

typedef  struct
{
    ENUM_AUDIO_INFO_TYPE    infoType;
    int     spdif_non_pcm_type; // codec type
    int     data_type;          // codec sub-type
    long    pinID;              // APP add this info for AO
} AUDIO_INFO_SPDIF_NONPCM_CFG;

typedef enum
{
    BS,
    COMMAND
} DELIVER_WHAT;

enum
{
    RTKExtractor_Normal = 0x100000,
    RTKExtractor_NOP,
    RTKExtractor_WaitSeek
};

/* audio format information (PRIVATEINFO_AUDIO_FORMAT) */
typedef struct _tagAUDIOFORMAT {
    ENUM_MEDIA_TYPE type;          /* format code, see "StreamClass/EType.h" */
    ENUM_MEDIA_TYPE systemType;    /* system format code, see "StreamClass/EType.h" */
    unsigned char   emphasis;      /* non-zero (true) means emphasis ON */
    unsigned char   mute;          /* non-zero (true) means mute ON */
    unsigned char   bitsPerSample;
    unsigned int    numberOfChannels;
    unsigned int    samplingRate;
    unsigned int    dynamicRange;  /* follow DVD-V spec, Page VI5-22 */
    int privateData[6];
} AUDIOFORMAT;

typedef struct
{
    int mIonSize;
    ion_user_handle_t mIonHandle;
    unsigned int mIonPhyAddr;
    unsigned int mIonVirAddr;
} ION_BUFFER;

typedef struct
{
    int type;
    int size;
    bool detectflag;
    unsigned int mPhyAddr;
    unsigned int mVirAddr;
} CMD_BUFFER;

typedef struct _WAVEFORMATEX {
    uint16_t wFormatTag;
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
    uint16_t cbSize;
    uint16_t reserved;
} WAVEFORMATEX;


typedef enum
{
    ENUM_AUDIO_NULL_CHANNEL_INDEX = 0,

    ENUM_AUDIO_LEFT_FRONT_INDEX = 1,            // L
    ENUM_AUDIO_RIGHT_FRONT_INDEX = 2,           // R
    ENUM_AUDIO_CENTER_FRONT_INDEX = 5,          // C
    ENUM_AUDIO_LFE_INDEX = 6,                   // LFE
    ENUM_AUDIO_LEFT_SURROUND_REAR_INDEX = 3,    // Ls or Lsr
    ENUM_AUDIO_RIGHT_SURROUND_REAR_INDEX = 4,   // Rs or Rsr
    ENUM_AUDIO_LEFT_OUTSIDE_FRONT_INDEX = 7,    // ENUM_AUDIO_LEFT_SURROUND_SIDE_INDEX,  Lss
    ENUM_AUDIO_RIGHT_OUTSIDE_FRONT_INDEX = 8,   // ENUM_AUDIO_RIGHT_SURROUND_SIDE_INDEX, Rss
    ENUM_AUDIO_SPDIF_LEFT_CHANNEL_INDEX = 9,
    ENUM_AUDIO_SPDIF_RIGHT_CHANNEL_INDEX = 10,

    ENUM_AUDIO_SURROUND_INDEX = 11,
    ENUM_AUDIO_CENTER_SURROUND_REAR_INDEX = 12,
    ENUM_AUDIO_OverHead_INDEX = 13,

    ENUM_AUDIO_LEFT_SURROUND_INDEX = 14,
    ENUM_AUDIO_RIGHT_SURROUND_INDEX = 15,
    ENUM_AUDIO_LEFT_FRONT_HIGH_INDEX = 16,
    ENUM_AUDIO_RIGHT_FRONT_HIGH_INDEX = 17,
    ENUM_AUDIO_LEFT_INNER_FRONT_INDEX = 18,
    ENUM_AUDIO_RIGHT_INNER_FRONT_INDEX = 19,
    ENUM_AUDIO_LEFT_REAR_INDEX = 20,
    ENUM_AUDIO_RIGHT_REAR_INDEX = 21,
    ENUM_AUDIO_LEFT_SURROUND_DIRECT_INDEX = 22,
    ENUM_AUDIO_RIGHT_SURROUND_DIRECT_INDEX = 23,
    ENUM_AUDIO_CENTER_FRONT_HIGH_INDEX = 24,
    ENUM_AUDIO_LFE2_INDEX = 25,

    ENUM_AUDIO_SPDIF_NON_PCM_TYPE = 256,
    ENUM_AUDIO_ENABLE_DOWNMIX = 257
} ENUM_AUDIO_CHANNEL_OUT_INDEX;

#if defined(MS12_FLOW_EN) || defined(UDC_PLAYER_EN)
typedef struct
{
    OMX_BOOL           isHasEncoder;
    OMX_BOOL           isHasConverter;
    OMX_BOOL           isListeningTest;
    OMX_BOOL           isDDPAssocPin;
    OMX_U8             inputPinMap;
    OMX_BOOL           isFileWriteTest;
    OMX_U8             MS12PPOutChNum;
    OMX_S32            MS12PPOutSampleRate;
    OMX_S8             fileWritePinType;
    OMX_BOOL           isFirstFileWrite;
    OMX_U32            fileWriteTotalSamplesPerCh;
    OMX_BOOL           isDDPHasSubstream;
    OMX_BOOL           isDecEOS;
    OMX_BOOL           gotDecEOS;

    OMX_AUDIO_MS_INPUT_TYPE decType;
    OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType;
    OMX_S8             ppChMapIdx[8];//L, R, C, LFE, Ls, Rs, Lss, Rss
    OMX_U8             fileWriteChNum;
    OMX_U8             isDualMain;
    OMX_U8             dummyInputMap;
    OMX_BOOL           isDummyInput;
    OMX_U32            fileSwitchPTS;
    OMX_BOOL           isSwitchFile;
    OMX_BOOL           isSetDecInitDropByPTS;
    OMX_S64            DecInitDropPTS;
    OMX_U32            decInitPTSOffset;
    OMX_BOOL           isSetMSPPRun;
    OMX_BOOL           isDropRcvPTS;
    OMX_BOOL           isSetDecDropByPTS;
    OMX_S64            DecDropPTS;
    OMX_BOOL           isAddAC4SyncWord;
    OMX_S8             outputPinType;

    char output_file[32];
} MS12_STRUCT;
#endif

typedef struct
{
    CODEC_PROTOTYPE base;
    long audioDecID;
    long audioAPPID;
    long audioOutID;
    long audioAPPPinID;
    long frameSize;
    bool isInitial;
    bool isInitial_Secure;
    bool isGetInfo;
    pthread_mutex_t gOmxLockGetinfo;
    bool isRTKExtractor;
    bool createAoMode;
    bool bDecoderOnSCPU;
#if defined(ATMOS_DEMO)
    unsigned int ms12mode;
#endif
    bool bUseProtectBuffer;
    bool mUsedInband;
    bool mUseLargeBuff;
    bool mUseResample;
    bool mUseRemix;
    struct resampler_itfe *mResampler;
#ifdef ENABLE_TEE_DRM_FLOW
    TEEC_Context        ctx;
    TEEC_Session        sess;
    RTK_TEEC_Session    rtk_sess;
#endif

    FRAME lastFrame;
    volatile OMX_S64 inPtsInfo;
    volatile OMX_S64 lastInPtsInfo;
    volatile OMX_S64 outPtsInfo;
    volatile bool isWaitSeek;
    AUDIOFORMAT audioFormat;
    unsigned int nframesize;    //framesize info from audiofw
    unsigned int audio_channel; //channel info from audiofw
    unsigned int audio_rate;    //sample rate info from audiofw
    unsigned int outChannels;   //desired output channel in transcode
    unsigned int outSampleRate; //desired output samplerate in transcode
    AUDIO_STATE audioState;//only use in CreateAoMode

#ifdef ENABLE_TEE_DRM_FLOW
    CMD_BUFFER  mSecure2INFO;
    IonAllocator *     mAllocatorTMP;
    IonAllocator *     mAllocatorTMP2;
    IonAllocator *     mAllocatorTMP_Secure;
    IonAllocator *     mAllocatorTMP_Secure2;
#endif
    RingBuffer *       mRingBufferBS;
    RingBuffer *       mRingBufferICQ;
    RingBuffer *       mRingBufferPTS;
    RingBuffer *       mRingBufferRawOutInfo;
    RingBuffer *       mRingBufferOutRing[AUDIO_DEC_OUTPIN];
    RingBuffer *       mRingBufferDECOUTPIN[AUDIO_DEC_OUTPIN];

    REFCLOCK* refClock;
    int mIonFd;
    ION_BUFFER mRefClockInstance;
    uint32_t audioHwSync;
    int32_t mSharefd;

    AUDIO_DEC_NEW_FORMAT infoFromRTKExtractor;
    void *omx_decoder;  // pointer to OMX_DECODER
#if defined(MS12_FLOW_EN) || defined(UDC_PLAYER_EN)
    long audioMS12PPID;
    long audioMS12PPPinID;
    long audioMS12EncID;
    long audioMS12RawCnvtrID;
    long audioMS12RawDecPPPinID;//pp pin id that connect to ddp decoder(as transcoder)
    bool isStateRun;
    bool isSetAudioFormat;
    bool isGetFileWriteChNum;
    MS12_STRUCT    ms12struct;

    RingBuffer *       mRingBufferMSPPOut[AUDIO_DEC_OUTPIN];
    RingBuffer *       mRingBufferMSEncBSOut;
    RingBuffer *       mRingBufferMSCnvtrRawOut;
    RingBuffer *       mRingBufferMSPPPTS;
    RingBuffer *       mRingBufferMSPPDmxOut[2];
    RingBuffer *       mRingBufferMSPPRawOut[AUDIO_DEC_OUTPIN];
    RingBuffer *       mRingBufferMSEncPTS;
    RingBuffer *       mRingBufferMSDecSubStrmOut[AUDIO_DEC_OUTPIN];
    RingBuffer *       mRingBufferMSCnvtrPTS;
#endif
    OMX_S8             mChMapIdx[8];//L, R, C, LFE, Ls, Rs, Lss, Rss
} CODEC_RTK;

// create codec instance
CODEC_PROTOTYPE *RTK_Audio_decoder_create(PRIVATE_STRUCT pRtkInfo, void *);

CODEC_STATE CheckAudioInfo(CODEC_RTK *arg);
RingBuffer *codec_ao_RingBuffer_alloc(int dRingallocSize, bool swap);
HRESULT DeliverSegmentEnd(CODEC_RTK *arg, int EOSID);
HRESULT aacSetParam(OMX_AUDIO_PARAM_ANDROID_AACPRESENTATIONTYPE *params);

HRESULT DeliverCmd(unsigned char *pData, long Size, CODEC_RTK *arg);
HRESULT DeliverPTS(CODEC_RTK *arg);
HRESULT DeliverNewSegment(CODEC_RTK *arg);

int GetSampleIndex(unsigned int sampleRate);
int detectAudioSpecicConfig(CODEC_PROTOTYPE *arg, STREAM_BUFFER *buf);
long GetGeneralInstanceID(long instanceID, long pinID);
int32_t ionAllocate(int ionfd, ion_user_handle_t *ionHandle, unsigned int *phyAddr, unsigned char *virtAddress, unsigned int size, int32_t sharefd);

HRESULT UnInitRawOutInfoQ(CODEC_RTK *arg);
CODEC_STATE GetFrameSize(CODEC_RTK *arg);

#ifdef __cplusplus
}
#endif
#endif // CODEC_RTK_H
