//=================================================================================================
// Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
//
// Filename: SeLib.h
// Abstract:
//   Related API Definitions of Columbus Streaming Engine
//
// History:
//   2008-02-15         cyyang          Initial Version
//   2011-01-18         zack            Modify for Saturn
//=================================================================================================

#ifndef _SE_LIB_H_
#define _SE_LIB_H_
//#include <Platform_Lib/Graphics/DirectGraphics.h>
//#ifdef USEDFB //+JT
//#include "../DG_DFB/DGDFB_private.h"
//#else
//#include "../DG/DG_private.h"
//#endif
#ifndef _SE_CMD_H_
/*
#if IS_CHIP(SATURN) || defined(IS_DARWIN) || defined(IS_MACARTHUR)
*/
    #include "xdr/OSALTypes.h"
    #include "SeCmdSaturn.h"
    #include "SeRegTableSaturn.h"
/*
#else
    #include "SeCmd.h"
#endif
*/
#endif


typedef void * SURFACEHANDLE;
typedef void * HANDLE;

#ifndef _SE_DRV_H_
#include "SeDrv.h"
#endif
//=================================================================================================
#define SEINFO_ERROR_INTERRUPT_STATUS_MASK			0x0000FFF4	//Interrupt Mask of Error Status

#define SEINFO_STRETCH_COEFF_TABLE_MAX_TAP			3	//Maximum Number of TAP Fields
#define SEINFO_STRETCH_COEFF_TABLE_MAX_RATIO		5	//Maximum Number of Ratio Fields
#define SEINFO_STRETCH_COEFF_TABLE_MAX_COEFF		32	//Maximum Number of Coefficient Fields

#define SEINFO_STRETCH_VSCALING_COEFF_MAX			16	//Maximum Number of Vertical Scaling Coefficient Fields
#define SEINFO_STRETCH_HSCALING_COEFF_MAX			32	//Maximum Number of Horizontal Scaling Coefficient Fields

#define SEINFO_STRETCH_DELTA_PHASE					163840000	//Base Value of Delta Phase: 2^14

#define SEINFO_STRETCH_SECTION_1					30000	//Coefficient Range 1 in Stretch Command
#define SEINFO_STRETCH_SECTION_2					60000	//Coefficient Range 2 in Stretch Command

//=================================================================================================
typedef enum _SEINFO_OPCODE
{
	SEINFO_OPCODE_WRITE_REGISTER = 0x01,    			//The Definition of Command Code: Write Register
	SEINFO_OPCODE_FETCH_CLUT = 0x02,    				//The Definition of Command Code: Fetch CLUT
	SEINFO_OPCODE_FORMAT_CONVERSION = 0x03,    			//The Definition of Command Code: Format Conversion
	SEINFO_OPCODE_DRAW_LINE = 0x04,    					//The Definition of Command Code: Draw Line
    SEINFO_OPCODE_LOCK_CLUT = 0x04,                     //The Definition of Command Code: Lock CLUT. Defind on Saturn.
	SEINFO_OPCODE_BITBLT = 0x05,   		 				//The Definition of Command Code: Bitblit
	SEINFO_OPCODE_STRETCH = 0x06,    					//The Definition of Command Code: Stretch
	SEINFO_OPCODE_MIRROR = 0x07,    					//The Definition of Command Code: Mirror
	SEINFO_OPCODE_DECODE_DVB = 0x08,    				//The Definition of Command Code: Decode_DVB
	SEINFO_OPCODE_WAIT_VO_VSYNC = 0x08,    				//The Definition of Command Code: Wait VO VSync. Defined on Saturn
	SEINFO_OPCODE_COPY = 0x09,    				//The Definition of Command Code: COPY
	SEINFO_OPCODE_ROTATE = 0x0A,    					//The Definition of Command Code: Rotate
	SEINFO_OPCODE_FELICS = 0x0B,    					//The Definition of Command Code: Felics
	SEINFO_OPCODE_BITMAP = 0x0C,    					//The Definition of Command Code: Bitmap
	SEINFO_OPCODE_DECIMATE = 0x0D,    					//The Definition of Command Code: Decimate
    SEINFO_OPCODE_BIBLIT_EX = 0x0D,                     //The Definition of Command Code: Bitblit with source color transform or directFB. Defined on Saturn.
    SEINFO_OPCODE_ALPHA = 0x0E,                         //The Definition of Command Code: Alpha
	SEINFO_OPCODE_NOP = 0x0F    						//The Definition of Command Code: NOP
	
} SEINFO_OPCODE;

//=================================================================================================
#define	SEINFO_COMMAND_QUEUE0 0							//The Definition of Command Queue Type: Command Queue 0
#define	SEINFO_COMMAND_QUEUE1 1							//The Definition of Command Queue Type: Command Queue 1
#define	SEINFO_COMMAND_QUEUE2 2							//The Definition of Command Queue Type: Command Queue 2
typedef int SEINFO_CMDQUEUE;
	
#if 0
typedef enum _SEINFO_CMDQUEUE
{
       SEINFO_COMMAND_QUEUE0 = 0,                                                      //The Definition of Command Queue Type: Command Queue 0
       SEINFO_COMMAND_QUEUE1 = 1,                                                      //The Definition of Command Queue Type: Command Queue 1
       SEINFO_COMMAND_QUEUE2 = 2                                                       //The Definition of Command Queue Type: Command Queue 2

} SEINFO_CMDQUEUE;
#endif

//=================================================================================================
typedef enum _SEINFO_DMAINFO
{
	SEINFO_DMA_CHANNEL0 = 0,							//The Definition of DMA Channel Type: DMA Channel 0
	SEINFO_DMA_CHANNEL1 = 1,							//The Definition of DMA Channel Type: DMA Channel 1
	SEINFO_DMA_CHANNEL2 = 2,							//The Definition of DMA Channel Type: DMA Channel 2
	SEINFO_DMA_CHANNEL3 = 3								//The Definition of DMA Channel Type: DMA Channel 3
	
} SEINFO_DMAINFO;

//=================================================================================================
typedef enum _SEINFO_CLIPPINGINFO
{
	SEINFO_CLIPPING_CHANNEL0 = 0,						//The Definition of Clipping Channel Type: Clipping Channel 0
	SEINFO_CLIPPING_CHANNEL1 = 1,						//The Definition of Clipping Channel Type: Clipping Channel 1
	SEINFO_CLIPPING_CHANNEL2 = 2,						//The Definition of Clipping Channel Type: Clipping Channel 2
	SEINFO_CLIPPING_CHANNEL3 = 3						//The Definition of Clipping Channel Type: Clipping Channel 3
	
} SEINFO_CLIPPINGINFO;

//=================================================================================================
typedef enum _SEINFO_CPU
{
	SEINFO_SCPU = 0,									//The Indicator of System CPU
	SEINFO_VCPU = 1										//The Indicator of Video CPU
	
} SEINFO_CPU;

//=================================================================================================
typedef enum _SEINFO_REGMODE
{
	SEINFO_REGMODE_REGISTER	= 0,						//The Definition of Register Mode: Register
	SEINFO_REGMODE_CLUT	= 1								//The Definition of Register Mode: CLUT
	
} SEINFO_REGMODE;

//=================================================================================================
#if 0
#if IS_CHIP(SATURN) || defined(IS_DARWIN) || defined(IS_MACARTHUR)
    // enum SEINFO_WRITEREG is defined in SeRegTableSaturn.h
