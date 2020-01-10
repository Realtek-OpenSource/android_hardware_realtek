#ifndef FW_MISC_H
#define FW_MISC_H

#include <basecomp.h>
#include "AudioRPC_System.h"
#include "hresult.h"
#include "AudioInbandAPI.h"
#include "audio_common.h"

#define OMXFW_TRACE_EN 1

#if OMXFW_TRACE_EN
#define OMXFW_TRACE(fmt, args...)   ALOGD("[OMX_FW]%s:"fmt, __FUNCTION__, ##args);
#else
#define OMXFW_TRACE(fmt, args...)
#endif

#define OMXFW_PRINT(fmt, args...)   ALOGD("[OMX_FW]%s:"fmt, __FUNCTION__, ##args);
#define OMXFW_WARNING(fmt, args...) { ALOGE("[OMX_FW WARN]"); ALOGD("[%s %d]:"fmt, __FUNCTION__, __LINE__, ##args); }
#define OMXFW_ERR() ALOGE("[OMX_FW: ERR @ %s %d]\n", __FUNCTION__, __LINE__);
#define OMX_DBG() ALOGD("[¡¹¡¹ @ %s %d]\n", __FUNCTION__, __LINE__);

////////////////////
// Data Structure //
////////////////////

////////////////////////
// Function Prototype //
////////////////////////
RPCRES_LONG *OMX_FW_RPC_Create(AUDIO_RPC_INSTANCE *instance);
HRESULT* OMX_FW_RPC_Run(long *pAgentID);
HRESULT* OMX_FW_RPC_Pause(long *pAgentID);
HRESULT* OMX_FW_RPC_Stop(long *pAgentID);
HRESULT* OMX_FW_RPC_Destroy(long *pAgentID);
HRESULT* OMX_FW_RPC_InitRingBuf(AUDIO_RPC_RINGBUFFER_HEADER *header, OSAL_S32 *ionhdl_header_fd, OSAL_S32 *ionhdl_fd);
HRESULT* OMX_FW_RPC_Flush(AUDIO_RPC_SENDIO *arg);
void OMX_FW_RPC_Destroy_Socket();
HRESULT* OMX_FW_RPC_Connect(AUDIO_RPC_CONNECTION* pConnection);
AUDIO_RPC_PRIVATEINFO_RETURNVAL* OMX_FW_RPC_PrivateInfo(AUDIO_RPC_PRIVATEINFO_PARAMETERS* pParameter);

#endif

