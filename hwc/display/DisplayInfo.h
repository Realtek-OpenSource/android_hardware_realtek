#ifndef __RTK_HWC_DISPLAY_INFO_H_
#define __RTK_HWC_DISPLAY_INFO_H_
#include <hwc_utils.h>
#include <vsync/Vsync.h>
#include <property/HWCProperty.h>
//#include <vowindow/VOWindowBase.h>

class DisplayInfo {
public:
    class Client {
    public:
        Client() : mService(NULL) {};

        virtual ~Client() {
            if (mService)
                mService->removeClient(this);
        };

        /* Client Side */
        enum displayinfo_event_cmd {
            DISPLAYINFO_CHANGE,
            VIDEOSTANDARD_CHANGE,
        };

        virtual void setDisplayInfo(DisplayInfo * service) {
            if (service)
                service->registerClient(this);
        };

        virtual int getVsyncPeriod  (void) { return (mService)?mService->getVsyncPeriod():-1;};
        virtual int getWidth        (void) { return (mService)?mService->getWidth      ():-1;};
        virtual int getHeight       (void) { return (mService)?mService->getHeight     ():-1;};
        virtual int getDpiX         (void) { return (mService)?mService->getDpiX       ():-1;};
        virtual int getDpiY         (void) { return (mService)?mService->getDpiY       ():-1;};
        virtual int getFps          (void) { return (mService)?mService->getFps        ():-1;};
        virtual int getDisplayType  (void) { return (mService)?mService->getDisplayType():-1;};
        virtual int getDisplayOutput(void) { return (mService)?mService->getDisplayOutput():-1;};

        virtual void DisplayInfoEvent(int /*cmd*/, int /*ext*/) {};

    private:
        friend class DisplayInfo;
        DisplayInfo * mService;
    };

    enum display_type {
        DISPLAY_PRIMARY,
        DISPLAY_EXTERNAL,
        DISPLAY_VIRTUAL,
        DISPLAY_MAX,
        DISPLAY_ERROR = -1,
    };

    enum display_output {
        DISPLAY_OUTPUT_NONE,
        DISPLAY_OUTPUT_HDMI,
        DISPLAY_OUTPUT_DP,
        DISPLAY_OUTPUT_DP_ONLY,
        DISPLAY_OUTPUT_DD,
        DISPLAY_OUTPUT_MAX,
        DISPLAY_OUTPUT_ERROR,
    };

    enum {
        FB0,
        FB1,    /* NOT READY : DONT USE! */
        HDMI,   /* NOT READY : DONT USE! */
    } DisplayDevice;

    DisplayInfo(Vsync * vsync, int display_device,
            enum display_type type = DISPLAY_PRIMARY,
            enum display_output output = DISPLAY_OUTPUT_HDMI);
    virtual ~DisplayInfo();

    virtual int getVsyncPeriod  (void);
    virtual int getWidth        (void);
    virtual int getHeight       (void);
    virtual int getDpiX         (void);
    virtual int getDpiY         (void);
    virtual int getFps          (void);
    virtual void updateResolution(const hwc_rect_t& rect);
    virtual void setDisplayType(enum display_type type) { mDisplayType = type; updateForceInfo();};
    virtual enum display_type getDisplayType(void) { return mDisplayType;};
    virtual void setDisplayOutput(enum display_output output) { mDisplayOutput = output; updateForceInfo();};
    virtual enum display_output getDisplayOutput(void) { return mDisplayOutput;};
    virtual bool getDisplayOutputConnected(void);

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);
    void SendEvent          (int cmd, int ext = 0);
    virtual void dump               (android::String8& buf, const char* prefix);
    void HDMIPlugEvent(bool In);
#ifdef HAS_DPTX
    void DPTxPlugEvent(bool In);
#endif
private:

    void    setDcBufferInfo(bool enable, int w, int h);
    int     validate();
    int     updateInfo();
    void    updateForceInfo();
    int     mDisplayDevice;
    int     mDisplayFd;
    int     mRefreshRate; // FPS = mRefreshRate / 1000
    int     mWidth;
    int     mHeight;
    int     mDpiX;
    int     mDpiY;

    int     mStableWidth;
    int     mStableHeight;

    enum display_type   mDisplayType;
    enum display_output mDisplayOutput;
    int     mForceWidth;
    int     mForceHeight;
    HWCProperty * mProperty;
    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;
    bool HDMIPlugIn;
#ifdef HAS_DPTX
    bool DPTxPlugIn;
#endif
};

#endif /* End of __RTK_HWC_DISPLAY_INFO_H_ */
