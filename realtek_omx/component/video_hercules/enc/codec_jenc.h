#ifndef ENCODER_JPEG_H_
#define ENCODER_JPEG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "codec.h"

    typedef struct JPEG_CONFIG {
        // ----------config-----------

        OMX_U32 qLevel;     // The quantization level. [0..9]
        OMX_U32 sliceHeight;

        // ---------- APP0 header related config -----------
        OMX_BOOL bAddHeaders;
        OMX_U32 xDensity;                   // Horizontal pixel density to APP0 header.
        OMX_U32 yDensity;                   // Vertical pixel density to APP0 header.

        //OMX_U32 comLength;                // length of comment header data
        //OMX_U8    *pCom;                  // Pointer to comment header data of size comLength.
        //OMX_U32 thumbnail;                // Indicates if thumbnail is added to stream.

        // ---------- encoder options -----------
        OMX_U32 codingWidth;
        OMX_U32 codingHeight;
        OMX_U32 yuvFormat; // output picture YUV format
        PRE_PROCESSOR_CONFIG pp_config;
    } JPEG_CONFIG;

// create codec instance
    ENCODER_PROTOTYPE* RTKHwEncOmx_encoder_create_jpeg(const JPEG_CONFIG* config);

#ifdef __cplusplus
}
#endif

#endif /*CODEC_JPEG_H_*/

