#ifndef __CAMERA3_OMXCOMPONENT_DECODE_HELPER__
#define __CAMERA3_OMXCOMPONENT_DECODE_HELPER__

#include <utils/List.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/SortedVector.h>
#include <utils/Mutex.h>
#include <utils/threads.h>
#include <OMX_Core.h>
#include <OMX_Component.h>
#include "OMXDecodeHelper.h"

#define ALLOCATOR_BUF_NUM       (32)

namespace androidcamera3 {

class OMXComponentDecodeHelper : public OMXDecodeHelper {

public:

    struct OMXEvent {
        inline OMXEvent(OMX_EVENTTYPE eEvent,
            OMX_U32 nData1,
            OMX_U32 nData2,
            OMX_PTR pEventData)
            : event(eEvent),
            data1(nData1),
            data2(nData2),
            ptr(pEventData) { }
        const char * describe() const;
        OMX_EVENTTYPE event;
        OMX_U32 data1;
        OMX_U32 data2;
        OMX_PTR ptr;
    };

    typedef struct _GrallocBufInfo {
        void *                  vAddr;
        size_t                  size;
        uint32_t                phyAddr;
        buffer_handle_t         buffer;
        OMX_BUFFERHEADERTYPE *  omx_buffer;
    } GrallocBufInfo;

    struct Connection {
        inline Connection(OMXComponentDecodeHelper *_component,
            int _componentPort,
            int _port)
        : port(_port),
          componentPort(_componentPort),
          component(_component) { }
        int port;
        int componentPort;
        OMXComponentDecodeHelper *component;
    };

    /**
     * Internal Event thread
     */
    class EventThread : public Thread {
    public:
        EventThread(OMXComponentDecodeHelper *parent);
        ~EventThread();
        void stop() { mRunning = false; }
    private:
        virtual bool                threadLoop();
        OMXComponentDecodeHelper *  mParent;
        bool                        mRunning;
    };

    /**
     * Fill input buffer thread
     */
    class InputBufferThread : public Thread {
    public:
        InputBufferThread(OMXComponentDecodeHelper *parent);
        ~InputBufferThread();
        void stop() { mRunning = false; }
    private:
        virtual bool                threadLoop();
        OMXComponentDecodeHelper *  mParent;
        bool                        mRunning;
    };

    OMXComponentDecodeHelper (
        OMXDecodeHelperCallback *callback,
        int32_t format,
        int w,
        int h);

    ~OMXComponentDecodeHelper();

    status_t                        init();
    status_t                        start();
    status_t                        stop();
    status_t                        release();

private:

    const char *                    mComponentName;
    OMX_VIDEO_CODINGTYPE            mCodecType;

    bool                            mExecuting;
    void *                          mDlHandle;

    sp<EventThread>                 mEventThread;
    sp<InputBufferThread>           mInputBufferThread;

    OMX_CALLBACKTYPE                mOMXCallbacks;
    OMX_HANDLETYPE                  mHandle;

    // port index
    int32_t                         mInput;
    int32_t                         mOutput;

    List<Connection>                mConnections;
    List<OMXEvent>                  mEvents;

    Vector<OMX_BUFFERHEADERTYPE*>   mInputBuffers;
    Vector<OMX_BUFFERHEADERTYPE*>   mOutputBuffers;

    Mutex                           mInBufferLock;
    Mutex                           mOutBufferLock;
    Mutex                           mEventLock;

    Condition                       mEventCondition;
    Condition                       mInputBufferCondition;
    Condition                       mOutputBufferCondition;

    GrallocBufInfo                  mGrallocBufs[ALLOCATOR_BUF_NUM];
    GrallocWrapper *                pGrallocWrapper;

    OMX_PARAM_PORTDEFINITIONTYPE    in_port_def;
    OMX_PARAM_PORTDEFINITIONTYPE    out_port_def;

    // OMX component so callback
    OMX_ERRORTYPE                   (*omx_init) (void);
    OMX_ERRORTYPE                   (*omx_deinit) (void);
    OMX_ERRORTYPE                   (*omx_get_handle) (
                                        OMX_HANDLETYPE * handle,
                                        OMX_STRING name,
                                        OMX_PTR data,
                                        OMX_CALLBACKTYPE * callbacks);

    OMX_ERRORTYPE                   (*omx_free_handle) (OMX_HANDLETYPE handle);

    void                            allocateGrallocBuf(size_t reqSize, size_t bufNum);
    void                            releaseGrallocBuf();

    void                            process_event(void);
    void                            process_decode(void);

    bool                            enablePort(uint32_t port);
    bool                            disablePort(uint32_t port);

    void                            cleanupBuffers();

    int                             initInputBuffers(int port = -1);
    int                             initOutputBuffers(int port = -1);
    int                             initOutputBuffers2(int port = -1);

    void                            removeThreads();

    bool                            emptyBuffer(OMX_BUFFERHEADERTYPE *);
    bool                            fillBuffer(OMX_BUFFERHEADERTYPE *);

    void                            flush(int port);

    void                            cleanupOutputBuffer(int32_t port = -1);
    void                            cleanupOutputBuffer2(int32_t port = -1);
    void                            cleanupInputBuffers(int32_t port = -1);

    bool                            waitForCommandComplete(OMX_COMMANDTYPE command,
                                        OMX_U32 nData,
                                        nsecs_t wait = 0);

    void                            get_omx_port_definition(int port_index,
                                        OMX_PARAM_PORTDEFINITIONTYPE * port_def);

    void                            update_omx_port_definition(int port_index,
                                        OMX_PARAM_PORTDEFINITIONTYPE * port_def);

    void                            get_omx_video_param(int port_index,
                                        OMX_VIDEO_PARAM_PORTFORMATTYPE *format);

    void                            update_omx_video_param(int port_index,
                                        OMX_VIDEO_PARAM_PORTFORMATTYPE *format);

    bool                            setState(OMX_STATETYPE state);
    inline OMX_HANDLETYPE           handle() const { return mHandle; }

    OMX_BUFFERHEADERTYPE *          inputBuffer();
    OMX_BUFFERHEADERTYPE *          outputBuffer();

    inline int32_t                  inputPort() const { return mInput; }
    inline int32_t                  outputPort() const { return mOutput; }

    // inner omx callback functions
    OMX_ERRORTYPE                   eventHandler(OMXEvent);
    void                            filledBuffer(OMX_BUFFERHEADERTYPE *buffer);
    void                            emptiedBuffer(OMX_BUFFERHEADERTYPE *buffer);

    // OMX-IL callback
    static OMX_ERRORTYPE            omxil_EventHandler(OMX_HANDLETYPE,
                                        OMX_PTR pAppData,
                                        OMX_EVENTTYPE eEvent,
                                        OMX_U32 nData1,
                                        OMX_U32 nData2,
                                        OMX_PTR pEventData);

    // a input buffer is used
    static OMX_ERRORTYPE            omxil_EmptyBufferDone(OMX_HANDLETYPE,
                                        OMX_PTR pAppData,
                                        OMX_BUFFERHEADERTYPE* pBuffer)
    {
        ((OMXComponentDecodeHelper*)pAppData)->emptiedBuffer(pBuffer);
        return OMX_ErrorNone;
    }

    // a output buffer is ready
    static OMX_ERRORTYPE            omxil_FillBufferDone(OMX_HANDLETYPE,
                                        OMX_PTR pAppData,
                                        OMX_BUFFERHEADERTYPE* pBuffer)
    {
        ((OMXComponentDecodeHelper*)pAppData)->filledBuffer(pBuffer);
        return OMX_ErrorNone;
    }

};

}; // namespace androidcamera3

#endif
