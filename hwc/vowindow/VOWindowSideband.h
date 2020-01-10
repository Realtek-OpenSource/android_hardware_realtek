#ifndef __RTK_HWC_VO_WINDOW_API_SIDEBAND_H_
#define __RTK_HWC_VO_WINDOW_API_SIDEBAND_H_
#include "VOWindowBase.h"

#include <SidebandClient.h>
#include <SidebandControl.h>
#include <gui/Surface.h>

#define RESOURCE_UPDATE_DELAY_NS 1000000000
class VOWindowSideband : public VOWindowBase {
public:
    enum flags_t {
        HIDDEN          = 0x1U <<   0,  //layer_state_t::eLayerHidden, /* 0x01    |     1:hide 0:shwo */
        OPAQUE          = 0x1U <<   1,  //layer_state_t::eLayerOpaque, /* 0x02 */
        REFRESH         = 0x1U <<   16,
        FRAME_READY     = 0x1U <<   17,
        FLUSH           = 0x1U <<   18,
        SIDEBAND_V1     = 0x1U <<   3,
        SIDEBAND_V2     = 0x1U <<   4,
    };

    enum TargetPlane {
        FLIP_V1,
        FLIP_V2,
    };

    VOWindowSideband();
    virtual ~VOWindowSideband();
    virtual int updateWindow(void);

    virtual int setSidebandStream(native_handle_t * handle, int plane);
    virtual void releaseSidebandStream(void);
    virtual void passToRender(void);
    virtual void stopToRender(void);
    virtual void dump(android::String8& buf, const char* prefix);
    virtual void clearState(void);
    virtual void DisplayInfoEvent(int cmd, int ext);
    virtual void getSidebandInfo(android::String8 &buf, const char* prefix);
private:
    native_handle_t * mSideband;
    android::sp<android::SidebandClient>  mClient;
    android::sp<android::SidebandControl> mControl;

    pthread_mutex_t mLock;

    bool mHidden;
    bool mClear;
    int64_t mResourceTime;
    hwc_rect_t mActiveSourceCrop, mActiveDisplayFrame;
    int64_t mKey;
    native_handle_t* mSidebandStream;
    int64_t mBWKey;
};
#endif /* End of __RTK_HWC_VO_WINDOW_API_SIDEBAND_H_ */
