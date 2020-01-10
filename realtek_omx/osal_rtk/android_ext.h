#ifndef _OMX_ANDROID_EXT_H
#define _OMX_ANDROID_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__LINARO_SDK__)
#include <stdint.h>
#include <stddef.h>   //for size_t
#include <cutils/native_handle.h>
#include "OMX_Types.h"
#include "OMX_Component.h"
#include "OMX_Core.h"
#include "OMX_Index.h"
#include "OMX_IndexExt.h"

// system/core/include/system/window.h
typedef const native_handle_t* buffer_handle_t;

#else
#include <hardware/gralloc.h>
#include <hardware/hardware.h>
// cannot include because C++ header ?
//
//
//#include "media/hardware/HardwareAPI.h"
#include "media/hardware/HardwareAPI_RealtekExt.h"
#include <media/openmax/OMX_Types.h>
#include <media/openmax/OMX_Component.h>
#include <media/openmax/OMX_Core.h>
#include <media/openmax/OMX_Index.h>
#include <media/openmax/OMX_IndexExt.h>
#endif

#ifndef OMX_IndexRealtekStart
#define OMX_IndexRealtekStart (0x7FFF0000)
#endif

/* For omx get physical Address */
//#define OMX_IndexParamVideoInputPhysical 0x06600000

enum {
    OMX_google_android_index_enableAndroidNativeBuffers  = OMX_IndexRealtekStart,
    OMX_google_android_index_getAndroidNativeBufferUsage , /* 0x7FFF0001 */
    OMX_google_android_index_useAndroidNativeBuffer      , /* 0x7FFF0002 */
    OMX_IndexConfigRTKThumbnailMode                      , /* 0x7FFF0003 */
    OMX_IndexConfigRTKExtractorMode                      , /* 0x7FFF0004 */
    OMX_IndexConfigRTKSetBSRingMode                      , /* 0x7FFF0005 */
    OMX_google_android_index_storeMetaDataInBuffers      , /* 0x7FFF0006 */
    OMX_google_android_index_prependSPSPPSToIDRFrames    , /* 0x7FFF0007 */
    OMX_google_android_index_configureVideoTunnelMode    , /* 0x7FFF0008 */
    OMX_google_android_index_describeColorFormat         , /* 0x7FFF0009 */
    OMX_google_android_index_allocateNativeHandle        , /* 0x7FFF000A */
    OMX_google_android_index_AdaptivePlayback            , /* 0x7FFF000B */
    OMX_google_android_index_describeHDRStaticInfo       , /* 0x7FFF000C */
    OMX_google_android_index_describeColorAspects        , /* 0x7FFF000D */

    OMX_realtek_android_index_notifyBufferAllocDone      = OMX_IndexRealtekStart + 0x100,
    OMX_realtek_android_index_encodeToInterlace          , /* 0x7FFF0101 */
    OMX_realtek_android_index_lowDelayMode               , /* 0x7FFF0102 */
    OMX_realtek_android_index_setSearchIFrm              , /* 0x7FFF0103 */
    OMX_realtek_android_index_enableDeInterlace          , /* 0x7FFF0104 */
    OMX_realtek_android_index_drmReturnIonInformation    , /* 0x7FFF0105 */
    OMX_realtek_android_index_notifyVeScaling            , /* 0x7FFF0106 */
    OMX_realtek_android_index_skipNonRefFrame            , /* 0x7FFF0107 */
    OMX_realtek_android_index_getFrameRate               , /* 0x7FFF0108 */
    OMX_realtek_android_index_getIsProg                  , /* 0x7FFF0109 */
    OMX_realtek_android_index_getIsHdr                   , /* 0x7FFF010A */
    OMX_realtek_android_index_notifyMVC                  , /* 0x7FFF010B */
    OMX_realtek_android_index_videoFullRange             , /* 0x7FFF010C */
    OMX_realtek_android_index_doviType                   , /* 0x7FFF010D */
    OMX_realtek_android_index_vp9HdrPara                 , /* 0x7FFF010E */
    OMX_realtek_android_index_notifyParentInfo           , /* 0x7FFF010F */

    OMX_realtek_android_index_notifyProtectedMode        = OMX_IndexRealtekStart + 0x110,
    OMX_realtek_android_index_configureAudioTunnelMode   , /* 0x7FFF0111 */
    OMX_realtek_android_index_configureVideoTunnelMode   , /* 0x7FFF0112 */
    OMX_realtek_android_index_setVideoTunnelModeState    , /* 0x7FFF0113 */
    OMX_realtek_android_index_setVideoEncRotAngle        , /* 0x7FFF0114 */
    OMX_Glinux_SetSearchIFrmLegacy                       , /* 0x7FFF0115 */
    OMX_realtek_android_index_setErrFrameDropThreshold   , /* 0x7FFF0116 */
    OMX_realtek_android_index_setHevcPerformance         , /* 0x7FFF0117 */
    OMX_realtek_android_index_notifyConsumerInfo         , /* 0x7FFF0118 */

