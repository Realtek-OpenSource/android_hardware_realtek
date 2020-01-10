#ifndef __RTK_HWC_HWLAYER_UTILS_BUFFER_BASE_H_
#define __RTK_HWC_HWLAYER_UTILS_BUFFER_BASE_H_
#include "hwlayer_utils.h"
#include "SWFence.h"
#include "GraphicBufferInfo.h"
#include "RingBufferBase.h"
#include "RefClockBase.h"

class BufferBase :
    virtual public GraphicBufferInfo::Client,
    virtual public SWFence::Client,
    virtual public RingBufferBase::Client,
    virtual public RefClockBase::Client {
public:

    BufferBase();
    virtual ~BufferBase();

    virtual void dump(android::String8& buf, const char* prefix = NULL);

    /*
     * Flow
     *  1. prepare(DEQUEUE) => queue(QUEUE) => release(FREE)
     *  2. prepare(DEQUEUE) => cancel(FREE)
     */

    virtual int prepareBuffer(buffer_handle_t handle);
    virtual int prepareBuffer(ExtBuffer * extBuffer);
    virtual int prepareBuffer(BufferBase * buffer); // for replica case
    virtual int prepareBuffer_() = 0;

    virtual void queueBuffer();
    virtual void queueBuffer_() = 0;

    virtual void cancelBuffer();
    virtual void cancelBuffer_() = 0;

    virtual int releaseBuffer();
    virtual bool releaseBufferCheck() = 0;

    virtual bool matchBuffer(buffer_handle_t handle) {
        return (getBufferHandle() == handle)?true:false;
    };

    virtual void removeBuffer();
    virtual void setBufferId(unsigned int id){
       mBufferId = id;
    }

    virtual unsigned int getBufferId(){
       return mBufferId;
    }

private:
    enum BufferState {
        FREE,
        DEQUEUE,
        QUEUE,
    };
    pthread_mutex_t                 mLock;
    enum BufferState                mState;
    unsigned int                   mBufferId;
};

#endif /* End of __RTK_HWC_HWLAYER_UTILS_BUFFER_BASE_H_ */
