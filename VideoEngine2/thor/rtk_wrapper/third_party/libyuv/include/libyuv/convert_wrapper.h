#ifndef _CONVERT_WRAPPER_H_
#define _CONVERT_WRAPPER_H_

#include <libyuv/row.h>

#ifdef HAS_NV12TORGB565ROW_NEON
int _NV12ToRGB565(const uint8* src_y, int src_stride_y,
                 const uint8* src_uv, int src_stride_uv,
                 uint8* dst_rgb565, int dst_stride_rgb565,
                 int width, int height);
#endif
#ifdef HAS_I422TOARGBROW_NEON
int _I420ToRGB565(const uint8* src_y, int src_stride_y,
                 const uint8* src_u, int src_stride_u,
                 const uint8* src_v, int src_stride_v,
                 uint8* dst_rgb565, int dst_stride_rgb565,
                 int width, int height);
#endif
int _RGBAToNV12(const uint8* src_rgba, int src_stride_rgba,
               uint8* dst_y, int dst_stride_y,
               uint8* dst_uv, int dst_stride_uv,
               int width, int height);
int _RGBAToNV21(const uint8* src_rgba, int src_stride_rgba,
               uint8* dst_y, int dst_stride_y,
               uint8* dst_vu, int dst_stride_vu,
               int width, int height);

#endif
