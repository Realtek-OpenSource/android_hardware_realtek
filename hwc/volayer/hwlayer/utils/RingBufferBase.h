#ifndef __RTK_HWC_HWLAYER_UTILS_RINGBUFFER_BASE_H_
#define __RTK_HWC_HWLAYER_UTILS_RINGBUFFER_BASE_H_
#include "hwlayer_utils.h"

#include <system/RingBuffer.h>

#include <RPCstruct.h>
#include <VideoRPC_System_data.h>
#include "../realtek_omx/osal_rtk/OSAL_RTK.h"
#include <rpc_common.h>
#include <InbandAPI.h>
#include <utils/Mutex.h>

class RingBufferBase {
public:
    enum LowDelayMode {
        LowDelayDef                 = LOW_DELAY_OFF,
        LowDelayOff                 = LOW_DELAY_OFF,
        LowDelayDecoder             = LOW_DELAY_DECODER,
        LowDelayDisplay             = LOW_DELAY_DISPLAY,
        LowDelayDecoderDisplay      = LOW_DELAY_DECODER_DISPLAY,
        LowDelayAVSync              = LOW_DELAY_AVSYNC,
        LowDelayDecoderAVSync       = LOW_DELAY_DECODER_AVSYNC,
    };
    class Client {
    public:
        Client():  mService(NULL) {};

        virtual ~Client() {
#if 0
            if (mService)
                mService->removeClient(this);
#endif
        };

        virtual void setRingBuffer(RingBufferBase* service = NULL) {
            if (service)
                service->registerClient(this);
            else if (mService)
                mService->removeClient(this);
        };

        unsigned int InbandCmd(int cmd_type, void *packet, unsigned int packet_size_in_bytes) {
            if (mService)
                return mService->InbandCmd(this, cmd_type, packet, packet_size_in_bytes);
            else
                return 0;
        };

        int ConfigLowDelay(enum LowDelayMode mode, int depth = 1, int init_frame = 1) {
            if(mService)
                return mService->ConfigLowDelay(this, mode, depth, init_frame);
            else
                return -1;
        };
        int SetDeintFlag(int flag) {
            if(mService)
                return mService->SetDeintFlag(this, flag);
            else
                return -1;
        };

        virtual void dump(android::String8& /*buf*/, const char* /*prefix*/) {};

    private:
        friend class RingBufferBase;
        RingBufferBase * mService;
    };

    RingBufferBase(unsigned int instanceID, CLNT_STRUCT clnt);
    virtual ~RingBufferBase();

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);

    unsigned int InbandCmd(Client * client, int cmd_type, void *packet, unsigned int packet_size_in_bytes);
    int ConfigLowDelay(Client * client, enum LowDelayMode mode, int depth = 1, int init_frame = 1);
    int SetDeintFlag(Client * client, int flag);

    unsigned int InbandCmd(int cmd_type, void *packet, unsigned int packet_size_in_bytes);
    int ConfigLowDelay(enum LowDelayMode mode, int depth = 1, int init_frame = 1);

private:
    unsigned int        sendInbandCmd(void *src, unsigned int cmd_size);
    unsigned int        recvInbandCmd(void *data, unsigned int size);
    int                 ConfigLowDelayDepth(int depth, int init_frame);
    int                 ConfigLowDelayMode(enum LowDelayMode mode);
    int                 SetDeintFlag(int flag);

    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;

    CLNT_STRUCT                     mClnt;
    unsigned int                    mInstanceID;
    size_t                          mICQBufferSize;
    pthread_mutex_t                 mLock;
    int                             mLowDelayMode;
    int                             mLowDelayDepth;
    int                             mInitFrame;
    int                             mDeintFlag;

    RingBuffer *                    mRingBuffer;
};

#endif /* End of __RTK_HWC_HWLAYER_UTILS_RINGBUFFER_BASE_H_ */
