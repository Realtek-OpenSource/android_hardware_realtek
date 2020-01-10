#ifndef ANDROID_CAMERA_HARDWARE_3_BASE
#define ANDROID_CAMERA_HARDWARE_3_BASE

#include <linux/videodev2.h>
#include <utils/List.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/SortedVector.h>
#include <utils/Mutex.h>
#include <utils/threads.h>
#include <hardware/camera3.h>
#include <include/CameraMetadata.h>
#include <libRTKAllocator/include/hardware/GrallocWrapper.h>

#include "Common.h"
#include "CameraCap.h"
#include "Base.h"

#define MAX_STREAM_NUM          64
#define DUMP_DEV                150
// MAX_BUFFERS_DEQUEUE is related to android.hardware.camera2.cts.SurfaceViewPreviewTest#testSurfaceSet
#define MAX_BUFFERS_DEQUEUE     4      // ? work-around cts
#define MAX_REQUEST_BUFFER_NUM  32
#define NSEC_PER_33MSEC         33000000LL
#define DEV_STR_LEN             32

#define CAMERA_GRALLOC_USAGE    GRALLOC_USAGE_HW_TEXTURE | \
                                GRALLOC_USAGE_HW_RENDER | \
                                GRALLOC_USAGE_SW_READ_OFTEN | \
                                GRALLOC_USAGE_SW_WRITE_OFTEN | \
                                GRALLOC_USAGE_HW_ION

#define HDMI_GRALLOC_USAGE      (CAMERA_GRALLOC_USAGE) | \
                                MIPI_HW_BUG_USAGE

#define LOG_FUNCTION()              ALOGV("[%s] ENTER",__FUNCTION__)
#define LOG_LINE()                  ALOGV("[%s][%d]",__FUNCTION__,__LINE__)
#define LOG_LINED()                 ALOGD("[%s][%d]",__FUNCTION__,__LINE__)
#define ALOGVV                      ALOGV

// from 9.0, migrate to hidl implementation
using android::hardware::camera::common::V1_0::helper::CameraMetadata;

using namespace android;

namespace android {

typedef List<camera3_stream_t*>           StreamList;
typedef List<camera3_stream_t*>::iterator StreamIterator;

class String8;

struct Res {
    int width;
    int height;

    Res() {
        width = 0;
        height = 0;
    }

    Res(int w, int h) {
        width = w;
        height = h;
    }

    bool operator< (const Res &rhs) const {
        if(width < rhs.width)
            return true;
        if(width == rhs.width && height < rhs.height)
            return true;
        return false;
    }
};

// a little bit hacky, but should be okay..
static const camera_metadata_rational colorTransform[9] = {
    {1,1}, {0,1}, {0,1},
    {0,1}, {1,1}, {0,1},
    {0,1}, {0,1}, {1,1} };

static const float colorGains[4] = {
    1.0f, 1.0f, 1.0f, 1.0f
};

static const int32_t kAvailableFormats[] = {
        HAL_PIXEL_FORMAT_RAW16,
        HAL_PIXEL_FORMAT_BLOB,
        HAL_PIXEL_FORMAT_RGBA_8888,
        HAL_PIXEL_FORMAT_IMPLEMENTATION_DEFINED,
        HAL_PIXEL_FORMAT_RTK_16_YCbCr_420_SP,
        HAL_PIXEL_FORMAT_RTK_W16_H16_YCrCb_420_SP,
        HAL_PIXEL_FORMAT_RTK_W16_H16_YCbCr_420_SP,
        // These are handled by YCbCr_420_888
        //        HAL_PIXEL_FORMAT_YV12,
        //        HAL_PIXEL_FORMAT_YCrCb_420_SP,
        HAL_PIXEL_FORMAT_YCbCr_420_888,
        //HAL_PIXEL_FORMAT_RGB_565,
        //HAL_PIXEL_FORMAT_Y16      // ImageFormat.DEPTH16
};

typedef struct _RECT_FPS_INFO {
    int32_t width;
    int32_t height;
    int32_t fps;
} RECT_FPS_INFO;

/**
 * This is a base class of all CameraHardware class, it defines the basic
 * interface of a hal3 module
 */
class CameraHardware3Base {

public:
    CameraHardware3Base(int camId,
        int v4l2Id,
        int facing);

