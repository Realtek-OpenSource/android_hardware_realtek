/*
 * HDCPTX22.h
 *
 *  Created on: 2014/7/31
 *      Author: bruce_huang
 *  Descriptions:
 *  	A simple class to control HDCP 2.2 TX nego protocol (over HDMI interface).
 *  	one may need to convert this class into a HAL structure for android porting.
 */

#ifndef HDCPTX22_H_
#define HDCPTX22_H_

//#include <sys/time.h>

#include <types.h>
#include <HDCP_KEY_SIZE.h>
#include <HDCP_TXRX_CMD.h>
#include <HDCP_ERROR.h>
#include <rcp_api.h>

#define LC128_SIZE (128/8)
#define CERT_RX_SIZE (4176/8)
#define KPRIVRX_SIZE (2560/8)
#define KH_SIZE         ( 128/8 )
#define KM_SIZE (128/8)
#define DKEY_SIZE (128/8)
#define KD_SIZE         ( 256/8 )
#define SESSIONKEY_SIZE ( 128/8 )
#define RIV_SIZE (64/8)


#define SRAM_ALIGN(d)           ((d + 7) & ~0x7)

#define SRAM_LC128_ENTRY        (0)
#define SRAM_LC128_SIZE         (SRAM_ALIGN(LC128_SIZE))

#define SRAM_CERT_RX_ENTRY      (SRAM_LC128_ENTRY + (SRAM_LC128_SIZE >> 3))
#define SRAM_CERT_RX_SIZE       (SRAM_ALIGN(CERT_RX_SIZE))

#define SRAM_KPRIV_RX_ENTRY     (SRAM_CERT_RX_ENTRY + (SRAM_CERT_RX_SIZE >> 3))
#define SRAM_KPRIV_RX_SIZE      (SRAM_ALIGN(KPRIVRX_SIZE))

#define SRAM_KH_ENTRY           (SRAM_KPRIV_RX_ENTRY + (SRAM_KPRIV_RX_SIZE >> 3))
#define SRAM_KH_SIZE            (SRAM_ALIGN(KH_SIZE))

#define SRAM_KM_ENTRY           (SRAM_KH_ENTRY + (SRAM_KH_SIZE >> 3))
#define SRAM_KM_SIZE            (SRAM_ALIGN(KM_SIZE))

#define SRAM_KD_ENTRY           (SRAM_KM_ENTRY + (SRAM_KM_SIZE >> 3))
#define SRAM_KD_SIZE            (SRAM_ALIGN(KD_SIZE))

#define SRAM_DK2_ENTRY          (SRAM_KD_ENTRY + (SRAM_KD_SIZE >> 3))
#define SRAM_DK2_SIZE           (SRAM_ALIGN(DKEY_SIZE))

#define SRAM_KS_XOR_LC128_ENTRY (SRAM_DK2_ENTRY + (SRAM_DK2_SIZE >> 3))
#define SRAM_KS_XOR_LC128_SIZE  (SRAM_ALIGN(SESSIONKEY_SIZE))

#define SRAM_RIV_ENTRY          (SRAM_KS_XOR_LC128_ENTRY + (SRAM_KS_XOR_LC128_SIZE >> 3))
#define SRAM_RIV_SIZE           (SRAM_ALIGN(RIV_SIZE))



/////////////////////////////////////////////////////////////////////////////////

#define spu_SetLc128(v)          RCP_SET_CW(SRAM_LC128_ENTRY,  (unsigned char*) v, LC128_SIZE)
#define spu_GetLc128(v)          RCP_GET_CW(SRAM_LC128_ENTRY,  (unsigned char*) v, LC128_SIZE)

//#define spu_SetCertRx(v)         RCP_SET_CW(SRAM_CERT_RX_ENTRY, (unsigned char*) v, CERT_RX_SIZE)
//#define spu_GetCertRx(v)         RCP_GET_CW(SRAM_CERT_RX_ENTRY, (unsigned char*) v, CERT_RX_SIZE)

//#define spu_SetKPrivRx(v)        RCP_SET_CW(SRAM_KPRIV_RX_ENTRY, (unsigned char*) v, KPRIVRX_SIZE)
//#define spu_GetKPrivRx(v)        RCP_GET_CW(SRAM_KPRIV_RX_ENTRY, (unsigned char*) v, KPRIVRX_SIZE)

#define spu_SetKH(v)             RCP_SET_CW(SRAM_KH_ENTRY, (unsigned char*) v, KH_SIZE)
#define spu_GetKH(v)             RCP_GET_CW(SRAM_KH_ENTRY, (unsigned char*) v, KH_SIZE)

