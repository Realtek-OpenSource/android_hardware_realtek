/*
 *  Copyright 2011 The LibYuv Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "libyuv/row_KK.h"

#ifdef __cplusplus
namespace libyuv {
extern "C" {
#endif

// This module is for GCC Neon
#if !defined(YUV_DISABLE_ASM) && defined(__ARM_NEON__)

// Read 8 Y, 4 U and 4 V from 422
#define READYUV422                                                             \
    "vld1.u8    {d0}, [%0]!                    \n"                             \
    "vld1.u32   {d2[0]}, [%1]!                 \n"                             \
    "vld1.u32   {d2[1]}, [%2]!                 \n"

// Read 8 Y and 4 UV from NV12
#define READNV12                                                               \
    "vld1.u8    {d0}, [%0]!                    \n"                             \
    "vld1.u8    {d2}, [%1]!                    \n"                             \
    "vmov.u8    d3, d2                         \n"/* split odd/even uv apart */\
    "vuzp.u8    d2, d3                         \n"                             \
    "vtrn.u32   d2, d3                         \n"                             \

// Read 8 Y and 4 VU from NV21
#define READNV21                                                               \
    "vld1.u8    {d0}, [%0]!                    \n"                             \
    "vld1.u8    {d2}, [%1]!                    \n"                             \
    "vmov.u8    d3, d2                         \n"/* split odd/even uv apart */\
    "vuzp.u8    d3, d2                         \n"                             \
    "vtrn.u32   d2, d3                         \n"                             \

#define YUV422TORGB                                                            \
    "veor.u8    d2, d26                        \n"/*subtract 128 from u and v*/\
    "vmull.s8   q8, d2, d24                    \n"/*  u/v B/R component      */\
    "vmull.s8   q9, d2, d25                    \n"/*  u/v G component        */\
    "vmov.u8    d1, #0                         \n"/*  split odd/even y apart */\
    "vtrn.u8    d0, d1                         \n"                             \
    "vsub.s16   q0, q0, q15                    \n"/*  offset y               */\
    "vmul.s16   q0, q0, q14                    \n"                             \
    "vadd.s16   d18, d19                       \n"                             \
    "vqadd.s16  d20, d0, d16                   \n"                             \
    "vqadd.s16  d21, d1, d16                   \n"                             \
    "vqadd.s16  d22, d0, d17                   \n"                             \
    "vqadd.s16  d23, d1, d17                   \n"                             \
    "vqadd.s16  d16, d0, d18                   \n"                             \
    "vqadd.s16  d17, d1, d18                   \n"                             \
    "vqrshrun.s16 d0, q10, #6                  \n"                             \
    "vqrshrun.s16 d1, q11, #6                  \n"                             \
    "vqrshrun.s16 d2, q8, #6                   \n"                             \
    "vmovl.u8   q10, d0                        \n"/*  set up for reinterleave*/\
    "vmovl.u8   q11, d1                        \n"                             \
    "vmovl.u8   q8, d2                         \n"                             \
    "vtrn.u8    d20, d21                       \n"                             \
    "vtrn.u8    d22, d23                       \n"                             \
    "vtrn.u8    d16, d17                       \n"                             \
    "vmov.u8    d21, d16                       \n"

#if defined(HAS_I422TOARGBROW_NEON) || defined(HAS_I422TOBGRAROW_NEON) ||      \
    defined(HAS_I422TOABGRROW_NEON) || defined(HAS_I422TORGBAROW_NEON)
static const vec8 kUVToRB  = { 127, 127, 127, 127, 102, 102, 102, 102,
                               0, 0, 0, 0, 0, 0, 0, 0 };
static const vec8 kUVToG = { -25, -25, -25, -25, -52, -52, -52, -52,
                             0, 0, 0, 0, 0, 0, 0, 0 };
#endif

