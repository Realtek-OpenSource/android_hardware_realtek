#ifndef __RTK_HWC_HWLAYER_VIDEO_DEBUGMESSAGE_H_
#define __RTK_HWC_HWLAYER_VIDEO_DEBUGMESSAGE_H_
#include "hwlayer_utils.h"

class DebugMessage {
public:
    class Client {
    public:
	struct debug_message {
		int display_time;
		int release_time;
		int display_cnt;
		int drop_cnt;
		unsigned int context;
		float timestamp;
		unsigned int bufferId;
	};

        Client():mService(NULL){};
        virtual ~Client() {};
        virtual void setDebugMessage(DebugMessage * service = NULL) {
            if (service)
                service->registerClient(this);
            else if (mService)
                mService->removeClient(this);
        };
        virtual void updataATraceInfo(struct debug_message *message) {
            if (mService)
                return mService->updataATraceInfo(this, message);
        };
    private:
        friend class DebugMessage;
        DebugMessage * mService;
        //bool atrace_start;
    };

    DebugMessage():atrace_start(false){};
    DebugMessage(enum VO_VIDEO_PLANE plane):atrace_start(false),mPlane(plane){};
    virtual ~DebugMessage();

    virtual void registerClient     (Client * client){
	client->mService = this;
    };
    virtual void removeClient       (Client * client){
	client->mService = NULL;
    };

    virtual void updataATraceInfo(Client * client, struct Client::debug_message *message);
    virtual const char *getPlaneInfo();
private:
    bool atrace_start;
    enum VO_VIDEO_PLANE mPlane;
};
#endif

