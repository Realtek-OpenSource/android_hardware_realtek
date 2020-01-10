//--=========================================================================--
//  This file is a part of VPU Reference API project
//-----------------------------------------------------------------------------
//
//       This confidential and proprietary software may be used only
//     as authorized by a licensing agreement from Chips&Media Inc.
//     In the event of publication, the following notice is applicable:
//
//            (C) COPYRIGHT 2006 - 2011  CHIPS&MEDIA INC.
//                      ALL RIGHTS RESERVED
//
//       The entire notice above must be reproduced on all authorized
//       copies.
//		This file should be modified by some customers according to their SOC configuration.
//--=========================================================================--

#ifndef _VPU_CONFIG_H_
#define _VPU_CONFIG_H_
#include "../config.h"


#define BODA950_CODE                    0x9500
#define CODA960_CODE                    0x9600
#define CODA980_CODE                    0x9800
#define WAVE510_CODE                    0x5100
#define WAVE512_CODE                    0x5120
#define WAVE520_CODE                    0x5200

#define PRODUCT_CODE_W_SERIES(x) (x == WAVE510_CODE || x == WAVE512_CODE || x == WAVE520_CODE)
#define PRODUCT_CODE_NOT_W_SERIES(x) (x == BODA950_CODE || x == CODA960_CODE || x == CODA980_CODE)

#define WAVE5_MAX_CODE_BUF_SIZE             (1024*1024)
#define WAVE5ENC_WORKBUF_SIZE               (128*1024)
#define WAVE512DEC_WORKBUF_SIZE             (2*1024*1024)


#define MAX_INST_HANDLE_SIZE            (32*1024)
#define MAX_NUM_INSTANCE                8
#define MAX_NUM_VPU_CORE                2
#define MAX_NUM_VCORE                   1

#ifdef PRODUCT_1GB_1080P
#define MAX_ENC_AVC_PIC_WIDTH           2048
#define MAX_ENC_AVC_PIC_HEIGHT          1088
#define MAX_ENC_PIC_WIDTH               2048
#define MAX_ENC_PIC_HEIGHT              1088
#else
#define MAX_ENC_AVC_PIC_WIDTH           4096
#define MAX_ENC_AVC_PIC_HEIGHT          2304
#define MAX_ENC_PIC_WIDTH               4096
#define MAX_ENC_PIC_HEIGHT              2304
#endif
#define MIN_ENC_PIC_WIDTH               96
#define MIN_ENC_PIC_HEIGHT              16

// for WAVE420
#define W4_MIN_ENC_PIC_WIDTH            256
#define W4_MIN_ENC_PIC_HEIGHT           128
#define W4_MAX_ENC_PIC_WIDTH            8192
#define W4_MAX_ENC_PIC_HEIGHT           8192

#ifdef PRODUCT_1GB_1080P
#define MAX_DEC_PIC_WIDTH               2048
#define MAX_DEC_PIC_HEIGHT              1088
#else
#define MAX_DEC_PIC_WIDTH               4096
#define MAX_DEC_PIC_HEIGHT              2304
#endif

#define MAX_CTU_NUM                     0x4000      // CTU num for max resolution = 8192x8192/(64x64)
#define MAX_SUB_CTU_NUM	                (MAX_CTU_NUM*4)

//  Application specific configuration
#ifdef HAPS_SIM
#define VPU_ENC_TIMEOUT                 (5000*1000)
#define VPU_DEC_TIMEOUT                 (5000*1000)
#define VPU_BUSY_CHECK_TIMEOUT          (5000*1000)
#else
#define VPU_ENC_TIMEOUT                 60000
#define VPU_DEC_TIMEOUT                 10000
#define VPU_BUSY_CHECK_TIMEOUT          5000
#endif /* HAPS_SIM */

