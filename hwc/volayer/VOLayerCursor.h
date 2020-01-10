#ifndef __RTK_HWC_LAYER_CURSOR_H_
#define __RTK_HWC_LAYER_CURSOR_H_
#include "VOLayerBase.h"
#include <vowindow/VOWindowCursor.h>
#include <cursor/CursorLayer.h>
#include <property/HWCProperty.h>

class VOLayerCursor : public VOLayerBase,
    virtual public VOWindowCursor,
    virtual HWCProperty
{
public:
    VOLayerCursor();
    virtual ~VOLayerCursor();
    virtual bool supportHwcLayer(hwc_layer_1_t * hwc_layer, int layer);
    virtual void prepare(void);
    virtual void set(void);
    virtual void dump(android::String8& buf, const char* prefix);

    virtual void setDisplayInfo(DisplayInfo * info) {VOWindowCursor::setDisplayInfo(info);};

    virtual void DisplayInfoEvent(int cmd, int ext);
private:
    void openLayer(void);
    void closeLayer(void);
    CursorLayer * mCursor;
    int mState;
};

#endif /* End of __RTK_HWC_LAYER_CURSOR_H_ */