#ifdef HAS_I422TOARGBROW_NEON
void I422ToARGBRow_NEON(const uint8* y_buf,
                        const uint8* u_buf,
                        const uint8* v_buf,
                        uint8* rgb_buf,
                        int width) {
  asm volatile (
    "vld1.u8    {d24}, [%5]                    \n"
    "vld1.u8    {d25}, [%6]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READYUV422
    YUV422TORGB
    "subs       %4, %4, #8                     \n"
    "vmov.u8    d23, #255                      \n"
    "vst4.8     {d20, d21, d22, d23}, [%3]!    \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(u_buf),    // %1
      "+r"(v_buf),    // %2
      "+r"(rgb_buf),  // %3
      "+r"(width)     // %4
    : "r"(&kUVToRB),  // %5
      "r"(&kUVToG)    // %6
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_I422TOARGBROW_NEON

#ifdef HAS_I422TOBGRAROW_NEON
void I422ToBGRARow_NEON(const uint8* y_buf,
                        const uint8* u_buf,
                        const uint8* v_buf,
                        uint8* rgb_buf,
                        int width) {
  asm volatile (
    "vld1.u8    {d24}, [%5]                    \n"
    "vld1.u8    {d25}, [%6]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READYUV422
    YUV422TORGB
    "subs       %4, %4, #8                     \n"
    "vswp.u8    d20, d22                       \n"
    "vmov.u8    d19, #255                      \n"
    "vst4.8     {d19, d20, d21, d22}, [%3]!    \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(u_buf),    // %1
      "+r"(v_buf),    // %2
      "+r"(rgb_buf),  // %3
      "+r"(width)     // %4
    : "r"(&kUVToRB),  // %5
      "r"(&kUVToG)    // %6
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_I422TOBGRAROW_NEON

#ifdef HAS_I422TOABGRROW_NEON
void I422ToABGRRow_NEON(const uint8* y_buf,
                        const uint8* u_buf,
                        const uint8* v_buf,
                        uint8* rgb_buf,
                        int width) {
  asm volatile (
    "vld1.u8    {d24}, [%5]                    \n"
    "vld1.u8    {d25}, [%6]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READYUV422
    YUV422TORGB
    "subs       %4, %4, #8                     \n"
    "vswp.u8    d20, d22                       \n"
    "vmov.u8    d23, #255                      \n"
    "vst4.8     {d20, d21, d22, d23}, [%3]!    \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(u_buf),    // %1
      "+r"(v_buf),    // %2
      "+r"(rgb_buf),  // %3
      "+r"(width)     // %4
    : "r"(&kUVToRB),  // %5
      "r"(&kUVToG)    // %6
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_I422TOABGRROW_NEON

#ifdef HAS_I422TORGBAROW_NEON
void I422ToRGBARow_NEON(const uint8* y_buf,
                        const uint8* u_buf,
                        const uint8* v_buf,
                        uint8* rgb_buf,
                        int width) {
  asm volatile (
    "vld1.u8    {d24}, [%5]                    \n"
    "vld1.u8    {d25}, [%6]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READYUV422
    YUV422TORGB
    "subs       %4, %4, #8                     \n"
    "vmov.u8    d19, #255                      \n"
    "vst4.8     {d19, d20, d21, d22}, [%3]!    \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(u_buf),    // %1
      "+r"(v_buf),    // %2
      "+r"(rgb_buf),  // %3
      "+r"(width)     // %4
    : "r"(&kUVToRB),  // %5
      "r"(&kUVToG)    // %6
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_I422TORGBAROW_NEON

#ifdef HAS_I422TORGB24ROW_NEON
void I422ToRGB24Row_NEON(const uint8* y_buf,
                        const uint8* u_buf,
                        const uint8* v_buf,
                        uint8* rgb_buf,
                        int width) {
  asm volatile (
    "vld1.u8    {d24}, [%5]                    \n"
    "vld1.u8    {d25}, [%6]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READYUV422
    YUV422TORGB
    "subs       %4, %4, #8                     \n"
    "vst3.8     {d20, d21, d22}, [%3]!         \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(u_buf),    // %1
      "+r"(v_buf),    // %2
      "+r"(rgb_buf),  // %3
      "+r"(width)     // %4
    : "r"(&kUVToRB),  // %5
      "r"(&kUVToG)    // %6
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_I422TORGB24ROW_NEON

#ifdef HAS_I422TORAWROW_NEON
void I422ToRAWRow_NEON(const uint8* y_buf,
                       const uint8* u_buf,
                       const uint8* v_buf,
                       uint8* rgb_buf,
                       int width) {
  asm volatile (
    "vld1.u8    {d24}, [%5]                    \n"
    "vld1.u8    {d25}, [%6]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READYUV422
    YUV422TORGB
    "subs       %4, %4, #8                     \n"
    "vswp.u8    d20, d22                       \n"
    "vst3.8     {d20, d21, d22}, [%3]!         \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(u_buf),    // %1
      "+r"(v_buf),    // %2
      "+r"(rgb_buf),  // %3
      "+r"(width)     // %4
    : "r"(&kUVToRB),  // %5
      "r"(&kUVToG)    // %6
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_I422TORAWROW_NEON

#ifdef HAS_NV12TOARGBROW_NEON
void NV12ToARGBRow_NEON(const uint8* y_buf,
                        const uint8* uv_buf,
                        uint8* rgb_buf,
                        int width) {
  asm volatile (
    "vld1.u8    {d24}, [%4]                    \n"
    "vld1.u8    {d25}, [%5]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READNV12
    YUV422TORGB
    "subs       %3, %3, #8                     \n"
    "vmov.u8    d23, #255                      \n"
    "vst4.8     {d20, d21, d22, d23}, [%2]!    \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(uv_buf),   // %1
      "+r"(rgb_buf),  // %2
      "+r"(width)     // %3
    : "r"(&kUVToRB),  // %4
      "r"(&kUVToG)    // %5
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_NV12TOARGBROW_NEON

#ifdef HAS_NV21TOARGBROW_NEON
void NV21ToARGBRow_NEON(const uint8* y_buf,
                        const uint8* uv_buf,
                        uint8* rgb_buf,
                        int width) {
  asm volatile (
    "vld1.u8    {d24}, [%4]                    \n"
    "vld1.u8    {d25}, [%5]                    \n"
    "vmov.u8    d26, #128                      \n"
    "vmov.u16   q14, #74                       \n"
    "vmov.u16   q15, #16                       \n"
    ".p2align  2                               \n"
  "1:                                          \n"
    READNV21
    YUV422TORGB
    "subs       %3, %3, #8                     \n"
    "vmov.u8    d23, #255                      \n"
    "vst4.8     {d20, d21, d22, d23}, [%2]!    \n"
    "bgt        1b                             \n"
    : "+r"(y_buf),    // %0
      "+r"(uv_buf),   // %1
      "+r"(rgb_buf),  // %2
      "+r"(width)     // %3
    : "r"(&kUVToRB),  // %4
      "r"(&kUVToG)    // %5
    : "cc", "memory", "q0", "q1", "q2", "q3",
      "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}
#endif  // HAS_NV21TOARGBROW_NEON

#ifdef HAS_SPLITUV_NEON
// Reads 16 pairs of UV and write even values to dst_u and odd to dst_v
// Alignment requirement: 16 bytes for pointers, and multiple of 16 pixels.
void SplitUV_NEON(const uint8* src_uv, uint8* dst_u, uint8* dst_v, int width) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld2.u8    {q0, q1}, [%0]!                \n"  // load 16 pairs of UV
    "subs       %3, %3, #16                    \n"  // 16 processed per loop
    "vst1.u8    {q0}, [%1]!                    \n"  // store U
    "vst1.u8    {q1}, [%2]!                    \n"  // Store V
    "bgt        1b                             \n"
    : "+r"(src_uv),  // %0
      "+r"(dst_u),   // %1
      "+r"(dst_v),   // %2
      "+r"(width)    // %3  // Output registers
    :                       // Input registers
    : "memory", "cc", "q0", "q1"  // Clobber List
  );
}
#endif  // HAS_SPLITUV_NEON

#ifdef HAS_COPYROW_NEON
// Copy multiple of 64
void CopyRow_NEON(const uint8* src, uint8* dst, int count) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vldm       %0!, {q0, q1, q2, q3}          \n"  // load 64
    "subs       %2, %2, #64                    \n"  // 64 processed per loop
    "vstm       %1!, {q0, q1, q2, q3}          \n"  // store 64
    "bgt        1b                             \n"
    : "+r"(src),   // %0
      "+r"(dst),   // %1
      "+r"(count)  // %2  // Output registers
    :                     // Input registers
    : "memory", "cc", "q0", "q1", "q2", "q3"  // Clobber List
  );
}
#endif  // HAS_COPYROW_NEON

#ifdef HAS_SETROW_NEON
// SetRow8 writes 'count' bytes using a 32 bit value repeated.
void SetRow8_NEON(uint8* dst, uint32 v32, int count) {
  asm volatile (  // NOLINT
    "vdup.u32  q0, %2                          \n"  // duplicate 4 ints
    "1:                                        \n"
    "subs      %1, %1, #16                     \n"  // 16 bytes per loop
    "vst1.u32  {q0}, [%0]!                     \n"  // store
    "bgt       1b                              \n"
    : "+r"(dst),   // %0
      "+r"(count)  // %1
    : "r"(v32)     // %2
    : "q0", "memory", "cc");
}

// TODO(fbarchard): Make fully assembler
// SetRow32 writes 'count' words using a 32 bit value repeated.
void SetRows32_NEON(uint8* dst, uint32 v32, int width,
                    int dst_stride, int height) {
  for (int y = 0; y < height; ++y) {
    SetRow8_NEON(dst, v32, width << 2);
    dst += dst_stride;
  }
}
#endif  // HAS_SETROW_NEON

#ifdef HAS_MIRRORROW_NEON
void MirrorRow_NEON(const uint8* src, uint8* dst, int width) {
  asm volatile (
    // compute where to start writing destination
    "add         %1, %2                        \n"
    // work on segments that are multiples of 16
    "lsrs        r3, %2, #4                    \n"
    // the output is written in two block. 8 bytes followed
    // by another 8. reading is done sequentially, from left to
    // right. writing is done from right to left in block sizes
    // %1, the destination pointer is incremented after writing
    // the first of the two blocks. need to subtract that 8 off
    // along with 16 to get the next location.
    "mov         r3, #-24                      \n"
    "beq         2f                            \n"

    // back of destination by the size of the register that is
    // going to be mirrored
    "sub         %1, #16                       \n"
    // the loop needs to run on blocks of 16. what will be left
    // over is either a negative number, the residuals that need
    // to be done, or 0. If this isn't subtracted off here the
    // loop will run one extra time.
    "sub         %2, #16                       \n"

    // mirror the bytes in the 64 bit segments. unable to mirror
    // the bytes in the entire 128 bits in one go.
    // because of the inability to mirror the entire 128 bits
    // mirror the writing out of the two 64 bit segments.
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld1.8      {q0}, [%0]!                   \n"  // src += 16
    "subs        %2, #16                       \n"
    "vrev64.8    q0, q0                        \n"
    "vst1.8      {d1}, [%1]!                   \n"
    "vst1.8      {d0}, [%1], r3                \n"  // dst -= 16
    "bge         1b                            \n"

    // add 16 back to the counter. if the result is 0 there is no
    // residuals so jump past
    "adds        %2, #16                       \n"
    "beq         5f                            \n"
    "add         %1, #16                       \n"
  "2:                                          \n"
    "mov         r3, #-3                       \n"
    "sub         %1, #2                        \n"
    "subs        %2, #2                        \n"
    // check for 16*n+1 scenarios where segments_of_2 should not
    // be run, but there is something left over.
    "blt         4f                            \n"

// do this in neon registers as per
// http://blogs.arm.com/software-enablement/196-coding-for-neon-part-2-dealing-with-leftovers/
  "3:                                          \n"
    "vld2.8      {d0[0], d1[0]}, [%0]!         \n"  // src += 2
    "subs        %2, #2                        \n"
    "vst1.8      {d1[0]}, [%1]!                \n"
    "vst1.8      {d0[0]}, [%1], r3             \n"  // dst -= 2
    "bge         3b                            \n"

    "adds        %2, #2                        \n"
    "beq         5f                            \n"
  "4:                                          \n"
    "add         %1, #1                        \n"
    "vld1.8      {d0[0]}, [%0]                 \n"
    "vst1.8      {d0[0]}, [%1]                 \n"
  "5:                                          \n"
    : "+r"(src),   // %0
      "+r"(dst),   // %1
      "+r"(width)  // %2
    :
    : "memory", "cc", "r3", "q0"
  );
}
#endif  // HAS_MIRRORROW_NEON

#ifdef HAS_MIRRORROWUV_NEON
void MirrorRowUV_NEON(const uint8* src, uint8* dst_a, uint8* dst_b, int width) {
  asm volatile (
    // compute where to start writing destination
    "add         %1, %3                        \n"  // dst_a + width
    "add         %2, %3                        \n"  // dst_b + width
    // work on input segments that are multiples of 16, but
    // width that has been passed is output segments, half
    // the size of input.
    "lsrs        r12, %3, #3                   \n"
    "beq         2f                            \n"
    // the output is written in to two blocks.
    "mov         r12, #-8                      \n"
    // back of destination by the size of the register that is
    // going to be mirrord
    "sub         %1, #8                        \n"
    "sub         %2, #8                        \n"
    // the loop needs to run on blocks of 8. what will be left
    // over is either a negative number, the residuals that need
    // to be done, or 0. if this isn't subtracted off here the
    // loop will run one extra time.
    "sub         %3, #8                        \n"

    // mirror the bytes in the 64 bit segments
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld2.8      {d0, d1}, [%0]!               \n"  // src += 16
    "subs        %3, #8                        \n"
    "vrev64.8    q0, q0                        \n"
    "vst1.8      {d0}, [%1], r12               \n"  // dst_a -= 8
    "vst1.8      {d1}, [%2], r12               \n"  // dst_b -= 8
    "bge         1b                            \n"

    // add 8 back to the counter. if the result is 0 there is no
    // residuals so return
    "adds        %3, #8                        \n"
    "beq         4f                            \n"
    "add         %1, #8                        \n"
    "add         %2, #8                        \n"
  "2:                                          \n"
    "mov         r12, #-1                      \n"
    "sub         %1, #1                        \n"
    "sub         %2, #1                        \n"
  "3:                                          \n"
      "vld2.8      {d0[0], d1[0]}, [%0]!       \n"  // src += 2
      "subs        %3, %3, #1                  \n"
      "vst1.8      {d0[0]}, [%1], r12          \n"  // dst_a -= 1
      "vst1.8      {d1[0]}, [%2], r12          \n"  // dst_b -= 1
      "bgt         3b                          \n"
  "4:                                          \n"
    : "+r"(src),    // %0
      "+r"(dst_a),  // %1
      "+r"(dst_b),  // %2
      "+r"(width)   // %3
    :
    : "memory", "cc", "r12", "q0"
  );
}
#endif  // HAS_MIRRORROWUV_NEON

#ifdef HAS_BGRATOARGBROW_NEON
void BGRAToARGBRow_NEON(const uint8* src_bgra, uint8* dst_argb, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d0, d1, d2, d3}, [%0]!        \n"  // load 8 pixels of BGRA.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vswp.u8    d1, d2                         \n"  // swap G, R
    "vswp.u8    d0, d3                         \n"  // swap B, A
    "vst4.8     {d0, d1, d2, d3}, [%1]!        \n"  // store 8 pixels of ARGB.
    "bgt        1b                             \n"
  : "+r"(src_bgra),  // %0
    "+r"(dst_argb),  // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "d0", "d1", "d2", "d3"  // Clobber List
  );
}
#endif  // HAS_BGRATOARGBROW_NEON

#ifdef HAS_ABGRTOARGBROW_NEON
void ABGRToARGBRow_NEON(const uint8* src_abgr, uint8* dst_argb, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d0, d1, d2, d3}, [%0]!        \n"  // load 8 pixels of ABGR.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vswp.u8    d0, d2                         \n"  // swap R, B
    "vst4.8     {d0, d1, d2, d3}, [%1]!        \n"  // store 8 pixels of ARGB.
    "bgt        1b                             \n"
  : "+r"(src_abgr),  // %0
    "+r"(dst_argb),  // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "d0", "d1", "d2", "d3"  // Clobber List
  );
}
#endif  // HAS_ABGRTOARGBROW_NEON

#ifdef HAS_RGBATOARGBROW_NEON
void RGBAToARGBRow_NEON(const uint8* src_rgba, uint8* dst_argb, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                           \n"
    "vld1.8     {d0, d1, d2, d3}, [%0]!         \n"  // load 8 pixels of RGBA.
    "subs       %2, %2, #8                      \n"  // 8 processed per loop.
    "vmov.u8    d4, d0                          \n"  // move A after RGB
    "vst4.8     {d1, d2, d3, d4}, [%1]!         \n"  // store 8 pixels of ARGB.
    "bgt        1b                              \n"
  : "+r"(src_rgba),  // %0
    "+r"(dst_argb),  // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "d0", "d1", "d2", "d3", "d4"  // Clobber List
  );
}
#endif  // HAS_RGBATOARGBROW_NEON

#ifdef HAS_RGB24TOARGBROW_NEON
void RGB24ToARGBRow_NEON(const uint8* src_rgb24, uint8* dst_argb, int pix) {
  asm volatile (
    "vmov.u8    d4, #255                       \n"  // Alpha
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld3.8     {d1, d2, d3}, [%0]!            \n"  // load 8 pixels of RGB24.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vst4.8     {d1, d2, d3, d4}, [%1]!        \n"  // store 8 pixels of ARGB.
    "bgt        1b                             \n"
  : "+r"(src_rgb24),  // %0
    "+r"(dst_argb),   // %1
    "+r"(pix)         // %2
  :
  : "memory", "cc", "d1", "d2", "d3", "d4"  // Clobber List
  );
}
#endif  // HAS_RGB24TOARGBROW_NEON

#ifdef HAS_RAWTOARGBROW_NEON
void RAWToARGBRow_NEON(const uint8* src_raw, uint8* dst_argb, int pix) {
  asm volatile (
    "vmov.u8    d4, #255                       \n"  // Alpha
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld3.8     {d1, d2, d3}, [%0]!            \n"  // load 8 pixels of RAW.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vswp.u8    d1, d3                         \n"  // swap R, B
    "vst4.8     {d1, d2, d3, d4}, [%1]!        \n"  // store 8 pixels of ARGB.
    "bgt        1b                             \n"
  : "+r"(src_raw),   // %0
    "+r"(dst_argb),  // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "d1", "d2", "d3", "d4"  // Clobber List
  );
}
#endif  // HAS_RAWTOARGBROW_NEON

#ifdef HAS_ARGBTORGBAROW_NEON
void ARGBToRGBARow_NEON(const uint8* src_argb, uint8* dst_rgba, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d1, d2, d3, d4}, [%0]!        \n"  // load 8 pixels of ARGB.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vmov.u8    d0, d4                         \n"  // move A before RGB.
    "vst4.8     {d0, d1, d2, d3}, [%1]!        \n"  // store 8 pixels of RGBA.
    "bgt        1b                             \n"
  : "+r"(src_argb),  // %0
    "+r"(dst_rgba),  // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "d0", "d1", "d2", "d3", "d4"  // Clobber List
  );
}
#endif  // HAS_ARGBTORGBAROW_NEON

#ifdef HAS_ARGBTORGB24ROW_NEON
void ARGBToRGB24Row_NEON(const uint8* src_argb, uint8* dst_rgb24, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d1, d2, d3, d4}, [%0]!        \n"  // load 8 pixels of ARGB.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vst3.8     {d1, d2, d3}, [%1]!            \n"  // store 8 pixels of RGB24.
    "bgt        1b                             \n"
  : "+r"(src_argb),   // %0
    "+r"(dst_rgb24),  // %1
    "+r"(pix)         // %2
  :
  : "memory", "cc", "d1", "d2", "d3", "d4"  // Clobber List
  );
}
#endif  // HAS_ARGBTORGB24ROW_NEON

#ifdef HAS_ARGBTORAWROW_NEON
void ARGBToRAWRow_NEON(const uint8* src_argb, uint8* dst_raw, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d1, d2, d3, d4}, [%0]!        \n"  // load 8 pixels of ARGB.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vswp.u8    d1, d3                         \n"  // swap R, B
    "vst3.8     {d1, d2, d3}, [%1]!            \n"  // store 8 pixels of RAW.
    "bgt        1b                             \n"
  : "+r"(src_argb),  // %0
    "+r"(dst_raw),   // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "d1", "d2", "d3", "d4"  // Clobber List
  );
}
#endif  // HAS_ARGBTORAWROW_NEON

#ifdef HAS_YUY2TOYROW_NEON
void YUY2ToYRow_NEON(const uint8* src_yuy2, uint8* dst_y, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld2.u8    {q0, q1}, [%0]!                \n"  // load 16 pixels of YUY2.
    "subs       %2, %2, #16                    \n"  // 16 processed per loop.
    "vst1.u8    {q0}, [%1]!                    \n"  // store 16 pixels of Y.
    "bgt        1b                             \n"
  : "+r"(src_yuy2),  // %0
    "+r"(dst_y),     // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "q0", "q1"  // Clobber List
  );
}
#endif  // HAS_YUY2TOYROW_NEON

