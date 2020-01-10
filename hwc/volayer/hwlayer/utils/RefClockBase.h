#ifndef __RTK_HWC_HWLAYER_UTILS_REFCLOCK_BASE_H_
#define __RTK_HWC_HWLAYER_UTILS_REFCLOCK_BASE_H_
#include "hwlayer_utils.h"
#include <utils/IonBuffer.h>

class RefClockBase {
public:
    class Client {
    public:
        Client() : mService(NULL) {};

        virtual ~Client() {
#if 0
            if (mService) {
                mService->removeClient(this);
            }
#endif
        };

        virtual void setRefClock(RefClockBase * service = NULL) {
            if (service)
                service->registerClient(this);
            else if (mService) {
                mService->removeClient(this);
            }
        };

        void * getRefClockPhyAddr() {
            if (mService)
                return mService->getRefClockPhyAddr(this);
            else
                return NULL;
        };

        unsigned int getRefClockUnusedContext() {
            if (mService)
                return mService->getRefClockUnusedContext(this);
            else
                return 0;
        };

        unsigned int getRefClockVideoContext() {
            if (mService)
                return mService->getRefClockVideoContext(this);
            else
                return 0;
        };

        unsigned int getRefClockAudioContext() {
            if (mService)
                return mService->getRefClockAudioContext(this);
            else
                return 0;
        };

        virtual void dump(android::String8& /*buf*/, const char* /*prefix*/) {};

    private:
        friend class RefClockBase;
        RefClockBase * mService;
    };

    RefClockBase(int audioHwSync = -1);
    virtual ~RefClockBase();

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);

    void * getRefClockPhyAddr(Client * client = NULL);
    unsigned int getRefClockUnusedContext(Client * client = NULL);
    unsigned int getRefClockVideoContext(Client * client = NULL);
    unsigned int getRefClockAudioContext(Client * client = NULL);
private:
    //pthread_mutex_t                 mLock;
    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;
    //unsigned char *                 mViraddr;
    //unsigned char *                 mPhyaddr;
    int                             mAudioHwSync;
    unsigned int                    mContext;
    IonBuffer *                     mIonBuffer;
};

#endif /* End of __RTK_HWC_HWLAYER_UTILS_REFCLOCK_BASE_H_ */
