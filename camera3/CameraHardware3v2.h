#ifndef ANDROID_CAMERA_HARDWARE_3_V2
#define ANDROID_CAMERA_HARDWARE_3_V2

#include <utils/Mutex.h>
#include "CameraHardware3Base.h"
#include "V4L2Device2Common.h"
#include "FormatConvertHelper.h"

#include <rtk_power/power.h>
#ifdef RTK_POWER_SERVICE_VERSION
#include <android/hardware/power/1.0/IPower.h>

using ::android::hardware::power::V1_0::IPower;
using ::android::hardware::power::V1_0::Feature;
using ::android::hardware::power::V1_0::PowerHint;
using ::android::hardware::power::V1_0::PowerStatePlatformSleepState;
using ::android::hardware::power::V1_0::Status;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::sp;

#endif /* end of RTK_POWER_SERVICE_VERSION */

using namespace androidcamera3;
using namespace android;

namespace android {

class CameraHardware3v2 : public CameraHardware3Base,
                            public V4L2Device2Callback {

    class PowerHintWatchdogThread : public Thread {
    public:
        PowerHintWatchdogThread(CameraHardware3v2 *parent) {
            mParent = parent;
#ifdef RTK_POWER_SERVICE_VERSION
            mPower = android::hardware::power::V1_0::IPower::getService();
#endif
        }

        ~PowerHintWatchdogThread();

        void stop() {
            mRunning = false;
            Mutex::Autolock l(mThreadLock);
            mSignal.signal();
        }

        void start() {
            mRunning = true;
            run("PowerHint");
        }

    private:
        virtual bool            threadLoop();
        bool                    mRunning;
        Mutex                   mThreadLock;
        Condition               mSignal;
        CameraHardware3v2*      mParent;
        nsecs_t                 mWaitTime = 1E9;

#ifdef RTK_POWER_SERVICE_VERSION
        sp<IPower>              mPower;
#endif

    };

    /**
     * Thread to return capture result and call notify
     */
    class ShutterThread : public Thread {
    public:
        ShutterThread(CameraHardware3v2 *parent);
        ~ShutterThread();
        void                    signal();
        void                    stop();
    private:

        virtual bool            threadLoop();

        enum {
            INPUT_QUEUE,
            OUTPUT_QUEUE,
            NO_QUEUE,
        } mQueueIndex;

        Mutex                   mThreadLock;
        Condition               mSignal;
        CameraHardware3v2*      mParent;
        bool                    mRunning;
    };

public:
    CameraHardware3v2(int camId,
        int v4l2Id,
        int facing);

    ~CameraHardware3v2();

    status_t connectCamera(/*hw_device_t** device*/);
    status_t closeCamera();
    status_t configureStreams(camera3_stream_configuration_t *streamList);
    status_t processCaptureRequest(const Request &r);
    status_t flush();
    status_t runtimeSetV4L2Device();
    void     cleanupOnPlugout();

    void submitRequest(Request *r);
    void submitErrorRequest(Request *r);

    /**
     * V4L2Device2Callback
     */
    void returnRequest(Request *r);

private:
    Mutex                       mLock;
    V4L2Device2Common*          mDevice;
    bool                        mFlushed;
    V4L2Params                  mV4L2Params;
    //int32_t                   mErrorFrames;
    int32_t                     mResultFrameNumber;
    int32_t                     mRequestFrameNumber;

    nsecs_t                     mPrevSystemTime;
    nsecs_t                     mPrevPTS;

    Mutex                       mOutputRequestQueueLock;
    Vector<Request *>           mOutputRequestQueue;

    Mutex                       mInputRequestQueueLock;
    Vector<Request *>           mInputRequestQueue;

    Mutex                       mFrameNumberQueueLock;
    Vector<int32_t>             mFrameNumberQueue;

    sp<ShutterThread>           mShutterThread;
    sp<PowerHintWatchdogThread> mPowerHintThread;

    FormatConvertHelper         *mFormatConvertHelper;

    void setV4L2Device(V4L2Params *params);

    bool queueCaptureRequest(const Request &r);
    void reportFailedRequest(const Request &r);

    void queueFinishedOutputRequest(Request *r);
    void dequeueOutputRequest();

    void queueReprocessRequest(const Request &r);
    void dequeueReprocessRequest();

    void queueFrameNumber(int32_t num);
    void dequeueFrameNumber();

    void signalDeviceIdle() { mStatus = STATUS_READY; }

    // implement it for CTS only.
    void submitReprocessRequest(Request *r);

    void removeShutterThread();
}; // class CameraHardware3v2

}; // namespace android

#endif // ANDROID_CAMERA_HARDWARE_3_V2
