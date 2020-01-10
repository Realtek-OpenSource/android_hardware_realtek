#ifndef __RTK_HWC_HWLAYER_UTILS_ION_BUFFER_INFO_H_
#define __RTK_HWC_HWLAYER_UTILS_ION_BUFFER_INFO_H_
#include "hwlayer_utils.h"
#include <ion/ion.h>
#include <rtk_ion.h>

class IonBuffer {
public:
    enum IonOper {
        AllocBuffer,
        ImportBuffer,
        ImportBuffer_lock,
    };

    enum IonHeapMask {
        MediaHeapMask = 0x1U << 0,
        AudioHeapMask = 0x1U << 1,
        SecureHeapMask = 0x1U << 2,
    };

    enum IonFlagMask {
        NONCACHED       = 0x1U << 0,
        SCPUACC         = 0x1U << 1,
        ACPUACC         = 0x1U << 2,
        HWIPACC         = 0x1U << 3,
        PROTECTED       = 0x1U << 4,
        SECURE_AUDIO    = 0x1U << 5,
    };

    IonBuffer(enum IonOper oper, long long oper_data,
            unsigned int heap_mask = MediaHeapMask,
            unsigned int flag_mask = (NONCACHED|SCPUACC|HWIPACC));

    virtual ~IonBuffer();
    void * getVirAddr() {return (mViraddr == MAP_FAILED)?NULL:mViraddr;};
    void * getPhyAddr() {return mPhyaddr;};
    int sync();
    long long getSize() {return mSize;};
    int getShareFd() {return mIonMmapFd;};
    static void *osal_memcpy(void * dst, const void * src, int count);
private:
    virtual void allocBuffer(long long bufferSize);
    virtual void importBuffer(int import_fd, bool lock);
    virtual void freeBuffer();

    int     mIonFd;
    int     mIonMmapFd;
    void *  mViraddr;
    void *  mPhyaddr;
    long long mSize;
    ion_user_handle_t mIonHandle;
    unsigned int mHeapMask;
    unsigned int mFlagMask;
};

#endif /* End of __RTK_HWC_HWLAYER_UTILS_ION_BUFFER_INFO_H_ */
