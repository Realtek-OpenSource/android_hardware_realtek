#ifndef __CAMERA3_FORMAT_CONVERT_HELPER__
#define __CAMERA3_FORMAT_CONVERT_HELPER__

#include <utils/Errors.h>
#include <hardware/gralloc.h>
#include <libRTKAllocator/include/hardware/GrallocWrapper.h>
#include "Base.h"
#include "Common.h"
#include "CameraMonitor.h"

#define RTK_RAW_BUFFER(x)    (  x==HAL_PIXEL_FORMAT_RTK_16_YCbCr_420_SP\
                             || x==HAL_PIXEL_FORMAT_RTK_W16_H16_YCrCb_420_SP\
                             || x==HAL_PIXEL_FORMAT_RTK_W16_H16_YCbCr_420_SP \
                             )

using namespace android;
using namespace android_camera_hal3;

namespace androidcamera3 {

typedef struct _BUF_CONVERT_INFO {
    int32_t         w;
    int32_t         h;
    int32_t         format;
    void            *vAddr;
    uint32_t        phyAddr;
    uint32_t        bufferSize;
    buffer_handle_t *pHandle;
    AllocatorDef    *allocator;
} BUF_CONVERT_INFO;

class FormatConvertHelper {

public:
    FormatConvertHelper(/*int32_t v4l2Fmt, int32_t halFmt*/
        GrallocWrapper *pGrallocWrapper,
        HDMIRX_STATUS *pRxStatus,
        int32_t v4l2Id);
    ~FormatConvertHelper();

    uint32_t                    mJpegMetaDstRawCount;
    uint32_t                    mJpegMetaSrcRawCount;
    uint32_t                    mJpegRstCount;

    status_t convertBuffers(Request *r);
    status_t convertBuffers(Request *r, BUF_CONVERT_INFO *ext);

    void setRtkPrivData(Request *r, uint32_t inputFps);

    void compressJPEG(
        JPEG_SRC_BUF_INFO *pSrc,
        JPEG_DST_BUF_INFO *pDst);

    bool getPrivData(StreamBuffer *pStreamBuf);

private:
    //int32_t                     mFormat;
    int32_t                     mHalPixelFormat;
    HDMIRX_STATUS *             mRxStatus;
    int32_t                     mV4l2Id;
    unsigned long               mSeHandle;

    alloc_device_t *            mBufAlignRemove_pAllocDev;
    const struct hw_module_t *  mGrallocModule;

    GrallocWrapper *            mGrallocWrapper;

    // backward compatible...
    uint8_t *                   mThumbBuffer;
    int32_t                     mThumbBufSize;

    CameraMonitor *             mCameraMonitor;

    nsecs_t prevTime;
    nsecs_t prevInterval;

    bool se_init(alloc_device_t **ppAllocDev);

    void se_uninit(alloc_device_t **ppAllocDev);

    bool ScaleYuvDstNoAlign(
        uint32_t srcPhyBuffer,
        uint8_t** ppYuv,
        uint32_t *scaled_buf_size,
        int iScaleWidthTo,
        int iScaleHeightTo,
        int srcWidth,
        int srcHeight);

    bool Nv12ScaleNoAlign(
        uint8_t *pSrc,
        uint8_t** ppYuv,
        uint32_t *scaled_buf_size,
        int iScaleWidthTo,
        int iScaleHeightTo,
        int srcWidth,
        int srcHeight);

    bool ScaleYuv(
        uint32_t srcPhyBuffer,
        uint8_t** ppYuv,
        uint32_t *scaled_buf_size,
        int iScaleWidthTo,
        int iScaleHeightTo,
        int srcWidth,
        int srcHeight);

    bool se_Create420spPhyBuffer(
        alloc_device_t *pAllocDev,
        int iWidth,
        int iHeight,
        int format,
        buffer_handle_t *pBufferHandle,
        uint32_t *pPhyBufferHandle);

    bool se_PhyBuf2VirBuf(
        int iWidth,
        int iHeight,
        buffer_handle_t pBufferHandle,
        void **pvirtaddr);

    bool se_DestroyPhyBuffer(
        alloc_device_t  *pAllocDev,
        buffer_handle_t pBufferHandle);

    bool isCompressedFormat(int v4l2Fmt);

    void findSrcBufInfo(
        const Request *r,
        BUF_CONVERT_INFO *pSrcInfo);

    status_t convertOneBuffer(
        BUF_CONVERT_INFO *src,
        BUF_CONVERT_INFO *dst,
        MISC_FIELD_INFO *info);

    status_t convertToRtkRawBuffer(
        BUF_CONVERT_INFO *src,
        BUF_CONVERT_INFO *dst);

    status_t convertToNativeRawBuffer(
        BUF_CONVERT_INFO *src,
        BUF_CONVERT_INFO *dst);

    status_t convertToJPEG(
        BUF_CONVERT_INFO *src,
        BUF_CONVERT_INFO *dst,
        MISC_FIELD_INFO *info);

    status_t processThumbnail(
        BUF_CONVERT_INFO *src,
        MISC_FIELD_INFO *info,
        uint8_t *pThumbBuf,
        uint32_t bufSize,
        int32_t *pByteUsed);

    int32_t createThumbnailJpeg(
        uint32_t srcPhyAddr,
        uint32_t srcWidth,
        uint32_t srcHeight,
        int32_t thumbWidth,
        int32_t thumbHeight);

    void getBufferVAddr(
        buffer_handle_t *buffer,
        int format,
        int w,
        int h,
        void **ppVPtr);

    void getBufferCbCr(
        buffer_handle_t *buffer,
        int w,
        int h,
        void **ppVPtr,
        void **ppCb,
        void **ppCr);

    void getBufferPhyAddr(
        buffer_handle_t *buffer,
        uint32_t *phyAddr);

    void dumpData(void *vaddr,
        int size,
        char *path,
        uint32_t *pCnt);

    void setRtkPrivData(
        StreamBuffer *pStreamBuf,
        uint32_t inputFps,
        nsecs_t pts);

    nsecs_t calFrameInterval(nsecs_t timestamp);

};

}; // namespace androidcamera3


#endif
