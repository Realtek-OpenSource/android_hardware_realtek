#ifndef V4L2_DEVICE_H
#define V4L2_DEVICE_H

#include <utils/threads.h>
#include <utils/Mutex.h>
#include <libRTKAllocator/include/allocator/Allocator.h>
#include <libRTKAllocator/include/allocator/IonAllocator.h>
#include <libRTKAllocator/include/allocator/MallocAllocator.h>
#include <media/stagefright/MediaCodec.h>
#include <pthread.h>
#include "V4L2Common.h"
#include "CamBufDef.h"
#include "Common.h"
#include "Camera3VoWritebackHelper.h"

#define NUMS_OF_ION_BUF     8
#define V4L2_DEV_STR_LEN    32

// jpeg compress policy, sync or async mode
#define SYNC_ENCODE_JPEG           (1)

using namespace android;

namespace androidcamera3 {

/**
 * mediacodec input queue item
 */
typedef struct mediacodec_input_queue {
    int32_t index;
} mediacodec_input_queue_t;

/**
 * mediacodec output queue item
 */
typedef struct mediacodec_output_queue {
    int32_t index;
    size_t offset;
    size_t size;
    int64_t timeUs;
    int32_t flags;
    void *vAddr;
    int64_t phyAddr;
    int w;
    int h;
} mediacodec_output_queue_t;

class V4L2Device : public VOWBCallback {

public:
    struct JpegListener {
        // TODO: feedback more information
        virtual bool onJpegComplete(bool success,uint8_t *vaddr, int size, int frameNumber, nsecs_t pts) = 0;
        virtual ~JpegListener();
    };

    V4L2Device(int deviceId, HDMIRX_STATUS *pHDMIRxStatus);
    ~V4L2Device();

    void init();
    void start();
    //void stop();
    bool grabFrame(gralloc_buf_info_t *buffers,
            int buffer_num,
            int req_frame_num,
            nsecs_t *ppts,
            JpegListener *listener,
            bool needThumbnail,
            int32_t thumbWidth,
            int32_t thumbHeight,
            JPEG_RST_INFO *pJpegRst);

    void compressJPEG(JPEG_SRC_BUF_INFO *pSrc, JPEG_DST_BUF_INFO *pDst);

    void removeJPEGThread();
    void *getJPEGThradPtr();
    void setDisplayParameters(
            int w,
            int h,
            int fmt,
            int fps,
            int halFmt,
            //uint32_t thumbWidth,
            //uint32_t thumbHeight,
            uint32_t jpgW,
            uint32_t jpgH);

    int  getWidth() {return mWidth;}
    int  getHeight() {return mHeight;}

    int  getJpgWidth() {return mJpgWidth;}
    int  getJpgHeight() {return mJpgHeight;}

    void breakWaitDequeueLoop() {
#if 1
        mBWaitDequeueLoop = false;

        {
            Mutex::Autolock l(mHalCondLock);
            mHalBufAvailableSignal.signal();
        }
#endif
    }

private:

    enum {
        kWhatCodecNotify         = 'cdcN',
        kWhatInputAvailable      = 'inpA'
    };

    /**
     * AHandler of MediaCodec
     */
    class MJPEGDecodeHandler : public AHandler {
    public:
        MJPEGDecodeHandler(V4L2Device *parent);
        virtual ~MJPEGDecodeHandler();
    protected:
        virtual void onMessageReceived(const sp <AMessage> &msg);
    private:
        V4L2Device *mParent;
    };

    /**
     * thread to operate v4l2 device
     */
    class V4L2Thread : public Thread {
    public:
        V4L2Thread(V4L2Device *parent);
        ~V4L2Thread();
    private:
        virtual bool threadLoop();
        V4L2Device  *mParent;
    };

    /**
     * thread to use media codec to decode MJPEG
     */ 
    class MediaCodecThread : public Thread {
    public:
        MediaCodecThread(V4L2Device *parent);
        ~MediaCodecThread();
    private:
        virtual bool threadLoop();
        V4L2Device  *mParent;
    };

    /**
     * one time thread to decode a jpeg picture.
     */ 
    class JPEGThread : public Thread {
    public:
        JPEGThread(V4L2Device *parent,
            JpegListener *listener,
            allocator_info_t *srcYUVBuf,
            gralloc_buf_info_t *dstJpgBufs,
            int num,
            int frameNumber,
            nsecs_t pts,
            bool needThumbnail,
            int32_t thumbWidth,
            int32_t thumbHeight,
            JPEG_RST_INFO *pRst);

