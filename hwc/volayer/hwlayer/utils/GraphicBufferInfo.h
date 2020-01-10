#ifndef __RTK_HWC_HWLAYER_UTILS_GRAPHICB_BUFFER_INFO_H_
#define __RTK_HWC_HWLAYER_UTILS_GRAPHICB_BUFFER_INFO_H_
#include "hwlayer_utils.h"

#include <hardware/gralloc.h>
#include <utils/Mutex.h>
#include "IonBuffer.h"

#include <GrallocCMD.h>
#define GRALLOC_BIT(i) (1U << i)
#define GRALLOC_BITS(_start, _end) ((GRALLOC_BIT(_end) - GRALLOC_BIT(_start)) + GRALLOC_BIT(_end))

#define HAL_PIXEL_FORMAT_RTK_P10_CM_MASK        GRALLOC_BIT(27)
#define HAL_PIXEL_FORMAT_RTK_P10_LM_MASK        GRALLOC_BIT(26)
#define HAL_PIXEL_FORMAT_RTK_P10_WIDTH_MASK     GRALLOC_BITS(13,25)
#define HAL_PIXEL_FORMAT_RTK_P10_HEIGHT_MASK    GRALLOC_BITS(0,12)

#define HAL_PIXEL_FORMAT_RTK_P10_CM_GET(x)      (((x) & HAL_PIXEL_FORMAT_RTK_P10_CM_MASK) >> 27)
#define HAL_PIXEL_FORMAT_RTK_P10_LM_GET(x)      (((x) & HAL_PIXEL_FORMAT_RTK_P10_LM_MASK) >> 26)
#define HAL_PIXEL_FORMAT_RTK_P10_WIDTH_GET(x)   (((x) & HAL_PIXEL_FORMAT_RTK_P10_WIDTH_MASK) >> 13)
#define HAL_PIXEL_FORMAT_RTK_P10_HEIGHT_GET(x)  (((x) & HAL_PIXEL_FORMAT_RTK_P10_HEIGHT_MASK) >> 0)
#define RTK_P10_MAX_COMPRESSED_PLANE 2

// If the format is not defined in android/system/core/include/system/graphics.h,
// we define them in here.
#ifndef HAL_PIXEL_FORMAT_RTK_W64_H64_YCbCr_420_SP
#define HAL_PIXEL_FORMAT_RTK_W64_H64_YCbCr_420_SP 0x37
#endif

#ifndef HAL_PIXEL_FORMAT_RTK_W64_H64_YCrCb_420_SP
#define HAL_PIXEL_FORMAT_RTK_W64_H64_YCrCb_420_SP 0x57
#endif

#ifndef HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED_VP9
#define HAL_PIXEL_FORMAT_RTK_P8_COMPRESSED_VP9 0x45
#endif

#ifndef HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED_VP9
#define HAL_PIXEL_FORMAT_RTK_P10_COMPRESSED_VP9 0x46
#endif

class ProtectedOps;
class GraphicBufferInfo {
public:
    struct private_yuv_data {
        unsigned int        phyAddr;
        unsigned int        size;
        int                 format;
        int                 width;
        int                 height;
        int                 stride;
        int                 usage;
        int                 share_fd;
        unsigned int        yuv_mode;
        int                 share_config_fd;
        unsigned long long  pts[2];
        int                 delay_mode;
        int                 delay_depth;
        unsigned int        IsForceDIBobMode;
        int                 init_frame;
        int                 deintflag; // 0:AUTODEINT 1:FORCEDEINT 2:FORCEPROGRESSIVE
        int                 ssid;
        unsigned long long  p10_compressed_offset[RTK_P10_MAX_COMPRESSED_PLANE];
        unsigned long long  p10_compressed_stride[RTK_P10_MAX_COMPRESSED_PLANE];
        unsigned long long  p10_compressed_sliceheight[RTK_P10_MAX_COMPRESSED_PLANE];
        unsigned int        lumaTableOffset;
        unsigned int        chromaTableOffset;
        unsigned int        lumaTableOffsetR;
        unsigned int        chromaTableOffsetR;
        int                 sliceheight;
        int                 ch_stride;
        int                 origin_width;
        int                 origin_height;
        unsigned int        reserve[29];
    };