    virtual ~CameraHardware3Base();

    // APIs talking with hal
    virtual status_t    connectCamera(/*hw_device_t** device*/)=0;
    virtual status_t    closeCamera()=0;
    virtual status_t    configureStreams(camera3_stream_configuration_t *streamList)=0;
    virtual status_t    flush()=0;
    virtual void        cleanupOnPlugout() = 0;

    status_t            initialize(const camera3_callback_ops_t *ops);
    void                uninitialize() { mStatus = STATUS_ERROR; }
    camera_metadata_t*  getStaticInfo();
    camera_metadata_t*  translateCapabilityToMetadata(int type);

    /**
     * Base class finish checking, and pass Request to child.
     */
    status_t            processCaptureRequest(camera3_capture_request_t *request);
    virtual status_t    processCaptureRequest(const Request &r)=0;

    // added from Android O, init V4L2 when receiving first process request, cause the
    // metadata within including fps info.
    virtual status_t    runtimeSetV4L2Device()=0;

protected:
    typedef KeyedVector<uint32_t, camera3_capture_request_t *> InFlightMap;

    template <typename fwkType, typename halType> struct QCameraMap {
        fwkType fwk_name;
        halType hal_name;
    };

    typedef struct {
        const char *const desc;
        cam_cds_mode_type_t val;
    } QCameraPropMap;

    /**
     * Private stream information, stored in camera3_stream_t->priv.
     */
    struct PrivateStreamInfo {
        bool alive;
    };

    static const QCameraMap<camera_metadata_enum_android_control_effect_mode_t,
            cam_effect_mode_type> EFFECT_MODES_MAP[];
    static const QCameraMap<camera_metadata_enum_android_control_awb_mode_t,
            cam_wb_mode_type> WHITE_BALANCE_MODES_MAP[];
    static const QCameraMap<camera_metadata_enum_android_control_scene_mode_t,
            cam_scene_mode_type> SCENE_MODES_MAP[];
    static const QCameraMap<camera_metadata_enum_android_control_af_mode_t,
            cam_focus_mode_type> FOCUS_MODES_MAP[];
    static const QCameraMap<camera_metadata_enum_android_color_correction_aberration_mode_t,
            cam_aberration_mode_t> COLOR_ABERRATION_MAP[];
    static const QCameraMap<camera_metadata_enum_android_control_ae_antibanding_mode_t,
            cam_antibanding_mode_type> ANTIBANDING_MODES_MAP[];
    static const QCameraMap<camera_metadata_enum_android_lens_state_t,
            cam_af_lens_state_t> LENS_STATE_MAP[];
    static const QCameraMap<camera_metadata_enum_android_control_ae_mode_t,
            cam_flash_mode_t> AE_FLASH_MODE_MAP[];
    static const QCameraMap<camera_metadata_enum_android_flash_mode_t,
            cam_flash_mode_t> FLASH_MODES_MAP[];
    static const QCameraMap<camera_metadata_enum_android_statistics_face_detect_mode_t,
            cam_face_detect_mode_t> FACEDETECT_MODES_MAP[];
    static const QCameraMap<camera_metadata_enum_android_lens_info_focus_distance_calibration_t,
            cam_focus_calibration_t> FOCUS_CALIBRATION_MAP[];
    static const QCameraMap<camera_metadata_enum_android_sensor_test_pattern_mode_t,
            cam_test_pattern_mode_t> TEST_PATTERN_MAP[];
    static const QCameraMap<camera_metadata_enum_android_sensor_reference_illuminant1_t,
            cam_illuminat_t> REFERENCE_ILLUMINANT_MAP[];
    static const QCameraMap<int32_t,
            cam_hfr_mode_t> HFR_MODE_MAP[];

    static const QCameraPropMap CDS_MAP[];

