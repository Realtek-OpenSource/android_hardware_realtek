//--=========================================================================--
//  This file is a part of VPU Reference API project
//-----------------------------------------------------------------------------
//
//       This confidential and proprietary software may be used only
//     as authorized by a licensing agreement from Chips&Media Inc.
//     In the event of publication, the following notice is applicable:
//
//            (C) COPYRIGHT CHIPS&MEDIA INC.
//                      ALL RIGHTS RESERVED
//
//       The entire notice above must be reproduced on all authorized
//       copies.
//
//--=========================================================================--
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "config.h"
#include "main_helper.h"

enum {
    CNMQC_ENV_NONE,
    CNMQC_ENV_GDBSERVER = (1<<16),      /*!<< It executes gdb server in order to debug F/W on the C&M FPGA env. */
    CNMQC_ENV_MAX,
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* @param options   It can be multiples of the above options.
 */
extern void InitializeDebugEnv(
    Uint32 productId,
    Uint32 options
);

extern void ReleaseDebugEnv(
    void
);

void PrintVpuStatus(
    Uint32 coreIdx,
    Uint32 productId
);

void PrintMemoryAccessViolationReason(
    Uint32          core_idx,
    void            *outp
);

void DumpCodeBuffer(
    const char* path
);

Int32 HandleDecInitSequenceError(DecHandle handle, Uint32 productId, DecOpenParam* openParam, DecInitialInfo* seqInfo, RetCode apiErrorCode);

void HandleDecoderError(
    DecHandle       handle,
    Uint32          frameIdx,
    TestDecConfig*  param,
    vpu_buffer_t*   fbMem,
    DecOutputInfo*  outputInfo
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SKIP_H_ */

