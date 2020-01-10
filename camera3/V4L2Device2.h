#ifndef _CAMERA_HAL3_V4L2DEVICE_2_
#define _CAMERA_HAL3_V4L2DEVICE_2_

#include <utils/List.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/SortedVector.h>
#include <utils/threads.h>
#include <utils/Mutex.h>
#include "V4L2Device2Common.h"

using namespace android;

namespace androidcamera3 {


/**
 * New implementation to reduce memory copy,
 * first used in HDMIRx Progressive tv system
 */
class V4L2Device2 : public V4L2Device2Common {

    typedef struct _V4L2_BUF_SLOT{
        int32_t id;
        Request *r;
        struct v4l2_buffer slot;
        // maybe more..
    } V4L2_BUF_SLOT;

    /**
     * Thread to enqueue buffer to v4l2 device
     */
    class EnqueueThread : public Thread {
    public:
        EnqueueThread(V4L2Device2 *parent);
        ~EnqueueThread();
        void            signal();
        void            stop();
    private:
        virtual bool    threadLoop();
        Mutex           mLock;
        Condition       mSignal;
        V4L2Device2     *mParent;
        bool            mRunning;
    };

    /**
     * Thread to deqeue buffer from v4l2 device
     */
    class DequeueThread : public Thread {
    public:
        DequeueThread(V4L2Device2 *parent);
        ~DequeueThread();
        void            signal();
        void            stop();
    private:
        virtual bool    threadLoop();
        Mutex           mLock;
        Condition       mSignal;
        V4L2Device2     *mParent;
        bool            mRunning;
    };

    /**
     * Watchdog thread to stop V4L2Device2 when dequeue timeout happened
     */
    class WatchdogThread : public Thread {
    public:
        WatchdogThread(V4L2Device2 *parent);
        ~WatchdogThread();
        bool            mTerminateV4L2;
        void            signal();
        void            stop();
    private:
        virtual bool    threadLoop();
        Mutex           mLock;
        Condition       mSignal;
        V4L2Device2     *mParent;
        bool            mRunning;
    };

public:
    V4L2Device2(
        int v4l2Id,
        V4L2Params *params,
        V4L2Device2Callback *callback,
        int maxBufferCount,
        GrallocWrapper *pGrallocWrapper,
        FormatConvertHelper *pConvertHelper,
        bool forceAllocator,
        bool usePhyAddr);

    ~V4L2Device2();

    //status_t            init();
    status_t            start();
    void                flush(bool reportError);

    void                dumpDeviceStatus();
    int32_t             getOccupiedRequestCount();

    bool                enqueueRequest(const Request& r);
    bool                dequeueRequest(Request *r);

private:
    //int               mQueueThreshold;
    nsecs_t             mLatestPts;
    uint32_t            mDumpCount;
    uint32_t            mReportFrameCounter;

    Mutex               mLock;

    Mutex               mSlotLock;
    V4L2_BUF_SLOT       mSlots[V4L2_SLOT_COUNT];

    Mutex               mAllocatorsLock;
    AllocatorInfo       mAllocators[V4L2_SLOT_COUNT];
    bool                mAllocatorsInited;

    sp<EnqueueThread>   mEnqueueThread;
    sp<DequeueThread>   mDequeueThread;
    sp<WatchdogThread>  mWatchdogThread;

    void                initAllocators(int32_t count);
    void                releaseAllocators();
    int32_t             findAvailableIONSlot();
    void                clearIONSlot(Request *r);

    status_t            stop();
    int32_t             findAvailableSlot();
    int32_t             getEnqueuedSlotCount();

    void                handleDequeueTimeout();

    void                submitV4L2Result(Request *r);

    void                dumpData(void *vaddr,
                            int size,
                            char *path,
                            unsigned int *pCnt);

    // function operating V4L2
    status_t            enqueueRawBuffer(Request *r);
    status_t            dequeueRawBuffer(int32_t *id);


}; // class V4L2Device2

}; // namespace androidcamera3

#endif // _CAMERA_HAL3_V4L2DEVICE_2_