    /** Fake 3A constants */
    static const nsecs_t kNormalExposureTime;
    static const nsecs_t kFacePriorityExposureTime;
    static const int     kNormalSensitivity;
    static const int     kFacePrioritySensitivity;

    // Rate of converging AE to new target value, as fraction of difference between
    // current and target value.
    static const float   kExposureTrackRate;

    // Minimum duration for precapture state. May be longer if slow to converge
    // to target exposure
    static const int     kPrecaptureMinFrames;

    // How often to restart AE 'scanning'
    static const int     kStableAeMaxFrames;

    // Maximum stop below 'normal' exposure time that we'll wander to while
    // pretending to converge AE. In powers of 2. (-2 == 1/4 as bright)
    static const float   kExposureWanderMin;

    // Maximum stop above 'normal' exposure time that we'll wander to while
    // pretending to converge AE. In powers of 2. (2 == 4x as bright)
    static const float   kExposureWanderMax;

    /* static configuration */
    static const uint32_t kMaxRawStreamCount = 1;
    static const uint32_t kMaxProcessedStreamCount = 3;
    static const uint32_t kMaxJpegStreamCount = 1;
    static const uint32_t kMaxReprocessStreamCount = 2;
    static const uint32_t kMaxBufferCount = MAX_BUFFERS_DEQUEUE;

    // We need a positive stream ID to distinguish external buffers from
    // sensor-generated buffers which use a nonpositive ID. Otherwise, HAL3 has
    // no concept of a stream id.
    static const uint32_t kGenericStreamId = 1;
    static const int64_t  kSyncWaitTimeout     = 10000000; // 10 ms
    static const int32_t  kMaxSyncTimeoutCount = 1000; // 1000 kSyncWaitTimeouts
    static const uint32_t kFenceTimeoutMs      = 2000; // 2 s

    // member to keep v4l2 info
	KeyedVector<int, String8> mFormatList;
	KeyedVector<Res, String8> mSizeList;
	KeyedVector<int, String8> mFpsList;

    Vector<RECT_FPS_INFO> mFpsInfoList;
    Vector<Res> mIgnoredSizeList;

    // camera capability info
    cam_capability_t_rtk mCamCapability;

    // camera capability metadata
    camera_metadata_t   *mStaticMetadata;

    // camera default request template metadata
    camera_metadata_t   *mDefaultMetadata[CAMERA3_TEMPLATE_COUNT];

    const camera3_callback_ops_t *mOps;

    /* Fake 3A state */
    uint8_t             mControlMode;
    bool                mFacePriority;
    uint8_t             mAeState;
    uint8_t             mAfState;
    uint8_t             mAwbState;
    uint8_t             mAeMode;
    uint8_t             mAfMode;
    uint8_t             mAwbMode;

    int                 mAeCounter;
    nsecs_t             mAeCurrentExposureTime;
    nsecs_t             mAeTargetExposureTime;
    int                 mAeCurrentSensitivity;

    bool                mCamOpened;

    int                 mCamId;
    int                 mV4l2Id;
    int                 mFacing;
    int                 mFormat;
    int                 mPerferedFps;

    char                mDevStr[DEV_STR_LEN];
    int                 mMaxFps;
    int                 mMinFps;

    int                 mMaxWidth;
    int                 mMaxHeight;

    int                 mMinWidth;
    int                 mMinHeight;

    uint32_t            mGrallocUsage;
    //int                 mThumbWidth;
    //int                 mThumbHeight;

    uint32_t            mDumpCount;
    bool                mFlushed;
    bool                mDoFlush;

    HDMIRX_STATUS       mHDMIRxStatus;
    uint32_t            mLatestFrameNumber;

    GrallocWrapper      *pGrallocWrapper;

    camera3_stream_t*  mInputStream;

    // All streams, including input stream
    StreamList         mStreams;
    // Cached settings from latest submitted request
    CameraMetadata     mPrevSettings;
    // tracking camera status
    enum {
        // State at construction time, and after a device operation error
        STATUS_ERROR = 0,
        // State after startup-time init and after device instance close
        STATUS_CLOSED,
        // State after being opened, before device instance init
        STATUS_OPEN,
        // State after device instance initialization
        STATUS_READY,
        // State while actively capturing data
        STATUS_ACTIVE
    } mStatus;

