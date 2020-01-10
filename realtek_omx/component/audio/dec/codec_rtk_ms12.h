#ifndef CODEC_RTK_MS12_H
#define CODEC_RTK_MS12_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "codec.h"
#include "EType.h"
#include "sideband_audio.h"

//#define DBG_OMX_MS12_MEM_LEAK

#ifdef DBG_OMX_MS12_MEM_LEAK
#define DBG_MS12_MEM ALOGD
#else
#define DBG_MS12_MEM(...)
#endif

typedef struct
{
    OMX_U32 dummyInputMap;
    OMX_U32 fileSwitchPTS;
}OMX_AUDIO_PARAM_MS12DUMMY;

CODEC_STATE decoder_decode_ms12(CODEC_PROTOTYPE *arg, STREAM_BUFFER *buf);
void        decoder_destroy_ms12(CODEC_PROTOTYPE *arg);
void        decoder_flush_ms12(CODEC_PROTOTYPE *arg);
CODEC_STATE decoder_getframe_ao_ms12(CODEC_PROTOTYPE *arg, FRAME *frame, OMX_BOOL eos);
CODEC_STATE decoder_getframe_ms12(CODEC_PROTOTYPE *arg, FRAME *frame, OMX_BOOL eos);
OMX_BOOL    decoder_ms12_is_ddpdec_has_substream(void *arg);
CODEC_STATE decoder_decode_ms12_filewrite(CODEC_PROTOTYPE *arg, STREAM_BUFFER *buf);
void        decoder_destroy_ms12_filewrite(CODEC_PROTOTYPE *arg);
CODEC_STATE decoder_getframe_ms12_filewrite(CODEC_PROTOTYPE *arg, FRAME *frame, OMX_BOOL eos);
OMX_BOOL    decoder_check_if_ms12_listening(void *arg);
OMX_BOOL    decoder_check_ms12_has_encoder(void *arg);
OMX_U8      decoder_ms12_get_inputpin_map(void *arg);
OMX_S8      decoder_ms12_get_filewrite_pin_type(void *arg, char *output_file_name);
OMX_BOOL    decoder_get_ms12_dual_main(void *arg);
OMX_BOOL    decoder_check_ms12_has_update_param(void *arg);
OMX_U8      decoder_get_ms12_dummy_input_map(void *arg);
void        decoder_get_ms12_update_param(void *arg, AUDIO_MS_PARAM_UPDATE_S *args);
OMX_BOOL    decoder_check_ms12_has_converter(void *arg);
OMX_U8      decoder_get_ms12_file_write_nch(void *arg, OMX_S8 fileWritePinType);
void        decoder_ms12_set_omx_dec_eos(void *arg, int pin);
OMX_S8      decoder_ms12_get_output_pin_type(OMX_S8 fileWritePinType);
OMX_AUDIO_MS12_INPUT_PIN_TYPE decoder_get_ms12_input_pin_type(void *arg);
OMX_AUDIO_MS_INPUT_TYPE       decoder_get_ms12_decoder_type(void *arg);

OMX_AUDIO_PARAM_MS12CFG* HACK_Malloc_MS12Cfg(void *arg);


HRESULT SetupMS12Config(CODEC_RTK *arg);
void InitMutexMS12(CODEC_RTK *this);
void InitializeMS12Var(CODEC_RTK *this);
void DestroyOMXMutex();

void CreateDecoderModule(CODEC_RTK *this, AUDIO_RPC_INSTANCE *instance, CLNT_STRUCT *clnt);
void CreateMS12PPModule(CODEC_RTK *this, AUDIO_RPC_INSTANCE *instance);
void DestroyMS12PPModule(CODEC_RTK *this);
void DestroyDecoderModule(CODEC_RTK *this);


void    InitDDPSubstreamRingBuf(CODEC_RTK *this);
HRESULT InitCnvtrDwnstrmICQMS12(CODEC_RTK *arg);

void SetGlobalOMXThreadInitedFlag(CODEC_RTK *this);
int  DeleteOMXAudioThread(OMX_AUDIO_MS12_INPUT_PIN_TYPE inType);

HRESULT SetAllDecodersRun(CODEC_RTK *this);
CODEC_STATE CheckAudioInfoMS12(CODEC_RTK *arg);
CODEC_STATE GetAudioDecInfoMS12(CODEC_RTK *this, OMX_BOOL isDecLoop);

AUDIO_IO_PIN GetMS12DecoderOutputPinID(CODEC_RTK *arg);
AUDIO_IO_PIN GetMS12DecoderInputPinID(CODEC_RTK *arg);
AUDIO_IO_PIN GetMS12DecoderICQPinID(CODEC_RTK *arg);
AUDIO_IO_PIN GetMS12DecoderDwnstrmICQPinID(CODEC_RTK *arg);
int GetMinOutputFrameSize(CODEC_RTK *this);
OMX_AUDIO_MS12_INPUT_PIN_TYPE GetMSMajorInputPinType(CODEC_RTK *this, OMX_U8 dummyInputMap);


HRESULT DeliverMS12InitParams(CODEC_RTK *arg);
HRESULT DeliverAudioFormatMS12(CODEC_RTK *arg);
HRESULT DeliverAudioFrameMS12(unsigned char *pData, long Size, CODEC_RTK *arg);
HRESULT DeliverAudioFrameMS12RawAAC(STREAM_BUFFER *buf, CODEC_RTK *this);
HRESULT DeliverMS12RuntimeUpdateParams(OMX_AUDIO_ms12_update_params *pParams);

void FlushMS12PPDwnmixOutput(CODEC_RTK *this);
void FlushMS12PPRawOutput(CODEC_RTK *this);
void FlushMS12PPMainOutput(CODEC_RTK *this);

void DeliverMSMajorDecoderPin(CODEC_RTK *this, OMX_S32 startPTS, OMX_U8 dummyInputMap);
void DeliverMSCertPlatfromType(CODEC_RTK *this, int platformType);
void DeliverMSPPRun(CODEC_RTK *this);
void DeliverMSDecInitPTSOffset(CODEC_RTK *this);
void DeliverMSPPOutputPinType(CODEC_RTK *this, int outputType);
void DeliverMSDecDropDataByPTS(CODEC_RTK *this, OMX_S64 dropAfterPTS);

void MS12DeliverMSDecDropDataByPTS(CODEC_RTK *this, OMX_S64 dropAfterPTS);
void MS12DeliverMSPPStart(CODEC_RTK *this);
void MS12DeliverMSPPPause(CODEC_RTK *this);

int MS12HandleSwitchFileProcess(CODEC_RTK *this);

void ms12_memcpy_update_param(AUDIO_MS_PARAM_UPDATE_S *args, OMX_AUDIO_ms12_update_params *pParams);

HRESULT CheckIsSupportMS12();

#ifdef __cplusplus
}
#endif
#endif // CODEC_RTK_MS12_H
