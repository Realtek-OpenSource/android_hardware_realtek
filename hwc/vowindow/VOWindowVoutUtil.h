#ifndef __RTK_HWC_VO_WINDOW_API_VOUTUTIL_H_
#define __RTK_HWC_VO_WINDOW_API_VOUTUTIL_H_
#include "VOWindowBase.h"
#include <property/HWCProperty.h>
class VOWindowVoutUtil : public VOWindowBase,
    virtual public HWCProperty
{
public:
    VOWindowVoutUtil();
    virtual ~VOWindowVoutUtil();
    virtual int updateWindow();
    virtual bool isRunning(void);
    enum {
        V1,
        V2,
        SUB1,
        OSD1,
        OSD2,
        WIN1,
        WIN2,
        WIN3,
        WIN4,
        WIN5,
        NONE
    } PLANE;
    virtual void    setPlane(int plane) {mPlane = plane;};
    virtual int     getPlane() {return mPlane;};
    virtual enum VO_VIDEO_PLANE getVOPlane();
    enum {
        VO_MIXER_DEFAULT = 0,
        VO_MIXER_OWNER_MASK = 0x10000,
    } VO_PLANE_MIXER_EXT;
    //virtual void setMixer(int mixer) { mMixer = mixer; };
    virtual void    dump(android::String8& buf, const char* prefix);
    virtual void    clearState(void);
    virtual void DisplayInfoEvent(int cmd, int ext);
private:
    int  setVoWindow(const hwc_rect_t& sourceBase, const hwc_rect_t& sourceCrop, const hwc_rect_t& displayFrame);
    int  getFramebufferBase(hwc_rect_t * rect);
    int  getWindowBase(hwc_rect_t * rect);
    int  mPlane;
    int  mMixer;
    bool mClear;
    pthread_mutex_t mLock;

    hwc_rect_t mActiveSourceBase;
    hwc_rect_t mActiveSourceCrop;
    hwc_rect_t mActiveDisplayFrame;
    bool       mHidden;
    VoutUtil * mVOutCtrl;
};

#endif /* End of __RTK_HWC_VO_WINDOW_API_VOUTUTIL_H_ */