    OMX_realtek_android_index_setAudioTransSampleRate    = OMX_IndexRealtekStart + 0x200,
    OMX_realtek_android_index_setAudioTransChannels      , /* 0x7FFF0201 */

    OMX_realtek_android_index_setMS12AudioDummyPin       = OMX_IndexRealtekStart + 0x300,
    OMX_realtek_android_index_setMS12DecDropByPTS        , /* 0x7FFF0301 */
    OMX_realtek_android_index_setMS12PPPause             , /* 0x7FFF0302 */
    OMX_realtek_android_index_setMS12PPStart             , /* 0x7FFF0303 */
    OMX_realtek_android_index_setMS12OMXDropPTS          , /* 0x7FFF0304 */
    OMX_realtek_android_index_setMS12RuntimeUpdateParam  , /* 0x7FFF0305 */

    OMX_Glinux_SetSearchIFrm                             = OMX_IndexRealtekStart + 0x400,
    OMX_Glinux_GetComparessInfo                          , /* 0x7FFF0401 */
    OMX_Glinux_GetAudioFrameLength                       , /* 0x7FFF0402 */
    OMX_Glinux_SetNativeBuffer                           , /* 0x7FFF0403 */
    OMX_Glinux_SetSpeedRate                              , /* 0x7FFF0404 */
    OMX_Glinux_SetAVsyncMode                             , /* 0x7FFF0405 */
};

#define LOCK_MODE_TO_GET_VIRTUAL_ADDRESS 0
#define LOCK_MODE_TO_GET_PHYSICAL_ADDRESS 1
#define LOCK_MODE_TO_GET_YCbCr_VIRTUAL_ADDRESS  2

enum {
    RTK_TUNNEL_STARTDEQUEUE = 0,
    RTK_TUNNEL_STOPDEQUEUE,
    RTK_TUNNEL_GETALLQUEUE,
    RTK_TUNNEL_FLUSH_START,
    RTK_TUNNEL_FLUSH_END,
};

/* copy from  /frameworks/native/include/media/hardware/MetadataBufferType.h */
/*
 * MetadataBufferType defines the type of the metadata buffers that
 * can be passed to video encoder component for encoding, via Stagefright
 * media recording framework. To see how to work with the metadata buffers
 * in media recording framework, please consult HardwareAPI.h
 *
 * The creator of metadata buffers and video encoder share common knowledge
 * on what is actually being stored in these metadata buffers, and
 * how the information can be used by the video encoder component
 * to locate the actual pixel data as the source input for video
 * encoder, plus whatever other information that is necessary. Stagefright
 * media recording framework does not need to know anything specific about the
 * metadata buffers, except for receving each individual metadata buffer
 * as the source input, making a copy of the metadata buffer, and passing the
 * copy via OpenMAX API to the video encoder component.
 *
 * The creator of the metadata buffers must ensure that the first
 * 4 bytes in every metadata buffer indicates its buffer type,
 * and the rest of the metadata buffer contains the
 * actual metadata information. When a video encoder component receives
 * a metadata buffer, it uses the first 4 bytes in that buffer to find
 * out the type of the metadata buffer, and takes action appropriate
 * to that type of metadata buffers (for instance, locate the actual
 * pixel data input and then encoding the input data to produce a
 * compressed output buffer).
 *
 * The following shows the layout of a metadata buffer,
 * where buffer type is a 4-byte field of MetadataBufferType,
 * and the payload is the metadata information.
 *
 * --------------------------------------------------------------
 * |  buffer type  |          payload                           |
 * --------------------------------------------------------------
 *
 */