#else
typedef enum _SEINFO_WRITEREG
{
														//The Definition of Valid Register Address
	SEINFO_REG_COLOR_FORMAT = 0x040,		
	SEINFO_REG_COLOR_KEY = 0x04C,
	SEINFO_REG_SRC_COLOR = 0x058,
	SEINFO_REG_SRC_COLOR2 = 0x064,
	SEINFO_REG_SRC_ALPHA = 0x070,
	SEINFO_REG_SRC_ALPHA2 = 0x4D0,
	SEINFO_REG_DEST_ALPHA = 0x07C,
	SEINFO_REG_RESULT_ALPHA = 0x088,

//=================================================================================================
	SEINFO_REG_BASE_ADDR0 = 0x094,
	SEINFO_REG_BASE_ADDR1 = 0x098,
	SEINFO_REG_BASE_ADDR2 = 0x09C,
	SEINFO_REG_BASE_ADDR3 = 0x0A0,
	SEINFO_REG_PITCH0 = 0x0A4,
	SEINFO_REG_PITCH1 = 0x0A8,
	SEINFO_REG_PITCH2 = 0x0AC,
	SEINFO_REG_PITCH3 = 0x0B0,

//=================================================================================================
	SEINFO_REG_FELICS_ADDR0 = 0x0F4,
	SEINFO_REG_FELICS_ADDR1 = 0x0F8,
	SEINFO_REG_FELICS_ADDR2 = 0x0FC,
	SEINFO_REG_FELICS_ADDR3 = 0x100,

//=================================================================================================
	SEINFO_REG_CLIP_X0 = 0x128,
	SEINFO_REG_CLIP_X1 = 0x12C,
	SEINFO_REG_CLIP_X2 = 0x130,
	SEINFO_REG_CLIP_X3 = 0x134,
	SEINFO_REG_CLIP_Y0 = 0x138,
	SEINFO_REG_CLIP_Y1 = 0x13C,
	SEINFO_REG_CLIP_Y2 = 0x140,
	SEINFO_REG_CLIP_Y3 = 0x144,	

//=================================================================================================
	SEINFO_REG_CONV_SCALING = 0x188,
	SEINFO_REG_CONV_COEF1 = 0x194,
	SEINFO_REG_CONV_COEF2 = 0x1A0,
	SEINFO_REG_CONV_COEF3 = 0x1AC,
	SEINFO_REG_CONV_COEF4 = 0x1B8,
	SEINFO_REG_CONV_COEF5 = 0x1C4,
	SEINFO_REG_CONV_COEF6 = 0x1D0,
	
//=================================================================================================
	SEINFO_REG_STRETCH = 0x1DC,
	SEINFO_REG_HDHS = 0x1E8,
	SEINFO_REG_VDHS = 0x1F4,
 	SEINFO_REG_HCOEF0 = 0x200,
 	SEINFO_REG_HCOEF1 = 0x204,
 	SEINFO_REG_HCOEF2 = 0x208,
 	SEINFO_REG_HCOEF3 = 0x20C,
 	SEINFO_REG_HCOEF4 = 0x210,
 	SEINFO_REG_HCOEF5 = 0x214,
 	SEINFO_REG_HCOEF6 = 0x218,
 	SEINFO_REG_HCOEF7 = 0x21C,
 	SEINFO_REG_HCOEF8 = 0x220,
 	SEINFO_REG_HCOEF9 = 0x224,
 	SEINFO_REG_HCOEF10 = 0x228,
 	SEINFO_REG_HCOEF11 = 0x22C,
 	SEINFO_REG_HCOEF12 = 0x230,	
 	SEINFO_REG_HCOEF13 = 0x234,	
 	SEINFO_REG_HCOEF14 = 0x238,	
 	SEINFO_REG_HCOEF15 = 0x23C,
 	SEINFO_REG_HCOEF16 = 0x240,
 	SEINFO_REG_HCOEF17 = 0x244,
 	SEINFO_REG_HCOEF18 = 0x248,
 	SEINFO_REG_HCOEF19 = 0x24C,
 	SEINFO_REG_HCOEF20 = 0x250,
 	SEINFO_REG_HCOEF21 = 0x254,
 	SEINFO_REG_HCOEF22 = 0x258,
 	SEINFO_REG_HCOEF23 = 0x25C,
 	SEINFO_REG_HCOEF24 = 0x260,
 	SEINFO_REG_HCOEF25 = 0x264,
 	SEINFO_REG_HCOEF26 = 0x268,
 	SEINFO_REG_HCOEF27 = 0x26C,
 	SEINFO_REG_HCOEF28 = 0x270,	
 	SEINFO_REG_HCOEF29 = 0x274,	
 	SEINFO_REG_HCOEF30 = 0x278,	
 	SEINFO_REG_HCOEF31 = 0x27C, 	
 	SEINFO_REG_HCOEF0_32  = 0x558,
 	SEINFO_REG_HCOEF1_32  = 0x55C,
 	SEINFO_REG_HCOEF2_32  = 0x560,
 	SEINFO_REG_HCOEF3_32  = 0x564,
 	SEINFO_REG_HCOEF4_32  = 0x568,
 	SEINFO_REG_HCOEF5_32  = 0x56C,
 	SEINFO_REG_HCOEF6_32  = 0x570,
 	SEINFO_REG_HCOEF7_32  = 0x574,
 	SEINFO_REG_HCOEF8_32  = 0x578,
 	SEINFO_REG_HCOEF9_32  = 0x57C,
 	SEINFO_REG_HCOEF10_32 = 0x580,
 	SEINFO_REG_HCOEF11_32 = 0x584,
 	SEINFO_REG_HCOEF12_32 = 0x588,	
 	SEINFO_REG_HCOEF13_32 = 0x58C,	
 	SEINFO_REG_HCOEF14_32 = 0x590,	
 	SEINFO_REG_HCOEF15_32 = 0x594,
 	SEINFO_REG_HCOEF16_32 = 0x598,
 	SEINFO_REG_HCOEF17_32 = 0x59C,
 	SEINFO_REG_HCOEF18_32 = 0x5A0,
 	SEINFO_REG_HCOEF19_32 = 0x5A4,
 	SEINFO_REG_HCOEF20_32 = 0x5A8,
 	SEINFO_REG_HCOEF21_32 = 0x5AC,
 	SEINFO_REG_HCOEF22_32 = 0x5B0,
 	SEINFO_REG_HCOEF23_32 = 0x5B4,
 	SEINFO_REG_HCOEF24_32 = 0x5B8,
 	SEINFO_REG_HCOEF25_32 = 0x5BC,
 	SEINFO_REG_HCOEF26_32 = 0x5C0,
 	SEINFO_REG_HCOEF27_32 = 0x5C4,
 	SEINFO_REG_HCOEF28_32 = 0x5C8,	
 	SEINFO_REG_HCOEF29_32 = 0x5CC,	
 	SEINFO_REG_HCOEF30_32 = 0x5D0,	
 	SEINFO_REG_HCOEF31_32 = 0x5D4, 	
	SEINFO_REG_VCOEF0 = 0x280,
	SEINFO_REG_VCOEF1 = 0x284,
	SEINFO_REG_VCOEF2 = 0x288,
	SEINFO_REG_VCOEF3 = 0x28C,
	SEINFO_REG_VCOEF4 = 0x290,
	SEINFO_REG_VCOEF5 = 0x294,
	SEINFO_REG_VCOEF6 = 0x298,
	SEINFO_REG_VCOEF7 = 0x29C,
	SEINFO_REG_VCOEF8 = 0x2A0,
	SEINFO_REG_VCOEF9 = 0x2A4,
	SEINFO_REG_VCOEF10 = 0x2A8,
	SEINFO_REG_VCOEF11 = 0x2AC,
	SEINFO_REG_VCOEF12 = 0x2B0, 
	SEINFO_REG_VCOEF13 = 0x2B4, 
	SEINFO_REG_VCOEF14 = 0x2B8, 
	SEINFO_REG_VCOEF15 = 0x2BC,
	SEINFO_REG_VCOEF0_16  = 0x5D8,
	SEINFO_REG_VCOEF1_16  = 0x5DC,
	SEINFO_REG_VCOEF2_16  = 0x5E0,
	SEINFO_REG_VCOEF3_16  = 0x5E4,
	SEINFO_REG_VCOEF4_16  = 0x5E8,
	SEINFO_REG_VCOEF5_16  = 0x5EC,
	SEINFO_REG_VCOEF6_16  = 0x5F0,
	SEINFO_REG_VCOEF7_16  = 0x5F4,
	SEINFO_REG_VCOEF8_16  = 0x5F8,
	SEINFO_REG_VCOEF9_16  = 0x5FC,
	SEINFO_REG_VCOEF10_16 = 0x600,
	SEINFO_REG_VCOEF11_16 = 0x604,
	SEINFO_REG_VCOEF12_16 = 0x608, 
	SEINFO_REG_VCOEF13_16 = 0x60C, 
	SEINFO_REG_VCOEF14_16 = 0x610, 
	SEINFO_REG_VCOEF15_16 = 0x614,

//=================================================================================================
	SEINFO_REG_2TO4_MAP = 0x440,
	SEINFO_REG_2TO8_MAP = 0x444,
	SEINFO_REG_4TO8_MAP0 = 0x448,
	SEINFO_REG_4TO8_MAP1 = 0x44C,
	SEINFO_REG_4TO8_MAP2 = 0x450,
	SEINFO_REG_4TO8_MAP3 = 0x454,

//=================================================================================================
	SEINFO_REG_FELICS_ABORT = 0x44C,
	SEINFO_REG_INT_STATUS = 0x474,
	
} SEINFO_WRITEREG;
#endif
#endif

