#ifndef __RTK_SECURE_HANDLE_DEFINE_H_
#define __RTK_SECURE_HANDLE_DEFINE_H_

#include <cutils/native_handle.h>

typedef struct secure_handle
{
    struct native_handle    nativeHandle;
    int                     sFd;
    unsigned int            uAllocSize;
    unsigned int            uPhyAddr;
    unsigned int            uMagic;
} secure_handle_t ;

#endif /* End of __RTK_SECURE_HANDLE_DEFINE_H_ */
