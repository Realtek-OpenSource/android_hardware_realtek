#ifndef __RTK_HWC_VO_WINDOW_VOUT_ORDER_H_
#define __RTK_HWC_VO_WINDOW_VOUT_ORDER_H_
#include <hwc_utils.h>
#include <utils/Vector.h>

class VOMixerServer {
public:
    class Client {
    public:
        enum MixerPlane {
            MIXER_PLANE_NONE,
            MIXER_PLANE_CSR,
            MIXER_PLANE_SUB2,
            MIXER_PLANE_OSD1,
            MIXER_PLANE_V2,
            MIXER_PLANE_SUB1,
            MIXER_PLANE_V1,
            MIXER_PLANE_V3,

            MIXER_PLANE_OSD2,
            MIXER_PLANE_PIC,
            MIXER_PLANE_DD,
            MIXER_PLANE_MAX,
        };

        Client(enum MixerPlane plane = MIXER_PLANE_NONE);
        virtual ~Client() {
            if (mService)
                mService->removeClient(this);
        };

        virtual void setVOMixerServer(VOMixerServer * service) {
            if (service)
                service->registerClient(this);
            mService = service;
        };

        virtual void setVOMixerPlane(enum MixerPlane plane) {
            if (mService)
                mService->setVOMixerPlane(this, plane);
            else
                mMixerPlane = plane;
        };

        virtual void setVOMixerOrder(int order) {
            if (mService)
                mService->setVOMixerOrder(this, order);
            else
                mMixerOrder = order;
        };

        virtual int upgradeVOMixerOrder(void) {
            if (mService)
                mService->upgradeOrder(this);
            return mMixerOrder;
        }

        virtual int getVOMixerMaxOrder() {
            if (mService)
                return mService->getVOMixerMaxOrder(this);
            else
                return 0;
        };

        virtual void clearVOMixerOrder(void) {
            if (mService)
                mService->clearVOMixerOrder(this);
            else {
                mUse = false;
            }
        }
    private:
        friend class VOMixerServer;
        VOMixerServer *     mService;
        pthread_mutex_t         mMutex;
        bool                    mUse;
        enum MixerPlane         mMixerPlane;
        int                     mMixerOrder;
    };

    VOMixerServer();
    virtual ~VOMixerServer();

    void    registerClient      (Client * client);
    int     removeClient        (Client * client);
    int     getVOMixerMaxOrder  (Client * client);
    void    setVOMixerPlane     (Client * client, enum Client::MixerPlane plane);
    void    setVOMixerOrder     (Client * client, int order);
    void    upgradeOrder        (Client * client);

    void    clearVOMixerOrder   (Client * client);
    void    prepareMixerOrder();
    void    undateMixerOrder();
    void    dump(android::String8& buf, const char* prefix);
private:

    struct planeConfig {
        int used;
        int order;
        int targetOrder;
    };

    struct MixerConfig {
        struct planeConfig plane [Client::MIXER_PLANE_MAX];
    } mMixerConfig;

    int     genMixerConfig      (struct MixerConfig * config);
    bool    FirmwareMixerIsReady();
    pthread_mutex_t             mLock;
    android::Vector<Client *>   mList;


    VoutUtil *                  mVOutCtrl;
    bool                        mFirmwareCheck;
    bool                        mFirmwareMixerIsReady;
    int                         mSetupOrder;
};

#endif /* End of __RTK_HWC_VO_WINDOW_VOUT_ORDER_H_ */
