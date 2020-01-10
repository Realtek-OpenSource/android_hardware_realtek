#ifndef __ALLOCATOR_BUF_DEF__
#define __ALLOCATOR_BUF_DEF__

#include <libRTKAllocator/include/hardware/GrallocWrapper.h>
#include <libRTKAllocator/include/allocator/IonAllocator.h>

using namespace android;

namespace androidcamera3 {

typedef struct _AllocatorBuf {
    int32_t         mIndex;
    AllocatorDef*   pAllocator;
    int32_t         mWidth;
    int32_t         mHeight;
    int32_t         mSize;
    void*           vAddr;
    uint32_t        phyAddr;
    nsecs_t         mPts;
    bool            mEnqueued;
    uint32_t        mBytesUsed;

    // basic constructor
    _AllocatorBuf() {
        pAllocator = NULL;
        mWidth = 0;
        mHeight = 0;
        mSize = 0;
        vAddr = NULL;
        phyAddr = 0;
        mIndex = 0;
        mPts = 0;
        mEnqueued = false;
    }

} AllocatorBuf;

};

#endif // __ALLOCATOR_BUF_DEF__
