#ifndef _CAMERA_HAL3_V4L2DEVICE2_COMMON_
#define _CAMERA_HAL3_V4L2DEVICE2_COMMON_

#include <libRTKAllocator/include/hardware/GrallocWrapper.h>
#include <libRTKAllocator/include/allocator/IonAllocator.h>
#include "V4L2Common.h"
#include "Base.h"
#include "V4L2Device2Callback.h"
#include "FormatConvertHelper.h"

#define FCC2ASCII(fmt)  ((char *)(&fmt))[0], ((char *)(&fmt))[1], ((char *)(&fmt))[2], ((char *)(&fmt))[3]

#define V4L2_SLOT_COUNT     8
#define STR_BUF_SIZE        64

using namespace android;

namespace androidcamera3 {

typedef struct _V4L2_PARAMS {
    int w;
    int h;
    int halFps;
    int v4l2format;
    int v4l2Fps;
} V4L2Params;

typedef struct _AllocatorInfo {
    AllocatorDef    *pAllocator;
    bool            mEnqueued;
    bool            mValid;
    int32_t         mWidth;
    int32_t         mHeight;
    int32_t         mSize;
    int32_t         mFormat;
    void*           mVAddr;
    uint32_t        mPhyAddr;
    int32_t         mFd;
} AllocatorInfo;

/**
 * This class defines the basic prototype of the functions that a
 * V4L2Device2 should support.
 */
class V4L2Device2Common {

public:
    V4L2Device2Common(
        int v4l2Id,
        V4L2Params *params,
        V4L2Device2Callback *callback,
        int maxBufferCount,
        GrallocWrapper *pGrallocWrapper,
        FormatConvertHelper *pConvertHelper,
        bool forceAllocator,
        bool usePhyAddr);

    virtual ~V4L2Device2Common();

    V4L2Params*         getParams() { return &mParams; }
    status_t            init();
    bool                isStreaming();

    // virtual functions
    virtual status_t    start() = 0;
    virtual void        flush(bool reportError) = 0;

    virtual void        dumpDeviceStatus() = 0;
    virtual int32_t     getOccupiedRequestCount() = 0;

    virtual bool        enqueueRequest(const Request& r) = 0;
    //virtual bool        dequeueRequest(Request *r) = 0;

    bool                isDeviceConnected();

    bool                mCanProcessRequest;
    void                handlePlugout() {
                            flush(true);
                        }
    // some commonly shared variables.
protected:
    int                 mV4L2Id;
    int                 mFd;
    struct vdIn         videoIn;
    V4L2Params          mParams;
    int32_t             mHalPixelFormat;
    V4L2Device2Callback *mCallback;
    FormatConvertHelper *mFormatConvertHelper;
    GrallocWrapper      *mGrallocWrapper;
    nsecs_t             mLatestPts;
    int                 mMaxBufferCount;
    uint64_t            mRequestCount;
    bool                mForceUseAllocatorBuf;
    bool                mUsePhyAddr;
    bool                mCheckHDCP;
    char                mDeviceStr[STR_BUF_SIZE];

    Mutex               mAllocatorsLock;
    AllocatorInfo       mAllocators[V4L2_SLOT_COUNT];
    bool                mAllocatorsInited;

    int32_t             mHdcpInitSkipFrameCount;
    int64_t             mHdcpTimeSend;
    int64_t             mHdcpTimeResponse;

    /**
     * Queue to record request sent from hal
     */
    Mutex               mRequestQueueLock;
    Vector<Request>     mRequestQueue;

    status_t            startStreaming();
    status_t            stopStreaming();

    void                closeDev();

    void                getBufferCbCr(
                            buffer_handle_t *buffer,
                            int w,
                            int h,
                            void **ppVPtr,
                            void **ppCb,
                            void **ppCr);

    void                getBufferPhyAddr(
                            buffer_handle_t *buffer,
                            uint32_t *phyAddr);

    int32_t             resolveDmaFd(buffer_handle_t *buffer);
    status_t            findMatchedRawBufferInfo(Request *r);


    void                initAllocators(int32_t count);
    void                releaseAllocators();

    bool                checkHDCP(StreamBuffer *pStreamBuf);
    bool                hdcpCheckEnabledByConfig();
    void                updateStreamBufFlag(Request *r);
};

}; // namespace androidcamera3

#endif
