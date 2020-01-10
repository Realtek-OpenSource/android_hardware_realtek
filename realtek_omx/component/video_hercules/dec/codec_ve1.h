#ifndef CODEC_VE1_H
#define CODEC_VE1_H

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
CODEC_PROTOTYPE *RTKHwDecOmx_decoder_create_ve1(OMX_VIDEO_CODINGTYPE eCompressionFormat, PRIVATE_STRUCT pRtkInfo);


typedef enum AVC_FORMAT /* avcExtension at vpuapi.h */
{
    AVCFORMAT_AVC           = 0,
    AVCFORMAT_MVC           = 1
}
AVC_FORMAT;

typedef enum MPEG4_FORMAT /* mp4Class at vpuapi.h */
{
    MPEG4FORMAT_MPEG4       = 0,
    MPEG4FORMAT_DIVX5       = 1,
    MPEG4FORMAT_XVID        = 2,
    MPEG4FORMAT_DIVX4       = 5,
    MPEG4FORMAT_SORENSON    = 256
} MPEG4_FORMAT;

#ifdef __cplusplus
}
#endif
#endif                       // CODEC_VE1_H