#ifdef HAS_UYVYTOYROW_NEON
void UYVYToYRow_NEON(const uint8* src_uyvy, uint8* dst_y, int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld2.u8    {q0, q1}, [%0]!                \n"  // load 16 pixels of UYVY.
    "subs       %2, %2, #16                    \n"  // 16 processed per loop.
    "vst1.u8    {q1}, [%1]!                    \n"  // store 16 pixels of Y.
    "bgt        1b                             \n"
  : "+r"(src_uyvy),  // %0
    "+r"(dst_y),     // %1
    "+r"(pix)        // %2
  :
  : "memory", "cc", "q0", "q1"  // Clobber List
  );
}
#endif  // HAS_UYVYTOYROW_NEON

#ifdef HAS_YUY2TOYROW_NEON
void YUY2ToUV422Row_NEON(const uint8* src_yuy2, uint8* dst_u, uint8* dst_v,
                         int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d0, d1, d2, d3}, [%0]!        \n"  // load 16 pixels of YUY2.
    "subs       %3, %3, #16                    \n"  // 16 pixels = 8 UVs.
    "vst1.u8    {d1}, [%1]!                    \n"  // store 8 U.
    "vst1.u8    {d3}, [%2]!                    \n"  // store 8 V.
    "bgt        1b                             \n"
  : "+r"(src_yuy2),  // %0
    "+r"(dst_u),     // %1
    "+r"(dst_v),     // %2
    "+r"(pix)        // %3
  :
  : "memory", "cc", "d0", "d1", "d2", "d3"  // Clobber List
  );
}
#endif  // HAS_YUY2TOYROW_NEON

