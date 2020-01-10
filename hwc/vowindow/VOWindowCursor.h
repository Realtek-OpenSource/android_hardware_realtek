#ifndef __RTK_HWC_VO_WINDOW_API_CURSOR_H_
#define __RTK_HWC_VO_WINDOW_API_CURSOR_H_
#include "VOWindowBase.h"
#include <cursor/CursorLayer.h>
class VOWindowCursor : public VOWindowBase
{
public:
    VOWindowCursor();
    virtual ~VOWindowCursor();
    virtual int updateWindow();

    virtual void setCursor(CursorLayer * layer = NULL) {
        mLayer = layer;
        if (mLayer != NULL)
            mLayer->setDisplayInfo(this);
    };
private:
    pthread_mutex_t mLock;
    CursorLayer * mLayer;
};

#endif /* End of __RTK_HWC_VO_WINDOW_API_CURSOR_H_ */
