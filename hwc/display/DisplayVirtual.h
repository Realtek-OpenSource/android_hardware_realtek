#ifndef __RTK_HWC_DISPLAY_VIRTUAL_H_
#define __RTK_HWC_DISPLAY_VIRTUAL_H_

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

class DisplayVirtual : public Display,
    virtual public Vsync::Client,
    virtual public Power::Client,
    virtual public HWCProperty
{
public:

    DisplayVirtual(Vsync * vsync, HWCCallbacks * callbacks);
    virtual ~DisplayVirtual();

private:
    pthread_mutex_t         mLayerLock;

};

#endif /* End of __RTK_HWC_DISPLAY_VIRTUAL_H_ */
