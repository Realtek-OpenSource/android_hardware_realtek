#ifndef VOWB_CALLBACK_H
#define VOWB_CALLBACK_H

#include "CamBufDef.h"

using namespace android;

namespace android {

/**
 * This is a simple interface that defines which
 * functions a VOWBHelper callback should support.
 */
class VOWBCallback {
public:
    virtual ~VOWBCallback();
    virtual void returnSrcBuffer(allocator_info_t *pBuf) = 0;
    virtual void signalBufferAvailable() = 0;
};

}; // namespace android

#endif  // VOWB_CALLBACK_H