    struct private_rtk_data {
        unsigned int        yuv_mode;
        unsigned long long  pts[2];
        int                 delay_mode;
        int                 delay_depth;
        unsigned int        IsForceDIBobMode;
        int                 init_frame;
        int                 deintflag; // 0:AUTODEINT 1:FORCEDEINT 2:FORCEPROGRESSIVE
        int                 ssid;
        unsigned int        lumaOffTblAddr;
        unsigned int        chromaOffTblAddr;
        unsigned int        lumaOffTblAddrR;
        unsigned int        chromaOffTblAddrR;
        unsigned int        bufBitDepth;
        unsigned int        bufFormat;
        unsigned int        transferCharacteristics;
        unsigned int        display_primaries_x0;
        unsigned int        display_primaries_y0;
        unsigned int        display_primaries_x1;
        unsigned int        display_primaries_y1;
        unsigned int        display_primaries_x2;
        unsigned int        display_primaries_y2;
        unsigned int        white_point_x;
        unsigned int        white_point_y;
        unsigned int        max_display_mastering_luminance;
        unsigned int        min_display_mastering_luminance;
        unsigned int        display_width;
        unsigned int        display_height;
        union {
            unsigned int        flag;
            struct {
                unsigned int    isHDCP:1; // bit[0]
            };
        } hdmi_flag;
        unsigned long long  hdmi_hdcp_key;
        unsigned long long  hdmi_hdcp_key_response;
        unsigned int        display_stride;
        unsigned int        video_full_range_flag; //default= 1
        unsigned int        matrix_coefficients; //default= 1
        unsigned int        is_tch_video;
        unsigned int        technicolor_data[152];
        unsigned int        hdr_metadata_addr;//'rtk9'
        unsigned int        hdr_metadata_size;//'rtk9'
        unsigned int        tch_metadata_addr;//'rtk9'
        unsigned int        tch_metadata_size;//'rtk9'
        unsigned int        dolby_register[3070];
        unsigned int        is_dolby_video;
        unsigned int        isAdaptive_playback;
        unsigned int        reserve[32768-3267];
    };

    class Client {
    public:

        class ExtBuffer {
        public:
            ExtBuffer() : refCount(0) {};
            virtual ~ExtBuffer() {};
            virtual void replica(const ExtBuffer * buffer) {
                this->refCount = buffer->refCount + 1;
            };
            virtual ExtBuffer * replica() {
                ExtBuffer * buffer = new ExtBuffer();
                buffer->replica(this);
                return buffer;
            };
        private:
            int refCount;
        };

        Client();
        virtual ~Client() {};

        virtual void setGraphicBufferInfo(GraphicBufferInfo * service = NULL) {
            if (service)
                service->registerClient(this);
            else if (mService != NULL) {
                clearBufferHandle();
                mService->removeClient(this);
                mService = NULL;
            }
        };

        virtual int validate(buffer_handle_t handle);

        virtual void setBufferHandle(buffer_handle_t handle);

        virtual void setExtBuffer(ExtBuffer * buffer);

        virtual ExtBuffer * getExtBuffer() {return mExtBuffer;};

        virtual void clearBufferHandle();

        virtual buffer_handle_t getBufferHandle() { return mHandle;};

        virtual struct private_yuv_data * getYUVData() { return &mYUVData;};
        virtual struct private_rtk_data * getPrivData() { return &mPrivData;};
        virtual void                      setPrivData();
        virtual GetMetadataInfo_t * getMetadataInfo() { return &metaInfo;};
        virtual int getGrallocVersion () { return mGralloc_version;};

