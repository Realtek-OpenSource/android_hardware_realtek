#ifndef __RTK_HWC_HWLAYER_COLORLOOKUPTABLE_H_
#define __RTK_HWC_HWLAYER_COLORLOOKUPTABLE_H_

#include <utils/IonBuffer.h>

class ColorLookUpTable {
public:
    typedef struct PHY_YUVA_DATA {
        unsigned char Y;
        unsigned char Cb;
        unsigned char Cr;
        unsigned char Alpha;
    } __attribute__((packed,aligned(1))) tPhyYuvaData;

    static const int MaxColorRow = 16;
    static const int ColorRowSize = sizeof(tPhyYuvaData); /* Y, Cb, Cr, Alpha : 4 Byte */

    class PixelBuffer {
    public:
        enum ScalerType {
            tNORMAL = 0,
            tDOUBLE,
            tSEMI,
        };

        PixelBuffer();
        virtual ~PixelBuffer();

        virtual void setPixelBuffer(void * buffer, int format, int w, int h, int stride, enum ScalerType scalerType = tNORMAL);
        virtual bool isOverflow() {return mIsOverflow;};
        virtual void * getPixelBufferPhyAddr();
        virtual void * getPixelBufferVirAddr();
        virtual void * getPixelBufferTablePhyAddr();
        virtual void * getPixelBufferTableVirAddr();

        virtual int    getPixelBufferWidth() {return mW;};
        virtual int    getPixelBufferHeight() {return mH;};
        virtual int    getPixelBufferStride() {return mStride;};
        virtual int    getPixelBufferFormat() {return mFormat;};

        virtual void dump(android::String8& buf, const char* prefix = NULL);
    private:
        friend class ColorLookUpTable;
        void resetBuffer();
        void sortPixel();

        int getPixelSize() {
            if (mW == -1 || mH == -1 || mBuffer == NULL)
                return 0;
            return mW*mH;
        };
        void getYCbCrAlpha(int pixelOffset, tPhyYuvaData * data);
        unsigned char getIdByCLUT(int pixelOffset);

        struct PIXEL_ID_MAP {
            unsigned char internalID;
        };


        void * mBuffer;
        int mFormat, mW, mH, mStride;
        enum ScalerType mScalerType;
        bool mIsOverflow;
        tPhyYuvaData mPixelTable[MaxColorRow];
        int mPixelTableStep;
        ColorLookUpTable * mReleaseTable;
        struct PIXEL_ID_MAP * mPixelsIdMap;
        unsigned char mPixelTableIdMap[MaxColorRow]; // write by ColorLookUpTable
        IonBuffer * mStreamBuffer;
    };

    ColorLookUpTable();
    virtual ~ColorLookUpTable();

    int genStream(PixelBuffer * inBuffer);
    virtual void dump(android::String8& buf, const char* prefix = NULL);

private:
    friend class PixelBuffer;
    void releaseTable(PixelBuffer * inBuffer);
    int genTable(PixelBuffer * inBuffer);
    virtual int getColorRowOccupiedCnt();
    class ColorRow {
    public:
        ColorRow(void * virTableAddr, int index) {
            tPhyYuvaData * vAddr = (tPhyYuvaData *)virTableAddr;
            mIndex = index;
            mData = vAddr+index;
            mRefCount = 0;
        };
        void plusOne() { mRefCount++;};
        void minusOne() { if (mRefCount > 0) mRefCount--;};

        bool isOccupied() { return (mRefCount > 0)?true:false;};

        bool isMatchData(unsigned char Y, unsigned char Cb, unsigned char Cr, unsigned char Alpha) {
            if (mData == NULL) return false;
            if (mData->Y==Y && mData->Cb==Cb && mData->Cr==Cr && mData->Alpha==Alpha)
                return true;
            else
                return false;
        };
        bool isMatchData(tPhyYuvaData * data) {
            return isMatchData(data->Y, data->Cb, data->Cr, data->Alpha);
        };

        int getIndex() {return mIndex;};

        void setData(unsigned char Y, unsigned char Cb, unsigned char Cr, unsigned char Alpha) {
            if (mData == NULL) return;
            mData->Y=Y; mData->Cb=Cb; mData->Cr=Cr; mData->Alpha=Alpha;
        };
        void setData(tPhyYuvaData * data) {
            return setData(data->Y, data->Cb, data->Cr, data->Alpha);
        };
    private:
    friend class ColorLookUpTable;
        int mIndex;
        tPhyYuvaData * mData;
        int mRefCount;
    };
    IonBuffer * mPhyTableBuffer;
    ColorRow * mColorRow[MaxColorRow];

    pthread_mutex_t                 mBufferLock;
    android::Vector<PixelBuffer*>   mBufferList;
};

#endif /* End of __RTK_HWC_HWLAYER_COLORLOOKUPTABLE_H_ */
