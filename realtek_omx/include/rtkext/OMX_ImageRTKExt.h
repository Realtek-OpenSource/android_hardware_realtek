#ifndef OMX_ImageRTKExt_h
#define OMX_ImageRTKExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Core.h>

/** Enum for standard image codingtype extensions */
typedef enum OMX_IMAGE_CODINGTYPE_RTKEXT {
    OMX_IMAGE_CodingVendorRTKStartUnused = OMX_IMAGE_CodingVendorStartUnused,
    OMX_IMAGE_CodingWEBP,         /**< WebP image format */
} OMX_IMAGE_CODINGTYPE_RTKEXT;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_ImageRTKExt_h */
/* File EOF */