//=================================================================================================
typedef enum _SEINFO_ROPCODE
{
	SEINFO_ROPCODE_AND = 0,       						//The Definition of ROP Code: AND
	SEINFO_ROPCODE_OR = 1,       						//The Definition of ROP Code: OR
	SEINFO_ROPCODE_XOR = 2,       						//The Definition of ROP Code: XOR
	SEINFO_ROPCODE_COPY = 3,       						//The Definition of ROP Code: COPY
	SEINFO_ROPCODE_NONE = 4,       						//The Definition of ROP Code: Disable
} SEINFO_ROPCODE;

//=================================================================================================
typedef enum _SEINFO_DFB_OPERATION //Saturn Spec, page 32, command Bitblit, word 2, field: ROP code
{
	SEINFO_DFB_OP_WRITE_TMP_SRC_DATA_TO_DDR = 0,        // Write temporal source data to DDR.
    SEINFO_DFB_OP_COPY_SRC_DATA_TO_DEST = 1,            // Copy source data to destination.
    SEINFO_DFB_OP_DISABLED = 4                         // Disable this feature.          
} SEINFO_DFB_OPERATION;

//=================================================================================================
typedef enum _SEINFO_MIRRORMODE
{
	SEINFO_MIRROR_X = 1,       							//The Definition of Mirror Mode: X Only
	SEINFO_MIRROR_Y = 2,       							//The Definition of Mirror Mode: Y Only
	SEINFO_MIRROR_XY = 3       							//The Definition of Mirror Mode: X and Y
	
} SEINFO_MIRRORMODE;

//=================================================================================================
typedef enum _SEINFO_CLUT
{
	SEINFO_FETCH_CLUT_4ARGB = 0,       					//The Definition of CLUT Mode: 4 Entries ARGB for Index2 Format
	SEINFO_FETCH_CLUT_16ARGB = 1,      		 			//The Definition of CLUT Mode: 16 Entries ARGB for Index4 Format 
	SEINFO_FETCH_CLUT_256ARGB = 2       				//The Definition of CLUT Mode: 256 Entries ARGB for Index8 Format 
	
} SEINFO_CLUT;

//=================================================================================================
typedef enum _SEINFO_SETUPMODE
{
	SEINFO_BITBLT_SETUP_CONST = 0,       				//The Definition of Setup Mode: Constant Mode (Refer to Register SE_Src_Color/SE_Src_Alpha)
	SEINFO_BITBLT_SETUP_MANUAL = 1       				//The Definition of Setup Mode: Manual Mode
	
} SEINFO_SETUPMODE;

//=================================================================================================
typedef enum _SEINFO_VSCALING_EN
{
	SEINFO_VSCALING_ENABLE = true,     					//Enable Vertical Scaling Operation
	SEINFO_VSCALING_DISABLE = false						//Disable Vertical Scaling Operation
	
} SEINFO_VSCALING_EN;

//=================================================================================================
typedef enum _SEINFO_HSCALING_EN
{
	SEINFO_HSCALING_ENABLE = true,     					//Enable Horizontal Scaling Operation
	SEINFO_HSCALING_DISABLE = false						//Disable Horizontal Scaling Operation
	
} SEINFO_HSCALING_EN;

//=================================================================================================
typedef enum _SEINFO_ALPHAPROC_EN
{
	SEINFO_ALPHAPROC_ENABLE = true,     				//Enable Alpha Operation
	SEINFO_ALPHAPROC_DISABLE = false   					//Disable Alpha Operation
	
} SEINFO_ALPHAPROC_EN;

//=================================================================================================
typedef enum _SEINFO_CLIPPING_EN
{
	SEINFO_CLIPPING_ENABLE = true,     					//Enable Clipping Operation
	SEINFO_CLIPPING_DISABLE = false						//Disable Clipping Operation
	
} SEINFO_CLIPPING_EN;

//=================================================================================================
typedef enum _SEINFO_CONVERT_YUV_EN
{
	SEINFO_CONVERT_YUV_ENABLE = true,     				//Enable ARGB->YUV Operation in Felics Command
	SEINFO_CONVERT_YUV_DISABLE = false					//Disable ARGB->YUV Operation in Felics Command
	
} SEINFO_CONVERT_YUV_EN;

//=================================================================================================
typedef enum _SEINFO_FELICS_ALPHA_EN
{
	SEINFO_FELICS_ALPHA_ENABLE = 0,       				//Enable Alpha Operation in Felics Command 
	SEINFO_FELICS_ALPHA_DISABLE = 1     				//Disable Alpha Operation in Felics Command 
	
} SEINFO_FELICS_ALPHA_EN;

//=================================================================================================
typedef enum _SEINFO_COMPRESSMODE
{
	SEINFO_DECOMPRESS = 0,  							//The Definition of Compress Mode: Decompress
	SEINFO_COMPRESS = 1									//The Definition of Compress Mode: Compress
	
} SEINFO_COMPRESSMODE;

//=================================================================================================
typedef enum _SEINFO_BITMAP_SRC
{
	SEINFO_BITMAP_DRAM = 0,     						//The Definition of Location of Bitmap: DRAM
	SEINFO_BITMAP_FLASH = 1  							//The Definition of Location of Bitmap: Flash
	
} SEINFO_BITMAP_SRC;

//=================================================================================================
typedef enum _SEINFO_BITMAP_DIR
{
	SEINFO_BITMAP_DIR_INC = 0,       					//The Definition of Direction of Bitmap: Increase
	SEINFO_BITMAP_DIR_DEC = 1     						//The Definition of Direction of Bitmap: Decrease
	
} SEINFO_BITMAP_DIR;

//=================================================================================================
typedef enum _SEINFO_BGCOLOR_EN
{
	SEINFO_BGCOLOR_ENABLE = true,     					//Enable Background Color in Bitmap Command
	SEINFO_BGCOLOR_DISABLE = false  					//Disable Background Color in Bitmap Command

} SEINFO_BGCOLOR_EN;

//=================================================================================================
typedef enum _SEINFO_FGCOLOR_EN
{
	SEINFO_FGCOLOR_ENABLE = true,       				//Enable Foreground Color in Bitmap Command
	SEINFO_FGCOLOR_DISABLE = false   					//Disable Foreground Color in Bitmap Command

} SEINFO_FGCOLOR_EN;

//=================================================================================================
typedef enum _SEINFO_BITMAP_32BIT_EN
{
	SEINFO_BITMAP_32BIT_ENABLE = true,     	   			//Enable 32-bit Color in Bitmap Command
	SEINFO_BITMAP_32BIT_DISABLE = false    	   			//Disable 32-bit Color in Bitmap Command

} SEINFO_BITMAP_32BIT_EN;

//=================================================================================================
typedef enum _SEINFO_NO_COLORMODIFY_EN
{
	SEINFO_NO_COLORMODIFY_ENABLE = true,     			
	SEINFO_NO_COLORMODIFY_DISABLE = false				

} SEINFO_NO_COLORMODIFY_EN;

