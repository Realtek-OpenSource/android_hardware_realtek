/*
 * HDCP_TX_CMD.h
 *
 *  Created on: 2014/7/31
 *      Author: bruce_huang
 */

#ifndef HDCP_TXRX_CMD_H_
#define HDCP_TXRX_CMD_H_

#include "types.h"
#include "HDCP_KEY_SIZE.h"

/** Following define TxRx command message ID **/
#define	AKE_INIT				2
#define	AKE_SEND_CERT			3
#define	AKE_NO_STORED_KM		4
#define	AKE_STORED_KM			5
#define	AKE_SEND_H_PRIME		7
#define	AKE_SEND_PAIRING_INFO	8
#define	LC_INIT					9
#define	LC_SEND_L_PRIME			10
#define	SKE_SEND_EKS			11
// repeater commands
#define REPEATER_AUTH_SEND_RECEIVERID_LIST	12
#define REPEATER_AUTH_SEND_ACK				15
#define	REPEATER_AUTH_STREAM_MANAGE			16
#define REPEATER_AUTH_STREAM_READY			17

/** Following define date structure of each message payload **/
typedef struct{
	UINT8 id;
	UINT8 rtx[HDCP_RTX_SIZE];
	UINT8 TxCaps[HDCP_RXTX_CAPS_SIZE];
}AKE_Init_Msg;

typedef struct{
	UINT8 id;
	//UINT8 repeater;
	UINT8 cert_rx[HDCP_RECEIVER_CERT_RX_SIZE];
	UINT8 rrx[HDCP_RRX_SIZE];
	UINT8 RxCaps[HDCP_RXTX_CAPS_SIZE];
}AKE_Send_Cert_Msg;

typedef struct{
	UINT8 id;
	UINT8 e_kpub_km[HDCP_EKPUB_KM_SIZE];
}AKE_No_Stored_km_Msg;

typedef struct{
	UINT8 id;
	UINT8 e_kh_km[HDCP_EKH_KM_SIZE];
	UINT8 m[HDCP_M_SIZE];
}AKE_Stored_km_Msg;

typedef struct{
	UINT8 id;
	UINT8 h_prime[HDCP_H_SIZE];
}AKE_Send_H_Prime_Msg;

typedef struct{
	UINT8 id;
	UINT8 e_kh_km[HDCP_EKH_KM_SIZE];
}AKE_Send_Pairing_Info_Msg;

typedef struct{
	UINT8 id;
	UINT8 rn[HDCP_RN_SIZE];
}Lc_Init_Msg;

typedef struct{
	UINT8 id;
	UINT8 l_prime[HDCP_L_SIZE];
}Lc_Send_L_Prime_No_Precompute_Msg;

typedef struct{
	UINT8 id;
	UINT8 edkey_ks[HDCP_EKS_SIZE];
	UINT8 r_iv[HDCP_RIV_SIZE];
}SKE_Send_Eks_Msg;


typedef struct{
	UINT8 id;
	UINT8 rxInfo[HDCP_RXINFO_SIZE];
	/**
	 *
	 * if(MAX_DEVS_EXCEEDED!=1 && MAX_CASCADE_EXCEEDED!=1){
	 * 		RepeaterAuth_Send_ReceiverID_List_Msg_Payload
	 * 		ReceiverID List.
	 * }
	 */
}RepeaterAuth_Send_ReceiverID_List_Msg_Heading;

typedef struct{
	UINT8 seq_num_V[HDCP_SEQ_NUM_V_SIZE];
	UINT8 v_prime[HDCP_V_SIZE];
	// ReceiverIDList[i]
}RepeaterAuth_Send_ReceiverID_List_Msg_Payload;

typedef struct{
	UINT8 id;
	UINT8 v[HDCP_V_SIZE];
}RepeaterAuth_Send_Ack_Msg;

typedef struct{
	UINT8 id;
	UINT8 seq_sum_m[HDCP_SEQ_NUM_M_SIZE];
	UINT8 k[HDCP_K_SIZE];
	// StreamID_Type[2*k]
}RepeaterAuth_Stream_Manage_Msg_Heading;

typedef struct{
	UINT8 id;
	UINT8 m_prime[HDCP_M_PRIME_SIZE];
}RepeaterAuth_Stream_Ready_Msg;

#endif /* HDCP_TXRX_CMD_H_ */
