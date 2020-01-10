#ifndef __RTK_HWC_VSYNC_LISTENER_H_
#define __RTK_HWC_VSYNC_LISTENER_H_
#include <hwc_utils.h>
class VsyncListener {
public:
    VsyncListener() {};
    virtual ~VsyncListener() {};

    virtual void VsyncEvent(void) = 0;
};
#endif /* End of __RTK_HWC_VSYNC_LISTENER_H_ */
