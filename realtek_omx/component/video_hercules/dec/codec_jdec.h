#ifndef CODEC_JPEG_H
#define CODEC_JPEG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "codec.h"

// create codec instance
CODEC_PROTOTYPE *RTKHwDecOmx_decoder_create_jpeg(OMX_BOOL motion_jpeg, PRIVATE_STRUCT pRtkInfo);

#ifdef __cplusplus
}
#endif
#endif                       // CODEC_JPEG_H