#define spu_SetKM(v)             RCP_SET_CW(SRAM_KM_ENTRY, (unsigned char*) v, KM_SIZE)
#define spu_GetKM(v)             RCP_GET_CW(SRAM_KM_ENTRY, (unsigned char*) v, KM_SIZE)

#define spu_SetKD(v)             RCP_SET_CW(SRAM_KD_ENTRY, (unsigned char*) v, KD_SIZE)
#define spu_GetKD(v)             RCP_GET_CW(SRAM_KD_ENTRY, (unsigned char*) v, KD_SIZE)

#define spu_SetDKey2(v)          RCP_SET_CW(SRAM_DK2_ENTRY, (unsigned char*) v, DKEY_SIZE)
#define spu_GetDKey2(v)          RCP_GET_CW(SRAM_DK2_ENTRY, (unsigned char*) v, DKEY_SIZE)

#define spu_SetKsXorLc128(v)     RCP_SET_CW(SRAM_KS_XOR_LC128_ENTRY, (unsigned char*) v, SRAM_KS_XOR_LC128_SIZE)
#define spu_GetKsXorLc128(v)     RCP_GET_CW(SRAM_KS_XOR_LC128_ENTRY, (unsigned char*) v, SRAM_KS_XOR_LC128_SIZE)

#define spu_SetRiv(v)            RCP_SET_CW(SRAM_RIV_ENTRY, (unsigned char*) v, RIV_SIZE)
#define spu_GetRiv(v)            RCP_GET_CW(SRAM_RIV_ENTRY, (unsigned char*) v, RIV_SIZE)



#define	MSG_BUF_SIZE	64
/** transmitter version **/
#define	HDCP_TRANSMITTER_INFO_VERSION		0x2
#define MAX_DOWNSTREAM_RECEIVERINUM			32

/** HDCP TX state machine **/
typedef enum{
	HDCP_STATE_IDLE,
	HDCP_STATE_SEND_AKE_INIT,
	HDCP_STATE_SEND_NO_STORED_KM,
	HDCP_STATE_SEND_STORED_KM,
	HDCP_STATE_SEND_LC_INIT,
	HDCP_STATE_RESEND_LC_INIT,
	HDCP_STATE_SEND_SKE,
	HDCP_STATE_REPEATER_AUTH_SEND_ACK,
	HDCP_STATE_REPEATER_SEND_STREAM_MANAGE,
	HDCP_STATE_POLLING_RXSTATUS,
}HDCP_STATE;

#if 0
static const char *hdcp_state_str[]={
	STR(HDCP_STATE_IDLE),
	STR(HDCP_STATE_SEND_AKE_INIT),
	STR(HDCP_STATE_SEND_NO_STORED_KM),
	STR(HDCP_STATE_SEND_STORED_KM),
	STR(HDCP_STATE_SEND_LC_INIT),
	STR(HDCP_STATE_RESEND_LC_INIT),
	STR(HDCP_STATE_SEND_SKE),
	STR(HDCP_STATE_REPEATER_AUTH_SEND_ACK),
	STR(HDCP_STATE_REPEATER_SEND_STREAM_MANAGE),
	STR(HDCP_STATE_POLLING_RXSTATUS)
};
#endif

/** define IO callback used by HDCP tx module **/
typedef INT32 (*hdcp_nego_read)(INT8 *buf, INT32 size);
typedef INT32 (*hdcp_nego_write)(INT8 *buf, INT32 size);
typedef INT32 (*hdcp_nego_can_read)(INT32 size);
typedef void (*hdcp_store_rx_info)(UINT8 *rID, INT32 rIDSize, UINT8 *km, INT32 kmSize, UINT8 *ekhkm, INT32 ekhkmSize, UINT8* m, INT32 mSize);
typedef INT32 (*hdcp_find_km_ekhkm)(UINT8 *rID, INT32 rIDSize, UINT8 *km, INT32 kmSize, UINT8 *ekhkm, INT32 ekhkmSize, UINT8* m, INT32 mSize);
typedef HDCP_RST (*hdcp_read_rx_status)(INT8 *reauth, INT8 *ready, INT32 *msg_size);
// called when Send_SKE is complete, deliver riv & ks to upper call module and enable HDCP encryption.
typedef void (*hdcp_auth_complete_handler)(UINT8 *riv, UINT32 riv_size, UINT8 *ks, UINT32 ks_size);
// re-auth happened, a callback for upper module to do something, maybe disable encryption or something.
typedef void (*hdcp_reauth_handler)(void);
// check if connected HDCP receiver is in revocation list
typedef bool (*hdcp_check_revocation_list)(UINT8 *receiverId, UINT8 *cert);

