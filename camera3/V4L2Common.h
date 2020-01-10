#ifndef _V4L2_COMMON_H_
#define _V4L2_COMMON_H_

#include <linux/videodev2.h>

#define VIDIOC_SET_PHY_ADDR_MODE     _IOWR('V', BASE_VIDIOC_PRIVATE+6, int)

/**
 * VideoIn info
 */
struct vdIn {
    struct v4l2_capability cap;
    struct v4l2_format format;
    struct v4l2_buffer buf;
    struct v4l2_requestbuffers rb;
    bool isStreaming;
    bool isInited;
    int fps;
    int width;
    int height;
    int formatIn;
    int framesizeIn;
    char devName[32];
};

#endif // _V4L2_COMMON_H_