//=================================================================================================
typedef enum _SEINFO_ERRORCOLOR_EN
{
	SEINFO_ERRORCOLOR_ENABLE = true,     				//Enable Error Color Pattern
	SEINFO_ERRORCOLOR_DISABLE = false					//Disable Error Color Pattern

} SEINFO_ERRORCOLOR_EN;

//=================================================================================================
typedef enum _SEINFO_BITMAP_ENDIAN
{
	SEINFO_BITMAP_BIG_ENDIAN = 0,     					//The Definition of Endian Type: Big Endian 
	SEINFO_BITMAP_LITTLE_ENDIAN = 1						//The Definition of Endian Type: Little Endian 
	
} SEINFO_BITMAP_ENDIAN;

//=================================================================================================
typedef enum _SEINFO_ROPMODE
{
	SEINFO_ALPHA_BLENDING = 0,     						//The Definition of ROP Mode: Alpha Blending
	SEINFO_ROP_MODE = 1									//The Definition of ROP Mode: ROP Mode
	
} SEINFO_ROPMODE;

//=================================================================================================
#ifndef __SEINFO_CORNER__
#define __SEINFO_CORNER__
typedef enum _SEINFO_CORNER
{
	SEINFO_BITBLT_CORNER_TOP_LEFT = 0,       			//The Definition of Starting Corner: Top-Left
	SEINFO_BITBLT_CORNER_TOP_RIGHT = 1,       			//The Definition of Starting Corner: Top-Right
	SEINFO_BITBLT_CORNER_BOTTOM_LEFT = 2,       		//The Definition of Starting Corner: Bottom-Left
	SEINFO_BITBLT_CORNER_BOTTOM_RIGHT = 3,       		//The Definition of Starting Corner: Bottom-Right
	SEINFO_BITBLT_CORNER_NONE = 4       				//The Definition of Starting Corner: Disable
	
} SEINFO_CORNER;
#endif
//=================================================================================================
typedef enum _SEINFO_ALPHAMODE
{
	SEINFO_BITBLT_ALPHA_CONST = 0,       				//The Definition of Alpha Mode: Constant (SE_Src_Alpha)
	SEINFO_BITBLT_ALPHA_1_CONST = 1,       				//The Definition of Alpha Mode: Constant (1 - SE_Src_Alpha)
	SEINFO_BITBLT_ALPHA_DEST = 2,       				//The Definition of Alpha Mode: Destination (Destination(A))
	SEINFO_BITBLT_ALPHA_1_DEST = 3,       				//The Definition of Alpha Mode: Destination (1 - Destination(A))
	SEINFO_BITBLT_ALPHA_SRC = 4,       					//The Definition of Alpha Mode: Source (Source(A))
	SEINFO_BITBLT_ALPHA_1_SRC = 5,       				//The Definition of Alpha Mode: Source (1 - Source(A))
/*
#if IS_CHIP(SATURN) || defined(IS_DARWIN) || defined(IS_MACARTHUR)
*/
    SEINFO_BITBLT_ALPHA_DFB_CONSTANT_0 = 6,             //The Definition of Alpha Mode: Constant Value 0(for DFB). Defined on Saturn
    SEINFO_BITBLT_ALPHA_DFB_CONSTANT_1 = 7,             //The Definition of Alpha Mode: Constant Value 1(for DFB). Defined on Saturn
	SEINFO_BITBLT_ALPHA_DISABLE = 8
/*
#else
    SEINFO_BITBLT_ALPHA_DISABLE = 6
#endif
*/
} SEINFO_ALPHAMODE;

//=================================================================================================
typedef enum _SEINFO_OUTPUT_ALPHAMODE
{
	SEINFO_OUTPUT_ALPHA_NORMAL = 0,     				//The Definition of Output Alpha Mode: Normal
	SEINFO_OUTPUT_ALPHA_CONST = 1 						//The Definition of Output Alpha Mode: Constant
	
} SEINFO_OUTPUT_ALPHAMODE;

//=================================================================================================
typedef enum _SEINFO_ALPHA_CMD_ALPHA_MODE
{
	SEINFO_ALPHA_CMD_ALPHA_CONST = 0,     				//The Definition of Alpha Mode: Constant (SE_Src_Alpha)
	SEINFO_ALPHA_CMD_ALPHA_INDEX = 1 					//The Definition of Alpha Mode: Using alpha index
} SEINFO_ALPHA_CMD_ALPHA_MODE;

//=================================================================================================
typedef enum _SEINFO_ALPHA_CMD_STREAM_MODE
{
	SEINFO_ALPHA_CMD_STREAM_ALPHA_ONLY = 0,
	SEINFO_ALPHA_CMD_STREAM_RGB565 = 1,
	SEINFO_ALPHA_CMD_STREAM_ARGB8888 = 2,
	SEINFO_ALPHA_CMD_STREAM_DISABLED = 3
} SEINFO_ALPHA_CMD_STREAM_MODE;

//=================================================================================================
typedef enum _SEINFO_STRETCH
{
	SEINFO_STRETCH_FIR = 1,       						//The Definition of Scaling Algorithm: FIR
	SEINFO_STRETCH_REPEAT_DROP = 2,       				//The Definition of Scaling Algorithm: Repeat/Drop
	SEINFO_STRETCH_DIRECTIONAL = 3       				//The Definition of Scaling Algorithm: Directional Scaling
	
} SEINFO_STRETCH;

//=================================================================================================
typedef enum _SEINFO_SACLING_TYPE
{
	SEINFO_SCALING_UP = 0,       						//The Definition of Scaling Type: Scaling Up
	SEINFO_SCALING_DOWN = 1,      						//The Definition of Scaling Type: Scaling Down
	SEINFO_SCALING_DISABLE = 2      					//The Definition of Scaling Type: Disable
	
} SEINFO_SACLING_TYPE;

//=================================================================================================
typedef enum _SEINFO_SACLING_TABLE
{
	SEINFO_SCALING_UP_2X = 0, 							//The Definition of Indicator of Coefficient Table: Scaling Up 2X
	SEINFO_SCALING_UP_4X = 1, 							//The Definition of Indicator of Coefficient Table: Scaling Up 4X
	SEINFO_SCALING_UP_8X = 2, 							//The Definition of Indicator of Coefficient Table: Scaling Up 8X
	SEINFO_SCALING_DOWN_2X = 3,							//The Definition of Indicator of Coefficient Table: Scaling Down 2X
	SEINFO_SCALING_DOWN_4X = 4							//The Definition of Indicator of Coefficient Table: Scaling Down 4X
	
} SEINFO_SACLING_TABLE;

//=================================================================================================
typedef enum _SEINFO_STRETCH_HTAP
{
	SEINFO_HSCALING_2TAP = 0,        					//The Definition of Number of Taps in Horizontal Scaling: 2 Taps    			
	SEINFO_HSCALING_4TAP = 1,         					//The Definition of Number of Taps in Horizontal Scaling: 4 Taps
	SEINFO_HSCALING_8TAP = 2     						//The Definition of Number of Taps in Horizontal Scaling: 8 Taps
	
} SEINFO_STRETCH_HTAP;

//=================================================================================================
typedef enum _SEINFO_STRETCH_VTAP
{
	SEINFO_VSCALING_2TAP = 0,       					//The Definition of Number of Taps in Vertical Scaling: 2 Taps
	SEINFO_VSCALING_4TAP = 1      						//The Definition of Number of Taps in Vertical Scaling: 4 Taps
	
} SEINFO_STRETCH_VTAP;

//=================================================================================================
typedef enum _SEINFO_DECIMATE_SCALING
{
	SEINFO_DECIMATE_AVERAGE2 = 0,       				//The Definition of Decimate Algorithm: Average 2
	SEINFO_DECIMATE_AVERAGE4 = 1,       				//The Definition of Decimate Algorithm: Average 4
  	
} SEINFO_DECIMATE_SCALING;

