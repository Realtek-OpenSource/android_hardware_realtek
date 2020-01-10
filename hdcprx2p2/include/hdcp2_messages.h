#ifndef HDCP2_MESSAGES_H
#define HDCP2_MESSAGES_H
typedef enum {
	NULL_MSG = 1,
	AKE_INIT = 2,
	AKE_SEND_CERT = 3,
	AKE_NO_STORED_EKM = 4,
	AKE_STORED_EKM = 5,
	AKE_SEND_RRX = 6,
	AKE_SEND_H_PRIME = 7,
	AKE_SEND_PAIRING_INFO = 8,
	LC_INIT = 9,
	LC_SEND_L_PRIME = 10,
	SKE_SEND_EKS = 11,
	REP_AUTH_SEND_RXID_LIST = 12,
	REPEATERAUTH_SEND_ACK = 15,
	REPEATERAUTH_STREAM_MANAGE = 16,
	REPEATERAUTH_STREAM_READY = 17,
	AKE_TRANSMITTER_INFO = 19,
	AKE_RECEIVER_INFO = 20,
} HDCPMsgId_t;

/**
 * Defines from the HDCP2 Interface Independent Adaptation Spec, Rev 2.2
 */

#define RTX_SIZE  (64 / 8)
#define TXCAPS_SIZE (24 / 8)
#define CERT_RX_SIZE (4176 / 8)
#define RRX_SIZE (64 / 8)
#define RXCAPS_SIZE (24 / 8)
#define KM_SIZE (128 / 8)
#define EKPUBKM_SIZE (1024 / 8)
#define H_SIZE (256 / 8)
#define RN_SIZE (64 / 8)
#define KD_SIZE         (256 / 8)
#define EKHKM_SIZE (128 / 8)
#define M_SIZE (RTX_SIZE + RRX_SIZE)
#define L_SIZE (256 / 8)
#define KS_SIZE (128 / 8)
#define RIV_SIZE (64 / 8)
#define DKEY_SIZE (128 / 8)
#define V_SIZE (256 / 8)
#define MP_SIZE (256 / 8)
#define DB_SIZE 95
#define DCP_LLC_KEY_SIZE 385
#define KEYSET_SIZE 864

//cloud add
#define seq_num_M_SIZE 3
#define Manage_k_SIZE 2
#define Stream_Type_SIZE  2

#define Mprime_SIZE  32

#define MAX_PACKED_MSG_SIZE (CERT_RX_SIZE + 2)
#define AKE_MSG_SEND_RRX_SIZE (RRX_SIZE + 1)
#define AKE_MSG_SEND_HPRIME_SIZE (H_SIZE + 1)
#define AKE_MSG_SEND_LPRIME_SIZE (L_SIZE + 1)
#define AKE_MSG_SEND_MOST_LPRIME_SIZE ((L_SIZE / 2) + 1)
#define AKE_TRANSMITTER_LENGTH_SIZE (16 / 8)
#define AKE_TRANSMITTER_VERSION_SIZE (8 / 8)
#define AKE_TRANSMITTER_CAPABILITY_MASK_SIZE (16 / 8)
#define AKE_TRANSMITTER_INFO_PAYLOAD_SIZE (AKE_TRANSMITTER_LENGTH_SIZE + AKE_TRANSMITTER_VERSION_SIZE + AKE_TRANSMITTER_CAPABILITY_MASK_SIZE)
#define AKE_RECEIVER_INFO_PAYLOAD_SIZE (AKE_TRANSMITTER_LENGTH_SIZE + AKE_TRANSMITTER_VERSION_SIZE + AKE_TRANSMITTER_CAPABILITY_MASK_SIZE)

/* Bruce try to define HDCP 2.2 related data length here*/
#define	AKE_COMPUTE_H_PRIME_META_BUF_SIZE	(14)	/*rtx + 1 + 2 + 1 + 2 refer to HDCP 2.2 spec p.78*/
#define	DOUBLE_RN_BUF_SIZE					(128 / 8)

#define RECEIVER_ID_SIZE (40 / 8)
#define KEY_PUBLIC_RX_SIZE (1048 / 8)
#define RESERVED_SIZE (16 / 8)
#define DCP_LLC_SIG_SIZE (3072 / 8)