typedef struct{
	UINT8 receiverId[HDCP_RECEIVER_ID_SIZE];
}RepeaterReceiverID;

typedef struct{
	UINT8 hdcp1_device_downstream;
	UINT8 hdcp2_0_repeater_downstream;
	UINT8 max_cascade_exceeded;
	UINT8 max_devs_exceeded;
	UINT8 device_count;
	UINT8 depth;
	RepeaterReceiverID downStreamReceivers[MAX_DOWNSTREAM_RECEIVERINUM];
}RepeaterRxInfo;


void HDCPTx22_init(void);
void HDCPTx22_deinit(void);





	// TODO: public API to allow upper module to deliver content stream management any time
	// refine later, for now, HDCP engine would only deliver one Content Stream Management
	// message to Rx side.

	// internal state control, Tx parameter config
typedef struct {
	// function pointer, provided by Application
	hdcp_nego_read read_fun;
	hdcp_nego_write write_fun;
	hdcp_nego_can_read check_read_fun;
	hdcp_store_rx_info store_rx_info_fun;
	hdcp_find_km_ekhkm find_km_ekhkm_fun;
	hdcp_read_rx_status read_rx_status_fun;
	hdcp_auth_complete_handler auth_complete_fun;
	hdcp_reauth_handler reauth_handler_fun;
	hdcp_check_revocation_list check_revocation_fun;

	HDCP_STATE mState;
	UINT8 mTxVersion;
	UINT32 mLCInitRetryCount;

	// Rx parameter config
	UINT8 mRepeater;
	UINT8 mRxVersion;

	INT8 mKeepPollingRxStatus;
	INT8 mStopHDCPNego;
	INT8 mReauthRetryCount;
	HDCP_ERR mErrCode;

	// HDCP meta data
	UINT8 mRtx[HDCP_RTX_SIZE];
	UINT8 mRrx[HDCP_RRX_SIZE];
	UINT8 mKm[HDCP_KM_SIZE];
	UINT8 mSeed[HDCP_SEED_SIZE];
	UINT8 mDKey0[HDCP_DKEY_SIZE];
	UINT8 mDKey1[HDCP_DKEY_SIZE];
	UINT8 mDKey2[HDCP_DKEY_SIZE];
	UINT8 mKD[HDCP_KD_SIZE];
	UINT8 mH[HDCP_H_SIZE];
	UINT8 mRn[HDCP_RN_SIZE];
	UINT8 mL[HDCP_L_SIZE];
	UINT8 mKs[HDCP_KS_SIZE];
	UINT8 mRIV[HDCP_RIV_SIZE];
	UINT8 mEKS[HDCP_EKS_SIZE];
	UINT8 mEKhKm[HDCP_EKH_KM_SIZE];
	// meta data for AKE_Stored_Km
	UINT8 mStoredKm[HDCP_KM_SIZE];
	UINT8 mStoredEkhKm[HDCP_EKH_KM_SIZE];
	UINT8 mStoredm[HDCP_M_SIZE];
	// meta data for Repeater
	UINT8 mRxInfo[HDCP_RXINFO_SIZE];
	UINT8 mVPrime[HDCP_V_SIZE];
	UINT8 mV[HDCP_V_OUT_SIZE];
	UINT8 mM[HDCP_M_PRIME_SIZE];
	RepeaterRxInfo mRepeaterRxInfo;
	INT32 mSeqNumV;
	// Repeater content stream management
	UINT8 *mPStreamIDType;
	UINT16 mk;
	INT32 mSeqNumM;
	UINT8 mSeqNumMBuf[HDCP_SEQ_NUM_M_SIZE];

	// cipher related buffer
	UINT8 mKsXORLc128[HDCP_KS_SIZE];
	UINT8 mRIVCipher[HDCP_RIV_SIZE];

	// useful fields in Receiver Public Cert
	UINT8 mReceiverID[HDCP_RECEIVER_ID_SIZE];
	UINT8 mReceiverPublicKey[HDCP_RECEIVER_PUBLIC_KEY_SIZE];
	UINT8 mProtocolDescriptor;
	UINT8 mLLCSignature[HDCP_RECEIVER_LLC_SIGNATURE_SIZE];

	// outgoing payload data structure
	AKE_Init_Msg ake_init_msg;
	AKE_No_Stored_km_Msg ake_no_stored_km_msg;
	AKE_Stored_km_Msg ake_stored_km_msg;
	Lc_Init_Msg lc_init_msg;
	SKE_Send_Eks_Msg ske_send_eks_msg;
	RepeaterAuth_Send_Ack_Msg repeaterAuth_send_ack_msg;
	RepeaterAuth_Stream_Manage_Msg_Heading repeaterAuth_stream_manage_msg_h;

	// incoming payload data structure
	AKE_Send_Cert_Msg ake_send_cert_msg;
	AKE_Send_H_Prime_Msg ake_send_h_prime_msg;
	AKE_Send_Pairing_Info_Msg ake_send_pairing_info_msg;
	Lc_Send_L_Prime_No_Precompute_Msg lc_send_l_prime_no_precompute_msg;
	RepeaterAuth_Send_ReceiverID_List_Msg_Heading repeaterAuth_send_receiverId_msg_h;
	RepeaterAuth_Send_ReceiverID_List_Msg_Payload repeaterAuth_send_receiverId_msg_p;
	RepeaterAuth_Stream_Ready_Msg repeaterAuth_stream_ready_msg;
} HdcpTxParam;
	// public APIs of HDCPTx engine
	HDCP_ERR start_hdcp_nego(void);
	void stop_hdcp_polling_rx_status(void);
	void stop_hdcp_nego(void);
	// reset internal control variables when a new transition is going to start.
	void init(void);

	// basic I/O used inside HDCP engine
	HDCP_ERR hdcp_safe_write(INT8 *buf, INT32 size, INT32 *rst);
	HDCP_ERR hdcp_safe_read(INT8 *buf, INT32 size, INT32 *rst);
	HDCP_ERR hdcp_safe_read_with_timeout(INT8 *buf, INT32 size, INT32 *rst, INT32 ms, UINT32* time_consume);

	// HDCP send message functions
	HDCP_ERR send_ake_init(void);
	HDCP_ERR send_ake_nostored_km(void);
	HDCP_ERR send_ake_stored_km(void);
	HDCP_ERR send_lc_init(void);
	HDCP_ERR send_ske(void);
	HDCP_ERR send_repeaterAuth_Ack(void);
	HDCP_ERR send_repeater_auth_content_stream_manage(void);

	// HDCP read message functions
	HDCP_ERR read_ake_send_cert(UINT32 time_out,UINT32 *time_consumed);
	HDCP_ERR read_ake_send_h_prime(UINT32 time_out, UINT32 *time_consumed);
	HDCP_ERR read_ake_send_pairing_info(UINT32 time_out, UINT32 *time_consumed);
	HDCP_ERR read_lc_send_l_prime_no_precompute(UINT32 time_out, UINT32 *time_consumed);
	// repeater commands
	HDCP_ERR read_repeater_auth_receiverId_list(UINT32 time_out, UINT32 *time_consumed);
	HDCP_ERR read_repeater_auth_content_stream_ready(UINT32 time_out, UINT32 *time_consumed);

	HDCP_ERR hdcp_send_msg(void);
	HDCP_ERR hdcp_read_msg(void);

	// HDCP helper functions
	HDCP_RST hdcp_check_stored_km(void);
	void hdcp_generate_random_rtx(void);
	void hdcp_generate_random_km(void);
	void hdcp_generate_random_seed(void);
	void hdcp_generate_random_rn(void);
	void hdcp_generate_random_ks(void);
	void hdcp_generate_random_riv(void);

	// HDCP basic service utility functions
	void hdcp_compute_h(void);
	void hdcp_compute_h_hdmi(void);

	void hdcp_compute_kd(void);
	void hdcp_compute_dkey(INT8 i);
	void hdcp_compute_l_no_precomputation(void);
	void hdcp_save_pairing_info(void);

	// HDCP repeater service utility functions
	HDCP_ERR hdcp_process_receiverId_list(UINT8 *buf, INT32 size);

	// timeout control related
	UINT32 hdcp_get_duration(struct timeval *start, struct timeval* end);

	// debug helper functions

	void dump_buffer(INT8 *buf, INT32 size, INT8 *description);
	void compare_buffers(INT8 *buf1, INT8 *buf2, INT32 size, INT8 *description);

	// verification functions
	HDCP_RST check_LLC_signature(void);
	HDCP_RST check_smr(void);
	// random number generator
	void generate_random_number(UINT8 *dst, INT32 size, const char *msg);
	// RxStatus monitor routine.
	void polling_rx_status(void);


#endif /* HDCPTX22_H_ */
