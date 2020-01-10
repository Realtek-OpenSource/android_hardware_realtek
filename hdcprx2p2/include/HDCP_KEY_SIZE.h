/*
 * HDCP_KEY_SIZE.h
 *
 *  Created on: 2014/8/4
 *      Author: bruce_huang
 */

#ifndef HDCP_KEY_SIZE_H_
#define HDCP_KEY_SIZE_H_

#include <crypto.h>

#define	HDCP_RTX_SIZE						8
#define	HDCP_RRX_SIZE						8
#define HDCP_M_SIZE							(HDCP_RTX_SIZE+HDCP_RRX_SIZE)	// m = (rtx || rrx)
#define	HDCP_CTR_SIZE						8	// ctr buffer used in calculating dkey i, it's size follows rtx and rrx
#define	HDCP_IV_SIZE						16	// IV = rtx || rrx , so it's size should be 16

#define	HDCP_KM_SIZE						(128/8)		// 16
//#define SHA256_DIGEST_SIZE 					(256/8)		// 32
#define	HDCP_SEED_SIZE						SHA256_DIGEST_SIZE	// should always be 32 bytes
#define	HDCP_EKPUB_KM_SIZE					(1024/8)
#define	HDCP_EKH_KM_SIZE					16
#define	HDCP_DKEY_SIZE						(128/8)
#define	HDCP_KD_SIZE						(256/8)	// kd = dkey0 || dkey1, so it's size is DKEY_SIZE x 2
#define	HDCP_H_SIZE							(256/8)
#define	HDCP_RN_SIZE						(64/8)
#define	HDCP_L_SIZE							32
#define	HDCP_KS_SIZE						(128/8)
#define	HDCP_RIV_SIZE						(64/8)
#define	HDCP_EKS_SIZE						(128/8)
#define	HDCP_RXTX_CAPS_SIZE					3
#define HDCP_TX_MODULUS_N_SIZE				384
#define	HDCP_TX_PUBLIC_EXPONENT_E_SIZE		1

#define HDCP_RECEIVER_ID_SIZE				5
#define	HDCP_RECEIVER_PUBLIC_KEY_SIZE		131	// (1024 bits n + 24 bits e)
#define	HDCP_RECEIVER_LLC_SIGNATURE_SIZE	384	// 3072/8
#define	HDCP_RECEIVER_CERT_RX_SIZE			522

/**
 * refer to table 2.1,
 * byte nums of
 * 1. ReceiverID             5
 * 2. Receiver Public key    131
 * 3. Reserved2
 * 4. Reserved1              2
 */
#define HDCP_LLC_SIGNATURE_M_SIZE			138

// Repeater commands related
#define	HDCP_RXINFO_SIZE					2
#define	HDCP_SEQ_NUM_V_SIZE					3
#define	HDCP_V_SIZE							16
#define HDCP_V_OUT_SIZE						(256/8)
#define	HDCP_SEQ_NUM_M_SIZE					3
#define	HDCP_K_SIZE							2
#define	HDCP_M_PRIME_SIZE					32

#endif /* HDCP_KEY_SIZE_H_ */