//=================================================================================================
typedef enum _SEINFO_COLORKEY
{
	SEINFO_COLORKEY_NONE = 0,       					//The Definition of Color Key: No Color Key
	SEINFO_COLORKEY_SOURCE = 1,       					//The Definition of Color Key: Source Side Color Key
	SEINFO_COLORKEY_DESTINATION = 2,       				//The Definition of Color Key: Destination Side Color Key
	SEINFO_COLORKEY_BOTH = 3       				        //The Definition of Color Key: Destination and Source Color Key
} SEINFO_COLORKEY;

//=================================================================================================
typedef enum _SEINFO_COLORKEY_DRAWLINE
{
	SEINFO_COLORKEY_DRAWLINE_NONE = 0,       			//The Definition of Color Key: No Color Key
	SEINFO_COLORKEY_DRAWLINE_DESTINATION = 1       		//The Definition of Color Key: Destination Side Color Key
	
} SEINFO_COLORKEY_DRAWLINE;

//=================================================================================================
typedef enum _SEINFO_CONVERSION
{
	SEINFO_CONVERSION_INDEX_ARGB = 0,       			//The Definition of Format Conversion: Index to ARGB
	SEINFO_CONVERSION_ARGB_ARGB = 1,       				//The Definition of Format Conversion: ARGB to ARGB
	SEINFO_CONVERSION_YUV_ARGB = 2,       				//The Definition of Format Conversion: YUV to ARGB
	SEINFO_CONVERSION_ARGB_YUV = 3       				//The Definition of Format Conversion: ARGB to YUV
	
} SEINFO_CONVERSION;

//=================================================================================================
typedef enum _SEINFO_INDEX_FORMAT
{
	SEINFO_FORMAT_INDEX2 = 0,       					//The Definition of Color Format: Index 2
	SEINFO_FORMAT_INDEX4 = 1,       					//The Definition of Color Format: Index 4
	SEINFO_FORMAT_INDEX8 = 2       						//The Definition of Color Format: Index 8
	
} SEINFO_INDEX_FORMAT;

//=================================================================================================
typedef enum _SEINFO_RGB_FORMAT
{
	SEINFO_FORMAT_RGB332 = 0,       					//The Definition of Color Format: RGB332
	SEINFO_FORMAT_RGB565 = 1,       					//The Definition of Color Format: RGB565
	SEINFO_FORMAT_ARGB1555 = 2,       					//The Definition of Color Format: ARGB1555
	SEINFO_FORMAT_ARGB4444 = 3,       					//The Definition of Color Format: ARGB4444
	SEINFO_FORMAT_ARGB8888 = 4       					//The Definition of Color Format: ARGB8888
	
} SEINFO_RGB_FORMAT;

//=================================================================================================
typedef enum _SEINFO_YUV_FORMAT
{
	SEINFO_FORMAT_YUV420 = 0,      			 			//The Definition of Color Format: YUV420
	SEINFO_FORMAT_YUV422 = 1,       					//The Definition of Color Format: YUV422
	SEINFO_FORMAT_YUV444 = 2       						//The Definition of Color Format: YUV444

} SEINFO_YUV_FORMAT;

//=================================================================================================
typedef enum _SEINFO_COLOR_FORMAT
{
	SEINFO_COLOR_FORMAT_INDEX2 = 0,       				//The Definition of Color Format: Index 2
	SEINFO_COLOR_FORMAT_INDEX4 = 1,       				//The Definition of Color Format: Index 4
	SEINFO_COLOR_FORMAT_INDEX8 = 2,       				//The Definition of Color Format: Index 8
	SEINFO_COLOR_FORMAT_RGB332 = 3,						//The Definition of Color Format: RGB332
	SEINFO_COLOR_FORMAT_RGB565 = 4,						//The Definition of Color Format: RGB565
	SEINFO_COLOR_FORMAT_ARGB1555 = 5, 					//The Definition of Color Format: ARGB1555
	SEINFO_COLOR_FORMAT_ARGB4444 = 6, 					//The Definition of Color Format: ARGB4444
	SEINFO_COLOR_FORMAT_ARGB8888 = 7,					//The Definition of Color Format: ARGB8888
	SEINFO_COLOR_FORMAT_Y = 8,							//The Definition of Color Format: Y
	SEINFO_COLOR_FORMAT_UV = 9,							//The Definition of Color Format: CbCr
	SEINFO_COLOR_FORMAT_YUV420 = 10,					//The Definition of Color Format: YCbCr420
	SEINFO_COLOR_FORMAT_YUV422 = 11,					//The Definition of Color Format: YCbCr422
	SEINFO_COLOR_FORMAT_YUV444 = 12,					//The Definition of Color Format: YCbCr444
	SEINFO_COLOR_FORMAT_RGB888 = 15						//The Definition of Color Format: RGB888
} SEINFO_COLOR_FORMAT;

//=================================================================================================
typedef enum _SEINFO_ARGB_ALPHA_LOCATION
{
	SEINFO_ARGB_ALPHA_LEFTMOST = 0,						//The Definition of Location of Alpha Bit: Left-Most
	SEINFO_ARGB_ALPHA_RIGHTMOST = 1,					//The Definition of Location of Alpha Bit: Right-Most
	SEINFO_ARGB_ALPHA_NONE = 2							//The Definition of Location of Alpha Bit: None
	
} SEINFO_ARGB_ALPHA_LOCATION;

//=================================================================================================
typedef enum _SEINFO_RGB_LOCATION
{
	SEINFO_RGB_LOCATION_LEFTMOST = 0,					//The Definition of Location of 2/6 for RGB565/RGB332: Left-Most 
	SEINFO_RGB_LOCATION_MIDDLE = 1,						//The Definition of Location of 2/6 for RGB565/RGB332: Middle
	SEINFO_RGB_LOCATION_RIGHTMOST = 2,					//The Definition of Location of 2/6 for RGB565/RGB332: Right-Most
	SEINFO_RGB_LOCATION_NONE = 3						//The Definition of Location of 2/6 for RGB565/RGB332: None
	
} SEINFO_RGB_LOCATION;

//=================================================================================================
typedef enum _SEINFO_SRC_FORMAT
{
	SEINFO_SRC_FORMAT_INDEX2 = 0,       				//The Definition of Color Format: Index 2
	SEINFO_SRC_FORMAT_INDEX4 = 1,       				//The Definition of Color Format: Index 4
	SEINFO_SRC_FORMAT_INDEX8 = 2,       				//The Definition of Color Format: Index 8
	SEINFO_SRC_FORMAT_RGB332 = 0,						//The Definition of Color Format: RGB332
	SEINFO_SRC_FORMAT_RGB565 = 1,						//The Definition of Color Format: RGB565
	SEINFO_SRC_FORMAT_ARGB1555 = 2, 					//The Definition of Color Format: ARGB1555
	SEINFO_SRC_FORMAT_ARGB4444 = 3, 					//The Definition of Color Format: ARGB4444
	SEINFO_SRC_FORMAT_ARGB8888 = 4,						//The Definition of Color Format: ARGB8888
	SEINFO_SRC_FORMAT_YUV420 = 0,						//The Definition of Color Format: YUV420
	SEINFO_SRC_FORMAT_YUV422 = 1,						//The Definition of Color Format: YUV422
	SEINFO_SRC_FORMAT_YUV444 = 2						//The Definition of Color Format: YUV444
	
} SEINFO_SRC_FORMAT;

//=================================================================================================
typedef enum _SEINFO_DEST_FORMAT
{
	SEINFO_DEST_FORMAT_RGB332 = 0,						//The Definition of Color Format: RGB332
	SEINFO_DEST_FORMAT_RGB565 = 1,						//The Definition of Color Format: RGB565
	SEINFO_DEST_FORMAT_ARGB1555 = 2, 					//The Definition of Color Format: ARGB1555
	SEINFO_DEST_FORMAT_ARGB4444 = 3, 					//The Definition of Color Format: ARGB4444
	SEINFO_DEST_FORMAT_ARGB8888 = 4,					//The Definition of Color Format: ARGB8888
	SEINFO_DEST_FORMAT_YUV420 = 0,						//The Definition of Color Format: YUV420
	SEINFO_DEST_FORMAT_YUV422 = 1,						//The Definition of Color Format: YUV422
	SEINFO_DEST_FORMAT_YUV444 = 2						//The Definition of Color Format: YUV444
	
} SEINFO_DEST_FORMAT;

