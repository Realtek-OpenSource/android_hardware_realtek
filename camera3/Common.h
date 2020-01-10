#ifndef _CAMERA_HAL3_COMMON_
#define _CAMERA_HAL3_COMMON_

#include <utils/Timers.h>
#include <hardware/gralloc.h>

// define HDMIRx v4l2Id
#define VIDEO_MAJOR         81
#define MIPI_MINOR          250

#define SUPPORT_EXIF        (1)

#define MIPI_HW_BUG_USAGE       0 //GRALLOC_USAGE_PRIVATE_3

using namespace android;

namespace android {

typedef struct _JPEG_RST_INFO {
    uint8_t *vaddr;
    int size;           // buffer size
    int jpegSize;       // jpeg file real size
    int frameNumber;
    nsecs_t pts;
    bool mSuccess;
    int mHasJPEG;
    uint8_t *pThumbBuf;
    uint32_t thumbSize;
} JPEG_RST_INFO;

typedef struct _HDMIRX_STATUS {
    int mSrcHdmiRx;
    int mSrcReady;
    int mSrcWidth;
    int mSrcHeight;
    int mSrcProgressive;
    int mSrcColor;
    int mSrcFps;
} HDMIRX_STATUS;

typedef struct _HDMITX_STATUS {
    int32_t mWidth;
    int32_t mHeight;
    int32_t mFps;
    int32_t mProgressive;
} HDMITX_STATUS;

typedef struct _JPEG_SRC_BUF_INFO {
    int32_t w;
    int32_t h;
    int32_t size;
    void *vaddr;
    uint32_t phyAddr;
}JPEG_SRC_BUF_INFO;

typedef struct _JPEG_DST_BUF_INFO {
    // jpeg
    int32_t size;
    int32_t w;
    int32_t h;
    void *vaddr;
    uint32_t phyAddr;
    int32_t bytesused;

    // thumbnail
    uint32_t tw;
    uint32_t th;
    void *thumbVAddr;
    //int32_t thumbBufSize;
    int32_t thumbBufUsed;

}JPEG_DST_BUF_INFO;

};

#endif
