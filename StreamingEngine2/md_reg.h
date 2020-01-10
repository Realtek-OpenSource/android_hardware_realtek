#ifndef SMQ_REG_H
#define SMQ_REG_H

#ifdef __cplusplus
extern "C" {
#endif

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define SMQ_COMMAND_ENTRIES 4096
#define INST_CNT_MASK 0xFFFF

#define SMQ_REG_BASE 0xB800B000  //TBD
#define IOA_SMQ_CNTL         ((volatile unsigned int *)0xB800B000)
#define IOA_SMQ_INT_STATUS   ((volatile unsigned int *)0xB800B004)
#define IOA_SMQ_INT_ENABLE   ((volatile unsigned int *)0xB800B008)
#define IOA_SMQ_CmdBase      ((volatile unsigned int *)0xB800B00C)
#define IOA_SMQ_CmdLimit     ((volatile unsigned int *)0xB800B010)
#define IOA_SMQ_CmdRdptr     ((volatile unsigned int *)0xB800B014)
#define IOA_SMQ_CmdWrptr     ((volatile unsigned int *)0xB800B018)
#define IOA_SMQ_CmdFifoState ((volatile unsigned int *)0xB800B01C)
#define IOA_SMQ_INST_CNT     ((volatile unsigned int *)0xB800B020)

#define SMQ_REG(r) (r)

#define SMQ_CLR_WRITE_DATA 0
#define SMQ_SET_WRITE_DATA 1

#define MOVE_DATA_SS 0x05
#define MOVE_DATA_SB 0x15
#define MOVE_DATA_BS 0x25
#define MOVE_DATA_SS_PITCH 0x35

#define SWAP_DATA_2B_SS        0x07
#define SWAP_DATA_2B_SS_PITCH  0x37

#define SWAP_DATA_4B_SS        0x0d
#define SWAP_DATA_4B_SS_PITCH  0x3d

//se control bits
typedef enum {
    SMQ_GO=BIT1,
    SMQ_CMD_SWAP=BIT2,
    SMQ_IDLE=BIT3,
} SE_CTRL;

#ifdef __cplusplus
}
#endif
#endif

