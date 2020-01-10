#ifndef __RTK_HWC_LAYER_SCALE_H_
#define __RTK_HWC_LAYER_SCALE_H_
#include "VOLayerBase.h"
#include <vowindow/VOWindowVoutUtil.h>
#include <arbiter/ResourceArbiter.h>
#include <property/HWCProperty.h>
#include <SidebandClient.h>

class VOLayerScale : public VOLayerBase,
    virtual public VOWindowVoutUtil,
    virtual public ResourceArbiter::Client,
    virtual public HWCProperty
{
public:
    enum TargetPlane {
        SCALE_NONE,
        SCALE_V1,
        SCALE_V2,
    };
    VOLayerScale(enum TargetPlane plane = SCALE_V1);
    virtual ~VOLayerScale();
    virtual bool supportHwcLayer(hwc_layer_1_t * hwc_layer, int layer);
    virtual void prepare();
    virtual void set();
    virtual void dump(android::String8& buf, const char* prefix);
    virtual void setDisplayInfo(DisplayInfo * info) {VOWindowVoutUtil::setDisplayInfo(info);};
    virtual void setTargetPlane(enum TargetPlane plane);
    virtual void setVOMixerServer(VOMixerServer * service);
    virtual void setResourceArbiter(ResourceArbiter * service);

    virtual int ResourceEvent(int /*notify*/) {return 0;};
    virtual void VsyncEvent(void);
private:
    class VOLayerScaleSub;
    class VOLayerScaleSub * mSUB1Order;
    class VOLayerScaleSub * mSUB2Order;
    int getTargetPlaneByProperty();
    bool                mState;
    pthread_mutex_t     mLock;
    int                 mTargetPlane;
};

#endif /* End of __RTK_HWC_LAYER_SCALE_H_ */
