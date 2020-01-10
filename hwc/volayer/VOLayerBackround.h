#ifndef __RTK_HWC_LAYER_BACKROUND_H_
#define __RTK_HWC_LAYER_BACKROUND_H_
#include "VOLayerBase.h"
class VOLayerBackround : public VOLayerBase {
public:
    VOLayerBackround();
    virtual ~VOLayerBackround();

    virtual void prepare();
    virtual void set();
    virtual void dump(android::String8& buf, const char* prefix);
};

#endif /* End of __RTK_HWC_LAYER_BACKROUND_H_ */
