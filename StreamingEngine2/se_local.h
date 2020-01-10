#ifndef STREAM_ENGINE_H
#define STREAM_ENGINE_H

#include "OSAL.h"
#include "hresult.h"

#include "se_reg.h"

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define SE_RegBase

#define SE_COMMAND_ENTRIES 4096
#define INST_CNT_MASK 0xFFFF

#define SE_REG(r) (r)

#define SE_CLR_WRITE_DATA 0
#define SE_SET_WRITE_DATA BIT0

//se control bits
typedef enum {
    //SE_WRITE_BIT=BIT0,
    //SE_CLR_WRITE_DATA=0,
    //SE_SET_WRITE_DATA=BIT0,
    SE_GO=BIT1,
    SE_IDLE=BIT2,
    SE_RESET=BIT3,
    SE_CMD_SWAP=BIT4
} SE_CTRL;

//interrupt status and control bits
typedef enum {
    INT_COML_EMPTY=BIT3,
    INT_SYNC=BIT2,
    INT_COM_ERR=BIT1,
} INT_STATUS, INT_CTRL;

typedef enum {
    DRAW_PEL=0x0,
    WRITE_REG=0x1,
    BITBLIT=0x2,
    //BM_AREA=0x3,
    MOVE_DATA=0x5,
    SYNC=0x7,
    NO_OF_OPCODES
} OPCODE;

typedef enum {
    CONST_ALPHA=0,
    ONE_MINUS_CONST_ALPHA=1,
    DST_PIXEL_ALPHA=2,
    ONE_MINUS_DST_PIXEL_ALPHA=3,
    SRC_PIXEL_ALPHA=4,
    ONE_MINUS_SRC_PIXEL_ALPHA=5
} ALPHA_TYPE;

typedef enum {
    SEL_ALPHA_WITH_COLOR_KEY=0,
    SEL_ALPHA = 0,
    SEL_ROP = 1
} MODE_SELECT;
  
typedef enum {
    SEL_CONST=0,
    SEL_VECT=1
} SRC_SELECT;
  
typedef enum {
     NORMAL_ALPHA=0,
     RSLT_ALPHA = 1
} SEL_OUTPUT_ALPHA;

typedef enum {
    BLIT_FWD=0,
    BLIT_REV=1
} BLIT_DIR;

typedef enum {
    NO_COLOR_KEY = 0,
    SRC_COLOR_KEY = 1,
    DEST_COLOR_KEY = 2,
    RESVD_COLOR_KEY = 3
}COLOR_KEY_MODE;

typedef int (*func_t)(DWORD cmd_word);

//OpCode related function pointer and command length
typedef struct {
    func_t func;
    DWORD dwCmdLen;
} OpFunc_t;

//A represents destination while B represents source
typedef enum {
    ROP_BLACK=0,
    ROP_AND, 
    ROP_A_AND_NB,
    ROP_A,
    ROP_NA_AND_B,
    ROP_B,
    ROP_X_OR,
    ROP_OR,
    ROP_NOR,
    ROP_XNOR,
    ROP_NB,
    ROP_A_OR_NB,
    ROP_NA,
    ROP_NA_OR_B,
    ROP_NAND,
    ROP_WHITE=0xF
}ROPCODE;

typedef enum {
    REG_SE_AddrMap=0x0,
    REG_SE_Color_Key=0x1,
    REG_SE_Def_Alpha=0x2,
    REG_SE_Rslt_Alpha=0x3,
    REG_SE_Src_Alpha=0x4,
    REG_SE_Src_Color=0x5,
    REG_SE_Clr_Format=0x6,
    REG_SE_Input=0x7
} REG_ADDR;

#endif

