#ifndef _CAMERA_HAL3_V4L2DEVICE_2_DOWN_FPS_
#define _CAMERA_HAL3_V4L2DEVICE_2_DOWN_FPS_

//#include <utils/List.h>
//#include <utils/KeyedVector.h>
//#include <utils/SortedVector.h>
//#include <utils/Vector.h>
#include <utils/threads.h>
#include <utils/Mutex.h>
#include "V4L2Device2Common.h"

using namespace android;

namespace androidcamera3 {

/**
 * This class is only used for cts testing mode,
 * cause in 8.1 cts, 15 fps MUST supported.
 */
class V4L2Device2DownFps : public V4L2Device2Common {

    /**
     * Thread to operate V4L2 Device
     */
    class V4L2WorkerThread : public Thread {
    public:
        V4L2WorkerThread(V4L2Device2DownFps *parent) {
            ALOGD("V4L2WorkerThread()");
            mParent = parent;
            mRunning = true;
        }

        ~V4L2WorkerThread(){
            ALOGD("~V4L2WorkerThread()");
        }

        void                    signal();
        void                    stop();
    private:
        virtual bool            threadLoop();
        Mutex                   mLock;
        Condition               mSignal;
        V4L2Device2DownFps *    mParent;
        bool                    mRunning;
    };

public:
    V4L2Device2DownFps(
        int v4l2Id,
        V4L2Params *params,
        V4L2Device2Callback *callback,
        int maxBufferCount,
        GrallocWrapper *pGrallocWrapper,
        FormatConvertHelper *pConvertHelper,
        bool forceAllocator, // don't care
        bool usePhyAddr);    // don't care

    ~V4L2Device2DownFps();

    //status_t              init();
    status_t                start();
    status_t                stop();
    void                    flush(bool reportError);

    void                    dumpDeviceStatus();
    int32_t                 getOccupiedRequestCount();

    bool                    enqueueRequest(const Request& r);
    bool                    dequeueRequest(Request *r);

private:
    int32_t                 mBufferCount;
    sp<V4L2WorkerThread>    mWorkerThread;
    int64_t                 mV4L2BufCounter;
    int32_t                 mDivider;

    status_t                enqeueAllBuffers();
    status_t                enqueueOneBuffer(int32_t id);
    status_t                dequeueOneBuffer(
                                int32_t *id,
                                nsecs_t *pts,
                                uint32_t *range);
    bool                    shouldReportRequest();
    status_t                deliverResult(
                                int32_t id,
                                nsecs_t pts,
                                uint32_t range);


}; // class V4L2Device2DownFps

}; // namespace androidcamera3

#endif // _CAMERA_HAL3_V4L2DEVICE_2_DOWN_FPS_
