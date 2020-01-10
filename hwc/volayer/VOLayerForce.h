#ifndef __RTK_HWC_LAYER_FORCE_H_
#define __RTK_HWC_LAYER_FORCE_H_
#include "VOLayerBase.h"
#include <vowindow/VOWindowVoutUtil.h>
#include <arbiter/ResourceArbiter.h>
#include <property/HWCProperty.h>


class VOLayerForce : public VOLayerBase,
    virtual public VOWindowVoutUtil,
    virtual public ResourceArbiter::Client,
    virtual public HWCProperty
{
public:
    VOLayerForce();
    virtual ~VOLayerForce();
    virtual bool supportHwcLayer(hwc_layer_1_t * hwc_layer, int layer);
    virtual void prepare(void);
    virtual void set(void);

    virtual void VsyncEvent(void);

    virtual void setDisplayInfo(DisplayInfo * info) {VOWindowVoutUtil::setDisplayInfo(info);};
    virtual void setResourceArbiter(ResourceArbiter * service) {
        ResourceArbiter::Client::setResourceArbiter(service);
    };
    virtual int ResourceEvent(int notify);
    virtual void dump(android::String8& buf, const char* prefix);
private:
    bool needToReguest(void);
    bool needToUpdateState(void);
    void updateState(void);

    bool mResourceGet;
    int mCheckCount;
    int mCheckRecount;
};

#endif /* End of __RTK_HWC_LAYER_FORCE_H_ */
