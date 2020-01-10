#ifndef __RTK_HWC_HWLAYER_UTILS_PLOCK_BASE_H_
#define __RTK_HWC_HWLAYER_UTILS_PLOCK_BASE_H_
#include "hwlayer_utils.h"
#include <utils/IonBuffer.h>

class PLockBase {
public:
    enum PlockStatus { /* size : unsigned char */
        PLOCK_STATUS_RESET      = 0xFF,
        PLOCK_STATUS_Q_PEND     = 0x99,
        PLOCK_STATUS_VO_LOCK    = 0x01,
        PLOCK_STATUS_VO_LOCK2   = 0x02,
        PLOCK_STATUS_VO_UNLOCK  = 0x00,
        PLOCK_ERR               = 0xFE,
    };

    class Client {
    public:
        Client():mService(NULL),mStatus(NULL),mPhyaddr(-1U),mIndex(-1U) {};

        virtual ~Client() {};

        virtual void setPLockBase(PLockBase * service = NULL) {
            if (service)
                service->registerClient(this);
            else if (mService)
                mService->removeClient(this);
        }

        virtual void setPLockStatus(enum PlockStatus status) {
            if (mService)
                mService->setPLockStatus(this, status);
        }

        virtual enum PlockStatus getPLockStatus() {
            if (mService)
                return mService->getPLockStatus(this);
            else
                return PLOCK_ERR;
        }

        virtual unsigned int getPLockPhyAddr() {
            if (mService)
                return mService->getPLockPhyAddr(this);
            else
                return -1U;
        }

        virtual unsigned int getPLockVersion() {
            if (mService)
                return mService->getPLockVersion(this);
            else
                return -1U;
        }

        virtual void dump(android::String8& buf, const char* prefix = NULL);
    private:
        friend class PLockBase;
        PLockBase * mService;
        unsigned char * mStatus;
        unsigned int mPhyaddr;
        unsigned int mIndex;
    };

    PLockBase(unsigned int maxIndex = 64, unsigned int version = 0x72746B32);
    virtual ~PLockBase();

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);
    virtual void setPLockStatus     (Client * client, enum PlockStatus status);
    virtual enum PlockStatus getPLockStatus (Client * client);
    virtual unsigned int getPLockPhyAddr    (Client * client);
    virtual unsigned int getPLockVersion    (Client * /*client*/) {
        return mVersion;
    };
    virtual void setPLockVersion(unsigned int version) {
        mVersion = version;
    };

private:
    void atraceDump();
    unsigned int getFreeIndex();
    pthread_mutex_t                 mLock;

    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;

    unsigned int mMaxIndex;
    size_t mPSize;
    unsigned int mVersion;
    IonBuffer *     mIonBuffer;
};

#endif /* End of __RTK_HWC_HWLAYER_UTILS_PLOCK_BASE_H_ */
