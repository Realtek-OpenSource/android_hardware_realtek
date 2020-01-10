#ifndef _V4L2DEVICE2_CALLBACK_
#define _V4L2DEVICE2_CALLBACK_

#include "Base.h"

using namespace android;

namespace android {

class V4L2Device2Callback {

public:
    virtual ~V4L2Device2Callback();

    virtual void returnRequest(Request *r) = 0;

#if 0
    virtual void submitRequest(Request *r) = 0;
    virtual void submitErrorRequest(Request *r) = 0;
    virtual void onReturnAllRequests() = 0;
    virtual void onUpdateDeviceState() = 0;
#endif
};

}; // namespace android


#endif // _V4L2DEVICE2_CALLBACK_
