#ifndef RTK_UTIL_H
#define RTK_UTIL_H

#include <OMX_Types.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include "OMX_CoreRTKExt.h"
#include "OMX_IndexRTKExt.h"

// Qm.n conversion macros
#define Q16_FLOAT(a) ((float)(a) / 65536.0)
#define FLOAT_Q16(a) ((OMX_U32) ((float)(a) * 65536.0))

#define UNUSED_PARAMETER(p) (void)(p)

#ifdef __cplusplus
extern "C" {
#endif

const char* RTKOmx_str_omx_state(OMX_STATETYPE s);
const char* RTKOmx_str_omx_err(OMX_ERRORTYPE e);
const char* RTKOmx_str_omx_cmd(OMX_COMMANDTYPE c);
const char* RTKOmx_str_omx_event(OMX_EVENTTYPE e);
const char* RTKOmx_str_omx_index(OMX_INDEXTYPE i);
const char* RTKOmx_str_omx_color(OMX_COLOR_FORMATTYPE f);
const char* RTKOmx_str_omx_supplier(OMX_BUFFERSUPPLIERTYPE bst);

//audio
const char* AudioOmx_str_omx_index(OMX_INDEXTYPE i);

OMX_U32 RTKOmx_make_int_ver(OMX_U8 major, OMX_U8 minor);

#ifdef __cplusplus
}
#endif
#endif // RTK_UTIL_H
