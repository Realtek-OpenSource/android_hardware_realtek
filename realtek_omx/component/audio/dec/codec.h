#ifndef RTK_DECODER_H
#define RTK_DECODER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <OMX_Types.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OSAL_RTK.h>
#include <OMX_AudioExt.h>
#include "OMX_AudioRTKExt.h"
#include "dbgmacros.h"
#include "AudioRPCBaseDS_data.h"
#include "EType.h"

    typedef enum
    {
        AUDIO_STOP,
        AUDIO_RUN
    }AUDIO_STATE;

    typedef struct STREAM_BUFFER
    {
        OMX_U8 *bus_data;
        OMX_U32 streamlen;
        OMX_TICKS nTimeStamp;
        OSAL_BUS_WIDTH bus_address; // use this for HW
        OMX_U32 nFlags;
    } STREAM_BUFFER;

    typedef struct STREAM_INFO
    {
        OMX_U32 framesize;   //TODO
        OMX_U32 channels;    // channels
        OMX_U32 samplerate;  // samplerate
    } STREAM_INFO;

    typedef struct FRAME
    {
        OMX_U8 *fb_bus_data; // pointer to DMA accesible output buffer.
        OMX_U32 fb_size;     // buffer size
        OMX_U32 size;        // output frame size in bytes
        OMX_TICKS nTimeStamp;
    } FRAME;

    typedef struct PRIVATE_STRUCT
    {
        OMX_AUDIO_CODINGTYPE AudioFormat;
        OMX_BOOL createAoMode;
        OMX_U32 audioHwSync;
        OMX_U32 inSampleRate;
        OMX_U32 inChannels;
        OMX_U32 inbitsPerSample;
        OMX_U32 outSampleRate;
        OMX_U32 outChannels;
        ENUM_MEDIA_TYPE type;
        OMX_BOOL bDecoderOnSCPU;
        OMX_BOOL bUseProtectBuffer;
    } PRIVATE_STRUCT;

    typedef enum CODEC_STATE
    {
        CODEC_NEED_MORE,
        CODEC_HAS_FRAME,
        CODEC_HAS_INFO,
        CODEC_OK,
        CODEC_EOS,
        CODEC_NEED_WAIT,
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

    typedef struct CODEC_PROTOTYPE CODEC_PROTOTYPE;

// internal CODEC interface
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
        //    CODEC_HAS_FRAME  - codec has one or more frame
        //    CODEC_NEED_WAIT  - input ring buffer full
        //    less than zero   - one of the enumerated error values
        //
        // Parameters:
        //
        //    CODEC_PROTOTYPE  - this codec instance
        //    STREAM_BUFFER    - data to be decoded
        CODEC_STATE(*decode) (CODEC_PROTOTYPE *, STREAM_BUFFER *);

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
        //  CODEC_NEED_MORE  - nothing happened, codec needs more data.
        //  CODEC_HAS_INFO   - headers were parsed and information about stream is ready.
        //  CODEC_OK         - everything OK but no frame was available.
        //  CODEC_HAS_FRAME  - got frame ok.
        //  CODEC_EOS        - end of stream
        //  less than zero   - one of the enumerated error values
        //
        // Parameters:
        //
        //  CODEC_PROTOTYPE  - this codec instance
        //  FRAME            - location where frame data is to be written
        //  OMX_BOOL         - end of stream (EOS) flag
        //
        CODEC_STATE(*getframe) (CODEC_PROTOTYPE *, FRAME *, OMX_BOOL);

        //Get the last frame from the decoder.
        CODEC_STATE(*getfakeframe) (CODEC_PROTOTYPE *, FRAME *);

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
        //int (*scanframe) (CODEC_PROTOTYPE *, STREAM_BUFFER *, OMX_U32 * first,
        //                  OMX_U32 * last);

        void (*reset) (CODEC_PROTOTYPE *);
        //Flush input ring and output ring buffer
        void (*flush) (CODEC_PROTOTYPE *);

        //Set decoder state
        void (*setstate) (CODEC_PROTOTYPE *, AUDIO_STATE);

        //Get decoder Mode
        int (*getMode) (CODEC_PROTOTYPE *);

        //Send EOS
        void (*sendEOS) (CODEC_PROTOTYPE *);
    };

OMX_AUDIO_PARAM_ALACTYPE *decoder_get_alac_info(void *arg);
OMX_AUDIO_PARAM_DSDTYPE *decoder_get_dsd_info(void *arg);
OMX_BOOL decoder_check_ms12_enable(void *arg);
void decoder_get_ms12_use_case(void *arg, AUDIO_MS_USE_CASE *use_case);
void decoder_get_ms12_init_param(void *arg, AUDIO_MS_INIT_PARAMS *init_args);
void decoder_get_ms12_runtime_param(void *arg, AUDIO_MS_RUNTIME_PARAMS *args);
void decoder_print_ms12_setting(void *arg);
void ms12_memcpy_init_param(AUDIO_MS_INIT_PARAMS *init_arg, OMX_AUDIO_MS_INIT_PARAMS *omx_init_args);
void ms12_memcpy_use_case(AUDIO_MS_USE_CASE *use_case, OMX_AUDIO_MS_USE_CASE *omx_use_case);
void ms12_memcpy_runtime_param(AUDIO_MS_RUNTIME_PARAMS *args, OMX_AUDIO_MS_RUNTIME_PARAMS *pParams);
void ms12_print_parameter_settings(OMX_AUDIO_PARAM_MS12CFG * ms12Cfg);

#if defined(__LINARO_SDK__)
int32_t property_get_env(char* property, char* setting);
#endif

#ifdef __cplusplus
}
#endif

#endif //RTK_DECODER_H
