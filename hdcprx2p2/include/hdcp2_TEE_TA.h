/*
 * types.h
 *
 *  Created on: 2014/8/1
 *      Author: bruce_huang
 */

#ifndef TEE_CA

//#include <tee_kernel_api.h>
#include <tee_client_api.h>

#define __RTK_TEE_HDCP_GENERIC_DEBUG__  1

#if __RTK_TEE_HDCP_GENERIC_DEBUG__
#define TEE_HDCP_DEBUG(format, ...) printf("[TEE_HDCP_DBG] " format "\n", ## __VA_ARGS__)
#else
#define TEE_HDCP_DEBUG(format, ...) 
#endif

#define TEE_HDCP_ERROR(format, ...) printf("[TEE_HDCP_ERR] " format "\n", ## __VA_ARGS__)
#define TEE_HDCP_INFO(format, ...) printf("[TEE_HDCP] " format "\n", ## __VA_ARGS__)




extern unsigned char Message_BACK_id3[];
extern unsigned char Message_BACK_id7[];
extern unsigned char Message_BACK_id10[];


#define TEE_CA_

extern void CA_processAkeInit(unsigned char *message, unsigned int length);
extern void CA_processAkeNoStoredEkm(unsigned char *message, unsigned int length);
extern void CA_processAkeStoredEkm(unsigned char *message, unsigned int length);
extern void CA_processLcInit(unsigned char *message, unsigned int length);
extern void CA_processSkeSendEks(unsigned char *message, unsigned int length);
extern void  CA_hdcp2_Rx_GetEKhKm(unsigned char *pOut, unsigned int  ulSize);


#define TEE_CA_EN 1 



#endif /* TYPES_H_ */