    uint32_t        stream_width;
    uint32_t        stream_height;
    uint32_t        jpg_width;
    uint32_t        jpg_height;

    int32_t         mRuntimeFps0;
    int32_t         mRuntimeFps1;

    void initCamCap();

    int initStaticMetadata();

    void makeTable(cam_dimension_t* dimTable,
        size_t size,
        size_t max_size,
        int32_t *sizeTable);

    size_t makeFPSTable2(cam_fps_range_t* fpsTable,
        size_t size,
        size_t max_size,
        int32_t *fpsRangesTable);

    size_t makeFPSTable(cam_fps_range_t* fpsTable,
        size_t size,
        size_t max_size,
        int32_t *fpsRangesTable);

    size_t filterJpegSizes(int32_t *jpegSizes,
        int32_t *processedSizes,
        size_t processedSizesCnt,
        size_t maxCount,
        cam_rect_t active_array_size,
        uint8_t downscale_factor);

    void addStreamConfig(Vector<int32_t> &available_stream_configs,
        int32_t scalar_format,
        const cam_dimension_t &dim,
        int32_t config_type);

    void makeOverridesList(cam_scene_mode_overrides_t* overridesTable,
        size_t size,
        size_t max_size,
        uint8_t *overridesList,
        uint8_t *supported_indexes);

    size_t calcMaxJpegSize();

    status_t equipeStream(camera3_stream_buffer *dst, const camera3_stream_buffer &src);

    int queryV4L2Info(int32_t v4l2Id);

    int enumPixelFormat(int v4l2fd);

    int enumFrameSize(int fmt, int v4l2fd);

    int enumFrameRate(int fmt, int width, int height, int v4l2fd);

    void filterFrameSize();

    bool isValidSize(int w, int h);

    int choiceBestV4L2Format();

    void getPerferedFps();

    int convertV4L2FmtToHalFmt(int v4l2Fmt);

    const char *getStreamForamtString(int format);

    status_t process3A(CameraMetadata &settings);

    status_t doFakeAE(CameraMetadata &settings);

    status_t doFakeAF(CameraMetadata &settings);

    status_t doFakeAWB(CameraMetadata &settings);

    void update3A(CameraMetadata &settings);

    int getStreamBufferSize(camera3_stream_buffer_t *stream_buffer);

    int getStreamBufferSize(StreamBuffer *stream_buffer);

    int getStreamBufferSize(buffer_handle_t *buffer);

    void getStreamBufferRect(buffer_handle_t *buffer,
        int *w,
        int *h);

    void getStreamBufferVAddr(buffer_handle_t *buffer,
        void **vPtr,
        int format,
        void **cb,
        void **cr);

    void getStreamBufferPhyAddr(buffer_handle_t *buffer,
        unsigned int *phyAddr);

    void getBufferVAddr(buffer_handle_t *pHandle,
        int w,
        int h,
        int usage,
        void **vPtr,
        int format,
        void **cb ,
        void **cr);

    bool addExif(JPEG_RST_INFO *pInfo,
        uint8_t *metaBuf /* , uint32_t bufSize */ ,
        MISC_FIELD_INFO *pMiscInfo);

    void dumpData(void *vaddr,
        int size,
        char *path,
        uint32_t *pCnt);

    void collectRequestMiscInfo(CameraMetadata &settings,
        MISC_FIELD_INFO *pInfo);

    int getHDMIRxDeviceStatus();

    void clearStreams();

    // some basic implementations
    status_t connectCameraBase();
    status_t closeCameraBase();
    status_t configureStreamsBase(camera3_stream_configuration_t *streamList);

    bool isBlockedRes(int w, int h);

    int32_t getMaxFpsOfRect(int32_t w, int32_t h);
    int32_t getMinFpsOfRect(int32_t w, int32_t h);

}; // class CameraHardware3Base

}; // namespace android

#endif // ANDROID_CAMERA_HARDWARE_3_BASE