//=================================================================================================
typedef enum _SEINFO_GRADIENT 
{
    SEINFO_GRADIENT_LEFT_TO_RIGHT = 0,					//The Definition of Direction for Gradient: Left-to-Right
    SEINFO_GRADIENT_TOP_TO_BOTTOM = 1,					//The Definition of Direction for Gradient: Top-to-Bottom
    SEINFO_GRADIENT_TOP_LEFT_TO_BOTTOM_RIGHT = 2,		//The Definition of Direction for Gradient: Top Left-to-Bottom Right
    SEINFO_GRADIENT_TOP_RIGHT_TO_BOTTOM_LEFT = 3,		//The Definition of Direction for Gradient: Top Right-to-Bottom Left
    SEINFO_GRADIENT_DISABLE = 4							//The Definition of Direction for Gradient: Disable
       
} SEINFO_GRADIENT;

//=================================================================================================
typedef enum _SEINFO_ROTATE 
{
    SEINFO_ROTATE_90 = 0,								//The Definition of Angle for Rotate Command: 90 Degrees
    SEINFO_ROTATE_180 = 1,								//The Definition of Angle for Rotate Command: 180 Degrees
    SEINFO_ROTATE_270 = 2,								//The Definition of Angle for Rotate Command: 270 Degrees
    SEINFO_ROTATE_DISABLE = 3							//The Definition of Direction for Gradient: Disable
       
} SEINFO_ROTATE;

//=================================================================================================
typedef enum _SEINFO_INTERLEAVING_MODE
{
    SEINFO_INTERLEAVING_MODE_ENABLE = true,				//The Definition of Enable Interleaving Mode
	SEINFO_INTERLEAVING_MODE_DISABLE = false			//The Definition of Disable Interleaving Mode
       
} SEINFO_INTERLEAVING_MODE;

//=================================================================================================
typedef enum _SEINFO_SRC_CLR_TRANSFORM // Saturn Sepc, page 33, Command Bitblit, Word4, field: src_clr_transform
{
    SEINFO_SRC_CLR_TRANSFORM_DISABLE = 0,               //Disable source color transform
    SEINFO_SRC_CLR_TRANSFORM_ENABLE_FOR_ALPHA_ONLY = 1, //Enable source color transform for alpha only
    SEINFO_SRC_CLR_TRANSFORM_ENABLE_FOR_ALL = 2         //Enable source color transform for all components(RGBA)
} SEINFO_SOURCE_COLOR_TRANSFORM;

//=================================================================================================
typedef enum _SEINFO_DFB_CLR_BLEND_MODE // Saturn Sepc, page 33, Command Bitblit, Word4, field: fb_sel_srcclr_blend & fb_sel_destclr_blend
{
	SEINFO_DFB_BLEND_CONST_0 = 0,      				    //Constant Value 0
	SEINFO_DFB_BLEND_CONST_1 = 1,      				    //Constant Value 1
	SEINFO_DFB_BLEND_ALPHA_DEST = 2,       				//Select dest alpha (i.e. dest(A) �V destination pixel by pixel alpha)
	SEINFO_DFB_BLEND_ALPHA_1_DEST = 3,       			//Select (1-dest(A))
	SEINFO_DFB_BLEND_ALPHA_SRC = 4,       				//Select pixel by pixel src alpha (i.e. src(A))
	SEINFO_DFB_BLEND_ALPHA_1_SRC = 5,       			//Select (1-src(A))
    SEINFO_DFB_BLEND_RGB_SRC = 6,       			    //Select source color src(RGB)
    SEINFO_DFB_BLEND_RGB_1_SRC = 7,       			    //Select (1-src(RGB))
    SEINFO_DFB_BLEND_RGB_DEST = 8,                      //Select destination color dest(RGB)
    SEINFO_DFB_BLEND_RGB_1_DEST = 9,                    //Select (1-dest(RGB))
    SEINFO_DFB_BLEND_MIN_ALPHA_SRC_1_DEST = 10,         //Select min(src(A), 1-dest(A))
 } SEINFO_DFB_CLR_BLEND_MODE;

//=================================================================================================
typedef struct _SE_FELICS_HEADER
{
	uint32_t	Word1;									//IO[63:32]: Reserved

    union                                  	
    {                                       	
		uint32_t	Value;		
		struct
		{
			uint32_t	BitStreamLength: 27;				//IO[26:0]: Bit Stream Length
			uint32_t	Abort: 1;						//IO[27]: Abort Status
			uint32_t	Reserved2: 4;					//IO[31:28]: Reserved

		} Fields;	
    } Word2;  

} SE_FELICS_HEADER;

//=================================================================================================
typedef struct _SE_PROCINFO                     		
{                                               		
    uint16_t    wDataX;                 				//Set Data Location X
    uint16_t    wDataY;                 				//Set Data Location Y
    uint16_t    wDataHeight;            				//Set Data Height
    uint16_t    wDataWidth;             				//Set Data Width

  	uint8_t		byCommandQueueSelect;   				//Select Corresponding Command Queue for Current Serivce
  	bool    	bInterruptService;      				//Select Which CPU to Service Interrupt Events

    uint8_t   	byBaseAddressIndex;     				//Set Index of Base Address 
                	                   	 				//- Sequential Mode: Select Corresponding SE_Baddr and SE_Pitch Registers
                    	               					//- Block Mode: Select DCU Address Index If Color Format is YUV                                                
    uint8_t 	byChronmaAddressIndex;  				//Set DCU Index of Chronma Address     
    bool    	bInterleavingModeEnable;				//Enable/Disable Interleaving Mode    
    
//#endif	//PLATFORM_COLUMBUS       


} SE_PROCINFO;

