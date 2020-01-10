#ifndef __RTK_HWC_HWLAYER_UTILS_SW_FENCE_H_
#define __RTK_HWC_HWLAYER_UTILS_SW_FENCE_H_
#include "hwlayer_utils.h"

class SWFence {
public:
    enum {
        InvalidFd = -1,
    };
    class Client {
    public:
        enum {
            InvalidFd = SWFence::InvalidFd,
        };

        Client() : mService(NULL), mFenceFd(InvalidFd), mContext(-1) {};

        virtual ~Client() {};

        virtual void setSWFence(SWFence * service = NULL) {
            if (service)
                service->registerClient(this);
            else if (mService) {
                if (mFenceFd != InvalidFd)
                    releaseFenceFd();
                mService->removeClient(this);
            }
        };

        virtual int acquiredFenceFd () {
            if (mService == NULL)
                return InvalidFd;

            if (mFenceFd != InvalidFd)
                return mFenceFd;

            mService->acquiredFenceFd(this);
            //ALOGI("[%s] (%p) %d:%d", __FUNCTION__, this, mContext, mFenceFd);
            return mFenceFd;
        };

        virtual int getFenceFd () {
            if (mService == NULL)
                return InvalidFd;
            return mFenceFd;
        };

        virtual int releaseFenceFd() {
            if (mService == NULL)
                return InvalidFd;
            //ALOGI("[%s] (%p) %d:%d", __FUNCTION__, this, mContext, mFenceFd);
            return mService->releaseFenceFd(this);
        };

        virtual void dump(android::String8& buf, const char* prefix = NULL);
    private:
        friend class SWFence;
        SWFence * mService;
        int mFenceFd;
        int mContext;
    };

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);

    virtual void acquiredFenceFd    (Client * client);
    virtual int  releaseFenceFd     (Client * client);

    SWFence();
    virtual ~SWFence();

private:
    virtual int acquiredFenceFd();
    void releaseFenceFd(int fenceFd);

    int                             mSync_timeline_fd;
    int                             mFenceIndex;
    pthread_mutex_t                 mLock;

    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;
};
#endif /* End of __RTK_HWC_HWLAYER_UTILS_SW_FENCE_H_ */
