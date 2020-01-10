#ifndef __RTK_HWC_HWLAYER_UTILS_H_
#define __RTK_HWC_HWLAYER_UTILS_H_
#include <utils/Log.h>
#include <cutils/atomic.h>
#include <cutils/properties.h>
#include <cutils/compiler.h>
#include <utils/Vector.h>
#include <sys/mman.h>
#include "../realtek_omx/osal_rtk/OSAL_RTK.h"
#include <RPCstruct.h>
#include <VideoRPC_System_data.h>
#include <rpc_common.h>
#include <hardware/gralloc.h>
#include <utils/threads.h>
#include <utils/Mutex.h>
#include <pthread.h>
#include <utils/String8.h>
#include <hresult.h>
#include <RPCProxy.h>

#define GRALLOC_ALIGN( value, base ) (((value) + ((base) - 1)) & ~((base) - 1))

#endif /* End of __RTK_HWC_HWLAYER_UTILS_H_ */
