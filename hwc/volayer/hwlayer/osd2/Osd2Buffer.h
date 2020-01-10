#ifndef __RTK_HWC_HWLAYER_OSD2_BUFFER_H_
#define __RTK_HWC_HWLAYER_OSD2_BUFFER_H_
#include <utils/BufferBase.h>

class Osd2Buffer : public BufferBase {

public:
    Osd2Buffer();
    virtual ~Osd2Buffer();
    virtual int prepareBuffer_();
    virtual void queueBuffer_();
    virtual void cancelBuffer_();
    virtual bool releaseBufferCheck();
    virtual void removeBuffer();
    virtual void dump(android::String8& buf, const char* prefix = NULL);

private:
    virtual void releaseBuffer_();
    virtual void resetWin();

    //reference from VIDEO_GRAPHIC_PICTURE_OBJECT struct and remove INBAND_CMD_PKT_HEADER;
    struct OSD_STATE {
        //INBAND_CMD_PKT_HEADER header ;
        INBAND_CMD_GRAPHIC_FORMAT format ;
        unsigned int PTSH ;
        unsigned int PTSL ;
        unsigned int context ;  /* system can check it to know which picture displaying on VO */
        int colorkey ;          /* -1: disable colorkey */
        int alpha ;             /*  0: disable constant alpha */
        unsigned int x ;
        unsigned int y ;
        unsigned int width ;
        unsigned int height ;
        unsigned int address ;
        unsigned int pitch ;
        unsigned int address_right ;
        unsigned int pitch_right ;
        INBAND_CMD_GRAPHIC_3D_MODE picLayout ;
        unsigned int afbc ;
        unsigned int afbc_block_split ;
        unsigned int afbc_yuv_transform ;

    } mObj;

    enum Osd2BufferFlags {
        FILLYUV         = 0x1U <<  0,
        QUEUE_BUFFER    = 0x1U <<  1,
    };
    unsigned int mFlags;
    unsigned int mCtx;
};
#endif /* End of __RTK_HWC_HWLAYER_VIDEO_BUFFER_H_ */
