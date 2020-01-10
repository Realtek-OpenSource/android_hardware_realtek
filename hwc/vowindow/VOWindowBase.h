#ifndef __RTK_HWC_VO_WINDOW_API_BASE_H_
#define __RTK_HWC_VO_WINDOW_API_BASE_H_
#include <hwc_utils.h>
#include <display/Display.h>
class VOWindowBase : public DisplayInfo::Client {
public:
    VOWindowBase();
    virtual ~VOWindowBase();
    virtual int             setWindow(int width, int height);
    virtual int             setWindow(int x, int y, int width, int height);
    virtual int             setWindow(const hwc_rect_t& displayFrame);
    virtual int             setWindow(const hwc_rect_t& sourceCrop, const hwc_rect_t& displayFrame);
    virtual int             setWindow(const hwc_rect_t& sourceBase, const hwc_rect_t& sourceCrop, const hwc_rect_t& displayFrame);
    virtual void            showWindow(void) {mHidden=false; updateWindow();};
    virtual void            hideWinsow(void) {mHidden=true; updateWindow();};

    virtual bool            getHiddenState(void) {return mHidden;};
    virtual void            clearState(void);

    virtual int             getSourceBase(hwc_rect_t * rect);
    virtual int             getSourceCrop(hwc_rect_t * rect);
    virtual int             getDisplayFrame(hwc_rect_t * rect);

    virtual bool            sameAsSourceBase(hwc_rect_t * rect);
    virtual bool            sameAsSourceCrop(hwc_rect_t * rect);
    virtual bool            sameAsDisplayFrame(hwc_rect_t * rect);

    virtual int             updateWindow(void) = 0;
    virtual void            dump(android::String8& buf, const char* prefix);

    virtual DisplayInfo::Client *   getDisplayInfo(void) {return this;};
private:
    hwc_rect_t mSourceBase;
    hwc_rect_t mSourceCrop;
    hwc_rect_t mDisplayFrame;
    bool mHidden;
};
#endif /* End of __RTK_HWC_VO_WINDOW_API_BASE_H_ */