        ~JPEGThread();
        // trick to run threadLoop in current thread.
        void syncRun() { threadLoop(); }
    private:
        V4L2Device          *mParent;
        JpegListener        *mListener;
        allocator_info_t    *mSrcYUVBuf;
        gralloc_buf_info_t  *mDstJpgBufs;
        int                  mNum;
        int                  mFrameNumber;
        nsecs_t              mPTS;
        JPEG_RST_INFO       *mJpgRst;
        bool                 mNeedThumbnail;
        int32_t              mThumbWidth;
        int32_t              mThumbHeight;

        virtual bool threadLoop();
    };

    /**
     * worker threads
     */ 
    sp<V4L2Thread>              mThread;
    sp<JPEGThread>              mJPEGThread;
    sp<MediaCodecThread>        mMediaCodecThread;

    /**
     * buffer infos of buffer that directly queues to V4L2 device
     */ 
    allocator_info_t            mAllocators[NUMS_OF_ION_BUF];

    /**
     * buffer infos of buffer that pass to vo writeback helper
     */
    allocator_info_t            mVOWBAllocators[VO_WRITEBAC_BUF_COUNT];

    /**
     * info of jpeg picture working buffer
     */
    allocator_info_t            mJPEGWorkingBuf;
    gralloc_buf_info_t          mJPEGWorkingDstBuf;

    /**
     * temp buffer to do resize task
     */ 
    allocator_info_t            mRawResizeBuf;

    /**
     * list of buffers juest dequeued from V4L2 device, could be NV12 raw frame, or MJPEG frames
     */
    Vector<allocator_info_t *>  mDequeuedBuffers;

    /**
     * input buffers requested by MediaCodec
     */
    Vector<mediacodec_input_queue_t *> mMediaCodecInputQueue;

    /**
     * output buffers reported by MediaCodec
     */
    Vector<mediacodec_output_queue_t *> mMediaCodecOutputQueue;

    mutable Mutex       mQueueMutex;
    mutable Mutex       mMediaCodecInputQueueMutex;
    mutable Mutex       mMediaCodecOutputQueueMutex;

    // members for MediaCodecThread loop control
    mutable Mutex       mMediaCodecCondLock;
    Condition           mFrameAvailableSignal;

    mutable Mutex       mHalCondLock;
    Condition           mHalBufAvailableSignal;

    int                 mWidth;
    int                 mHeight;

    int                 mJpgWidth;
    int                 mJpgHeight;

    int                 mFormat;            // v4l2 format
    int                 mHalPixelFormat;    // hal format
    int                 mFps;
    int                 mBufSize;
    char                mDevice[V4L2_DEV_STR_LEN];
    int                 mDeviceId;
    bool                mNeed16Align;
    bool                mNeedCheckHDCP;
    struct vdIn         videoIn;
    int                 mFd;
    bool                mBDoDequeue;
    bool                mBWaitDequeueLoop;
    bool                mMediaCodecThreadAlive;
    bool                mTrustDriverPts;
    unsigned long       mSeHandle;

    alloc_device_t     *mBufAlignRemove_pAllocDev;
    const struct hw_module_t *mGrallocModule;

    GrallocWrapper      *mGrallocWrapper;
    bool                mPassRtkPrivData;

    unsigned int        mDumpFileCnt;
    unsigned int        mDumpFileCntMcdc;
    unsigned int        mDumpFileCntScalNoAli;
    unsigned int        mDumpFileCntNative;

    nsecs_t             mBaseTime;
    nsecs_t             mPreviousPTS;

    //uint32_t            mThumbWidth;
    //uint32_t            mThumbHeight;

    uint8_t            *mThumbBuffer;
    uint32_t            mThumbBufSize;

    HDMIRX_STATUS      *mHDMIRxStatus;

    int64_t             mHdcpTimeSend;
    int64_t             mHdcpTimeResponse;
    int32_t             mHdcpInitSkipFrameCount;

    bool                mUseDMABufMode;

    // MediaCodec related members..
    sp<ALooper>                 mLooper;
    sp<MediaCodec>              mCodec;
    sp<MJPEGDecodeHandler>      mHandler;
    sp<AMessage>                mReply;

