#ifndef ANDROID_CAMERA_HARDWARE_3
#define ANDROID_CAMERA_HARDWARE_3

#include "CameraHardware3Base.h"
#include "V4L2Device.h"

using namespace androidcamera3;

namespace android{

class CameraHardware3 : public CameraHardware3Base {

public:
    CameraHardware3(int camId,
        int v4l2Id,
        int facing);

    ~CameraHardware3();

    status_t            connectCamera(/*hw_device_t** device*/);
    status_t            closeCamera();
    status_t            configureStreams(camera3_stream_configuration_t *streamList);
    status_t            processCaptureRequest(const Request &r);
    status_t            flush();
    status_t            runtimeSetV4L2Device();

private:
    InFlightMap         mInFlightMap;
    Mutex               mInFlightMapLock;
    Mutex               mLock;
    V4L2Device          *mDevice;
    gralloc_buf_info_t  mGrallocBufInfos[MAX_REQUEST_BUFFER_NUM];
    Mutex               mV4l2Lock;
    List<Request>       mInFlightQueue;
    Mutex               mInFlightLock;
    Condition           mInFlightSignal;
    bool                mInFlightQueueAlive;

    // flow control variables
    nsecs_t             mPrevPTS;
    nsecs_t             mPrevSystemTime;

    void sendCaptureResult(camera3_capture_result_t *result);
    void sendNotify(camera3_notify_msg_t *msg);
    void addFrameRecord(uint32_t frameNumber,camera3_capture_request_t *req);
    void removeFrameRecord(uint32_t frameNumber);
    void cleanupForbiddenFrameRecords();
    void signalReadoutIdle();
    bool removeReadoutThread();
    void returnFailedRequest(Request *r);
    bool queueCaptureRequest(const Request &r);
    bool clearCaptureRequestQueue();

    int32_t getInFlightQueueSize() {
        return mInFlightQueue.size();
    }

    void setV4L2Device(int w,
        int h,
        int fps,
        int format,
        int jpg_w,
        int jpg_h);

    friend class V4L2Device;

    /**
     * Processing thread for sending out results
     */
    class ReadoutThread : public Thread , private V4L2Device::JpegListener{
      public:
        ReadoutThread(CameraHardware3 *parent);
        ~ReadoutThread();

        // Test if the readout thread is idle (no in-flight requests, not
        // currently reading out anything
        bool     isIdle();

        void     signalInFlightSignal();

        // Wait until isIdle is true
        status_t waitForReadout();

      private:
        static const nsecs_t kWaitPerLoop  = 10000000L; // 10 ms
        static const nsecs_t kMaxWaitLoops = 1000;
        static const size_t  kMaxQueueSize = 2;

        CameraHardware3 *mParent;

        bool          mThreadActive;
        bool          mThreadBreak;

        virtual bool threadLoop();
        bool threadLoopInternal();

        // Only accessed by threadLoop
        Request mCurrentRequest;

        nsecs_t mCaptureTime;

        Mutex                 mJpegLock;
        bool                  mJpegWaiting;
        camera3_stream_buffer mJpegHalBuffer;
        uint32_t              mJpegFrameNumber;
        nsecs_t               mJpegCaptureTime;
        void                 *mJpegBufVAddr;
        int                   mJpegBufSize;
        CameraMetadata        mJpegSettings;

        virtual bool onJpegComplete(bool success,
            uint8_t *vaddr,
            int size,
            int frameNumber,
            nsecs_t pts);

        void handleReprocessRequest(/*Request &req*/);
    };

    sp<ReadoutThread> mReadoutThread;

};  // class CameraHardware3

}; // namespace android

#endif // ANDROID_CAMERA_HARDWARE_3
