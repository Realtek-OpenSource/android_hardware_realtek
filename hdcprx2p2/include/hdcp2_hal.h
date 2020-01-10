/**
 * Hardware specific defines
 *
 * INTEL CONFIDENTIAL
 * Copyright 2010-2011 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to
 * the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors.  Title to the Material remains with Intel
 * Corporation or its suppliers and licensors.  The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors.  The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material may
 * be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or
 * delivery of the Materials,  either expressly, by implication, inducement,
 * estoppel or otherwise.  Any license under such intellectual property
 * rights must be express and approved by Intel in writing.
 */

#ifndef HDCP2_HAL_H
#define HDCP2_HAL_H
#define TEST_HDCP2_2_RX_DRIVER
#include <linux/kernel.h>
//#include <linux/slab.h>
#include <linux/fs.h>
//#include <linux/delay.h>
#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/uaccess.h>

#define H2uint8  unsigned char
#define H2uint16 unsigned short
#define H2uint32 unsigned int
#define H2uint64 unsigned long

/* Define boolean types */
#define H2bool   unsigned char

#define TRUE     1
#define FALSE    0

#define HDCP2X_AES_KEY_0  0x39dfc22d
#define HDCP2X_AES_KEY_1  0xd0210342
#define HDCP2X_AES_KEY_2  0x233ff1ce
#define HDCP2X_AES_KEY_3  0x959d0274
/* Define status codes */
typedef enum {
	H2_OK = 0,
	H2_ERROR
} H2status;

/* Define log function */
#define ENABLE  1
#define DISABLE 0
#define ENABLE_DDC_WRITE    1

/*void debugLogPrint( H2bool bEnable, const char * pFmt, ... );*/
#define HDCP2DBGLOG(key, msg, len)  do {pr_debug(key); spu_print(msg, len); } while (0)
#define H2DBGLOG(arg)		/*do{ debugLogPrint arg ; }while(0)*/
void spu_print(unsigned char *message, int length);
/* Define the H2Sha256Ctx structure. */

extern void Hdmi_HDCP_2_2_Init(void);
extern void  msg_hander(void);
extern void drvif_Hdmi_HDCP2_2_Write_Data_to_TX(unsigned char* bSendData,unsigned short wLen);
extern void drvif_KS_Setting(unsigned char* bKs);
#endif