    // deinterlace helper
    Camera3VoWritebackHelper *mVOWBHelper;
    bool                      mNeedVOWB;

    void uninit();

    void allocateIONBufs();
    void allocateV4L2Bufs();
    void allocateVOWBBufs();

    int  initV4L2(const char *device,
            int width,
            int height,
            int pixelformat,
            int numBuffers,
            int fps,
            allocator_info_t *buf_infos);

    int  startStreaming();
    int  stopStreaming();

    bool queueFrame(allocator_info_t *pInfo);
    bool dequeueFrameToQueue();

    // Basic queue operation API
    void pushToQueue(allocator_info_t *pInfo);
    void pushToMediaCodecInputQueue(mediacodec_input_queue_t *item);
    void pushToMediaCodecOutputQueue(mediacodec_output_queue_t *item);

    allocator_info_t *popFromQueue();
    mediacodec_input_queue_t *popFromMediaCodecInputQueue();
    mediacodec_output_queue_t *popFromMediaCodecOutputQueue();

    void closeDev();

    bool ScaleYuvDstNoAlign(uint32_t srcPhyBuffer,
                uint8_t** ppYuv,
                uint32_t *scaled_buf_size,
                int iScaleWidthTo,
                int iScaleHeightTo,
                int srcWidth,
                int srcHeight);

    bool ScaleYuv(uint32_t srcPhyBuffer,
            uint8_t** ppYuv,
            uint32_t *scaled_buf_size,
            int iScaleWidthTo,
            int iScaleHeightTo,
            int srcWidth,
            int srcHeight);

    bool se_Create420spPhyBuffer(alloc_device_t  *pAllocDev,
            int iWidth,
            int iHeight,
            int format,
            buffer_handle_t *pBufferHandle,
            uint32_t *pPhyBufferHandle);
    bool se_PhyBuf2VirBuf(int iWidth,
            int iHeight,
            buffer_handle_t pBufferHandle,
            void **pvirtaddr);
    bool se_DestroyPhyBuffer(alloc_device_t  *pAllocDev,
            buffer_handle_t pBufferHandle);

    bool se_init(alloc_device_t  **ppAllocDev);
    void se_uninit(alloc_device_t  **ppAllocDev);

    void dumpData(void *vaddr, int size, char *path, unsigned int *pCnt);
    bool isDisplayParamValid();
    void calculateAllocBufSize(int w_src, int h_src, int fmt, bool aligned, int *pw, int *ph, int *psize);
    void calculateDisplayBufferSize(int w_src, int h_src, int halfmt, bool aligned, int *pw, int *ph, int *psize);
    bool displayBufferReady();

    bool convertRawBuffer(
        uint8_t *dstVAddr,
        uint8_t *cb,
        uint8_t *cr,
        uint32_t srcPhyAddr,
        uint8_t *srcVAddr,
        int32_t dstSize,
        int32_t srcSize,
        int32_t dstWidth,
        int32_t dstHeight,
        int32_t srcWidth,
        int32_t srcHeight);

    allocator_info_t *getDisplayRawBuffer();
    mediacodec_output_queue_t *getDisplayCodecBuffer();
    bool isCompressedFormat(int v4l2Fmt);
    void returnMediaCodecOutputBuffer(mediacodec_output_queue_t *item);
    bool createMediaCodec();
    void cleanUpMediaCodec();
    char *getMediaCodecTypeString();
    bool checkMJPEGFrameValidate(allocator_info_t *pInfo);
    // MediaCodec callbacks
    void handleInputAvailable(int32_t index);
    void handleOutputAvailable(int32_t index, size_t offset, size_t size, int64_t timeUs, int32_t flags);

    void prepareSrcRawIONBuf();

    int32_t createThumbnailJpeg(
        uint32_t srcPhyAddr,
        uint32_t srcWidth,
        uint32_t srcHeight,
        int32_t thumbWidth,
        int32_t thumbHeight);

    nsecs_t calcFrameInterval(nsecs_t timestamp);

    // for HDCP protection
    bool checkPrivData(gralloc_buf_info_t *buf);
    bool hdcpCheckEnabled();

    // VOWBCallback
    void returnSrcBuffer(allocator_info_t *pBuf);
    void signalBufferAvailable();
};

}; // namespace android

#endif // V4L2_DEVICE_H

