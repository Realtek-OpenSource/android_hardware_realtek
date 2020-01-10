#ifndef __CAMERA3_MEDIACODEC_DECODE_HELPER__
#define __CAMERA3_MEDIACODEC_DECODE_HELPER__

#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/MediaErrors.h>
#include <media/ICrypto.h>
#include <media/stagefright/MediaCodec.h>
#include "OMXDecodeHelper.h"
#include "Camera3BufferQueue.h"

using namespace android;

namespace androidcamera3 {

class MediaCodecDecodeHelper : public OMXDecodeHelper {

public:

    enum {
        kWhatCodecNotify         = 'cdcN',
        kWhatInputAvailable      = 'inpA'
    };

    /**
     * AHandler of MediaCodec
     */
    class MyDecodeHandler : public AHandler {
    public:
        MyDecodeHandler(MediaCodecDecodeHelper *parent);
        virtual ~MyDecodeHandler();
    protected:
        virtual void onMessageReceived(const sp <AMessage> &msg);
    private:
        MediaCodecDecodeHelper *mParent;
    };

    /**
     * thread to management input/output buffer control
     */
    class MediaCodecThread : public Thread {
    public:
        MediaCodecThread(MediaCodecDecodeHelper *parent, bool out);
        ~MediaCodecThread();

        void                        signal();
        void                        stop();

    private:
        virtual bool                threadLoop();
        bool                        loopIn();
        bool                        loopOut();

        MediaCodecDecodeHelper *    mParent;
        bool                        mOut;
        Mutex                       mLock;
        Condition                   mSignal;
        bool                        mRunning;
    };

    MediaCodecDecodeHelper(
        OMXDecodeHelperCallback *callback,
        int32_t format,
        int w,
        int h);

    ~MediaCodecDecodeHelper();

    status_t                    init();
    status_t                    start();
    status_t                    stop();
    status_t                    release();

private:

    sp<ALooper>                 mLooper;
    sp<MediaCodec>              mCodec;
    sp<MyDecodeHandler>         mHandler;
    sp<AMessage>                mReply;

    sp<MediaCodecThread>        mInputBufThread;
    sp<MediaCodecThread>        mOutputBufThread;

    BufferQueue<int>*           mInputBufIdQueue;
    BufferQueue<int>*           mOutputBufIdQueue;

    status_t                    createMediaCodec();
    void                        cleanUpMediaCodec();
    char *                      getMediaCodecTypeString();

    void                        codecInputAvailable(int index);
    void                        codecOutputAvailable(int32_t index,
                                    size_t offset,
                                    size_t size,
                                    int64_t timeUs,
                                    int32_t flags);
};

};

#endif
