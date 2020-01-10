#ifndef __RTK_HWC_HWLAYER_CURSOR_BUFFER_H_
#define __RTK_HWC_HWLAYER_CURSOR_BUFFER_H_
#include <utils/BufferBase.h>
#include "CursorTexture.h"
#include <VoutUtil.h>
#include <hwc_utils.h>
#include "CursorLayer.h"

class CursorLayer;
class CursorBuffer : public BufferBase,
    virtual public CursorTexture::Client
{
public:
    class CoordinateObject : public ExtBuffer
    {
    public:
      using GraphicBufferInfo::Client::ExtBuffer::replica;
        CoordinateObject()
            : mX(0), mY(0), mHide(false), mTimestamp(0), isInvalid(false) {};
        virtual ~CoordinateObject() {};
        virtual void replica(const CoordinateObject * buffer) {
            ExtBuffer::replica(buffer);
            this->isInvalid = true; /* the CoordinateObject is not support the replica function*/
        };
        virtual CoordinateObject * replica() {
            CoordinateObject * buffer = new CoordinateObject();
            buffer->replica(this);
            return buffer;
        };

        virtual void setWin(int x, int y) { mX = x; mY=y;};
        virtual void setHide(bool hide) { mHide = hide;};
        virtual void setPTS(int64_t timestamp) { mTimestamp=timestamp;};
    private:
        friend class CursorBuffer;
        int mX;
        int mY;
        bool mHide;
        int64_t mTimestamp;
        bool isInvalid;
    };

    CursorBuffer();
    virtual ~CursorBuffer();
    virtual void removeBuffer();
    virtual int prepareBuffer_();
    virtual void queueBuffer_();
    virtual void cancelBuffer_();
    virtual bool releaseBufferCheck();
    virtual void dump(android::String8& buf, const char* prefix = NULL);

    virtual void setLayer(CursorLayer * layer = NULL) {mLayer = layer;};
    void resetWindowRatio();
private:
    int getWindowBase(hwc_rect_t* rect);
    int getFramebufferBase(hwc_rect_t* rect);
    int updateWindowRatio();
    enum ColorLookUpTable::PixelBuffer::ScalerType getScalerType();
    int prepareBuffer_picture();
    int prepareBuffer_coordinate();
    void resetCursorBufferState();

    /*
     * cmd type : VIDEO_CURSOR_INBAND_CMD_TYPE_PICTURE_OBJECT
     * data struct : VIDEO_CSR_PICTURE_OBJECT
     */
    struct CURSOR_PICTURE_OBJECT {
        unsigned int context;
        unsigned int width;
        unsigned int height;
        unsigned int /*INBAND_CMD_GRAPHIC_FORMAT*/ colorFmt;
        unsigned int address;
        unsigned int address_right;
        unsigned int clut_address;
        unsigned int PTSH;
        unsigned int PTSL;
        unsigned int reserved[4];
    } mPictureObject;

    /*
     * cmd type : VIDEO_CURSOR_INBAND_CMD_TYPE_COORDINATE_OBJECT
     * data struct : VIDEO_CSR_COORDINATE_OBJECT
     */
    struct CURSOR_COORDINATE_OBJECT {
          unsigned int hide;
          unsigned int context;
          unsigned int x;
          unsigned int y;
          unsigned int PTSH;
          unsigned int PTSL;
          unsigned int reserved[4];
    } mCoordinateObject;

    enum BufferType {
        tNONE = 1U <<0,
        tPICTURE = 1U <<1,
        tCOORDINATE = 1U<<2,
        tQUEUE = 1U <<3,
    } mType;

    unsigned int mReleaseContext;
    VoutUtil * mVOutCtrl;
    float mWidthRatio, mHeightRatio;
    class CursorLayer * mLayer;
    bool mWindowRatioIsReady;
};

#endif /* End of __RTK_HWC_HWLAYER_CURSOR_BUFFER_H_ */