#if defined(__LINARO_SDK__)
typedef enum {
    kMetadataBufferTypeCameraSource  = 0,
    kMetadataBufferTypeGrallocSource = 1,
    kMetadataBufferTypeANWBuffer = 2,
    kMetadataBufferTypePhysicalAddr = 3,
    kMetadataBufferTypeNativeHandleSource = 9,
    kMetadataBufferTypeInvalid = -1,
} MetadataBufferType;
#else
typedef enum {

    /*
     * kMetadataBufferTypeCameraSource is used to indicate that
     * the source of the metadata buffer is the camera component.
     */
    kMetadataBufferTypeCameraSource  = 0,

    /*
     * kMetadataBufferTypeGrallocSource is used to indicate that
     * the payload of the metadata buffers can be interpreted as
     * a buffer_handle_t.
     * So in this case,the metadata that the encoder receives
     * will have a byte stream that consists of two parts:
     * 1. First, there is an integer indicating that it is a GRAlloc
     * source (kMetadataBufferTypeGrallocSource)
     * 2. This is followed by the buffer_handle_t that is a handle to the
     * GRalloc buffer. The encoder needs to interpret this GRalloc handle
     * and encode the frames.
     * --------------------------------------------------------------
     * |  kMetadataBufferTypeGrallocSource | buffer_handle_t buffer |
     * --------------------------------------------------------------
     *
     * See the VideoGrallocMetadata structure.
     */
    kMetadataBufferTypeGrallocSource = 1,

    /*
     * kMetadataBufferTypeGraphicBuffer is used to indicate that
     * the payload of the metadata buffers can be interpreted as
     * an ANativeWindowBuffer, and that a fence is provided.
     *
     * In this case, the metadata will have a byte stream that consists of three parts:
     * 1. First, there is an integer indicating that the metadata
     * contains an ANativeWindowBuffer (kMetadataBufferTypeANWBuffer)
     * 2. This is followed by the pointer to the ANativeWindowBuffer.
     * Codec must not free this buffer as it does not actually own this buffer.
     * 3. Finally, there is an integer containing a fence file descriptor.
     * The codec must wait on the fence before encoding or decoding into this
     * buffer. When the buffer is returned, codec must replace this file descriptor
     * with a new fence, that will be waited on before the buffer is replaced
     * (encoder) or read (decoder).
     * ---------------------------------
     * |  kMetadataBufferTypeANWBuffer |
     * ---------------------------------
     * |  ANativeWindowBuffer *buffer  |
     * ---------------------------------
     * |  int fenceFd                  |
     * ---------------------------------
     *
     * See the VideoNativeMetadata structure.
     */
    kMetadataBufferTypeANWBuffer = 2,

    /*
     * kMetadataBufferTypeNativeHandleSource is used to indicate that
     * the payload of the metadata buffers can be interpreted as
     * a native_handle_t.
     *
     * In this case, the metadata that the encoder receives
     * will have a byte stream that consists of two parts:
     * 1. First, there is an integer indicating that the metadata contains a
     * native handle (kMetadataBufferTypeNativeHandleSource).
     * 2. This is followed by a pointer to native_handle_t. The encoder needs
     * to interpret this native handle and encode the frame. The encoder must
     * not free this native handle as it does not actually own this native
     * handle. The handle will be freed after the encoder releases the buffer
     * back to camera.
     * ----------------------------------------------------------------
     * |  kMetadataBufferTypeNativeHandleSource | native_handle_t* nh |
     * ----------------------------------------------------------------
     *
     * See the VideoNativeHandleMetadata structure.
     */
    kMetadataBufferTypeNativeHandleSource = 3,

    /* This value is used by framework, but is never used inside a metadata buffer  */
    kMetadataBufferTypeInvalid = -1,


    // Add more here...

    /*
     * kMetadataBufferTypePhysicalAddr is used to indicate that
     * the payload of the metadata buffers can be interpreted as
     * a physical address.
     * So in this case,the metadata that the encoder receives
     * will have a byte stream that consists of four parts:
     * 1. First, there is an integer indicating that it is a metadata
     * with physical address (kMetadataBufferTypePhysicalAddr)
     * 2. Second, there is a physical address of a video frame.
     * 3. Third, there is a h aspect ratio
     * 4. Forth, there is a l aspect ratio
     * -------------------------------------------------------------------------
     * |  kMetadataBufferTypeGrallocSource |        physical address           |
     * -------------------------------------------------------------------------
     * |           aspect_h                |             aspect_l              |
     * -------------------------------------------------------------------------
     */
    kMetadataBufferTypePhysicalAddr = 9,

} MetadataBufferType;
#endif

struct GetAudioFrameLength {
    OMX_U32 nFrameLength;
};

struct GetVPUCompressInfo {
    OMX_U32 lumasize;
    OMX_U32 chromasize;
    OMX_U32 pixel_format; // android_pixel_format_t
};

struct NativeBufferParams {
    OMX_U32 nPortIndex;
    OMX_BOOL enable;
};

struct NativeBufferInfo {
    OMX_U32 virt_addr;
    OMX_U32 phys_addr;
};

struct EnableAndroidNativeBuffersParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL enable;
};