// codec specific configuration
#define VPU_REORDER_ENABLE              1   // it can be set to 1 to handle reordering DPB in host side.
#define CBCR_INTERLEAVE			        1 //[default 1 for BW checking with CnMViedo Conformance] 0 (chroma separate mode), 1 (chroma interleave mode) // if the type of tiledmap uses the kind of MB_RASTER_MAP. must set to enable CBCR_INTERLEAVE
#define VPU_ENABLE_BWB			        1

#define HOST_ENDIAN                     VDI_LITTLE_ENDIAN //VDI_128BIT_LITTLE_ENDIAN //RTK change endian from VDI_128BIT_LITTLE_ENDIAN to VDI_LITTLE_ENDIAN
#define VPU_FRAME_ENDIAN                HOST_ENDIAN
#define VPU_STREAM_ENDIAN               HOST_ENDIAN
#define VPU_USER_DATA_ENDIAN            HOST_ENDIAN
#define VPU_SOURCE_ENDIAN               HOST_ENDIAN
#define DRAM_BUS_WIDTH                  16

#define W512_VPU_FRAME_ENDIAN		VDI_128BIT_LITTLE_ENDIAN
#define W512_VPU_STREAM_ENDIAN		VDI_128BIT_LITTLE_ENDIAN
#define W512_VPU_USER_DATA_ENDIAN   VDI_128BIT_LITTLE_ENDIAN

/************************************************************************/
/* VPU COMMON MEMORY                                                    */
/************************************************************************/
#ifdef PRODUCT_1GB_1080P
#define COMMAND_QUEUE_DEPTH             1
#else
#define COMMAND_QUEUE_DEPTH             4
#endif

#define ONE_TASKBUF_SIZE_FOR_W5DEC_CQ         (8*1024*1024)   /* upto 8Kx4K, need 8Mbyte per task*/
#define ONE_TASKBUF_SIZE_FOR_W5ENC_CQ         (8*1024*1024)   /* upto 8Kx8K, need 8Mbyte per task.*/
#define ONE_TASKBUF_SIZE_FOR_W5DEC_4K_CQ      (7*1024*1024)   /* upto 4Kx2K, need 7Mbyte per task*/
#define ONE_TASKBUF_SIZE_FOR_W5DEC_1080P_CQ   (3*1024*1024)   /* upto 2048x1088, need 2Mbyte per task*/

#ifdef PRODUCT_1GB_1080P
#define ONE_TASKBUF_SIZE_FOR_CQ     ONE_TASKBUF_SIZE_FOR_W5DEC_1080P_CQ
#else
#define ONE_TASKBUF_SIZE_FOR_CQ     ONE_TASKBUF_SIZE_FOR_W5DEC_4K_CQ //ONE_TASKBUF_SIZE_FOR_W5DEC_CQ
#endif

#define SIZE_COMMON                 (2*1024*1024)
#define SIZE_COMMON_W5_CQ           ((2*1024*1024) + (COMMAND_QUEUE_DEPTH*ONE_TASKBUF_SIZE_FOR_CQ))

//=====4. VPU REPORT MEMORY  ======================//
#define SIZE_REPORT_BUF                 (0x10000)

#define STREAM_END_SIZE                 0
#define STREAM_END_SET_FLAG             0
#define STREAM_END_CLEAR_FLAG           -1
#define EXPLICIT_END_SET_FLAG           -2

#define USE_BIT_INTERNAL_BUF            1
#define USE_IP_INTERNAL_BUF             1
#define USE_DBKY_INTERNAL_BUF           1
#define USE_DBKC_INTERNAL_BUF           1
#define USE_OVL_INTERNAL_BUF            1
#define USE_BTP_INTERNAL_BUF            1
#define USE_ME_INTERNAL_BUF             1

/* WAVE410 only */
#define USE_BPU_INTERNAL_BUF            1
#define USE_VCE_IP_INTERNAL_BUF         1
#define USE_VCE_LF_ROW_INTERNAL_BUF     1

/* WAVE420 only */
#define USE_IMD_INTERNAL_BUF            1
#define USE_RDO_INTERNAL_BUF            1
#define USE_LF_INTERNAL_BUF             1


#endif  /* _VPU_CONFIG_H_ */

