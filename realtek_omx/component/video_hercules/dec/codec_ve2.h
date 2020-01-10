#ifndef CODEC_VE2_H
#define CODEC_VE2_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "codec.h"
#include "ion/ion.h"
#ifdef ENABLE_TEE_DRM_FLOW
#include "tee_client_api.h"
#include "tee_api.h"
#endif

// create codec instance
CODEC_PROTOTYPE *RTKHwDecOmx_decoder_create_ve2(OMX_VIDEO_CODINGTYPE eCompressionFormat, PRIVATE_STRUCT pRtkInfo);

#ifdef __cplusplus
}
#endif
#endif                       // CODEC_VE2_H

