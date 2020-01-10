#ifndef FW_MISC_MS12_H
#define FW_MISC_MS12_H

//#include <basecomp.h>
//#include "AudioRPC_System.h"
#include "hresult.h"
//#include "AudioInbandAPI.h"
//#include "audio_common.h"


////////////////////
// Data Structure //
////////////////////

////////////////////////
// Function Prototype //
////////////////////////
HRESULT* OMX_FW_RPC_MS12_Init_Cfg(AUDIO_RPC_MS_INIT_CFG *arg);
HRESULT* OMX_FW_RPC_MS12_Runtime_Cfg(AUDIO_RPC_MS_RUNTIME_CFG *arg);
HRESULT* OMX_FW_RPC_MS12_Update_Params(AUDIO_RPC_MS_PARAM_UPDATE *arg);
HRESULT* OMX_FW_RPC_MS12_Clear_Update_Params(AUDIO_RPC_MS_CLEAR_PARAM_UPDATE *arg);
HRESULT* OMX_FW_RPC_MS12_Runtime_Update_Params(AUDIO_RPC_MS_PARAM_UPDATE *arg);

#endif