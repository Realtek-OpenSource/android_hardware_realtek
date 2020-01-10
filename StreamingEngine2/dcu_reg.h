#ifndef DCU_REG_H
#define DCU_REG_H

#include "dc_reg.h"

#define DCU_REG(r) (r)
/*
#if IS_CHIP(MARS) || IS_CHIP(JUPITER)|| IS_CHIP(SATURN) || defined(IS_DARWIN) || defined(IS_MACARTHUR)
*/
#define PreparePictSetWriteData(index, pitch, addr)  ((((index) & 0xFF) << 24) | \
                                                      ((((pitch) >> 8) & 0x3F) << 16) | \
                                                      (((addr) >> (11+((readl(DCU_REG(PLI_DC_SYS_MISC)) >> 16) & 0x3))) & 0x3FFF))
/*
#else

#define PreparePictSetWriteData(index, pitch, addr)  ((((index) & 0x3F) << 18) | \
                                                      ((((pitch) >> 8) & 0x1F) << 13) | \
                                                      (((addr) >> (11+((readl(DCU_REG(PLI_DC_SYS_MISC)) >> 16) & 0x3))) & 0x1FFF))

#endif
*/
#endif


