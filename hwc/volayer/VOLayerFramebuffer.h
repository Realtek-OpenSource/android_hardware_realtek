#ifndef __RTK_HWC_LAYER_FRAMEBUFFER_H_
#define __RTK_HWC_LAYER_FRAMEBUFFER_H_
#include "VOLayerBase.h"
#include <vowindow/VOWindowVoutUtil.h>

class VOLayerFramebuffer : public VOLayerBase, virtual public VOWindowVoutUtil {
public:
    VOLayerFramebuffer();
    virtual ~VOLayerFramebuffer();

    virtual void prepare();
    virtual void set();
    virtual void dump(android::String8& buf, const char* prefix);
    virtual void setDisplayInfo(DisplayInfo * info) {VOWindowVoutUtil::setDisplayInfo(info);};
    //virtual void waitAcquireFence(void) {};
private:
    static const int MaxAcquireFenceFdCount = 3;
    hw_module_t const* mGrallocModule;
    framebuffer_device_t* mFbDev;
    int mAcquireFenceFd[MaxAcquireFenceFdCount];
    int mAcquireFenceFdStep;
#ifdef SKIP_FIRST_FRAME_FOR_AFBC_WORKAROUND
    int mSkipCount;
#endif /* End of SKIP_FIRST_FRAME_FOR_AFBC_WORKAROUND */
};

#endif /* End of __RTK_HWC_LAYER_FRAMEBUFFER_H_ */