#ifdef HAS_UYVYTOYROW_NEON
void UYVYToUV422Row_NEON(const uint8* src_uyvy, uint8* dst_u, uint8* dst_v,
                         int pix) {
  asm volatile (
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d0, d1, d2, d3}, [%0]!        \n"  // load 16 pixels of UYVY.
    "subs       %3, %3, #16                    \n"  // 16 pixels = 8 UVs.
    "vst1.u8    {d0}, [%1]!                    \n"  // store 8 U.
    "vst1.u8    {d2}, [%2]!                    \n"  // store 8 V.
    "bgt        1b                             \n"
  : "+r"(src_uyvy),  // %0
    "+r"(dst_u),     // %1
    "+r"(dst_v),     // %2
    "+r"(pix)        // %3
  :
  : "memory", "cc", "d0", "d1", "d2", "d3"  // Clobber List
  );
}
#endif  // HAS_UYVYTOYROW_NEON

#ifdef HAS_YUY2TOYROW_NEON
void YUY2ToUVRow_NEON(const uint8* src_yuy2, int stride_yuy2,
                      uint8* dst_u, uint8* dst_v, int pix) {
  asm volatile (
    "adds       %1, %0, %1                     \n"  // stride + src_yuy2
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d0, d1, d2, d3}, [%0]!        \n"  // load 16 pixels of YUY2.
    "subs       %4, %4, #16                    \n"  // 16 pixels = 8 UVs.
    "vld4.8     {d4, d5, d6, d7}, [%1]!        \n"  // load next row YUY2.
    "vrhadd.u8  d1, d1, d5                     \n"  // average rows of U
    "vrhadd.u8  d3, d3, d7                     \n"  // average rows of V
    "vst1.u8    {d1}, [%2]!                    \n"  // store 8 U.
    "vst1.u8    {d3}, [%3]!                    \n"  // store 8 V.
    "bgt        1b                             \n"
  : "+r"(src_yuy2),     // %0
    "+r"(stride_yuy2),  // %1
    "+r"(dst_u),        // %2
    "+r"(dst_v),        // %3
    "+r"(pix)           // %4
  :
  : "memory", "cc", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"  // Clobber List
  );
}
#endif  // HAS_YUY2TOYROW_NEON

