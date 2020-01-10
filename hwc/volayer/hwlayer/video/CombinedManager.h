#ifndef __RTK_HWC_HWLAYER_COMBINED_MANAGER_H_
#define __RTK_HWC_HWLAYER_COMBINED_MANAGER_H_
#include <utils/hwlayer_utils.h>

class CombinedManager {
public:
    class Client {
    public:
        Client() :
            mState(CombinedNone),
            mService(NULL),
            mSSID(-1),
            mResource(NULL),
            mOrder(0) {};

        virtual ~Client() {};

        virtual void setCombinedManager(CombinedManager * service = NULL) {
            if (service)
                return service->registerClient(this);
            else if (mService)
                return mService->removeClient(this);
        }

        /* State Change
         *      CombinedNone => CombinedStandBy     : setCombinedSSID
         *      CombinedStandBy => CombinedNone     : unsetCombinedSSID
         *      CombinedStandBy => CombinedDone     : setCombinedDone
         *
         *  (first unsetCombinedSSID client)
         *      CombinedDone => CombinedNone        : unsetCombinedSSID
         *
         *  (second unsetCombinedSSID client)
         *      CombinedDone => CombinedFree (by first unsetCombinedSSID client)
         *      CombinedFree => CombinedNone        : unsetCombinedSSID
         */
        virtual void setCombinedSSID(int ssid) {
            if (mService)
                return mService->setCombinedSSID(this, ssid);
        }

        virtual void setCombinedDone() {
            if (mService)
                return mService->setCombinedDone(this);
        }

        virtual void unsetCombinedSSID() {
            if (mService)
                return mService->unsetCombinedSSID(this);
        }

        /* In the exchange of resources between different client */
        virtual int getMaxCombinedOrder() {
            if (mService)
                return mService->getMaxCombinedOrder(this);
            else
                return 0;
        }

        virtual void * getCombinedResourceByOrder(int order = 0) {
            if (mService)
                return mService->getCombinedResourceByOrder(this, order);
            else
                return NULL;
        }

        virtual void * getCombinedResource() {
            return mResource;
        }

        virtual void setCombinedResource(void * resource = NULL) {
            mResource = resource;
        }

        enum CombinedManagerEventCmd {
            CME_SSID_BROADCAST = 1,
            CME_STATE_CHANGE,
        };
        virtual void CombinedManagerEvent(int /*cmd*/, int /*ext*/) {};

        virtual bool isCombinedSlot()       { return (mState != CombinedNone);};
        virtual bool isCombinedFree()       { return (mState == CombinedFree);};
        virtual bool isCombinedStandBy()    { return (mState == CombinedStandBy);};
        virtual bool isCombinedDone()       { return (mState == CombinedDone);};
        virtual bool getCombinedOrder()     { return mOrder;};
    private:
        friend class CombinedManager;

        enum CombinedClientState {
            CombinedNone = 0,
            CombinedFree,
            CombinedStandBy,
            CombinedDone,
        } mState;
        CombinedManager * mService;
        int     mSSID;
        void *  mResource;
        int     mOrder;

    };

    CombinedManager();
    virtual ~CombinedManager();

    virtual void    registerClient      (Client * client);
    virtual void    removeClient        (Client * client);

    virtual void    setCombinedSSID     (Client * client, int ssid);
    virtual void    setCombinedDone     (Client * client);
    virtual void    unsetCombinedSSID   (Client * client);

    virtual int     getMaxCombinedOrder (Client * client);
    virtual void *  getCombinedResourceByOrder (Client * client, int order);

private:
    pthread_mutex_t                 mLock;
    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;
};

#endif /* End of __RTK_HWC_HWLAYER_COMBINED_MANAGER_H_ */
