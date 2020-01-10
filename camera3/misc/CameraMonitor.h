#ifndef _CAMERA_MONITOR_
#define _CAMERA_MONITOR_

#include <pthread.h>
#include <sysutils/NetlinkEvent.h>
#include "Common.h"
#include "misc.h"

#define     EVENT_BUF_SIZE  10

typedef int (*refresh_cameras)();

namespace android_camera_hal3 {

typedef struct event_info {
    bool mEnable;
    const char *mSysfs;
    const char *mMsg;
} event_info_t;

typedef enum {
    HDCP_STATE_OFF,
    HDCP_STATE_ON,
    //HDCP_STATE_1X,
    //HDCP_STATE_2X
}ENUM_HDCP_STATE;

class CameraMonitor {

public:
    static CameraMonitor*   Instance();

    virtual                 ~CameraMonitor();

    ENUM_HDCP_STATE         getHDCPState() { return mHDCPState; }
    void                    handleSwitchEvent();
    void                    onInitialize();
    void                    setCallback(refresh_cameras cb) { mCallback = cb; }
    void                    updateHdcpState();
    bool                    isMonitoredEvent(const char *msg);

private:
    CameraMonitor();
    static CameraMonitor*   sInstance;

    pthread_t               mUeventThread;
    refresh_cameras         mCallback;
    ENUM_HDCP_STATE         mHDCPState;

    event_info_t*           mEventInfos[EVENT_BUF_SIZE];
    event_info_t            mHDMIRxEvent;
    ssize_t                 mMonitoredEventNum;
    //event_info_t            mHDCP1xEvent;
    //event_info_t            mHDCP22Event;

    static void*            pthread_entry(void *ptr);
    void                    initEventInfo();
};

};

#endif
