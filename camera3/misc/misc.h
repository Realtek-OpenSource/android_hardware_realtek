#ifndef _CAMERA_MISC_H
#define _CAMERA_MISC_H

#include "Common.h"

#define ROUNDUP(x, base)        ((x + base - 1) & ~(base - 1))
#define ROUNDUP16(x)            ROUNDUP(x, 16)
#define FCC2ASCII(fmt)          ((char *)(&fmt))[0], ((char *)(&fmt))[1], ((char *)(&fmt))[2], ((char *)(&fmt))[3]

namespace android {

int getHDMIRxStatus(HDMIRX_STATUS *pStatus);
int getHDMITxStatus(HDMITX_STATUS *pStatus);
//int CameraFmtToV4L2(const char *fmt);
const char *V4L2FmtToStr(int fmt);
int V4L2FmtToBpp(int fmt);
int V4L2ToHalPixel(int fmt);
int isCompressedFmt(int fmt);

}; // namespace android

#endif //_CAMERA_MISC_H