#define KEY_PUBLIC_DCPLLC_N_SIZE (3072 / 8)
#define KEY_PUBLIC_DCPLLC_E_SIZE (8 / 8)

#define KEY_PUBLIC_RX_N_SIZE (1024 / 8)
#define KEY_PUBLIC_RX_E_SIZE (24 / 8)

#define AKEINIT_MSG_SIZE (1 + RTX_SIZE + TXCAPS_SIZE)
#define AKESENDCERT_MSG_SIZE (1 + CERT_RX_SIZE + RRX_SIZE + RXCAPS_SIZE)

#define CERT_RESERVED_SIZE (16 / 8)
#define CERT_SIGN_SIZE (3072 / 8)
#define LC128_SIZE (128 / 8)
#define KPRIVRX_SIZE (2560 / 8)

#define EDKEYKS_SIZE (128 / 8)

#define MAX_DEPTH (4)
#define MAX_DEVICECOUNT (32)
#define REPEATERAUTHLIST_BASE_SIZE (37)
#define RECEIVERID_SIZE (40 / 8)
#define MAX_PACKED_MSG_SIZE (CERT_RX_SIZE + 2)
#define RXID_SIZE (40 / 8)
#define KPUBRX_SIZE (1048 / 8)
#define KPUBRX_P    (512 / 8)
#define KPUBRX_Q    (512 / 8)
#define KPUBRX_dP   (512 / 8)
#define KPUBRX_dQ   (512 / 8)
#define KPUBRX_qInv (512 / 8)

#define SESSIONKEY_SIZE (128 / 8)
#define MASTERKEY_SIZE  (128 / 8)
#define KH_SIZE         (128 / 8)
#define CTR_SIZE        (64 / 8)
#define STREAM_CTR_SIZE (32 / 8)
#define AES_BLK_SIZE    (256 / 8)

#define RXinfo_SIZE    (2)

#define Seq_num_V_SIZE    (3)
#ifdef TEST_HDCP2_2_TX_DRIVER
typedef struct {
	unsigned short Transmitter_cap_mask;
	unsigned char Version;
} H2_TxCapsPayLoad;

typedef struct {
	unsigned char rTx[RTX_SIZE];
} H2_RTxPayLoad;

typedef struct {
	unsigned char Cert_rx[CERT_RX_SIZE];
} H2_CertRxPayLoad;

typedef struct {
	unsigned short Receiver_cap_mask;
	unsigned char Version;
} H2_RxCapsPayLoad;

typedef struct {
	unsigned char rRx[RRX_SIZE];
} H2_RRxPayLoad;

#endif	/*  */

#ifdef TEST_HDCP2_2_RX_DRIVER

/* Message Ids from HDCP Interface Independent Adaptation Specification
	 Revision 2.0.*/
typedef struct {
	unsigned char rTx[RTX_SIZE];
} H2_AKEInitPayLoad;

/*
typedef struct
{
	unsigned short Receiver_cap_mask;
	unsigned char Version;
}H2_RxCapsPayLoad;

*/
typedef struct {
	unsigned char EKpub_Km[EKPUBKM_SIZE];
} H2_AKENoStoredEkmPayLoad;
typedef struct {
	unsigned char EKh_Km[EKHKM_SIZE];
	unsigned char m[M_SIZE];
} H2_AKEStoredEkmPayLoad;
typedef struct {
	unsigned char rn[RN_SIZE];
} H2_LCInitPayLoad;
typedef struct {
	unsigned char Edkey_Ks[EDKEYKS_SIZE];
	unsigned char riv[RIV_SIZE];
} H2_SKESendEksPayLoad;

/* Messages sent from Rx to Tx*/
typedef struct {
	unsigned char Cert_rx[CERT_RX_SIZE];
	unsigned char rrx[RRX_SIZE];
	unsigned char rxcaps[RXCAPS_SIZE];
} H2_AKESendCertPayLoad;
typedef struct {
	unsigned char rrx[RRX_SIZE];
} H2_AKESendrrxPayLoad;
typedef struct {
	unsigned char Hprime[H_SIZE];
} H2_AKESendHprimePayLoad;
typedef struct {
	unsigned char Ekh_Km[EKHKM_SIZE];
} H2_AKESendPairingInfoPayLoad;
typedef struct {
	unsigned char Lprime[L_SIZE];
} H2_LCSendLprimePayLoad;

