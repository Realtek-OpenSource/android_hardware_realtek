#ifndef CAMERA3_VOWRITEBACK_HELPER
#define CAMERA3_VOWRITEBACK_HELPER

#include <utils/threads.h>
#include <utils/Mutex.h>
#include <utils/Errors.h>
#include <pthread.h>
#include "VOWriteBack.h"
#include "VOWBCallback.h"
#include "CamBufDef.h"

#define VO_WRITEBAC_BUF_COUNT   6

#define STATUS_CLEARED          (0)
#define STATUS_LOCKED           (1<<0)

using namespace android;

namespace android {

typedef struct vowb_allocator_info {
    allocator_info_t *alloc_info;
    uint32_t status;
} vowb_allocator_info_t;

class Camera3VoWritebackHelper {

public:
    Camera3VoWritebackHelper(VOWBCallback *pCallback);
    ~Camera3VoWritebackHelper();

    status_t init(uint32_t bufCount, int32_t width, int32_t height);
    status_t uninit();
    status_t setBufs(allocator_info_t *pBufs, int32_t size);
    status_t setInputBufsInfo(allocator_info_t *pBufs, int32_t size);
    status_t start();
    status_t stop();

    /**
     * V4L2 enqueue a buffer to VOWB
     */
    status_t enqueueInputBuf(allocator_info_t *pBuf);

    /**
     * V4L2 dequeue a buffer from VOWB
     */
    allocator_info_t *dequeueOutputBuf(bool blocked);

    /**
     * V4L2 finish using this buffer, clear it, so VOWB can use it again
     */
    status_t releaseOutputBuf(allocator_info_t *pBuf);

    /**
     * V4L2 query mDequeuedBuffers size
     */
    int32_t getDequeueBufferSize() { return mDequeuedBuffers.size(); }

private:

    /**
     * An internal worker thread to enqueue buffers to VO from queue
     */
    class VOEnqueueThread : public Thread {
    public:
        VOEnqueueThread(Camera3VoWritebackHelper *parent);
        ~VOEnqueueThread();
        void stop() { mRunning = false ; }
        void signal();
    private:
        virtual bool threadLoop();
        Camera3VoWritebackHelper *mParent;
        bool mRunning;
    };

    /**
     * An internal worker thread to dequeue buffers from VO to queue
     */
    class VODequeueThread : public Thread {
    public:
        VODequeueThread(Camera3VoWritebackHelper *parent);
        ~VODequeueThread();
        void stop() { mRunning = false ; }
        void signal();
    private:
        virtual bool threadLoop();
        Camera3VoWritebackHelper *mParent;
        bool mRunning;
    };

    VOWBCallback *mCallback;
    VOWriteBack *mInstance;

    uint32_t mBufCount;
    int32_t mWidth;
    int32_t mHeight;

    /**
     * Use this array to keep information of buffers used by VO
     */
    vowb_allocator_info_t mBufs[VO_WRITEBAC_BUF_COUNT];

    /**
     * Use this array to keep information of buffers used by V4L2
     */
    allocator_info_t **mInputBufsInfo;

    /**
     * vector to keeps enqueued v4l2 buffers
     */
    mutable Mutex       mLockEQ;
    Vector<allocator_info_t *> mEnqueuedBuffers;

    /**
     * vector to keep deinterlaced buffers from VO
     */
    mutable Mutex       mLockDQ;
    Vector<allocator_info_t *> mDequeuedBuffers;

    /**
     * vector to keep candidate buffers that is going to return back to V4L2
     */
    mutable Mutex       mLockRetQ;
    Vector<allocator_info_t *> mReturnBuffers;

    /**
     * vector to keep pts queue
     */
    mutable Mutex       mLockPTSQ;
    Vector<nsecs_t> mPTSQueue;

    sp<VOEnqueueThread> mEnqueueThread;
    sp<VODequeueThread> mDequeueThread;

    mutable Mutex       mEnqueueLock;
    Condition           mEnqueueSignal;

    mutable Mutex       mDequeueLock;
    Condition           mDequeueSignal;

    mutable Mutex       mCounterLock;
    int32_t             mAvailCounter;

    uint32_t            mOutputDumpCount;

    mutable Mutex       mVoCounterLock;
    uint32_t            mVoAvailCounter;

    void addCounter(int val);
    void addVoCounter(int val);

    /**
     * read input buffers from mEnqueuedBuffers and pass to VO
     */
    status_t enqueueInputBuf2VO();

    /**
     * Try to get two output buffers from VO everytime
     */
    status_t dequeueOutputBufFromVO(YUV_STATE *pBuf0, YUV_STATE *pBuf1);

    /**
     * use info in YUV_STATE to find mapped output buffer
     */
    allocator_info_t *findVOBufByYuvState(YUV_STATE *pBuf);

    /**
     * add buffers get from VOWB to mDequeuedBuffers
     */
    status_t enqueueDequeuedBuffers(allocator_info_t *pBuf);

    /**
     * I/O functions of RetQueue
     */
    status_t enqueueRetBuf(allocator_info_t *pBuf);
    status_t dequeueRetBuf();
    allocator_info_t *peekRetBuf();

    /**
     * I/O functions of pts queue
     */
    status_t enqueuePTS(nsecs_t pts);
    status_t dequeuePTS();

    /**
     * check if candidate buffer can return back to V4L2
     */
    status_t returnBufToV4L2();

    /**
     * Debug function, dump YUV data to file
     */
    void dumpData(void *vaddr, int32_t size, char *path, uint32_t *pCnt);
    void dumpAcquiredInputBufferNums();
    void dumpRetBufQueueState();
    //void dumpInputBufState();
}; // Camera3VoWritebackHelper

}; // namespace android

#endif // CAMERA3_VOWRITEBACK_HELPER