        virtual bool isReplicaBuffer()  { return (mState & BufferReplica)   ? true : false;};
        virtual bool isGrallocBuffer()  { return (mState & BufferGralloc)   ? true : false;};
        virtual bool isFreedBuffer()    { return (mState & BufferFree)      ? true : false;};
        virtual bool isExtraBuffer()    { return (mState & BufferExtra)     ? true : false;};

        virtual void * getPhyAddr(unsigned int slot = 0, long long * pBufferSize = NULL);
        virtual void * getVirAddr(long long * pBufferSize = NULL);

#ifdef ENABLE_TEE_DRM_FLOW
        virtual int Tee_4ByteSwap (unsigned int dstPhyAddr, int size) {
            int ret = -1;
            pthread_mutex_lock(&mLock);
            if (mService) {
                ret = mService->Tee_4ByteSwap(dstPhyAddr, size);
            }
            pthread_mutex_unlock(&mLock);
            return ret;
        }
#endif

        virtual int setReplicaFrom(Client * from) {
            int ret = -1;
            pthread_mutex_lock(&mLock);
            if (mService && from) {
                ret = mService->replicaCopy(this, from);
            };
            pthread_mutex_unlock(&mLock);
            return ret;
        };

        virtual int setReplicaTo(Client * to) {
            int ret = -1;
            pthread_mutex_lock(&mLock);
            if (mService && to) {
                ret = mService->replicaCopy(to, this);
            };
            pthread_mutex_unlock(&mLock);
            return ret;
        };

        virtual void dump(android::String8& buf, const char* prefix = NULL);

        virtual void flushMetaBuffer() {
            if (mMetadataBuffer != NULL)
                mMetadataBuffer->flushBuffer();
        }
    private:
        friend class GraphicBufferInfo;
        unsigned long getOffset(unsigned int slot);
        void lockBuffer()     { pthread_mutex_lock  (&mReleaseLock);};
        void unlockBuffer()   { pthread_mutex_unlock(&mReleaseLock);};

        enum BufferState {
            BufferFree          = 0x1U << 0,
            BufferGralloc       = 0x1U << 1,
            BufferReplica       = 0x1U << 2,
            BufferExtra         = 0x1U << 3,
        };

        pthread_mutex_t             mLock;
        pthread_mutex_t             mReleaseLock;
        GraphicBufferInfo *         mService;
        struct private_yuv_data     mYUVData;
        struct private_rtk_data     mPrivData;
        buffer_handle_t             mHandle;
        int                         mState; /*enum BufferState*/
        void *                      mViraddr;
        long long                   mViraddrSize;
        IonBuffer *                 mIonBuffer;
        ExtBuffer *                 mExtBuffer;
        IonBuffer *                 mShareBuffer;
        GetMetadataInfo_t           metaInfo;
        int                         mGralloc_version;
        IonBuffer *                 mReplicaMetadata;
        IonBuffer *                 mMetadataBuffer;
    };

    GraphicBufferInfo();
    virtual ~GraphicBufferInfo();

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);

    virtual void setPrivData(Client * client);
    virtual void setBufferHandle(Client * client, buffer_handle_t handle);
    virtual void setExtBuffer(Client * client, Client::ExtBuffer * buffer);
    virtual int validate(Client * client, buffer_handle_t handle);
    virtual int clearBufferHandle(Client * client);

    virtual int replicaCopy(Client * des, Client * src);

#ifdef ENABLE_TEE_DRM_FLOW
    virtual int Tee_4ByteSwap(unsigned int dstPhyAddr, int size);
#endif

private:
    const struct hw_module_t * getGrallocModule();

    pthread_mutex_t                 mLock;
    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;

    const struct hw_module_t *      mGrallocModule;
    ProtectedOps *                  mProtectedOps;
};

#endif /* End of __RTK_HWC_HWLAYER_UTILS_GRAPHICB_BUFFER_INFO_H_ */
