#ifndef __RTK_HWC_VSYNC_H_
#define __RTK_HWC_VSYNC_H_
#include <hwc_utils.h>
#include <utils/Vector.h>
#include <vsync/VsyncListener.h>

class Vsync {
public:
    class Client : public VsyncListener {
    public:
        Client();
        virtual ~Client();
        /* Client side */
        virtual void VsyncEvent(void) = 0;
        virtual int getClientVsyncPeriod  (void) {
            if (mService)
                return mService->getVsyncPeriod();
            else
                return 16666666;
        };

        virtual void setVsyncService(Vsync * service) {
            if (service)
                service->registerListener(this);
            mService = service;
        };

    private:
        /* Server side */
        friend class Vsync;
        static void *       EventThread(void * data);

        enum EventCmd{
            EVENT_CMD_VSYNC     = 0x1U << 0,
            EVENT_CMD_EOS       = 0x1U << 1,
        };
        void                PushEvent(unsigned int event_cmd);

        Vsync *             mService;
        unsigned int        mEventCmd;
        pthread_t           mThread;
        pthread_mutex_t     mMutex;
        pthread_cond_t      mCond;
    };
    Vsync();
    virtual ~Vsync();

    void    registerListener(Client * listener);
    int     removeListener  (Client * listener);

    void    SendEvent       (void);
    int     waitNextSync    (void);

    int     getVsyncPeriod  (void) {return mVsyncPeriodNs;};
    int64_t getTimestamp    (void) {return mTimestamp;};

    void    dump(android::String8& buf, const char* prefix);
private:
    static void *  MainLoop (void * data);

    bool                mEOS;
    pthread_t           mThread;
    pthread_mutex_t     mLock;
    android::Vector<Client *> mList;
    int                 mFd;
    int64_t             mTimestamp;
    int64_t             mVsyncPeriodNs;
    pthread_attr_t      mThreadAttr;
};

#endif /* End of __RTK_HWC_VSYNC_H_ */
