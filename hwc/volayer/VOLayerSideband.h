#ifndef __RTK_HWC_LAYER_SIDEBAND_H_
#define __RTK_HWC_LAYER_SIDEBAND_H_
#include "VOLayerBase.h"
#include <vowindow/VOWindowSideband.h>
#include <property/HWCProperty.h>
#include <SidebandClient.h>

class VOLayerSideband : public VOLayerBase,
    virtual public VOWindowSideband,
    virtual ResourceArbiter::Client,
    virtual HWCProperty
{
public:
    enum TargetPlane {
        FLIP_V1,
        FLIP_V2,
        FLIP_V3,
    };

    VOLayerSideband(enum TargetPlane plane = FLIP_V1);
    virtual ~VOLayerSideband();
    virtual bool supportHwcLayer(hwc_layer_1_t * hwc_layer, int layer);
    virtual void prepare();
    virtual void set();
    virtual void dump(android::String8& buf, const char* prefix);
    virtual void setDisplayInfo(DisplayInfo * info) {VOWindowSideband::setDisplayInfo(info);};
    virtual void setResourceArbiter(ResourceArbiter * service) {
        ResourceArbiter::Client::setResourceArbiter(service);
    };

    virtual int ResourceEvent(int /*notify*/) {return 0;};

    virtual void VsyncEvent(void);
private:
    int mTargetPlane;
    const native_handle_t * mSidebandStream;
    int64_t mKey; //To decide if layer was changed. if layer was changed, we need to reset window.
};
#endif /* End of __RTK_HWC_LAYER_SIDEBAND_H_ */
