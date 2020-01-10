#ifndef _CAMERA_HAL3_V4L2DEVICE_2_MJPG_
#define _CAMERA_HAL3_V4L2DEVICE_2_MJPG_

#include <utils/List.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/SortedVector.h>
#include <utils/threads.h>
#include <utils/Mutex.h>
//#include <media/stagefright/MediaCodec.h>
#include "AllocatorBufDef.h"
#include "V4L2Common.h"
#include "V4L2Device2Common.h"
#include "V4L2Device2Callback.h"
#include "FormatConvertHelper.h"
#include "OMXDecodeHelper.h"
#include "OMXDecodeHelperCallback.h"
#include "Camera3BufferQueue.h"

#define V4L2_BUF_NUM        (V4L2_SLOT_COUNT)

using namespace android;

namespace androidcamera3 {

class V4L2Device2MJPG : public V4L2Device2Common,
                        public OMXDecodeHelperCallback {

public:

    /**
     * thread to operate v4l2 device
     */
    class V4L2Thread : public Thread {
    public:
        V4L2Thread(V4L2Device2MJPG *parent);
        ~V4L2Thread();
        void                signal();
        void                stop();
    private:
        virtual bool        threadLoop();
        V4L2Device2MJPG*    mParent;
        Mutex               mLock;
        Condition           mSignal;
        bool                mRunning;
    };

    V4L2Device2MJPG(
        int v4l2Id,
        V4L2Params *params,
        V4L2Device2Callback *callback,
        int maxBufferCount,
        GrallocWrapper *pGrallocWrapper,
        FormatConvertHelper *pConvertHelper,
        bool forceAllocator,
        bool usePhyAddr);

    ~V4L2Device2MJPG();

    status_t                    start();
    void                        flush(bool reportError);
    void                        dumpDeviceStatus();
    int32_t                     getOccupiedRequestCount();
    bool                        enqueueRequest(const Request& r);
    bool                        dequeueRequest(Request *r);

    // callbacks of OMXDecodeHelperCallback
    status_t                    onInputBufferAvailable(
                                    uint8_t *vAddr,
                                    int32_t phyAddr,
                                    size_t capacity,
                                    nsecs_t *pts,
                                    size_t *range);

    status_t                    onOutputBufferAvailable(
                                    uint8_t *vAddr,
                                    int32_t phyAddr,
                                    size_t range,
                                    nsecs_t pts);

private:
    AllocatorBuf                mAllocBufs[V4L2_BUF_NUM];

    BufferQueue<AllocatorBuf*>* mMediaCodecInputQueue;

    OMXDecodeHelper *           mDecodeHelper;

    Mutex                       mLock;

    Mutex                       mRequestQueueWaitLock;
    Condition                   mRequestQueueSignal;

    bool                        mDeviceRunning;

    sp<V4L2Thread>              mV4L2Thread;

    FILE *                      mV4L2RawFd;

    status_t                    stop();
    void                        stopDevice();

    void                        initAllocBufs(int32_t w, int32_t h);
    void                        releaseAllocBufs();

    status_t                    queueAllRawBufs();
    status_t                    dequeueRawBuffer(int32_t *id);
    status_t                    enqueueRawBuffer(AllocatorBuf *buf);

    bool                        checkMJPEGFrameValidate(AllocatorBuf *buf);

    void                        dumpEnqueuedBufCount();

    void                        openRawFd();
    void                        closeRawFd();
    void                        writeRawFd(char *buf, size_t length);

};

}; // namespace androidcamera3


#endif // _CAMERA_HAL3_V4L2DEVICE_2_MJPG_
