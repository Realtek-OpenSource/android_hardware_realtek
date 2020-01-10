#ifndef __RTK_HWC_HWLAYER_OSD2_LAYER_H_
#define __RTK_HWC_HWLAYER_OSD2_LAYER_H_
#include <utils/LayerBase.h>
#include "Osd2Buffer.h"

class Osd2Layer :
    public  LayerBase,
    virtual GraphicBufferInfo::Client
{
public:
  using LayerBase::connect;
    Osd2Layer();
    virtual ~Osd2Layer();

    virtual int                 connect(enum VO_VIDEO_PLANE plane, int BufferCnt);
    virtual int                 disconnect();
    virtual BufferBase *        createBuffer();
    virtual void                removeBuffer(BufferBase * buffer);
    virtual enum VO_VIDEO_PLANE getPlane() {return mPlane;};
    virtual int                 validate(buffer_handle_t /*handle*/) {/* do nothing*/ return true;};
    virtual int                 getMaxBufferCount() {return mBufferCount;};
    virtual void                dump(android::String8& buf, const char* prefix) {return LayerBase::dump(buf, prefix);};

private:
    GraphicBufferInfo * mGBInfo;
    int mBufferCount;
    enum VO_VIDEO_PLANE mPlane;
};
#endif /* End of __RTK_HWC_HWLAYER_OSD2_LAYER_H_ */
