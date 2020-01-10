#ifndef __RTK_HWC_DISPLAY_PRIMARY_H_
#define __RTK_HWC_DISPLAY_PRIMARY_H_

#include <map>
#include <set>
#include <hwc_utils.h>
#include <volayer/VOLayerBase.h>
#include <vsync/Vsync.h>
#include <callbacks/Callbacks.h>
#include <arbiter/ResourceArbiter.h>
#include <power/Power.h>
#include "DisplayInfo.h"
#include <vowindow/VOWindowBase.h>
#include <property/HWCProperty.h>
#include <vowindow/VOMixerServer.h>
#include <layer/Layer.h>
#include "Display.h"

class VOWindowBase;
class Layer;

class DisplayPrimary : public Display,
    virtual public Vsync::Client,
    virtual public Power::Client,
    virtual public HWCProperty
{
public:
    DisplayPrimary(Vsync * vsync, HWCCallbacks * callbacks);
    virtual ~DisplayPrimary();
    virtual void VsyncEvent();
private:
    VOWindowBase *          mDisplayWindow; //framebuffer target
    pthread_mutex_t         mLayerLock;
    android::Vector<VOLayerBase*> layerList;

};

#endif /* End of __RTK_HWC_DISPLAY_PRIMARY_H_ */
