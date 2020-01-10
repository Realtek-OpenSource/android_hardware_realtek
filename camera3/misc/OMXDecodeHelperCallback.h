#ifndef __CAMERA3_OMX_DECODE_HELPER_CALLBACK__
#define __CAMERA3_OMX_DECODE_HELPER_CALLBACK__

#include <utils/Timers.h>
#include <utils/Errors.h>

using namespace android;

namespace androidcamera3 {

class OMXDecodeHelperCallback {

public:
    virtual ~OMXDecodeHelperCallback();

    /**
     * Callback to fill this Buffer, blocking mode
     * - vAddr      : virtual address
     * - phyAddr    : physical address
     * - capacity   : buffer size
     * - pts        : frame pts, set by callback
     * - range      : actual data range, set by Callback
     *
     * Return value : OK or ERROR
     */
    virtual status_t onInputBufferAvailable(
        uint8_t *vAddr,
        int32_t phyAddr,
        size_t capacity,
        nsecs_t *pts,
        size_t *range) = 0;

    /**
     * Callback to consume output buffer, blocking mode
     * - vAddr    : virtual address
     * - phyAddr  : physical address
     * - range    : data range
     * - pts      : buffer pts
     */
    virtual status_t onOutputBufferAvailable(
        uint8_t *vAddr,
        int32_t phyAddr,
        size_t range,
        nsecs_t pts) = 0;

};

};


#endif
