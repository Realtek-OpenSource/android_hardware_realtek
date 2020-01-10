#ifndef ENCODER_VIDEO_H
#define ENCODER_VIDEO_H

#ifdef __cplusplus
extern  "C" {
#endif

#include "codec.h"
#include "OMX_Video.h"

    typedef struct VENC_CONFIG
    {
        // ----------config-----------
        OMX_VIDEO_PARAM_AVCTYPE avc_config;
        OMX_VIDEO_PARAM_MPEG4TYPE mp4_config;
        OMX_VIDEO_PARAM_H263TYPE h263_config;

        // ---------codingctrl-----------
        // sliceSize * 16
        // Only slice height can be changed once stream has been started.
        OMX_U32 nSliceHeight;

        // I frame period.
        OMX_U32 nPFrames;

        // seiMessages
        OMX_BOOL bSeiMessages;

        // videoFullRange
        OMX_U32 nVideoFullRange;

        // constrainedIntraPrediction
        OMX_BOOL bConstrainedIntraPrediction;

        // disableDeblockingFilter
        OMX_BOOL bDisableDeblocking;

        ENCODER_COMMON_CONFIG common_config;
        RATE_CONTROL_CONFIG rate_config;
        PRE_PROCESSOR_CONFIG pp_config;
        ERROR_CORRECT_CONFIG err_config;

        // use store meta data mode
        OMX_BOOL bUseStoreMetaData;

        // use interlace encoding mode
        OMX_BOOL bEncodeToInterlace;

        // append AUD data
        OMX_BOOL bEnableAUD;

        // rotate image
        OMX_S32 nRotateAngle;
    } VENC_CONFIG;

// create codec instance
    ENCODER_PROTOTYPE* RTKHwEncOmx_encoder_create_video(const VENC_CONFIG* config, OMX_VIDEO_CODINGTYPE eCompressionFormat);


#ifdef __cplusplus
}
#endif
#endif // ENCODER_VIDEO_H

