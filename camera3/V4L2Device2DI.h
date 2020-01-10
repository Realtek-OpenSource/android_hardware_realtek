#ifndef _V4L2DEVICE2_DI_H_
#define _V4L2DEVICE2_DI_H_

#include <utils/List.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/SortedVector.h>
#include <utils/threads.h>
#include <utils/Mutex.h>

#include "V4L2Device2Common.h"
#include "VoDeInterlaceHelper.h"

/* 4 bufers would cause MIPI drop frame, 6 is okay */
#define V4L2_DI_SLOT_NUM           (6)

using namespace android;

namespace androidcamera3 {

typedef struct di_buffer_info {
    int32_t         mId;
    buffer_handle_t mHandle;
    android_ycbcr   mYCbCr;
    uint32_t        mPhyAddr;
    size_t          mSize;
    int32_t         mFd;
} di_buffer_info_t;

class V4L2Device2DI : public V4L2Device2Common,
                      public DeInterlaceCallback {

    /* A simple buffer control helper class */
    class BufferQueue {
    public:
        BufferQueue() {}
        ~BufferQueue() {}

        KeyedVector<buffer_handle_t,Request> mBuffers;

        Mutex                                mLock;
        Condition                            mSignal;

        status_t        queueBuffer(
                            buffer_handle_t key,
                            Request value);

        status_t        removeBuffer(buffer_handle_t key);
        status_t        removeBufferAt(size_t idx); 
        Request         valueFor(buffer_handle_t key);

        int32_t         size() { return (int32_t) (mBuffers.size()) ; }
    };

    class Worker : public Thread {
    public:
        Worker(V4L2Device2DI *parent, const char *name)
        {
            mParent = parent;
            mName = name;
            mRunning = true;
        }

        virtual ~Worker();

        // implemented by child class.
        virtual bool            loopFunc() = 0;

        const char *            mName;
        bool                    mRunning;
        V4L2Device2DI *         mParent;
        Mutex                   mWorkerLock;
        Condition               mWorkerSignal;

        bool threadLoop()
        {
            return loopFunc();
        }

        void start()
        {
            run(mName);
        }

        void stop()
        {
            mRunning = false;
            {
                Mutex::Autolock l(mWorkerLock);
                mWorkerSignal.signal();
            }

            requestExitAndWait();
        }
    };

    class DequeueWorker : public Worker {
    public:
        DequeueWorker(V4L2Device2DI *parent, const char *name)
        : Worker(parent,name) {
        }
        ~DequeueWorker();

        bool loopFunc();
    };

public:
    V4L2Device2DI(
        int v4l2Id,
        V4L2Params *params,
        V4L2Device2Callback *callback,
        int maxBufferCount,
        GrallocWrapper *pGrallocWrapper,
        FormatConvertHelper *pConvertHelper,
        bool forceAllocator,
        bool usePhyAddr);

    ~V4L2Device2DI();

    /* V4L2Device2Common APIs */
    status_t                start();
    void                    flush(bool reportError);
    void                    dumpDeviceStatus();
    int32_t                 getOccupiedRequestCount();
    bool                    enqueueRequest(const Request& r);

    /* DeInterlaceCallback APIS */
    void                    onInputBufferReturned(const buffer_handle_t &buf);
    void                    onOutputBufferAvailable(const buffer_handle_t &buf);

private:
    di_buffer_info_t        mV4l2Bufs[V4L2_DI_SLOT_NUM];

    sp<DequeueWorker>       mDequeueWorker;

    VoDeInterlaceHelper *   mDIHelper;
    BufferQueue *           mRequestQueue;

    Mutex                   mVDLock;

    status_t                stop();
    status_t                allocateV4L2Buffer(di_buffer_info_t *pInfo);
    status_t                releaseV4L2Buffer(di_buffer_info_t *pInfo);
    status_t                vidQueueBuffer(di_buffer_info_t *pInfo);
    status_t                vidDequeueBuffer(int32_t *id);
    di_buffer_info_t *      findDiBufInfo(const buffer_handle_t &buf);
    status_t                registerExtBuffer(Request *pr);
    status_t                freeDIExtBuffer(Request *pr);
    status_t                completeSensorBuffers(Request *pr);
    status_t                findSmallestRequestIdInQueue(int32_t *id);
};

}; // namespace androidcamera3

#endif
