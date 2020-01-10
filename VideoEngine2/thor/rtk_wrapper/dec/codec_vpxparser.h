#ifndef CODEC_VPXPARSER_H
#define CODEC_VPXPARSER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <OMX_Types.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OSAL_RTK.h>

struct Vp9FrameTag
{
    OMX_U32 key_frame;
    OMX_U32 show_frame;
};

void ParseSuperframeIndex(const OMX_U8* data, OMX_U32 data_sz,
                          const OMX_U8* buf, OMX_U32 buf_sz,
                          OMX_U32 sizes[8], OMX_S32* count);

void ParseSuperframeIndexProtect(void *sess, OMX_U32 data, OMX_U32 data_sz,
                                 OMX_U32 buf_sz,
                                 OMX_U32 sizes[8], OMX_S32* count);

OMX_U32 Vp9DecodeFrameTag(const OMX_U8 *strm, OMX_U32 data_len, OMX_U32 buf_len,
                          struct Vp9FrameTag *frame_tag);

#ifdef __cplusplus
}
#endif
#endif                       // CODEC_VPXPARSER_H

