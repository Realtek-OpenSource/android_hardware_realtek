#ifndef __RTK_HWC_RESOURCEARBITER_H_
#define __RTK_HWC_RESOURCEARBITER_H_
#include <hwc_utils.h>
#include <utils/Vector.h>

#define DEFAULT_PRIORITY 100

class ResourceArbiter {
public:
    class Client {
    public:
        enum Sort {
            V1_Window = 0,
            V2_Window,
            OSD1_Window,
            SUB1_Window,
            SUB2_Window,
            NONE_Window,
        };

        Client(uint32_t sort = NONE_Window, uint32_t priority = DEFAULT_PRIORITY)
            : mSort(sort),
            mPriority(priority),
            mResourceOwner(false),
            mService(NULL) {};

        virtual ~Client() {
            if (mService!=NULL)
                mService->removeClient(this);
        };

        /* Client Side */
        void setResourceArbiter(ResourceArbiter * service) {
            if (service)
                service->registerClient(this);
        };

        virtual bool getResourceState() {
            if (mService == NULL) return false;
            return isOwner();
        };

        virtual bool requestResource() {
            if (mService == NULL) return false;
            if (isOwner()) return true;
            return mService->requestResource(this);
        };

        virtual void releaseResource() {
            if (mService!=NULL)
                mService->releaseResource(this);
        };

        virtual uint32_t getSort() {
            return mSort;
        };

        virtual void setPriority(uint32_t priority) {
            mPriority = priority;
        };

        virtual void setSort(uint32_t sort) {
            if (sort != mSort) {
                if (mService != NULL)
                    mService->changeSort(this, sort);
                else
                    mSort = sort;
            }
        };

        /*virtual*/ void dump(android::String8& buf, const char* prefix);


        enum NotifyEvent {
            RESOURCE_RECOVERY,
            RESOURCE_OWNER_CHANGE,
        };

        virtual int ResourceEvent(int notify) = 0;

    private:
        friend class ResourceArbiter;
        /* Server Side */

        bool isOwner() {
            return mResourceOwner;
        };

        void setOwner() {
            mResourceOwner = true;
        };

        void clearOwner() {
            mResourceOwner = false;
        };

        void stopOwner() {
            ResourceEvent(RESOURCE_RECOVERY);
            clearOwner();
        };

        void notifyOwnerChange() {
            ResourceEvent(RESOURCE_OWNER_CHANGE);
        };

        uint32_t getPriority() {
            return mPriority;
        };

        uint32_t            mSort;
        uint32_t            mPriority;
        bool                mResourceOwner;
        ResourceArbiter *   mService;
    };

    /* Server */
    ResourceArbiter();
    virtual ~ResourceArbiter();

    virtual void registerClient(Client * client);
    virtual void removeClient(Client * client);

    virtual bool requestResource(Client * client);
    virtual void releaseResource(Client * client);
    virtual void changeSort(Client * client, uint32_t sort);
    virtual void dump(android::String8& buf, const char* prefix);
private:
    bool isOwnedByUs(Client * client);
    pthread_mutex_t mLock;
    android::Vector<Client*> mList;;
};

#endif /* End of __RTK_HWC_RESOURCEARBITER_H_ */
