#ifndef OMX_ComponentRTKExt_h
#define OMX_ComponentRTKExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header must include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully 
 */
#include <OMX_Types.h>

/** Set/query the commit mode */
typedef struct OMX_CONFIG_COMMITMODETYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
    OMX_BOOL bDeferred;
} OMX_CONFIG_COMMITMODETYPE;

/** Explicit commit */
typedef struct OMX_CONFIG_COMMITTYPE {
    OMX_U32 nSize;
    OMX_VERSIONTYPE nVersion;
} OMX_CONFIG_COMMITTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_ComponentRTKExt_h */
