#ifndef __RTK_HWC_POWER_H_
#define __RTK_HWC_POWER_H_
#include <hwc_utils.h>
#include <utils/Vector.h>

class PowerListener {
public:
    PowerListener() {};
    virtual ~PowerListener() {};
    enum {
        PE_SUSPEND_SUSPEND,
        PE_SUSPEND_RESUME,
        PE_SCREEN_BLANK,
        PE_SCREEN_POWER_MODE,
    };

    virtual void PowerEvent(int cmd, int ext) = 0;
private:
};

class Power {
public:

    class Client : public PowerListener{
    public:
        Client ()
            : mService(NULL) {};

        virtual ~Client() {
            if (mService)
                mService->removeClient(this);
        };

        /* Client Side */

        virtual void SendEvent(int cmd, int ext) {
            if (mService == NULL) return;
            mService->SendEvent(this, cmd, ext);
        };

        /* PowerListener API */
        virtual void PowerEvent(int /*cmd*/, int /*ext*/) {};

    private:
        friend class Power;

        /* Server Side */
        void setPower(Power * power) { mService = power;};

        Power * mService;
    };

    Power();
    virtual ~Power();

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);
    virtual void SendEvent          (Client * client, int cmd, int ext);

    virtual void registerListener   (PowerListener * listener);
    virtual int  removeListener     (PowerListener * listener);

private:
    void SendEvent(int cmd, int ext);
    pthread_mutex_t                 mClientLock;
    pthread_mutex_t                 mListenerLock;

    android::Vector<Client*>        mClientList;
    android::Vector<PowerListener*> mListenerList;;
};

#endif /* End of __RTK_HWC_POWER_H_ */
