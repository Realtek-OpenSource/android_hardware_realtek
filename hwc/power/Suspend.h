#ifndef __RTK_HWC_POWER_SUSPEND_H_
#define __RTK_HWC_POWER_SUSPEND_H_
#include <hwc_utils.h>
#include <utils/Vector.h>
#include <power/Power.h>
#include <vsync/VsyncListener.h>
#include <vsync/Vsync.h>
#include <property/HWCProperty.h>

class Suspend : public Power::Client,
    virtual public Vsync::Client,
    virtual public HWCProperty
{
public:
    Suspend();
    virtual ~Suspend();

    /* PowerListener API */
    virtual void PowerEvent(int cmd, int ext);

    /* VsyncListener API */
    virtual void VsyncEvent(void);

    virtual void dump(android::String8& buf, const char* prefix);
private:
    void    setupTimestamp(bool assert);
    void    setupCoolboot(void);
    void    setupWFI(void);
    int     getWakLock(bool debug);
    bool    WakeLock(void);
    void    Process(void);
    void    WatchdogTask(void);
    int     getContext(void);
    void    WakeupTask(void);

    enum {
        GOTO_SUSPEND        = 0x1U <<   0,
        BLANK               = 0x1U <<   1,
    };
    int64_t         mMaxWaitByWakeLockUs;
    int64_t         mSuspendTimestampUs;
    uint32_t        mFlags;
    int             mContext;
    int             mSuspendModeFd;
    int             mPowerStateFd;
    int             mWatchdogSecFd;
    int             mWatchdogEnFd;
    int             mContexFd;
    FILE *          mWakeLockFptr;
    int             mSuspendCtl;

};
#endif /* End of __RTK_HWC_POWER_SUSPEND_H_ */
