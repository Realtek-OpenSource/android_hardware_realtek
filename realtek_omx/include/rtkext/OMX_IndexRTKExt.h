#ifndef OMX_IndexRTKExt_h
#define OMX_IndexRTKExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Index.h>


typedef enum OMX_INDEXEXTTYPE_RTKEXT {

    OMX_IndexParamVideoInputPhysical = 0x06600000,  /**< RTK Used for DRM */

    //OMX_IndexVendorStartUnused = 0x7F000000,
    OMX_IndexVendorRTKStartUnused = OMX_IndexVendorStartUnused,
    OMX_IndexParamAudioDts,                  /**< reference: OMX_AUDIO_PARAM_DTSTYPE */
    OMX_IndexParamAudioMlp,                  /**< reference: OMX_AUDIO_PARAM_MLPTYPE */
    OMX_IndexParamAudioWmaPro,               /**< reference: OMX_AUDIO_PARAM_WMAPROTYPE */
    OMX_IndexParamAudioAlac,                 /**< reference: OMX_AUDIO_PARAM_ALACTYPE */
    OMX_IndexParamAudioMS12,                 /**< reference: OMX_AUDIO_PARAM_MS12CFG */
    OMX_IndexParamAudioDSD,                  /**< reference: OMX_AUDIO_PARAM_DSDTYPE */
    OMX_IndexParamAudioDtsHd,                /**< reference: OMX_AUDIO_PARAM_DTSHDTYPE */
    OMX_IndexParamAudioApe,                  /**< reference: OMX_AUDIO_PARAM_APETYPE */
    OMX_IndexParamAudioMpegH,                /**< reference: OMX_AUDIO_PARAM_MPEGHTYPE */

} OMX_INDEXEXTTYPE_RTKEXT;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_IndexRTKExt_h */
/* File EOF */
