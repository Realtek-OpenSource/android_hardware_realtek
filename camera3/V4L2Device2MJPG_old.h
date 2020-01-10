#ifndef _CAMERA_HAL3_V4L2DEVICE_2_MJPG_
#define _CAMERA_HAL3_V4L2DEVICE_2_MJPG_

#include <utils/List.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/SortedVector.h>
#include <utils/threads.h>
#include <utils/Mutex.h>
#include <media/stagefright/MediaCodec.h>
#include <libRTKAllocator/include/hardware/GrallocWrapper.h>
#include <libRTKAllocator/include/allocator/IonAllocator.h>
#include "V4L2Common.h"
#include "V4L2Device2Common.h"
#include "V4L2Device2Callback.h"
#include "FormatConvertHelper.h"
#include "OMXDecodeHelper.h"
#include "Camera3BufferQueue.h"

#define V4L2_BUF_NUM        (V4L2_SLOT_COUNT)

using namespace android;

namespace androidcamera3 {

typedef struct _AllocatorBuf {
    int32_t         mIndex;
    AllocatorDef*   pAllocator;
    int32_t         mWidth;
    int32_t         mHeight;
    int32_t         mSize;
    void*           vAddr;
    nsecs_t         mPts;
    bool            mEnqueued;
    int32_t         mBytesUsed;

    // basic constructor
    _AllocatorBuf()
    : pAllocator(NULL),
      mWidth(0),
      mHeight(0),
      mSize(0),
      vAddr(NULL),
      mIndex(0),
      mPts(0),
      mEnqueued(false)
    {}

} AllocatorBuf;


class V4L2Device2MJPG : public V4L2Device2Common {

public:

    enum {
        kWhatCodecNotify         = 'cdcN',
        kWhatInputAvailable      = 'inpA'
    };

    /**
     * AHandler of MediaCodec
     */
    class MJPEGDecodeHandler : public AHandler {
    public:
        MJPEGDecodeHandler(V4L2Device2MJPG *parent);
        virtual ~MJPEGDecodeHandler();
    protected:
        virtual void onMessageReceived(const sp <AMessage> &msg);
    private:
        V4L2Device2MJPG *mParent;
    };

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

    /**
     * thread to use media codec to decode MJPEG
     */
    class MediaCodecThread : public Thread {
    public:
        MediaCodecThread(V4L2Device2MJPG *parent, bool out);
        ~MediaCodecThread();
        void                signal();
        void                stop();
    private:
        virtual bool        threadLoop();
        bool                loopIn();
        bool                loopOut();
        V4L2Device2MJPG*    mParent;
        bool                mOut;
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

private:
    AllocatorBuf                mAllocBufs[V4L2_BUF_NUM];

    BufferQueue<AllocatorBuf*>* mMediaCodecInputQueue;
    BufferQueue<int>*           mInputBufIdQueue;
    BufferQueue<int>*           mOutputBufIdQueue;

    sp<ALooper>                 mLooper;
    sp<MediaCodec>              mCodec;
    sp<MJPEGDecodeHandler>      mHandler;
    sp<AMessage>                mReply;

    Mutex                       mRequestQueueWaitLock;
    Condition                   mRequestQueueSignal;

    bool                        mDeviceRunning;

    sp<V4L2Thread>              mV4L2Thread;
    sp<MediaCodecThread>        mInputBufThread;
    sp<MediaCodecThread>        mOutputBufThread;

    FILE *                      mV4L2RawFd;

    void                        stop();
    void                        stopDevice();

    void                        initAllocBufs(int32_t w, int32_t h);
    void                        releaseAllocBufs();

    status_t                    queueAllRawBufs();
    status_t                    dequeueRawBuffer(int32_t *id);
    status_t                    enqueueRawBuffer(AllocatorBuf *buf);

    bool                        checkMJPEGFrameValidate(AllocatorBuf *buf);

    status_t                    createMediaCodec();
    void                        cleanUpMediaCodec();
    char *                      getMediaCodecTypeString();

    void                        codecInputAvailable(int32_t index);
    void                        codecOutputAvailable(
                                    int32_t index,
                                    size_t offset,
                                    size_t size,
                                    int64_t timeUs,
                                    int32_t flags);

    void                        dumpEnqueuedBufCount();

    void                        openRawFd();
    void                        closeRawFd();
    void                        writeRawFd(char *buf, size_t length);

};

}; // namespace androidcamera3


#endif // _CAMERA_HAL3_V4L2DEVICE_2_MJPG_
