#ifndef __RTK_HWC_LAYER_OSD2_H_
#define __RTK_HWC_LAYER_OSD2_H_
#include "VOLayerBase.h"
#include <vowindow/VOWindowVoutUtil.h>
#include "hwlayer/osd2/Osd2Layer.h"
#include <arbiter/ResourceArbiter.h>
#include <property/HWCProperty.h>

class VOLayerOSD2 : public VOLayerBase,
    virtual public VOWindowVoutUtil,
    virtual public ResourceArbiter::Client,
    virtual public HWCProperty
{
public:
    VOLayerOSD2();
    virtual ~VOLayerOSD2();
    //virtual bool supportHwcLayer(hwc_layer_1_t * hwc_layer);
    virtual void prepare(void);
    virtual void set(void);
    virtual void dump(android::String8& buf, const char* prefix);
    virtual void setDisplayInfo(DisplayInfo * info) {VOWindowVoutUtil::setDisplayInfo(info);};
    virtual void setResourceArbiter(ResourceArbiter * service) {
        ResourceArbiter::Client::setResourceArbiter(service);
    };
    virtual int ResourceEvent(int notify);
    virtual void VsyncEvent(void);
private:
    void openLayer(void);
    void closeLayer(void);
    Osd2Layer * mHWLayer;
    bool mState;
    pthread_mutex_t     mLock;
    unsigned int        mTransform;
};

#endif /* End of __RTK_HWC_LAYER_OSD2_H_ */
