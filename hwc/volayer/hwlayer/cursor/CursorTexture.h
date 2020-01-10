#ifndef __RTK_HWC_HWLAYER_CURSOR_TEXTURE_H_
#define __RTK_HWC_HWLAYER_CURSOR_TEXTURE_H_

#include "ColorLookUpTable.h"

class CursorTexture {
public:
    class Client : virtual public ColorLookUpTable::PixelBuffer {
    public:
        Client();
        virtual ~Client();

        virtual void setCursorTexture(CursorTexture * service = NULL) {
            if (service) {
                service->registerClient(this);
            } else if (mService != NULL) {
                mService->removeClient(this);
            }
        };
        virtual int setCursorTextureBuffer(void * buffer, int format, int w, int h, int stride,
                enum ColorLookUpTable::PixelBuffer::ScalerType scalerType = tNORMAL);
        virtual void * getCursorTexturePhyAddr();
        virtual void * getCursorTextureVirAddr();
        virtual void * getCursorTextureTablePhyAddr();
        virtual void * getCursorTextureTableVirAddr();
        virtual int    getCursorTextureWidth() {return getPixelBufferWidth();};
        virtual int    getCursorTextureHeight() {return getPixelBufferHeight();};
        virtual int    getCursorTextureStride() {return getPixelBufferStride();};
        virtual int    getCursorTextureFormat() {return getPixelBufferFormat();};
        virtual void dump(android::String8& buf, const char* prefix = NULL);

    private:
        friend class CursorTexture;
        CursorTexture * mService;
    };

    CursorTexture();
    virtual ~CursorTexture();

    virtual void registerClient     (Client * client);
    virtual void removeClient       (Client * client);

    virtual int genStream           (Client * client);
    virtual void dump(android::String8& buf, const char* prefix = NULL);

private:
    unsigned long MAX_CLUT;


    pthread_mutex_t                 mLock;
    pthread_mutex_t                 mClientLock;
    android::Vector<Client*>        mClientList;

    pthread_mutex_t                     mCLUTLock;
    android::Vector<ColorLookUpTable*>  mCLUTList;
};

#endif /* End of __RTK_HWC_HWLAYER_CURSOR_TEXTURE_H_ */
