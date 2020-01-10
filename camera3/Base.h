/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * This file includes various basic structures that are needed by multiple parts
 * of the fake camera 2 implementation.
 */

#ifndef HW_EMULATOR_CAMERA2_BASE_H
#define HW_EMULATOR_CAMERA2_BASE_H

#include <system/window.h>
#include <hardware/camera3.h>
#include <include/CameraMetadata.h>
#include <utils/Vector.h>
#include <utils/Timers.h>
#include <libRTKAllocator/include/allocator/Allocator.h>
#include "RtkPrivBufDef.h"
#include "Debug.h"

#define GPS_METHOD_STRLEN       128

using android::hardware::camera::common::V1_0::helper::CameraMetadata;

namespace android {

/* Internal structure for passing buffers across threads */
struct StreamBuffer {
    // Positive numbers are output streams
    // Negative numbers are input reprocess streams
    // Zero is an auxillary buffer
    int streamId;
    uint32_t width, height;
    uint32_t format;
    uint32_t dataSpace;
    uint32_t stride;
    buffer_handle_t *buffer;
    int32_t usage;
    int32_t gralloc_usage;
    uint8_t *img;
    void *y;
    void *cb;
    void *cr;
    uint32_t phyAddr;
    int32_t buf_size;
    bool bufferSuccess;

    // RtkPrivData fields
    GraphicBufferInfo::private_rtk_data rtkData;
    GraphicBufferInfo::private_rtk_data rtkDataReturn;

    StreamBuffer()
    : streamId(0),
      width(0),
      height(0),
      format(0),
      dataSpace(0),
      stride(0),
      buffer(NULL),
      usage(0),
      gralloc_usage(0),
      img(NULL),
      y(NULL),
      cb(NULL),
      cr(NULL),
      phyAddr(0),
      buf_size(0),
      bufferSuccess(true)
    {}

};

typedef Vector<StreamBuffer>            Buffers;
typedef Vector<camera3_stream_buffer>   HalBufferVector;

typedef struct _MISC_FIELD_INFO {
    // thumbnail
    int thumbWidth;
    int thumbHeight;
    // GPS
    double gpsCoordinates[3];
    int64_t gpsTimestamp;
    uint8_t gpsProcessingMethod[GPS_METHOD_STRLEN];

} MISC_FIELD_INFO;

struct Request {
    // Basic fields
    uint32_t                frameNumber;
    CameraMetadata          settings;       // bad coding style, fix me later
    HalBufferVector *       buffers;
    Buffers *               sensorBuffers;
    // added for reprocessing capability.
    camera3_stream_buffer * input_buffer;
    int                     input_buffer_sync_fd;
    uint32_t                num_output_buffers;
    uint32_t                num_jpeg_output_buffers;
    bool                    flushed;
    // extension for V4L2Device2 mode
    StreamBuffer *          pMarkedBuf;
    nsecs_t                 pts;
    uint32_t                bytesused;
    bool                    mSuccess;
    MISC_FIELD_INFO         mMiscInfo;
    // if no buffer found in Request,
    // then V4L2Device2 should allocate a buffer by itself
    AllocatorDef *          allocator;
    int32_t                 allocatorWidth;
    int32_t                 allocatorHeight;
    int32_t                 allocatorFormat;
    int32_t                 allocatorBufferSize;
    int32_t                 allocatorSlotId;
    void *                  allocatorVAddr;
    uint32_t                allocatorPhyAddr;
    int32_t                 allocatorIonFd;

    /* V4L2Device2DI extension */
    buffer_handle_t         mDIExtBuffer;
    android_ycbcr           mDIExtBufferYCbCr;
    uint32_t                mDIExtBufferPhyAddr;
    size_t                  mDIExtBufferSize;

    nsecs_t                 mInPTS;
    nsecs_t                 mOutPTS;

#if 0
    Request operator=(Request r){
        frameNumber             = r.frameNumber;
        settings                = r.settings;
        buffers                 = r.buffers;
        sensorBuffers           = r.sensorBuffers;
        mJpegRequest            = r.mJpegRequest;
        input_buffer            = r.input_buffer;
        input_buffer_sync_fd    = r.input_buffer_sync_fd;
        num_output_buffers      = r.num_output_buffers;
        flushed                 = r.flushed;
        pMarkedBuf              = r.pMarkedBuf;
        pts                     = r.pts;
        bytesused               = r.bytesused;
        mSuccess                = r.mSuccess;
        mMiscInfo               = r.mMiscInfo;
        allocator               = r.allocator;
        allocatorWidth          = r.allocatorWidth;
        allocatorHeight         = r.allocatorHeight;
        allocatorFormat         = r.allocatorFormat;
        allocatorBufferSize     = r.allocatorBufferSize;
        allocatorSlotId         = r.allocatorSlotId;
    }
#endif

    Request()
    : frameNumber(0),
      settings(),
      buffers(NULL),
      sensorBuffers(NULL),
      input_buffer(NULL),
      input_buffer_sync_fd(-1),
      num_output_buffers(0),
      num_jpeg_output_buffers(0),
      flushed(false),
      pMarkedBuf(NULL),
      pts(0),
      bytesused(0),
      mSuccess(false),
      mMiscInfo(),
      allocator(NULL),
      allocatorWidth(0),
      allocatorHeight(0),
      allocatorFormat(0),
      allocatorBufferSize(0),
      allocatorSlotId(-1),
      allocatorVAddr(NULL),
      allocatorPhyAddr(0),
      mDIExtBuffer(0)
    {
    }

    ~Request()
    {
    }
};

} // namespace android;

#endif