#ifdef HAS_UYVYTOYROW_NEON
void UYVYToUVRow_NEON(const uint8* src_uyvy, int stride_uyvy,
                      uint8* dst_u, uint8* dst_v, int pix) {
  asm volatile (
    "adds       %1, %0, %1                     \n"  // stride + src_uyvy
    ".p2align  2                               \n"
  "1:                                          \n"
    "vld4.8     {d0, d1, d2, d3}, [%0]!        \n"  // load 16 pixels of UYVY.
    "subs       %4, %4, #16                    \n"  // 16 pixels = 8 UVs.
    "vld4.8     {d4, d5, d6, d7}, [%1]!        \n"  // load next row UYVY.
    "vrhadd.u8  d0, d0, d4                     \n"  // average rows of U
    "vrhadd.u8  d2, d2, d6                     \n"  // average rows of V
    "vst1.u8    {d0}, [%2]!                    \n"  // store 8 U.
    "vst1.u8    {d2}, [%3]!                    \n"  // store 8 V.
    "bgt        1b                             \n"
  : "+r"(src_uyvy),     // %0
    "+r"(stride_uyvy),  // %1
    "+r"(dst_u),        // %2
    "+r"(dst_v),        // %3
    "+r"(pix)           // %4
  :
  : "memory", "cc", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"  // Clobber List
  );
}
#endif  // HAS_UYVYTOYROW_NEON

