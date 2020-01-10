#ifndef _MD_DRV_H_
#define _MD_DRV_H_

#include "md.h"
#include <sys/ioctl.h>
#include "dcu_reg.h"
#include "sb2_reg.h"

#ifndef _MD_REG_H_
//#if !IS_CHIP(SATURN) && !defined(IS_DARWIN) && !defined(IS_MACARTHUR)
//#include "SeReg.h"
//#else
#include "MdRegSaturn.h"
//#endif
#endif

//=================================================================================================

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define MD_COMMAND_ENTRIES 4096
#define INST_CNT_MASK 0xFFFF

#define MD_REG(r) (r)

#define MD_CLR_WRITE_DATA 0
//#define MD_SET_WRITE_DATA BIT0

#define MdClearWriteData 0

//md control bits
typedef enum
{
	MdWriteData = BIT0,
    MdGo = BIT1,
    MdEndianSwap = BIT2,
    MdIdle = BIT3
} MD_CTRL_REG;

//=================================================================================================

#endif

//=================================================================================================
// End of File