#define H2_MAX_DEVICECOUNT 31
typedef struct {
/*
	unsigned char maxDevsExceeded;	// true if devcount > 31
	unsigned char maxCascadeExceeded;	// true if depth > 4
	unsigned char deviceCount;
	unsigned char depth;
	unsigned char VPrime[V_SIZE];
	*/
		unsigned char Rxinfo[2];
	unsigned char Seq_num[3];
	unsigned char VPrime[32]; //V_SIZE/2
	unsigned char Receiver_ID_LIST[RECEIVERID_SIZE*MAX_DEVICECOUNT]; //V_SIZE/2
	unsigned char maxDevsExceeded; /* true if devcount > 31*/
	unsigned char maxCascadeExceeded;   /* true if depth > 4*/
	unsigned char deviceCount;
	unsigned char depth;
	unsigned char HDCP2_0_repeater_downstream;
	unsigned char HDCP1_device_downstream;
} H2_RepeaterAuthSendRxIdList_PayLoad;

typedef struct {
unsigned char V[16];

} H2_RepeaterSendAck_PayLoad;



typedef struct {
unsigned char seq_num_M[seq_num_M_SIZE];
unsigned char Manage_k[Manage_k_SIZE];
unsigned char Stream_Type[Stream_Type_SIZE];

} H2_RepeaterAuthStreamManage_PayLoad;


typedef struct {
unsigned char MPrime[Mprime_SIZE];
} H2_RepeaterAuthStreamReady_PayLoad;

/**
 * Pack and unpack functions. These functions convert the incoming packed
 * message into structures which can be more easily manipulated.
 *
 * The Unpack() functions are for TX -> RX messages, and Pack() functions
 * are for RX -> TX messages.
 */
int h2MsgAkeInitUnpack(const unsigned char *pMsg, unsigned int length,
			   H2_AKEInitPayLoad * payload);
int h2MsgAkeSendCertPack(unsigned char *pMsg, unsigned int *pLength,
			   const H2_AKESendCertPayLoad *payload);
int h2MsgAkeNoStoredEkmUnpack(const unsigned char *pMsg, unsigned int length,
				H2_AKENoStoredEkmPayLoad *payload);
int h2MsgAkeStoredEKmUnpack(const unsigned char *pMsg, unsigned int length,
			      H2_AKEStoredEkmPayLoad *payload);
int h2MsgAkeSendRrxPack(unsigned char *pMsg, unsigned int *pLength,
			  const H2_AKESendrrxPayLoad *payload);
int h2MsgAkeSendHprimePack(unsigned char *pMsg, unsigned int *pLength,
			     const H2_AKESendHprimePayLoad *payload);
int h2MsgAkeSendPairingInfoPack(unsigned char *pMsg, unsigned int *pLength,
				  const H2_AKESendPairingInfoPayLoad *payload);
int h2MsgLcInitUnpack(const unsigned char *pMsg, unsigned int length,
			H2_LCInitPayLoad *payload);
int h2MsgLcSendLprimePack(unsigned char *pMsg, unsigned int *pLength,
			    const H2_LCSendLprimePayLoad *payload);
int h2MsgSkeSendEksUnpack(const unsigned char *pMsg, unsigned int length,
			    H2_SKESendEksPayLoad *payload);
int h2MsgRepeaterAuthSendReceiverIdListPack(unsigned char *pMsg,
					      unsigned int *pLength,
					      const
					      H2_RepeaterAuthSendRxIdList_PayLoad
					      *payload,
					      const unsigned char *rcvrIds);

int h2MsgRepeaterAuthStraeamManageUnpack(const unsigned char *pMsg, unsigned int length, H2_RepeaterAuthStreamManage_PayLoad *payload);

int h2MsgRepeaterAuthStreamReadyPack(unsigned char *pMsg, unsigned int *pLength,
					      const H2_RepeaterAuthStreamReady_PayLoad *payload);

#endif	/*  */
#endif
