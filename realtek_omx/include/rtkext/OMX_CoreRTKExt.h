#ifndef OMX_CoreRTKExt_h
#define OMX_CoreRTKExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Core.h>

/** Extensions to the OMX_COMMANDTYPE */
typedef enum OMX_COMMANDEXTTYPE
{
    //OMX_CommandVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
    OMX_CommandVendorRTKStartUnused = OMX_CommandVendorStartUnused,
    OMX_CommandAudioFwStateSet,
} OMX_COMMANDEXTTYPE;

/** Extensions to the OMX_STATEEXTTYPE */
typedef enum OMX_STATEEXTTYPE
{
    //OMX_StateVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
    OMX_StateVendorRTKStartUnused = OMX_StateVendorStartUnused, /**< Reserved region for introducing Vendor Extensions */
    OMX_RTKAudioPause = 0x7F000001,
    OMX_RTKAudioResume = 0x7F000002,
} OMX_STATEEXTTYPE;

/** Extensions to the standard IL errors. */ 
typedef enum OMX_ERROREXTTYPE 
{
    OMX_ErrorInvalidMode = (OMX_S32) (OMX_ErrorKhronosExtensions + 0x00000001),
    OMX_ErrorExtMax = 0x7FFFFFFF
} OMX_ERROREXTTYPE;


/** Event type extensions. */
typedef enum OMX_EVENTEXTTYPE
{
    OMX_EventIndexSettingChanged = OMX_EventKhronosExtensions, /**< component signals the IL client of a change
                                                                    in a param, config, or extension */
    OMX_EventExtMax = 0x7FFFFFFF
} OMX_EVENTEXTTYPE;


/** Enable or disable a callback event. */
typedef struct OMX_CONFIG_CALLBACKREQUESTTYPE {
    OMX_U32 nSize;              /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;   /**< OMX specification version information */
    OMX_U32 nPortIndex;         /**< port that this structure applies to */
    OMX_INDEXTYPE nIndex;       /**< the index the callback is requested for */
    OMX_BOOL bEnable;           /**< enable (OMX_TRUE) or disable (OMX_FALSE) the callback */
} OMX_CONFIG_CALLBACKREQUESTTYPE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_CoreRTKExt_h */
/* File EOF */
