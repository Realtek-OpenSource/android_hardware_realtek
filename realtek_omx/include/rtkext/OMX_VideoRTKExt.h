#ifndef OMX_VideoRTKExt_h
#define OMX_VideoRTKExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 *  * header to compile without errors.  The includes below are required
 *  * for this header file to compile successfully
 *  */
#include <OMX_Core.h>

typedef enum OMX_VIDEO_CODINGTYPE_RTKEXT {
    //OMX_VIDEO_CodingVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
    OMX_VIDEO_CodingVendorRTKStartUnused = OMX_VIDEO_CodingVendorStartUnused,
    /** TODO: RTK custom unofficial values */
    OMX_VIDEO_CodingSORENSON= 0x7FFFFFFE,
    OMX_VIDEO_CodingDIVX= 0x7FFFFFFD,   /* DIVX 4/5*/
    OMX_VIDEO_CodingDIVX3= 0x7FFFFFFC, /* DIVX3 */
    OMX_VIDEO_CodingAVS = 0x7FFFFFFB,  /* AVS */
} OMX_VIDEO_CODINGTYPE_RTKEXT;

typedef enum OMX_VIDEO_WMVFORMATTYPE_RTKEXT {
    //OMX_VIDEO_WMFFormatVendorStartUnused = 0x7F000000,
    OMX_VIDEO_WMFFormatVendorRTKStartUnused = OMX_VIDEO_WMFFormatVendorStartUnused,
    OMX_VIDEO_RTK_TS_VC1, /**< Rtk Extractor TS VC1 format */
} OMX_VIDEO_WMVFORMATEXTTYPE_RTKEXT;

typedef enum OMX_VIDEO_WMVPROFILETYPE {
    OMX_VIDEO_WMVProfileSimple = 0,
    OMX_VIDEO_WMVProfileMain,
    OMX_VIDEO_WMVProfileAdvanced,
    OMX_VIDEO_WMVProfileUnknown           = 0x6EFFFFFF,
    OMX_VIDEO_WMVProfileKhronosExtensions = 0x6F000000, /**< Reserved region for introducing Khronos Standard Extensions */
    OMX_VIDEO_WMVProfileVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
} OMX_VIDEO_WMVPROFILETYPE;

typedef enum OMX_VIDEO_WMVLEVELTYPE {
    OMX_VIDEO_WMVLevelLow = 0,
    OMX_VIDEO_WMVLevelMedium,
    OMX_VIDEO_WMVLevelHigh,
    OMX_VIDEO_WMVLevelL0,
    OMX_VIDEO_WMVLevelL1,
    OMX_VIDEO_WMVLevelL2,
    OMX_VIDEO_WMVLevelL3,
    OMX_VIDEO_WMVLevelL4,
    OMX_VIDEO_WMVLevelUnknown           = 0x6EFFFFFF,
    OMX_VIDEO_WMVLevelKhronosExtensions = 0x6F000000, /**< Reserved region for introducing Khronos Standard Extensions */
    OMX_VIDEO_WMVLevelVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
} OMX_VIDEO_WMVLEVELTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_VideoRTKExt_h */
/* File EOF */