// A pointer to this struct is passed to OMX_SetParameter() when the extension
// index "OMX.google.android.index.storeMetaDataInBuffers"
// is given.
//
// When meta data is stored in the video buffers passed between OMX clients
// and OMX components, interpretation of the buffer data is up to the
// buffer receiver, and the data may or may not be the actual video data, but
// some information helpful for the receiver to locate the actual data.
// The buffer receiver thus needs to know how to interpret what is stored
// in these buffers, with mechanisms pre-determined externally. How to
// interpret the meta data is outside of the scope of this method.
//
// Currently, this is specifically used to pass meta data from video source
// (camera component, for instance) to video encoder to avoid memcpying of
// input video frame data. To do this, bStoreMetaDta is set to OMX_TRUE.
// If bStoreMetaData is set to false, real YUV frame data will be stored
// in the buffers. In addition, if no OMX_SetParameter() call is made
// with the corresponding extension index, real YUV data is stored
// in the buffers.
struct StoreMetaDataInBuffersParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bStoreMetaData;
};

// A pointer to this struct is passed to OMX_SetParameter() when the extension
// index "OMX.google.android.index.prepareForAdaptivePlayback" is given.
//
// This method is used to signal a video decoder, that the user has requested
// seamless resolution change support (if bEnable is set to OMX_TRUE).
// nMaxFrameWidth and nMaxFrameHeight are the dimensions of the largest
// anticipated frames in the video.  If bEnable is OMX_FALSE, no resolution
// change is expected, and the nMaxFrameWidth/Height fields are unused.
//
// If the decoder supports dynamic output buffers, it may ignore this
// request.  Otherwise, it shall request resources in such a way so that it
// avoids full port-reconfiguration (due to output port-definition change)
// during resolution changes.
//
// DO NOT USE THIS STRUCTURE AS IT WILL BE REMOVED.  INSTEAD, IMPLEMENT
// METADATA SUPPORT FOR VIDEO DECODERS.
struct PrepareForAdaptivePlaybackParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_BOOL bEnable;
    OMX_U32 nMaxFrameWidth;
    OMX_U32 nMaxFrameHeight;
};

// A pointer to this struct is passed to OMX_SetParameter when the extension
// index for the 'OMX.google.android.index.useAndroidNativeBuffer' extension is
// given.  This call will only be performed if a prior call was made with the
// 'OMX.google.android.index.enableAndroidNativeBuffers' extension index,
// enabling use of Android native buffers.
struct UseAndroidNativeBufferParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_U32 nPortIndex;
    OMX_PTR pAppPrivate;
    OMX_BUFFERHEADERTYPE **bufferHeader;
//    const sp<ANativeWindowBuffer>& nativeBuffer;
};

// A pointer to this struct is passed to OMX_GetParameter when the extension
// index for the 'OMX.google.android.index.getAndroidNativeBufferUsage'
// extension is given.  The usage bits returned from this query will be used to
// allocate the Gralloc buffers that get passed to the useAndroidNativeBuffer
// command.
struct GetAndroidNativeBufferUsageParams {
    OMX_U32 nSize;              // IN
    OMX_VERSIONTYPE nVersion;   // IN
    OMX_U32 nPortIndex;         // IN
    OMX_U32 nUsage;             // OUT
};

// Meta data buffer layout used to transport output frames to the decoder for
// dynamic buffer handling.
struct VideoCodecMetaData {
  MetadataBufferType eType;
  buffer_handle_t pHandle;
  OMX_U32 nAspectH;
  OMX_U32 nAspectL;
  OMX_U32 pVuiFrameRate;
};

// A pointer to this struct is passed to OMX_SetParameter when the extension
// index for the 'OMX.google.android.index.prependSPSPPSToIDRFrames' extension
// is given.
// A successful result indicates that future IDR frames will be prefixed by
// SPS/PPS.
struct PrependSPSPPSToIDRFramesParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_BOOL bEnable;
};

// Structure describing a media image (frame)
// Currently only supporting YUV
    typedef enum MediaImageType {
        MEDIA_IMAGE_TYPE_UNKNOWN = 0,
        MEDIA_IMAGE_TYPE_YUV,
    }MediaImageType;

    typedef enum MediaImagePlaneIndex {
        Y = 0,
        U,
        V,
        MAX_NUM_PLANES
    }MediaImagePlaneIndex;

    typedef struct MediaImagePlaneInfo {
        size_t mOffset;             // offset of first pixel of the plane in bytes
                                    // from buffer offset
        size_t mColInc;             // column increment in bytes
        size_t mRowInc;             // row increment in bytes
        size_t mHorizSubsampling;   // subsampling compared to the largest plane
        size_t mVertSubsampling;    // subsampling compared to the largest plane
    }MediaImagePlaneInfo;

