#ifndef SB2_REG_H
#define SB2_REG_H

#include "sb2_reg.h"

#define SB2_REG(r) (r)

#define PrepareTileStartAddrWriteData(a)  (((((a) >> 11) & 0xFFFF) << 11) | (1 << 27))
#define PreparePicWidthWriteData(w)  ((((w) & 0x7) << 7) | (1 << 10))
#define PreparePicIndexWriteData(i)  ((((i) & 0x3F) << 0) | (1 << 6))

#endif

