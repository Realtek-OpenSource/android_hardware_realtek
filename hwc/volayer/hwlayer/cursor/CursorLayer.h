#ifndef __RTK_HWC_HWLAYER_CURSOR_LAYER_H_
#define __RTK_HWC_HWLAYER_CURSOR_LAYER_H_
#include <utils/LayerBase.h>
#include "CursorBuffer.h"
#include "CursorTexture.h"
#include <display/DisplayInfo.h>

class CursorBuffer;

class CursorLayer :
    public LayerBase,
    virtual GraphicBufferInfo::Client
{
public:
  using LayerBase::connect;
    CursorLayer();
    virtual ~CursorLayer();

    virtual int                 connect(enum VO_VIDEO_PLANE plane, int BufferCnt);
    virtual int                 disconnect();
    virtual int                 render(buffer_handle_t handle, int *pFenceFd = NULL);
    virtual BufferBase *        createBuffer();
    virtual void                removeBuffer(BufferBase * buffer);
    virtual enum VO_VIDEO_PLANE getPlane() {return mPlane;};
    virtual int                 validate(buffer_handle_t handle);
    virtual int                 getMaxBufferCount() {return mBufferCount;};

    virtual void                setWindow(bool show) {mHide = !show;};
    virtual void                setWindow(int x, int y, int w, int h) {mX=x; mY=y; mW=w; mH=h;};
    virtual void                commitWindow() {return updateWindow();};

    virtual void                dump(android::String8& buf, const char* prefix);
    virtual void                setDisplayInfo(DisplayInfo::Client * client = NULL) {mDisplayInfo = client;};
    virtual DisplayInfo::Client * getDisplayInfo() {return mDisplayInfo;};
    void resetCursorWindow();
private:
    virtual void                updateWindow();

    GraphicBufferInfo * mGBInfo;
    android::Vector<CursorBuffer*> mCursorBufferList;
    pthread_mutex_t                mCursorListLock;
    CursorTexture * mTexture;
    int mBufferCount;
    enum VO_VIDEO_PLANE mPlane;
    bool mHide;
    int mX, mY, mW, mH;
    DisplayInfo::Client * mDisplayInfo;
};
#endif /* End of __RTK_HWC_HWLAYER_CURSOR_LAYER_H_ */