typedef struct MediaImage {
    MediaImageType mType;
    size_t mNumPlanes;              // number of planes
    size_t mWidth;                  // width of largest plane (unpadded, as in nFrameWidth)
    size_t mHeight;                 // height of largest plane (unpadded, as in nFrameHeight)
    size_t mBitDepth;               // useable bit depth
    MediaImagePlaneInfo mPlane[MAX_NUM_PLANES];
}MediaImage;

// A pointer to this struct is passed to OMX_GetParameter when the extension
// index for the 'OMX.google.android.index.describeColorFormat'
// extension is given.  This method can be called from any component state
// other than invalid.  The color-format, frame width/height, and stride/
// slice-height parameters are ones that are associated with a raw video
// port (input or output), but the stride/slice height parameters may be
// incorrect. bUsingNativeBuffers is OMX_TRUE if native android buffers will
// be used (while specifying this color format).
//
// The component shall fill out the MediaImage structure that
// corresponds to the described raw video format, and the potentially corrected
// stride and slice-height info.
//
// The behavior is slightly different if bUsingNativeBuffers is OMX_TRUE,
// though most implementations can ignore this difference. When using native buffers,
// the component may change the configured color format to an optimized format.
// Additionally, when allocating these buffers for flexible usecase, the framework
// will set the SW_READ/WRITE_OFTEN usage flags. In this case (if bUsingNativeBuffers
// is OMX_TRUE), the component shall fill out the MediaImage information for the
// scenario when these SW-readable/writable buffers are locked using gralloc_lock.
// Note, that these buffers may also be locked using gralloc_lock_ycbcr, which must
// be supported for vendor-specific formats.
//
// For non-YUV packed planar/semiplanar image formats, or if bUsingNativeBuffers
// is OMX_TRUE and the component does not support this color format with native
// buffers, the component shall set mNumPlanes to 0, and mType to MEDIA_IMAGE_TYPE_UNKNOWN.
typedef struct DescribeColorFormatParams {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    // input: parameters from OMX_VIDEO_PORTDEFINITIONTYPE
    OMX_COLOR_FORMATTYPE eColorFormat;
    OMX_U32 nFrameWidth;
    OMX_U32 nFrameHeight;
    OMX_U32 nStride;
    OMX_U32 nSliceHeight;
    OMX_BOOL bUsingNativeBuffers;

    // output: fill out the MediaImage fields
    MediaImage sMediaImage;
}DescribeColorFormatParams;

// A pointer to this struct is passed to OMX_SetParameter or OMX_GetParameter
// when the extension index for the
// 'OMX.google.android.index.configureVideoTunnelMode' extension is  given.
// If the extension is supported then tunneled playback mode should be supported
// by the codec. If bTunneled is set to OMX_TRUE then the video decoder should
// operate in "tunneled" mode and output its decoded frames directly to the
// sink. In this case nAudioHwSync is the HW SYNC ID of the audio HAL Output
// stream to sync the video with. If bTunneled is set to OMX_FALSE, "tunneled"
// mode should be disabled and nAudioHwSync should be ignored.
// OMX_GetParameter is used to query tunneling configuration. bTunneled should
// return whether decoder is operating in tunneled mode, and if it is,
// pSidebandWindow should contain the codec allocated sideband window handle.
struct ConfigureVideoTunnelModeParams {
    OMX_U32 nSize;              // IN
    OMX_VERSIONTYPE nVersion;   // IN
    OMX_U32 nPortIndex;         // IN
    OMX_BOOL bTunneled;         // IN/OUT
    OMX_U32 nAudioHwSync;       // IN
    OMX_PTR pSidebandWindow;    // OUT
};

OMX_U32 lockAndroidNativeBuf(buffer_handle_t handle, OMX_U32 Width, OMX_U32 Height, OMX_U32 mode, void *pAddrs[]);
OMX_U32 unlockAndroidNativeBuf(buffer_handle_t handle);