// 16x2 pixels -> 8x1.  width is number of argb pixels. e.g. 16.
#define RGBTOUV(QB, QG, QR) \
    "vmul.s16   q8, " #QB ", q10               \n"  /* B                    */ \
    "vmls.s16   q8, " #QG ", q11               \n"  /* G                    */ \
    "vmls.s16   q8, " #QR ", q12               \n"  /* R                    */ \
    "vadd.u16   q8, q8, q15                    \n"  /* +128 -> unsigned     */ \
    "vmul.s16   q9, " #QR ", q10               \n"  /* R                    */ \
    "vmls.s16   q9, " #QG ", q14               \n"  /* G                    */ \
    "vmls.s16   q9, " #QB ", q13               \n"  /* B                    */ \
    "vadd.u16   q9, q9, q15                    \n"  /* +128 -> unsigned     */ \
    "vqshrn.u16  d0, q8, #8                    \n"  /* 16 bit to 8 bit U    */ \
    "vqshrn.u16  d1, q9, #8                    \n"  /* 16 bit to 8 bit V    */

// 16x2 pixels -> 8x1.  width is number of argb pixels. e.g. 16.
#define RGBTOVU(QB, QG, QR) \
    "vmul.s16   q8, " #QB ", q10               \n"  /* B                    */ \
    "vmls.s16   q8, " #QG ", q11               \n"  /* G                    */ \
    "vmls.s16   q8, " #QR ", q12               \n"  /* R                    */ \
    "vadd.u16   q8, q8, q15                    \n"  /* +128 -> unsigned     */ \
    "vmul.s16   q9, " #QR ", q10               \n"  /* R                    */ \
    "vmls.s16   q9, " #QG ", q14               \n"  /* G                    */ \
    "vmls.s16   q9, " #QB ", q13               \n"  /* B                    */ \
    "vadd.u16   q9, q9, q15                    \n"  /* +128 -> unsigned     */ \
    "vqshrn.u16  d1, q8, #8                    \n"  /* 16 bit to 8 bit U    */ \
    "vqshrn.u16  d0, q9, #8                    \n"  /* 16 bit to 8 bit V    */

