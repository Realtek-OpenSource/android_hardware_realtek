#ifndef _MD_LIB_H_
#define _MD_LIB_H_
//#include <Platform_Lib/Graphics/DirectGraphics.h>
//#ifdef USEDFB //+JT
//#include "../DG_DFB/DGDFB_private.h"
//#else
//#include "../DG/DG_private.h"
//#endif
#ifndef _MD_CMD_H_
/*
#if IS_CHIP(SATURN) || defined(IS_DARWIN) || defined(IS_MACARTHUR)
*/
    #include "xdr/OSALTypes.h"
    #include "MdCmdSaturn.h"
#endif


typedef void * SURFACEHANDLE;
typedef void * HANDLE;

#ifndef _MD_DRV_H_
#include "MdDrv.h"
#endif
//=================================================================================================
#define MDINFO_ERROR_INTERRUPT_STATUS_MASK			0x0000FFF4	//Interrupt Mask of Error Status
//=================================================================================================
typedef enum _MDINFO_OPCODE
{
	MDINFO_OPCODE_NORMAL_MODE = 0x5,    			//The Definition of Move Data Operation: Normal Mode
	MDINFO_OPCODE_2B_MODE = 0x7,    			//The Definition of Move Data Operation: 2B Mode
	MDINFO_OPCODE_4B_MODE = 0xD    			//The Definition of Move Data Operation: 4B Mode
} MDINFO_OPCODE;

//=================================================================================================
typedef enum _MDINFO_MOVE_MODE
{
	MDINFO_MOVE_MODE_SS = 0x0,    			//The Definition of Move Mode: Seq to Seq
	MDINFO_MOVE_MODE_SB = 0x1,    			//The Definition of Move Mode: Seq to Blk
	MDINFO_MOVE_MODE_BS = 0x2,    			//The Definition of Move Mode: Blk to Seq
	MDINFO_MOVE_MODE_BB = 0x3    			//The Definition of Move Mode: Blk to Blk
} MDINFO_MOVE_MODE;

//=================================================================================================
#define	MDINFO_COMMAND_QUEUE0 0							//The Definition of Command Queue Type: Command Queue 0
#define	MDINFO_COMMAND_QUEUE1 1							//The Definition of Command Queue Type: Command Queue 1
#define	MDINFO_COMMAND_QUEUE2 2							//The Definition of Command Queue Type: Command Queue 2
typedef int MDINFO_CMDQUEUE;

#if 0
typedef enum _MDINFO_CMDQUEUE
{
       MDINFO_COMMAND_QUEUE0 = 0,                                                      //The Definition of Command Queue Type: Command Queue 0
       //MDINFO_COMMAND_QUEUE1 = 1,                                                      //The Definition of Command Queue Type: Command Queue 1
       //MDINFO_COMMAND_QUEUE2 = 2                                                       //The Definition of Command Queue Type: Command Queue 2
} MDINFO_CMDQUEUE;
#endif

//=================================================================================================
typedef enum _MDINFO_CPU
{
	MDINFO_SCPU = 0,									//The Indicator of System CPU
	MDINFO_VCPU = 1										//The Indicator of Video CPU
} MDINFO_CPU;

//=================================================================================================
#ifdef __cplusplus
extern "C" {
#endif
HRESULT
MD_WriteRegister(
	MDINFO_CMDQUEUE 	byCommandQueue,
    uint32_t          	dRegisterValue,
    uint32_t          	sRegisterValue,
    uint32_t          	sizeValue
    );

HRESULT
MD_ExecCmd(
	MDINFO_CMDQUEUE		byCommandQueue					//Select Specific Command Queue
	);

HRESULT
MD_WaitCmdDone(
	MDINFO_CMDQUEUE		byCommandQueue					//Select Specific Command Queue
	);

#ifdef __cplusplus
} // extern "C"
#endif
//=================================================================================================

#endif //_MD_LIB_H_

//=================================================================================================
// End of File