// HDR color description parameters.
// This is passed via OMX_SetConfig or OMX_GetConfig to video encoders and decoders when the
// 'OMX.google.android.index.describeHDRColorInfo' extension is given and an HDR stream
// is detected.  Component SHALL behave as described below if it supports this extension.
//
// Currently, only Static Metadata Descriptor Type 1 support is required.
//
// VIDEO ENCODERS: the framework uses OMX_SetConfig to specify the HDR static information of the
// coded video.
// This may happen:
//   a) before the component transitions to idle state
//   b) before the input frame is sent via OMX_EmptyThisBuffer in executing state
//   c) during execution, just before an input frame with a different HDR static
//      information is sent.
//
// The framework also uses OMX_GetConfig to
//   d) verify the HDR static information that will be written to the stream.
//
// 1. Encoders SHOULD maintain an internal HDR static info data, initialized to Unspecified values.
//    This represents the values that will be written into the bitstream.
// 2. Upon OMX_SetConfig, they SHOULD update their internal state to the info received
//    (including Unspecified values). For specific parameters that are not supported by the
//    codec standard, encoders SHOULD substitute Unspecified values. NOTE: no other substitution
//    is allowed.
// 3. OMX_GetConfig SHALL return the internal state (values that will be written).
// 4. OMX_SetConfig SHALL always succeed before receiving the first frame if the encoder is
//    configured into an HDR compatible profile. It MAY fail with OMX_ErrorUnsupportedSettings error
//    code if it is not configured into such a profile, OR if the configured values would change
//    AND the component does not support updating the HDR static information mid-stream. If the
//    component supports updating a portion of the information, those values should be updated in
//    the internal state, and OMX_SetConfig SHALL succeed. Otherwise, the internal state SHALL
//    remain intact.
//
// VIDEO DECODERS: the framework uses OMX_SetConfig to specify the default HDR static information
// to use for the video.
//   a) This only happens if the client supplies this information, in which case it occurs before
//      the component transitions to idle state.
//   b) This may also happen subsequently if the default HDR static information changes.
//
// The framework also uses OMX_GetConfig to
//   c) get the final HDR static information reported by the coded bitstream after taking the
//      default values into account.
//
// 1. Decoders should maintain two HDR static information structures - the default values as
//    reported by the framework, and the coded values as reported by the bitstream - as each
//    structure can change independently from the other.
// 2. Upon OMX_SetConfig, it SHALL update its default structure regardless of whether such static
//    parameters could be supplied by the component bitstream. (E.g. it should blindly support all
//    parameter values, even seemingly illegal ones). This SHALL always succeed.
//  Note: The descriptor ID used in sInfo may change in subsequent calls. (although for now only
//    Type 1 support is required.)
// 3. Upon OMX_GetConfig, the component SHALL return the final HDR static information by replacing
//    Unspecified coded values with the default values. This SHALL always succeed. This may be
//    provided using any supported descriptor ID (currently only Type 1) with the goal of expressing
//    the most of the available static information.
// 4. Whenever the component processes HDR static information in the bitstream even ones with
//    Unspecified parameters, it SHOULD update its internal coded structure with that information
//    just before the frame with the new information would be outputted, and the component SHALL
//    signal an OMX_EventPortSettingsChanged event with data2 set to the extension index.
// NOTE: Component SHOULD NOT signal a separate event purely for HDR static info change, if it
//    occurs together with a port definition (e.g. size), color aspect or crop change.
// 5. If certain parameters of the HDR static information encountered in the bitstream cannot be
//    represented using sInfo, the component SHALL use the closest representation.
//
// Note: the size of sInfo may increase in the future by supporting additional descriptor types.
// Implementations SHOULD NOT require a certain size.

// HDR Static Metadata Descriptor as defined by CTA-861-3.
typedef enum ID {
    kType1 = 0, // Static Metadata Type 1
}ID;

typedef struct __attribute__ ((__packed__)) Primaries1 {
    // values are in units of 0.00002
    uint16_t x;
    uint16_t y;
}Primaries1;

typedef struct __attribute__ ((__packed__)) Type1 {
    Primaries1 mR; // display primary 0
    Primaries1 mG; // display primary 1
    Primaries1 mB; // display primary 2
    Primaries1 mW; // white point
    uint16_t mMaxDisplayLuminance; // in cd/m^2
    uint16_t mMinDisplayLuminance; // in 0.0001 cd/m^2
    uint16_t mMaxContentLightLevel; // in cd/m^2
    uint16_t mMaxFrameAverageLightLevel; // in cd/m^2
}Type1;

typedef struct __attribute__ ((__packed__)) HDRStaticInfo {
    OMX_U8 mID;
    Type1 sType1;
}HDRStaticInfo;

struct DescribeHDRStaticInfoParams {
    OMX_U32 nSize;                 // IN
    OMX_VERSIONTYPE nVersion;      // IN
    OMX_U32 nPortIndex;            // IN
    HDRStaticInfo sInfo;           // IN/OUT
};