//=================================================================================================
#ifdef __cplusplus
extern "C" {
#endif

HRESULT
SE_WriteRegister(                               	//The Definition of Write Register Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SEINFO_REGMODE     	bRegisterModeSelect,        	//Select Write Mode for Register/CLUT
    SEINFO_WRITEREG 	wRegisterAddress,           	//Set Write Address of Register/CLUT 
    uint32_t          	dwRegisterValue             	//Set Specific Data for Write Register Command
    );              	                            	
	                            	
HRESULT             	                            	
SE_BitBltEx(        	                            	//The Definition of Bitblit Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
//    SURFACEHANDLE		hDestinationHandle,         	//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,    	//Related Command Parameters of Destination Side
//    SURFACEHANDLE		hSourceHandle,              	//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo,         	//Related Command Parameters of Source Side
	SEINFO_ALPHAMODE    bySrcAlphaModeSelect,			//Select Alpha Mode for Source Side
	uint8_t				bySrcAplhaValue,				//Set Specific Alpha Value of Source Side
	SEINFO_ALPHAMODE    byDestAlphaModeSelect,			//Select Alpha Mode for Destination Side
	uint8_t				byDestAplhaValue,				//Set Specific Alpha Value of Destination Side
	SEINFO_OUTPUT_ALPHAMODE byOutputAlphaModeSelect,	//Set Output Alpha Mode
	uint8_t				byOutputAlphaValue,				//Set Forced Alpha Value
    SEINFO_SETUPMODE    bSetupModeSelect,           	//Select Setup Mode for BitBlit Command
    SEINFO_CORNER      	byStartingCorner,           	//Set Starting Corner for BitBlit Command
    SEINFO_GRADIENT    	byGradientModeSelect,       	//Set Angle for Gradient Operation
    SEINFO_COLORKEY    	byColorKeySelect,           	//Select Color Key
    SEINFO_ROPCODE     	byRopCode,                   	//Set ROP Code for ROP Operation
    void*               pExtraParam               //Extra parameters depended on platform.
    );              	                            	
                    	                            	
HRESULT             	                            	
SE_Stretch(         	                            	//The Definition of Stretch Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,         	//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,    	//Related Command Parameters of Destination Side   
    SURFACEHANDLE		hSourceHandle,              	//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo,         	//Related Command Parameters of Source Side  
    SEINFO_SACLING_TYPE byVerticalScalingType,			//Select Vertical Scaling Type
    uint32_t  			dwVerticalScalingRatio,			//Set Vertical Scaling Ratio
    SEINFO_STRETCH_VTAP	byVerticalTapNumber,			//Set Number of Taps for Vertical Scaling
    SEINFO_SACLING_TYPE byHorizontalScalingType,		//Select Horizontal Scaling Type
    uint32_t  			dwHorizontalScalingRatio,     	//Set Horizontal Scaling Ratio
    SEINFO_STRETCH_HTAP	byHorizontalTapNumber,			//Set Number of Taps for Horizontal Scaling
    SEINFO_STRETCH    	byScalingAlgorithmSelect,   	//Select Scaling Algorithm
    SEINFO_COLORKEY    	byColorKeySelect,            	//Select Color Key
    SEINFO_ALPHAPROC_EN bAlphaEnable,					//Enable /Disable Alpha Operation
    uint8_t				iVerticalScalingOffset,
    void*               pExtraParam               //Extra parameters depended on platform.
    );              	                            	

HRESULT             	                            	
SE_FetchClut(       	                           	//The Definition of Fetch CLUT Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SEINFO_CLUT        	byFetchModeSelect,          	//Select CLUT Type for Fetch CLUT Command
    uint32_t          	dwStartingAddress           	//Set Starting Address for Fetch Operation
    );              	                            	

HRESULT
SE_LockClut(
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    bool                bLock                           //true: lock CLUT, false: unlock CLUT.
    );
//RTK MARK
#if 0
/*
bool
SE_GetLockState(
    SEINFO_CMDQUEUE&    byCommandQueue                  //Which Command Queue Lock the CLUT
    );
*/
#endif
HRESULT             	                            	
SE_FormatConversion(	                           	//The Definition of Format Conversion Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,         	//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,    	//Related Command Parameters of Destination Side 
    SURFACEHANDLE		hSourceHandle,              	//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo,         	//Related Command Parameters of Source Side    
    SEINFO_CONVERSION  	byConversionModeSelect,     	//Set Conversion Mode
    SEINFO_DEST_FORMAT 	byDestinationFormatSelect,  	//Set Color Format of Destination Side
    SEINFO_SRC_FORMAT  	bySourceFormatSelect,       	//Set Color Format of Source Side
    SEINFO_COLORKEY    	byColorKeySelect,            	//Select Color Key
	SEINFO_OUTPUT_ALPHAMODE byOutputAlphaModeSelect,   	//Set Output Alpha Mode
	uint8_t				byOutputAlphaValue,				//Set Forced Alpha Value
	void*               pExtraParam               //Extra parameters depended on platform.
    );              	                            	
                    	                            	
HRESULT             	                            	
SE_Felics(          	                            	//The Definition of Felics Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hSourceHandle,              	//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo,         	//Related Command Parameters of Source Side
    SEINFO_COMPRESSMODE	bCompressMode,            		//Set Operational Mode of Felics Command
    SEINFO_CONVERT_YUV_EN bConvertYuvEnable,    		//Enable/Disable ARGB->YUB before Felics Command
    SEINFO_FELICS_ALPHA_EN bAlphaEnable,          		//Enable/Disable Alpha Processing in Felics
    uint32_t			dwBitstreamBufferAddress0,		//Set Base Address of 1st Bitstream Buffer
    uint32_t        	dwBitstreamLength0,				//Set Length of 1st Bitstream (Read From Header) 
    uint32_t			dwBitstreamBufferAddress1,		//Set Base Address of 2nd Bitstream Buffer
    uint32_t        	dwBitstreamLength1,				//Set Length of 2nd Bitstream (Read From Header) 
    uint32_t			dwBitstreamBufferAddress2,		//Set Base Address of 3rd Bitstream Buffer
    uint32_t        	dwBitstreamLength2,				//Set Length of 3rd Bitstream (Read From Header) 
    uint32_t			dwBitstreamBufferAddress3,		//Set Base Address of 4th Bitstream Buffer
    uint32_t        	dwBitstreamLength3				//Set Length of 4th Bitstream (Read From Header)  
    );              	                            	
                    	                            	
HRESULT             	                            	
SE_Mirror(          	                            	//The Definition of Mirror Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,         	//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,    	//Related Command Parameters of Destination Side 
    SURFACEHANDLE		hSourceHandle,              	//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo,         	//Related Command Parameters of Source Side
    SEINFO_MIRRORMODE  	byMirrorDirection           	//Set Mirror Direction
    );              	                            	
                    	                            	
HRESULT             	                            	
SE_Bitmap(          	                            	//The Definition of Bitmap Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,         	//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,    	//Related Command Parameters of Destination Side 
    SEINFO_BITMAP_SRC  	bBitmapLoadingLocation,     	//Set Location of Bitmap Loading Operation
    SEINFO_BITMAP_DIR  	bFlashAddressDirection,     	//Set Fetch Order on Flash Memory
    SEINFO_BITMAP_ENDIAN bPixelOrder,                	//Set Bitmap Order Within a Byte
    uint32_t          	dwBitmapStartingAddress,    	//Set Starting Address of Bitmap Loading Operation
    SEINFO_BGCOLOR_EN   bBackgroundColorEnable,     	//Enable/Disable Background Color
    uint32_t          	dwBackgroundColor,          	//Set Specific Value of Background Color
    SEINFO_FGCOLOR_EN   bForegroundColorEnable,     	//Enable/Disable Foreground Color
    uint32_t          	dwForegroundColor,           	//Set Specific Value of Foreground Color
    SEINFO_BITMAP_32BIT_EN bUse32BitColorFormat    		//Use 32-bit Color Format
    );                                          	
                                                	
HRESULT                                         	
SE_DvbSubtitleDecode(                        	//The Definition of Decode_DVB Command for Columbus Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,         	//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,    	//Related Command Parameters of Destination Side 
    uint32_t          	dwPixelDataSubBlockAddress, 	//Set Starting Address for the Pixel-Data_Sub-Block() Data
    uint16_t          	wPixelDataSubBlockLength,   	//Set Length for the Pixel-Data_Sub-Block() Data in Bytes
    SEINFO_NO_COLORMODIFY_EN bNoColorModification      	//If Set, IP Will Not Draw The Pixel When The Decoded Pixel Has an Index Value of '1'
    );              	                            	
                    	                            	
#ifdef CONFIG_PLATFORM_MARS	                            	
HRESULT             	                            	
SE_DrawLine(										//The Definition of Draw Line Command for Mars Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,				//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,		//Related Command Parameters of Destination Side
    SURFACEHANDLE		hSourceHandle,					//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo, 			//Related Command Parameters of Source Side
	SEINFO_ALPHAMODE    bySrcAlphaModeSelect,			//Select Alpha Mode for Source Side
	uint8_t				bySrcAplhaValue,				//Set Specific Alpha Value of Source Side
	SEINFO_ALPHAMODE    byDestAlphaModeSelect,			//Select Alpha Mode for Destination Side
	uint8_t				byDestAplhaValue,	      		//Set Specific Alpha Value of Destination Side
	SEINFO_OUTPUT_ALPHAMODE byOutputAlphaModeSelect,	//Set Output Alpha Mode
	uint8_t				byOutputAlphaValue,				//Set Forced Alpha Value
    SEINFO_GRADIENT    	byGradientModeSelect,			//Set Angle for Gradient Operation
    SEINFO_COLORKEY_DRAWLINE byColorKeySelect,			//Select Color Key
    SEINFO_ROPCODE     	byRopCode						//Set ROP Code for ROP Operation
    );              	                            	
                    	                            	
HRESULT             	                            	
SE_Decimate(										//The Definition of Decimate Command for Mars Streaming Engine
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,				//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,		//Related Command Parameters of Destination Side
    SURFACEHANDLE		hSourceHandle,					//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo, 			//Related Command Parameters of Source Side
    SEINFO_VSCALING_EN	bVerticalScalingEnable,			//Enable /Disable Vertical Scaling
    SEINFO_DECIMATE_SCALING	byVerticalScalingAlgorithmSelect,	//Select Vertical Scaling Algorithm
    SEINFO_HSCALING_EN	bHorizontalScalingEnable, 		//Enable /Disable Horizontal Scaling   
    SEINFO_DECIMATE_SCALING	byHorizontalScalingAlgorithmSelect,	//Select Horizontal Scaling Algorithm
    SEINFO_COLORKEY 	byColorKeySelect,				//Select Color Key   
    SEINFO_ALPHAPROC_EN bAlphaEnable					//Enable /Disable Alpha Operation
    );    

HRESULT
SE_Rotate(
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,				//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,		//Related Command Parameters of Destination Side
    SURFACEHANDLE		hSourceHandle,					//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo, 			//Related Command Parameters of Source Side
    SEINFO_ROTATE      	byRotateMode					//Set Angle of Rotate Operation
    );              	                            	
                    	                            	
HRESULT             	                            	
SE_BdrleDecode(     	                            	
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,				//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,		//Related Command Parameters of Destination Side
    uint32_t          	dwRleCodedLineDataAddress,		//Set Starting Address for the Rle_Coded_Line() Data
    uint16_t          	wRleCodedLineDataLength,		//Set Length for the Rle_Coded_Line() Data in Bytes
    uint16_t			wObjectHeight,					//Height of The Object
    uint16_t			wObjectWidth,					//Width of The Object
    SEINFO_ERRORCOLOR_EN bErrorColorEnable,				//Enable The Fill Function for The Rest of The Line or The Rest of The Object
    uint8_t           	byErrorColorPattern				//The Fill Color Used When bErrorColorEnable is Enabled
    );
    
#endif	//CONFIG_PLATFORM_MARS

//#if IS_CHIP(SATURN) || defined(IS_DARWIN) || defined(IS_MACARTHUR)

HRESULT
SE_Rotate(
	SEINFO_CMDQUEUE 	byCommandQueue,					//Select Specific Command Queue
    SURFACEHANDLE		hDestinationHandle,				//Related Handling Information of Destination Side
    SE_PROCINFO     	*pSeDestinationProcInfo,		//Related Command Parameters of Destination Side
    SURFACEHANDLE		hSourceHandle,					//Related Handling Information of Source Side Handler
    SE_PROCINFO     	*pSeSourceProcInfo, 			//Related Command Parameters of Source Side
    SEINFO_ROTATE      	byRotateMode					//Set Angle of Rotate Operation
    );    
//#endif

HRESULT
SE_ExecCmd(
	SEINFO_CMDQUEUE		byCommandQueue					//Select Specific Command Queue
	);    

HRESULT
SE_WaitCmdDone(
	SEINFO_CMDQUEUE		byCommandQueue					//Select Specific Command Queue
	);  

HRESULT
SE_SetDmaInfo(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	SEINFO_DMAINFO		byDmaChannel,					//Select Specific DMA Channel
	uint32_t			dwBaseAddress,					//Set Base Address of Current DMA Channel
	uint32_t			dwPitch,						//Set Pitch of Current DMA Channel
	SEINFO_INTERLEAVING_MODE bInterleavingModeEnable	//Enable/Disable Interleaving Mode
	); 

HRESULT
SE_SetFelicsDmaInfo(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	SEINFO_DMAINFO		byDmaChannel,					//Select Specific Felics DMA Channel
	uint32_t			dwBaseAddress					//Set Base Address of Current Felics DMA Channel
	); 

HRESULT
SE_SetClippingInfo(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	SEINFO_CLIPPING_EN	bClippingEnable,				//Enable/Disable Clipping Operation
	SEINFO_CLIPPINGINFO	byClippingChannel,				//Select Specific Clipping Channel
	uint16_t			wXmin,							//Set Top Location of X
	uint16_t			wYmin,							//Set Top Location of Y	
	uint16_t			wXmax,							//Set Bottom Location of X
	uint16_t			wYmax							//Set Bottom Location of Y
	); 

HRESULT
SE_SetColorFormat(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	SEINFO_COLOR_FORMAT	byColorFormat,					//Select Specific Color Format
	SEINFO_ARGB_ALPHA_LOCATION byArgbAlphaLocation,		//Select Location of Alpha Bit
	SEINFO_ARGB_ALPHA_LOCATION byOutputArgbAlphaLocation,	//Select Output Location of Alpha Bit
	SEINFO_RGB_LOCATION byRgbLocation,					//Select Location of 2/6 for RGB565/RGB332
	SEINFO_RGB_LOCATION byOutputRgbLocation,			//Select Location of 2/6 for RGB565/RGB332
	void* pExtraParam		                    //Extra parameters depended on platform
	); 

HRESULT
SE_SetColorKey(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwColorKey						//Select Specific Color Key
	);

HRESULT
SE_SetDestColorKey(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwColorKey						//Select Specific Color Key
	);

HRESULT
SE_SetFormatConvertBitblitColorKey(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwColorKey						//Select Specific Color Key
	);

HRESULT
SE_SetSourceColor1(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwSourceColor					//Select Specific Color of Source Side
	);

HRESULT
SE_SetSourceColor2(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwSourceColor					//Select Specific 2nd Color of Source Side
	);

HRESULT
SE_SetSourceAlpha1(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwSourceAlpha					//Select Specific Alpha of Source Side
	);

HRESULT
SE_SetSourceAlpha2(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwSourceAlpha					//Select Specific 2nd Alpha of Source Side
	);

HRESULT
SE_SetDestAlpha(
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwDestAlpha						//Select Specific Alpha of Destination Side
	);

HRESULT
SE_SetConstAlpha(								
	SEINFO_CMDQUEUE		byCommandQueue,					//Select Specific Command Queue
	uint32_t			dwConstAlpha					//Select Specific Const Alpha Value
	);	

size_t
SE_GetBitStreamLength(		
	uint32_t			dwBitStreamBufferAddress		//Base Address of Bitstream Buffer
	);	

HRESULT
SE_WaitVSync(HANDLE hQueue, int count);

HANDLE
SE_RequestQueue(void);

HRESULT
SE_ReleaseQueue(HANDLE hQueue);

HRESULT
SE_SetConvCoeff(SEINFO_CMDQUEUE byCommandQueue);

HRESULT 
SE_Alpha(SEINFO_CMDQUEUE byCommandQueue,                //Select Specific Command Queue
         SE_PROCINFO* pSeSrcProcInfo,                   //Related Command Parameters of Source Side
         SE_PROCINFO* pSeDestProcInfo,                  //Related Command Parameters of Destination Side
         SE_PROCINFO* pSeOutputProcInfo,                //Related Command Parameters of Result Side
         SEINFO_ALPHA_CMD_ALPHA_MODE selAlpha,          //Select alpha mode
         uint8_t srcAplhaValue,                         //Select alpha value
         uint8_t srcChromaAddrIndex ,                //Source chroma address index if source color is YUV
         uint8_t destChromaAddrIndex ,               //Destination chroma address index if source color is YUV
         uint8_t outputChromaAddrIndex ,             //Result chroma address index if source color is YUV
         void* pExtraParam );                     //Extra parameters depended on platform.

HRESULT
SE_Copy(
    SEINFO_CMDQUEUE         byCommandQueue,
    SE_PROCINFO         *pSeDestinationProcInfo,
    SE_PROCINFO         *pSeSourceProcInfo
    );

#ifdef __cplusplus
} // extern "C"
#endif
//=================================================================================================

#endif //_SE_LIB_H_

//=================================================================================================
// End of File
