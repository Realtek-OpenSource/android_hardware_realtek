#ifndef __RTK_HWC_HWLAYER_UTILS_LAYER_BASE_H_
#define __RTK_HWC_HWLAYER_UTILS_LAYER_BASE_H_
#include "hwlayer_utils.h"
#include "RingBufferBase.h"
#include "RefClockBase.h"
#include "BufferBase.h"


class LayerBaseRPC {
public:
    enum AgentType {
        AgentRun,
        AgentPause,
        AgentStop,
        AgentDestroy,
        AgentNum,
    };

    LayerBaseRPC();
    virtual ~LayerBaseRPC();

    virtual void            createInstance(enum VIDEO_VF_TYPE type);
    virtual int             toAgentDisplay(enum VO_VIDEO_PLANE plane);
    virtual int             toAgentState(enum AgentType cmd);
    virtual int             setRefClock(RefClockBase * refClock);

    virtual unsigned int        getInstance()   { return mInstance;};
    virtual enum VO_VIDEO_PLANE getPlane()      { return mPlane;};
    virtual CLNT_STRUCT         getClint()      { return mClnt;};

private:
    CLNT_STRUCT             mClnt;
    unsigned int            mInstance;
    enum VO_VIDEO_PLANE     mPlane;
};

/********************************************************************************************/

class LayerBase {
public:
    /* user operated */
    LayerBase();
    virtual ~LayerBase();
    virtual int                 connect();
    virtual int                 disconnect();
    virtual int                 render(buffer_handle_t handle, int *pFenceFd = NULL);
    virtual int                 freeze(bool enable, bool lock = false);
    virtual bool                releaseLoop();
    virtual void                dump(android::String8& buf, const char* prefix);
    virtual bool                isConnect() {return mConnect;};

    /* need to be implemented */
    virtual BufferBase *        createBuffer() = 0;
    virtual void                removeBuffer(BufferBase * buffer) = 0;
    virtual enum VO_VIDEO_PLANE getPlane() = 0;
    virtual int                 validate(buffer_handle_t handle) = 0;
    virtual int                 getMaxBufferCount() = 0;

    /* Buffer api */
    virtual BufferBase *        dequeueBuffer();
    virtual void                queueBuffer(BufferBase * buffer);
    virtual void                cancelBuffer(BufferBase * buffer);
    virtual BufferBase *        getLastRenderedBuffer(int stackCnt = 0);
    virtual BufferBase *        getFrontRenderedBuffer(int stackCnt = 0);
    virtual int                 getRenderedBufferCount();
    virtual void                releaseBuffer(BufferBase * buffer);

    virtual void                lock() {pthread_mutex_lock(&mLock);};
    virtual void                unlock() {pthread_mutex_unlock(&mLock);};
private:
    class BufferSlot {
    public:
        enum BufferSlotState {
            DEQUEUE,
            QUEUE,
            FREE,
        };

        BufferSlot(BufferBase * buffer, LayerBase * layer)
            : mBuffer(buffer),
            mLayer(layer),
            mContext(0),
            mState(FREE) {};

        virtual ~BufferSlot() {
            mBuffer->removeBuffer();
            mLayer->removeBuffer(mBuffer);
        };

        BufferBase * mBuffer;
        LayerBase * mLayer;
        unsigned long long mContext;
        enum BufferSlotState mState;
    };

    bool                    mConnect;
    pthread_mutex_t         mLock;
    LayerBaseRPC *          mRPC;

    bool        loop();
    struct      LooperThread;
    android::sp<LooperThread> mThread;

    /* Service */
    RingBufferBase *        mRingBuffer;
    RefClockBase *          mRefClock;
    SWFence *               mSWFence;
    GraphicBufferInfo *     mGBInfo;

    /* Buffer List */
    pthread_mutex_t                 mBufferLock;
    android::Vector<BufferSlot*>    mBufferList;
    unsigned long long              mBufferContext;
};

#endif /* End of __RTK_HWC_HWLAYER_UTILS_LAYER_BASE_H_ */