// Color space description (aspects) parameters.
// This is passed via OMX_SetConfig or OMX_GetConfig to video encoders and decoders when the
// 'OMX.google.android.index.describeColorAspects' extension is given. Component SHALL behave
// as described below if it supports this extension.
//
// bDataSpaceChanged and bRequestingDataSpace is assumed to be OMX_FALSE unless noted otherwise.
//
// VIDEO ENCODERS: the framework uses OMX_SetConfig to specify color aspects of the coded video.
// This may happen:
//   a) before the component transitions to idle state
//   b) before the input frame is sent via OMX_EmptyThisBuffer in executing state
//   c) during execution, just before an input frame with a different color aspect information
//      is sent.
//
// The framework also uses OMX_GetConfig to
//   d) verify the color aspects that will be written to the stream
//   e) (optional) verify the color aspects that should be reported to the container for a
//      given dataspace/pixelformat received
//
// 1. Encoders SHOULD maintain an internal color aspect state, initialized to Unspecified values.
//    This represents the values that will be written into the bitstream.
// 2. Upon OMX_SetConfig, they SHOULD update their internal state to the aspects received
//    (including Unspecified values). For specific aspect values that are not supported by the
//    codec standard, encoders SHOULD substitute Unspecified values; or they MAY use a suitable
//    alternative (e.g. to suggest the use of BT.709 EOTF instead of SMPTE 240M.)
// 3. OMX_GetConfig SHALL return the internal state (values that will be written).
// 4. OMX_SetConfig SHALL always succeed before receiving the first frame. It MAY fail afterwards,
//    but only if the configured values would change AND the component does not support updating the
//    color information to those values mid-stream. If component supports updating a portion of
//    the color information, those values should be updated in the internal state, and OMX_SetConfig
//    SHALL succeed. Otherwise, the internal state SHALL remain intact and OMX_SetConfig SHALL fail
//    with OMX_ErrorUnsupportedSettings.
// 5. When the framework receives an input frame with an unexpected dataspace, it will query
//    encoders for the color aspects that should be reported to the container using OMX_GetConfig
//    with bDataSpaceChanged set to OMX_TRUE, and nPixelFormat/nDataSpace containing the new
//    format/dataspace values. This allows vendors to use extended dataspace during capture and
//    composition (e.g. screenrecord) - while performing color-space conversion inside the encoder -
//    and encode and report a different color-space information in the bitstream/container.
//    sColorAspects contains the requested color aspects by the client for reference, which may
//    include aspects not supported by the encoding. This is used together with guidance for
//    dataspace selection; see 6. below.
//
// VIDEO DECODERS: the framework uses OMX_SetConfig to specify the default color aspects to use
// for the video.
// This may happen:
//   a) before the component transitions to idle state
//   b) during execution, when the resolution or the default color aspects change.
//
// The framework also uses OMX_GetConfig to
//   c) get the final color aspects reported by the coded bitstream after taking the default values
//      into account.
//
// 1. Decoders should maintain two color aspect states - the default state as reported by the
//    framework, and the coded state as reported by the bitstream - as each state can change
//    independently from the other.
// 2. Upon OMX_SetConfig, it SHALL update its default state regardless of whether such aspects
//    could be supplied by the component bitstream. (E.g. it should blindly support all enumeration
//    values, even unknown ones, and the Other value). This SHALL always succeed.
// 3. Upon OMX_GetConfig, the component SHALL return the final color aspects by replacing
//    Unspecified coded values with the default values. This SHALL always succeed.
// 4. Whenever the component processes color aspect information in the bitstream even with an
//    Unspecified value, it SHOULD update its internal coded state with that information just before
//    the frame with the new information would be outputted, and the component SHALL signal an
//    OMX_EventPortSettingsChanged event with data2 set to the extension index.
// NOTE: Component SHOULD NOT signal a separate event purely for color aspect change, if it occurs
//    together with a port definition (e.g. size) or crop change.
// 5. If the aspects a component encounters in the bitstream cannot be represented with enumeration
//    values as defined below, the component SHALL set those aspects to Other. Restricted values in
//    the bitstream SHALL be treated as defined by the relevant bitstream specifications/standards,
//    or as Unspecified, if not defined.
//
// BOTH DECODERS AND ENCODERS: the framework uses OMX_GetConfig during idle and executing state to
//   f) (optional) get guidance for the dataspace to set for given color aspects, by setting
//      bRequestingDataSpace to OMX_TRUE. The component SHALL return OMX_ErrorUnsupportedSettings
//      IF it does not support this request.
//
// 6. This is an information request that can happen at any time, independent of the normal
//    configuration process. This allows vendors to use extended dataspace during capture, playback
//    and composition - while performing color-space conversion inside the component. Component
//    SHALL set the desired dataspace into nDataSpace. Otherwise, it SHALL return
//    OMX_ErrorUnsupportedSettings to let the framework choose a nearby standard dataspace.
//
// 6.a. For encoders, this query happens before the first frame is received using surface encoding.
//    This allows the encoder to use a specific dataspace for the color aspects (e.g. because the
//    device supports additional dataspaces, or because it wants to perform color-space extension
//    to facilitate a more optimal rendering/capture pipeline.).
//
// 6.b. For decoders, this query happens before the first frame, and every time the color aspects
//    change, while using surface buffers. This allows the decoder to use a specific dataspace for
//    the color aspects (e.g. because the device supports additional dataspaces, or because it wants
//    to perform color-space extension by inline color-space conversion to facilitate a more optimal
//    rendering pipeline.).
//
// Note: the size of sAspects may increase in the future by additional fields.
// Implementations SHOULD NOT require a certain size.

