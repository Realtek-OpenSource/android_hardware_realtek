/*
 * SeAPI.h
 *
 *  Created on: Mar 24, 2014
 *      Author: charleslin
 */

#ifndef SEAPI_H_
#define SEAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "OSAL.h"
#include "hresult.h"
#include "se.h"
#include "SeLib.h"

HRESULT
SE_FormatConv(  /*SURFACEHANDLE handleDes,*/
    int nXDest,
    int nYDest,
    int nWidth,
    int nHeight,
    /*SURFACEHANDLE handleSrc,*/
    int nXSrc,
    int nYSrc,
    PIXEL_FORMAT dstpixelFormat,
    PIXEL_FORMAT srcpixelFormat,
    unsigned int dstPAddr, unsigned int srcPAddr,
    bool bIsSrcColorKey,
    bool bIsConstAlpha,
    uint8_t alpha,
    HANDLE hQueue,
    uint32_t colorKey);

HRESULT
SE_BitBlt_API(  //SURFACEHANDLE handleDes,
        unsigned int dstPAddr, unsigned int srcPAddr,
            int nXDest,
            int nYDest,
            int nWidth,
            int nHeight,
            int bgWidth,
//          SURFACEHANDLE handleSrc,
            int srcColor,
            int nXSrc,
            int nYSrc,
            int ropCode,
            HANDLE hQueue,
            SEINFO_CORNER corner);

HRESULT
SE_CopyEx_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int nXDest,
            int nYDest,
            int nWidth,
            int nHeight,
            int nXSrc,
            int nYSrc,
            HANDLE hQueue);

HRESULT
SE_Memcpy_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int size,
            HANDLE hQueue);

HRESULT
SE_2DMemcpy_API( unsigned int dstPAddr, unsigned int srcPAddr,
        int nDstStride,
        int nDstSliceHeight,
        int nSrcStride,
        int nSrcSliceHeight,
        int nWidth,
        int nHeight,
        HANDLE hQueue);

HRESULT
SE_2DMemcpyByteSwap_API( unsigned int dstPAddr, unsigned int srcPAddr,
        int nDstStride,
        int nDstSliceHeight,
        int nSrcStride,
        int nSrcSliceHeight,
        int nWidth,
        int nHeight,
        HANDLE hQueue);

HRESULT
SE_Scaler_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int nDestWidht,
            int nDestHeight,
            int nSrcWidth,
            int nSrcHeight,
            HANDLE hQueue,
            unsigned int interlace);

HRESULT
SE_Scaler_API_Dst_No_Align ( unsigned int dstPAddr, unsigned int srcPAddr,
            int nDestWidht,
            int nDestHeight,
            int nSrcWidth,
            int nSrcHeight,
            HANDLE hQueue,
            unsigned int interlace);

HRESULT
SE_HdmiRxYuv422ToYuyv_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int nDestWidth,
            int nDestHeight,
            int nSrcWidth,
            int nSrcHeight,
            HANDLE hQueue);

HRESULT
SE_HdmiRxYuv422ToYuv420_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int nDestWidth,
            int nDestHeight,
            int nSrcWidth,
            int nSrcHeight,
            HANDLE hQueue);

HRESULT
SE_Yuv422ToYuv420_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int nDestWidth,
            int nDestHeight,
            int nSrcWidth,
            int nSrcHeight,
            HANDLE hQueue);

HRESULT
SE_JpegYuv422ToYuv420_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int nWidth,
            int nHeight,
            HANDLE hQueue);

HRESULT SE_ArgbToYuv420_API(unsigned int dstPAddr, unsigned int srcPAddr,
	        int nWidth, int nHeight,
	        HANDLE hQueue);

#ifdef __cplusplus
}
#endif

#endif /* SEAPI_H_ */