// TODO(fbarchard): Consider vhadd vertical, then vpaddl horizontal, avoid shr.
void ARGBToUVRow_NEON(const uint8* src_argb, int src_stride_argb,
                      uint8* dst_u, uint8* dst_v, int width) {
  asm volatile (
    "add        %1, %0, %1                     \n"  // src_stride + src_argb
    "vmov.s16   q10, #112 / 2                  \n"  // UB / VR 0.875 coefficient
    "vmov.s16   q11, #74 / 2                   \n"  // UG -0.5781 coefficient
    "vmov.s16   q12, #38 / 2                   \n"  // UR -0.2969 coefficient
    "vmov.s16   q13, #18 / 2                   \n"  // VB -0.1406 coefficient
    "vmov.s16   q14, #94 / 2                   \n"  // VG -0.7344 coefficient
    "vmov.u16   q15, #0x8080                   \n"  // 128.5
  "1:                                          \n"
    MEMACCESS(0)
    "vld4.8     {d0, d2, d4, d6}, [%0]!        \n"  // load 8 ARGB pixels.
    MEMACCESS(0)
    "vld4.8     {d1, d3, d5, d7}, [%0]!        \n"  // load next 8 ARGB pixels.
    "vpaddl.u8  q0, q0                         \n"  // B 16 bytes -> 8 shorts.
    "vpaddl.u8  q1, q1                         \n"  // G 16 bytes -> 8 shorts.
    "vpaddl.u8  q2, q2                         \n"  // R 16 bytes -> 8 shorts.
    MEMACCESS(1)
    "vld4.8     {d8, d10, d12, d14}, [%1]!     \n"  // load 8 more ARGB pixels.
    MEMACCESS(1)
    "vld4.8     {d9, d11, d13, d15}, [%1]!     \n"  // load last 8 ARGB pixels.
    "vpadal.u8  q0, q4                         \n"  // B 16 bytes -> 8 shorts.
    "vpadal.u8  q1, q5                         \n"  // G 16 bytes -> 8 shorts.
    "vpadal.u8  q2, q6                         \n"  // R 16 bytes -> 8 shorts.

    "vrshr.u16  q0, q0, #1                     \n"  // 2x average
    "vrshr.u16  q1, q1, #1                     \n"
    "vrshr.u16  q2, q2, #1                     \n"

    "subs       %4, %4, #16                    \n"  // 32 processed per loop.
    RGBTOUV(q0, q1, q2)
    MEMACCESS(2)
    "vst1.8     {d0}, [%2]!                    \n"  // store 8 pixels U.
    MEMACCESS(3)
    "vst1.8     {d1}, [%3]!                    \n"  // store 8 pixels V.
    "bgt        1b                             \n"
  : "+r"(src_argb),  // %0
    "+r"(src_stride_argb),  // %1
    "+r"(dst_u),     // %2
    "+r"(dst_v),     // %3
    "+r"(width)        // %4
  :
  : "cc", "memory", "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7",
    "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}


void RGBAToNV12Row_NEON(const uint8* src_rgba, int src_stride_rgba,
                      uint8* dst_y, uint8* dst_y_next, uint8* dst_uv, int width) {
  asm volatile (
    "add        %1, %0, %1                     \n"  // src_stride + src_rgba
    "vmov.s16   q10, #112 / 2                  \n"  // UB / VR 0.875 coefficient
    "vmov.s16   q11, #74  / 2                  \n"  // UG -0.5781 coefficient
    "vmov.s16   q12, #38  / 2                  \n"  // UR -0.2969 coefficient
  "1:                                          \n"
    "vmov.s16   q13, #64                       \n"  // Add 64 constant
    "vmov.u8    d28, #33                       \n"  // R * 0.2578 coefficient
    "vmov.u8    d29, #65                       \n"  // G * 0.5078 coefficient
    "vmov.u8    d30, #13                       \n"  // B * 0.1016 coefficient
    "vmov.u8    d31, #16                       \n"  // Add 16 constant
    MEMACCESS(0)
    "vld4.8     {d0, d2, d4, d6}, [%0]!        \n"  // load 8 RGBA pixels. {R, G, B, A}
    MEMACCESS(0)
    "vld4.8     {d1, d3, d5, d7}, [%0]!        \n"  // load next 8 RGBA pixels.
    "vmull.u8   q8, d0, d28                    \n"  // R0
    "vmlal.u8   q8, d2, d29                    \n"  // G0
    "vmlal.u8   q8, d4, d30                    \n"  // B0
    "vqadd.u8   q8, q13                        \n"
    "vqrshrun.s16 d6, q8, #7                   \n"  // 16 bit to 8 bit Y0
    "vqadd.u8   d6, d31                        \n"
    "vmull.u8   q9, d1, d28                    \n"  // R1
    "vmlal.u8   q9, d3, d29                    \n"  // G1
    "vmlal.u8   q9, d5, d30                    \n"  // B1
    "vqadd.u8   q9, q13                        \n"
    "vqrshrun.s16 d7, q9, #7                   \n"  // 16 bit to 8 bit Y1
    "vqadd.u8   d7, d31                        \n"
    MEMACCESS(2)
    "vst1.u64   {d6-d7}, [%2]!                 \n"  // store 16 pixels at Y.

    MEMACCESS(1)
    "vld4.8     {d8, d10, d12, d14}, [%1]!     \n"  // load 8 more RGBA pixels.
    MEMACCESS(1)
    "vld4.8     {d9, d11, d13, d15}, [%1]!     \n"  // load last 8 RGBA pixels.
    "vmull.u8   q8, d8,  d28                   \n"  // R0
    "vmlal.u8   q8, d10, d29                   \n"  // G0
    "vmlal.u8   q8, d12, d30                   \n"  // B0
    "vqadd.u8   q8, q13                        \n"
    "vqrshrun.s16 d14, q8, #7                  \n"  // 16 bit to 8 bit Y0
    "vqadd.u8   d14, d31                       \n"
    "vmull.u8   q9, d9,  d28                   \n"  // R1
    "vmlal.u8   q9, d11, d29                   \n"  // G1
    "vmlal.u8   q9, d13, d30                   \n"  // B1
    "vqadd.u8   q9, q13                        \n"
    "vqrshrun.s16 d15, q9, #7                  \n"  // 16 bit to 8 bit Y1
    "vqadd.u8   d15, d31                       \n"
    MEMACCESS(3)
    "vst1.u64   {d14-d15}, [%3]!                 \n"  // store 16 pixels at next line Y.

    "vmov.s16   q13, #18 / 2                   \n"  // VB -0.1406 coefficient
    "vmov.s16   q14, #94 / 2                   \n"  // VG -0.7344 coefficient
    "vmov.u16   q15, #0x8080                   \n"  // 128.5
    "vpaddl.u8  q0, q0                         \n"  // R 16 bytes -> 8 shorts.
    "vpaddl.u8  q1, q1                         \n"  // G 16 bytes -> 8 shorts.
    "vpaddl.u8  q2, q2                         \n"  // B 16 bytes -> 8 shorts.
    "vpadal.u8  q0, q4                         \n"  // R 16 bytes -> 8 shorts.
    "vpadal.u8  q1, q5                         \n"  // G 16 bytes -> 8 shorts.
    "vpadal.u8  q2, q6                         \n"  // B 16 bytes -> 8 shorts.

    "vrshr.u16  q0, q0, #1                     \n"  // 2x average
    "vrshr.u16  q1, q1, #1                     \n"
    "vrshr.u16  q2, q2, #1                     \n"

    "subs       %5, %5, #16                    \n"  // 32 processed per loop.
    RGBTOUV(q2, q1, q0)
    MEMACCESS(4)
    "vst2.u8    {d0, d1}, [%4]!                \n"  // store 8 pixels UV.
    "bgt        1b                             \n"

  : "+r"(src_rgba),  // %0
    "+r"(src_stride_rgba),  // %1
    "+r"(dst_y),     // %2
    "+r"(dst_y_next),     // %3
    "+r"(dst_uv),     // %4
    "+r"(width)        // %5
  :
  : "cc", "memory", "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7",
    "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}

void RGBAToNV21Row_NEON(const uint8* src_rgba, int src_stride_rgba,
                      uint8* dst_y, uint8* dst_y_next, uint8* dst_vu, int width) {
  asm volatile (
    "add        %1, %0, %1                     \n"  // src_stride + src_rgba
    "vmov.s16   q10, #112 / 2                  \n"  // UB / VR 0.875 coefficient
    "vmov.s16   q11, #74  / 2                  \n"  // UG -0.5781 coefficient
    "vmov.s16   q12, #38  / 2                  \n"  // UR -0.2969 coefficient
  "1:                                          \n"
    "vmov.s16   q13, #64                       \n"  // Add 64 constant
    "vmov.u8    d28, #33                       \n"  // R * 0.2578 coefficient
    "vmov.u8    d29, #65                       \n"  // G * 0.5078 coefficient
    "vmov.u8    d30, #13                       \n"  // B * 0.1016 coefficient
    "vmov.u8    d31, #16                       \n"  // Add 16 constant
    MEMACCESS(0)
    "vld4.8     {d0, d2, d4, d6}, [%0]!        \n"  // load 8 RGBA pixels. {R, G, B, A}
    MEMACCESS(0)
    "vld4.8     {d1, d3, d5, d7}, [%0]!        \n"  // load next 8 RGBA pixels.
    "vmull.u8   q8, d0, d28                    \n"  // R0
    "vmlal.u8   q8, d2, d29                    \n"  // G0
    "vmlal.u8   q8, d4, d30                    \n"  // B0
    "vqadd.u8   q8, q13                        \n"
    "vqrshrun.s16 d6, q8, #7                   \n"  // 16 bit to 8 bit Y0
    "vqadd.u8   d6, d31                        \n"
    "vmull.u8   q9, d1, d28                    \n"  // R1
    "vmlal.u8   q9, d3, d29                    \n"  // G1
    "vmlal.u8   q9, d5, d30                    \n"  // B1
    "vqadd.u8   q9, q13                        \n"
    "vqrshrun.s16 d7, q9, #7                   \n"  // 16 bit to 8 bit Y1
    "vqadd.u8   d7, d31                        \n"
    MEMACCESS(2)
    "vst1.u64   {d6-d7}, [%2]!                 \n"  // store 16 pixels at Y.

    MEMACCESS(1)
    "vld4.8     {d8, d10, d12, d14}, [%1]!     \n"  // load 8 more RGBA pixels.
    MEMACCESS(1)
    "vld4.8     {d9, d11, d13, d15}, [%1]!     \n"  // load last 8 RGBA pixels.
    "vmull.u8   q8, d8,  d28                   \n"  // R0
    "vmlal.u8   q8, d10, d29                   \n"  // G0
    "vmlal.u8   q8, d12, d30                   \n"  // B0
    "vqadd.u8   q8, q13                        \n"
    "vqrshrun.s16 d14, q8, #7                  \n"  // 16 bit to 8 bit Y0
    "vqadd.u8   d14, d31                       \n"
    "vmull.u8   q9, d9,  d28                   \n"  // R1
    "vmlal.u8   q9, d11, d29                   \n"  // G1
    "vmlal.u8   q9, d13, d30                   \n"  // B1
    "vqadd.u8   q9, q13                        \n"
    "vqrshrun.s16 d15, q9, #7                  \n"  // 16 bit to 8 bit Y1
    "vqadd.u8   d15, d31                       \n"
    MEMACCESS(3)
    "vst1.u64   {d14-d15}, [%3]!                 \n"  // store 16 pixels at next line Y.

    "vmov.s16   q13, #18 / 2                   \n"  // VB -0.1406 coefficient
    "vmov.s16   q14, #94 / 2                   \n"  // VG -0.7344 coefficient
    "vmov.u16   q15, #0x8080                   \n"  // 128.5
    "vpaddl.u8  q0, q0                         \n"  // R 16 bytes -> 8 shorts.
    "vpaddl.u8  q1, q1                         \n"  // G 16 bytes -> 8 shorts.
    "vpaddl.u8  q2, q2                         \n"  // B 16 bytes -> 8 shorts.
    "vpadal.u8  q0, q4                         \n"  // R 16 bytes -> 8 shorts.
    "vpadal.u8  q1, q5                         \n"  // G 16 bytes -> 8 shorts.
    "vpadal.u8  q2, q6                         \n"  // B 16 bytes -> 8 shorts.

    "vrshr.u16  q0, q0, #1                     \n"  // 2x average
    "vrshr.u16  q1, q1, #1                     \n"
    "vrshr.u16  q2, q2, #1                     \n"

    "subs       %5, %5, #16                    \n"  // 32 processed per loop.
    RGBTOVU(q2, q1, q0)
    MEMACCESS(4)
    "vst2.u8    {d0, d1}, [%4]!                \n"  // store 8 pixels UV.
    "bgt        1b                             \n"

  : "+r"(src_rgba),  // %0
    "+r"(src_stride_rgba),  // %1
    "+r"(dst_y),     // %2
    "+r"(dst_y_next),     // %3
    "+r"(dst_vu),     // %4
    "+r"(width)        // %5
  :
  : "cc", "memory", "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7",
    "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
  );
}

void RGB24ToYRow_NEON(const uint8* src_rgb24, uint8* dst_y, int width) {
  asm volatile (
    "vmov.u8    d4, #13                        \n"  // B * 0.1016 coefficient
    "vmov.u8    d5, #65                        \n"  // G * 0.5078 coefficient
    "vmov.u8    d6, #33                        \n"  // R * 0.2578 coefficient
    "vmov.u8    d7, #16                        \n"  // Add 16 constant
  "1:                                          \n"
    MEMACCESS(0)
    "vld3.8     {d0, d1, d2}, [%0]!            \n"  // load 8 pixels of RGB24.
    "subs       %2, %2, #8                     \n"  // 8 processed per loop.
    "vmull.u8   q8, d0, d4                     \n"  // B
    "vmlal.u8   q8, d1, d5                     \n"  // G
    "vmlal.u8   q8, d2, d6                     \n"  // R
    "vqrshrun.s16 d0, q8, #7                   \n"  // 16 bit to 8 bit Y
    "vqadd.u8   d0, d7                         \n"
    MEMACCESS(1)
    "vst1.8     {d0}, [%1]!                    \n"  // store 8 pixels Y.
    "bgt        1b                             \n"
  : "+r"(src_rgb24),  // %0
    "+r"(dst_y),  // %1
    "+r"(width)        // %2
  :
  : "cc", "memory", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "q8"
  );
}


#endif  // __ARM_NEON__

#ifdef __cplusplus
}  // extern "C"
}  // namespace libyuv
#endif
