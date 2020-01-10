#ifndef __CAMERA3_OMX_DECODE_HELPER__
#define __CAMERA3_OMX_DECODE_HELPER__

#include <utils/Errors.h>
#include "OMXDecodeHelperCallback.h"

using namespace android;

namespace androidcamera3 {

/**
 * A simple class to wrap decode mode
 * - via MediaCodec
 * - via OMX component directly
 */
class OMXDecodeHelper {

public:
    virtual                     ~OMXDecodeHelper();

    bool                        mDeviceRunning;

    virtual status_t            init() = 0;
    virtual status_t            start() = 0;
    virtual status_t            stop() = 0;
    virtual status_t            release() = 0;

protected:
    OMXDecodeHelperCallback *   mCallback;
    int32_t                     mFormat;
    int32_t                     mWidth;
    int32_t                     mHeight;

}; // OMXDecodeHelper

}; // namespace androidcamera3

#endif // __CAMERA3_OMX_DECODE_HELPER__