typedef enum Range {
    RangeUnspecified,
    RangeFull,
    RangeLimited,
    RangeOther = 0xff,
}Range;

typedef enum Primaries {
    PrimariesUnspecified,
    PrimariesBT709_5,       // Rec.ITU-R BT.709-5 or equivalent
    PrimariesBT470_6M,      // Rec.ITU-R BT.470-6 System M or equivalent
    PrimariesBT601_6_625,   // Rec.ITU-R BT.601-6 625 or equivalent
    PrimariesBT601_6_525,   // Rec.ITU-R BT.601-6 525 or equivalent
    PrimariesGenericFilm,   // Generic Film
    PrimariesBT2020,        // Rec.ITU-R BT.2020 or equivalent
    PrimariesOther = 0xff,
}Primaries;

typedef enum Transfer {
    TransferUnspecified,
    TransferLinear,         // Linear transfer characteristics
    TransferSRGB,           // sRGB or equivalent
    TransferSMPTE170M,      // SMPTE 170M or equivalent (e.g. BT.601/709/2020)
    TransferGamma22,        // Assumed display gamma 2.2
    TransferGamma28,        // Assumed display gamma 2.8
    TransferST2084,         // SMPTE ST 2084 for 10/12/14/16 bit systems
    TransferHLG,            // ARIB STD-B67 hybrid-log-gamma

    // transfers unlikely to be required by Android
    TransferSMPTE240M = 0x40, // SMPTE 240M
    TransferXvYCC,          // IEC 61966-2-4
    TransferBT1361,         // Rec.ITU-R BT.1361 extended gamut
    TransferST428,          // SMPTE ST 428-1
    TransferOther = 0xff,
}Transfer;

typedef enum MatrixCoeffs {
    MatrixUnspecified,
    MatrixBT709_5,          // Rec.ITU-R BT.709-5 or equivalent
    MatrixBT470_6M,         // KR=0.30, KB=0.11 or equivalent
    MatrixBT601_6,          // Rec.ITU-R BT.601-6 625 or equivalent
    MatrixSMPTE240M,        // SMPTE 240M or equivalent
    MatrixBT2020,           // Rec.ITU-R BT.2020 non-constant luminance
    MatrixBT2020Constant,   // Rec.ITU-R BT.2020 constant luminance
    MatrixOther = 0xff,
}MatrixCoeffs;

typedef enum Standard {
    StandardUnspecified,
    StandardBT709,                  // PrimariesBT709_5 and MatrixBT709_5
    StandardBT601_625,              // PrimariesBT601_6_625 and MatrixBT601_6
    StandardBT601_625_Unadjusted,   // PrimariesBT601_6_625 and KR=0.222, KB=0.071
    StandardBT601_525,              // PrimariesBT601_6_525 and MatrixBT601_6
    StandardBT601_525_Unadjusted,   // PrimariesBT601_6_525 and MatrixSMPTE240M
    StandardBT2020,                 // PrimariesBT2020 and MatrixBT2020
    StandardBT2020Constant,         // PrimariesBT2020 and MatrixBT2020Constant
    StandardBT470M,                 // PrimariesBT470_6M and MatrixBT470_6M
    StandardFilm,                   // PrimariesGenericFilm and KR=0.253, KB=0.068
    StandardOther = 0xff,
}Standard;

typedef struct __attribute__ ((__packed__)) ColorAspects {
    Range mRange;                // IN/OUT
    Primaries mPrimaries;        // IN/OUT
    Transfer mTransfer;          // IN/OUT
    MatrixCoeffs mMatrixCoeffs;  // IN/OUT
}ColorAspects;

struct DescribeColorAspectsParams {
    OMX_U32 nSize;                 // IN
    OMX_VERSIONTYPE nVersion;      // IN
    OMX_U32 nPortIndex;            // IN
    OMX_BOOL bRequestingDataSpace; // IN
    OMX_BOOL bDataSpaceChanged;    // IN
    OMX_U32 nPixelFormat;          // IN
    OMX_U32 nDataSpace;            // OUT
    ColorAspects sAspects;         // IN/OUT
};

#ifdef __cplusplus
}
#endif

#endif //_OMX_ANDROID_EXT_H
