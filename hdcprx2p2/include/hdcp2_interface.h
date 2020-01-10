#ifndef HDCP2_TX_INTERFACE_H
#define HDCP2_TX_INTERFACE_H
#include <hdcp2_hal.h>
#include <hdcp2_messages.h>
/*
typedef enum
{
   H2_OK = 0,
   H2_ERROR

} H2status;
*/

extern unsigned char global_certRx[CERT_RX_SIZE];
extern unsigned char global_kprivRx[KPRIVRX_SIZE];

#define REAPETER_2p2  0 // TEST 
/*
/////////////////////////////////////////////////////
// layout of secure flush (1KB : 0x3FF)
//---------------------------------------------------
// 0x000-0x00F : lc128     S (16)
// 0x010-0x21F : cert_rx   N (522 + 6 padding)
// 0x220-0x35F : kpriv_rx  S (320)
// 0x360-0x36F : kh        S (16)
// 0x370-0x37F : km        S (16)
// 0x380-0x39F : kd        S (32)
// 0x3A0-0x3AF : dkey2     S (16)
// 0x3B0-0x3BF : Ks^lc128  S (16)   TS Descramble Key
// 0x3C0-0x3C7 : Riv       S (8)
// 0x3C8-0x3D7 : ks        S (16)
/////////////////////////////////////////////////////
*/
//#define HDCP2_ENTRY         	(57)
#define HDCP2_ENTRY         	(0)

#define SRAM_ALIGN(d)           ((d + 7) & ~0x7)

#define SRAM_LC128_ENTRY        (HDCP2_ENTRY)
#define SRAM_LC128_SIZE         (SRAM_ALIGN(LC128_SIZE))

//#define SRAM_CERT_RX_ENTRY      (SRAM_LC128_ENTRY + (SRAM_LC128_SIZE >> 3))
//#define SRAM_CERT_RX_SIZE       (SRAM_ALIGN(CERT_RX_SIZE))

//#define SRAM_KPRIV_RX_ENTRY     (SRAM_CERT_RX_ENTRY + (SRAM_CERT_RX_SIZE >> 3))
//#define SRAM_KPRIV_RX_SIZE      (SRAM_ALIGN(KPRIVRX_SIZE))

#define SRAM_KH_ENTRY           (SRAM_LC128_ENTRY + (SRAM_LC128_SIZE >> 3))
#define SRAM_KH_SIZE            (SRAM_ALIGN(KH_SIZE))

#define SRAM_KM_ENTRY           (SRAM_KH_ENTRY + (SRAM_KH_SIZE >> 3))
#define SRAM_KM_SIZE            (SRAM_ALIGN(MASTERKEY_SIZE))

#define SRAM_KD_ENTRY           (SRAM_KM_ENTRY + (SRAM_KM_SIZE >> 3))
#define SRAM_KD_SIZE            (SRAM_ALIGN(KD_SIZE))

#define SRAM_DK2_ENTRY          (SRAM_KD_ENTRY + (SRAM_KD_SIZE >> 3))
#define SRAM_DK2_SIZE           (SRAM_ALIGN(DKEY_SIZE))

#define SRAM_KS_XOR_LC128_ENTRY (SRAM_DK2_ENTRY + (SRAM_DK2_SIZE >> 3))
#define SRAM_KS_XOR_LC128_SIZE  (SRAM_ALIGN(SESSIONKEY_SIZE))

#define SRAM_RIV_ENTRY          (SRAM_KS_XOR_LC128_ENTRY + (SRAM_KS_XOR_LC128_SIZE >> 3))
#define SRAM_RIV_SIZE           (SRAM_ALIGN(RIV_SIZE))

#define SRAM_DATA_DECRYPT_ENTRY (SRAM_RIV_ENTRY + (RIV_SIZE >> 3))
#define SRAM_DATA_DECRYPT_SIZE  (SRAM_ALIGN(SESSIONKEY_SIZE))


/*//////////////////////////////////////////////////////////////////////////////*/

#define spu_SetLc128(v)          RCP_SET_CW(SRAM_LC128_ENTRY,  (unsigned char *) v, LC128_SIZE)
#define spu_GetLc128(v)          RCP_GET_CW(SRAM_LC128_ENTRY,  (unsigned char *) v, LC128_SIZE)

#define spu_SetCertRx(v)         memcpy(global_certRx,(unsigned char*)v, CERT_RX_SIZE)//RCP_SET_CW(SRAM_CERT_RX_ENTRY, (unsigned char *) v, CERT_RX_SIZE)
#define spu_GetCertRx(v)         memcpy((unsigned char*)v,global_certRx, CERT_RX_SIZE)//RCP_GET_CW(SRAM_CERT_RX_ENTRY, (unsigned char *) v, CERT_RX_SIZE)

#define spu_SetKPrivRx(v)        memcpy(global_kprivRx,(unsigned char*)v, KPRIVRX_SIZE)//RCP_SET_CW(SRAM_KPRIV_RX_ENTRY, (unsigned char *) v, KPRIVRX_SIZE)
#define spu_GetKPrivRx(v)        memcpy((unsigned char*)v, global_kprivRx,KPRIVRX_SIZE)//RCP_GET_CW(SRAM_KPRIV_RX_ENTRY, (unsigned char *) v, KPRIVRX_SIZE)

#define spu_SetKH(v)             RCP_SET_CW(SRAM_KH_ENTRY, (unsigned char *) v, KH_SIZE)
#define spu_GetKH(v)             RCP_GET_CW(SRAM_KH_ENTRY, (unsigned char *) v, KH_SIZE)

#define spu_SetKM(v)             RCP_SET_CW(SRAM_KM_ENTRY, (unsigned char *) v, MASTERKEY_SIZE)
#define spu_GetKM(v)             RCP_GET_CW(SRAM_KM_ENTRY, (unsigned char *) v, MASTERKEY_SIZE)

#define spu_SetKD(v)             RCP_SET_CW(SRAM_KD_ENTRY, (unsigned char *) v, KD_SIZE)
#define spu_GetKD(v)             RCP_GET_CW(SRAM_KD_ENTRY, (unsigned char *) v, KD_SIZE)

#define spu_SetDKey2(v)          RCP_SET_CW(SRAM_DK2_ENTRY, (unsigned char *) v, DKEY_SIZE)
#define spu_GetDKey2(v)          RCP_GET_CW(SRAM_DK2_ENTRY, (unsigned char *) v, DKEY_SIZE)

#define spu_SetKsXorLc128(v)     RCP_SET_CW(SRAM_KS_XOR_LC128_ENTRY, (unsigned char *) v, SRAM_KS_XOR_LC128_SIZE)
#define spu_GetKsXorLc128(v)     RCP_GET_CW(SRAM_KS_XOR_LC128_ENTRY, (unsigned char *) v, SRAM_KS_XOR_LC128_SIZE)

#define spu_SetRiv(v)            RCP_SET_CW(SRAM_RIV_ENTRY, (unsigned char *) v, RIV_SIZE)
#define spu_GetRiv(v)            RCP_GET_CW(SRAM_RIV_ENTRY, (unsigned char *) v, RIV_SIZE)

#define spu_SetDateDecrypto(v)            RCP_SET_CW(SRAM_DATA_DECRYPT_ENTRY, (unsigned char*) v, SRAM_DATA_DECRYPT_SIZE)
#define spu_GetDateDecrypto(v)            RCP_GET_CW(SRAM_DATA_DECRYPT_ENTRY, (unsigned char*) v, SRAM_DATA_DECRYPT_SIZE)

typedef struct {
	unsigned char DeviceCount;
	unsigned char Depth;
	unsigned char DevicesExceeded;
	unsigned char DepthExceeded;

	/*hdcp2.2*/
	unsigned char HDCP20RepeaterDownStream;
	unsigned char HDCP1DeviceDownStream;
	unsigned char seq_num_V[3];
	unsigned char V[V_SIZE];
	unsigned char Ksvs[5 * MAX_DEVICECOUNT];
} H2_gKsvInfo;

/*//////////////////////////////////////////////////////////////////////////////*/
#ifdef TEST_HDCP2_2_TX_DRIVER
 typedef struct {
	unsigned int seq_num_m;
	unsigned int k;
	unsigned char mp[1024];
} H2_gStreamInfo;

/**
 * Definitions for various sizes
 */
H2status hdcp2_Tx_GenrTx(void);
H2status hdcp2_Tx_GetrTx(unsigned char *message);
H2status hdcp2_Tx_SetTxcaps(unsigned char *message);
H2status hdcp2_Tx_GetTxcaps(unsigned char *message);
H2status hdcp2_Tx_SetCertRx(unsigned char *message);
H2status hdcp2_Tx_SetrRx(unsigned char *message);
H2status hdcp2_Tx_GetrRx(unsigned char *message);
H2status hdcp2_Tx_SetRxcaps(unsigned char *message);
H2status hdcp2_Tx_GetRxcaps(unsigned char *message);
H2status hdcp2_Tx_SetRepeater(void);
H2status hdcp2_Tx_ParseCertRx(void);
H2status hdcp2_Tx_GetReceiverID(unsigned char *message);
H2status hdcp2_Tx_GetKpubRx(unsigned char *message);
H2status hdcp2_Tx_GetDcpllcSig(unsigned char *message);
H2status hdcp2_Tx_GetCertM(unsigned char *message);
H2status hdcp2_Tx_GetCertS(unsigned char *message);
H2status hdcp2_Tx_GenKm(void);
H2status hdcp2_Tx_GetKm(unsigned char *message);
H2status hdcp2_Tx_GetKeyDcpllc_N(unsigned char *message);
H2status hdcp2_Tx_GetKeyDcpllc_E(unsigned char *message);
H2status hdcp2_Tx_GetKeyPublicRx_N(unsigned char *message);
H2status hdcp2_Tx_GetKeyPublicRx_E(unsigned char *message);
void RCP_HDCP2_GenKd(int KmCw, unsigned char *Rtx, unsigned char *Rrx,
		      unsigned char *Rn, int KdCW, int modeHDCP22);
H2status hdcp2_Tx_SetRnAKE(unsigned char *message);
H2status hdcp2_Tx_GenHprime(void);
H2status hdcp2_Tx_GetHprime(unsigned char *message);
H2status hdcp2_Tx_SetEkhkm(unsigned char *message);
H2status hdcp2_Tx_GetEkhkm(unsigned char *message);
H2status hdcp2_Tx_Genm(void);
H2status hdcp2_Tx_Getm(unsigned char *message);
H2status hdcp2_Tx_GenRn(void);
H2status hdcp2_Tx_GetRn(unsigned char *message);
H2status hdcp2_Tx_GenLprime(void);
H2status hdcp2_Tx_GetLprime(unsigned char *message);
H2status hdcp2_Tx_GenKs(void);
H2status hdcp2_Tx_GetKs(unsigned char *message);
H2status hdcp2_Tx_GenRiv(void);
H2status hdcp2_Tx_GetRiv(unsigned char *message);
H2status hdcp2_Tx_GenEdkeyKs(void);
H2status hdcp2_Tx_GetEdkeyks(unsigned char *message);
H2status hdcp2_Tx_SetKeyDcpllc_N();
H2status hdcp2_Tx_SetKeyDcpllc_E();
H2status hdcp2_Tx_decrypt(H2uint8 InputCtr[12], H2uint8 *pData,
			    H2uint32 Len);
H2status hdcp2_Tx_SetKsXorLc128(const H2uint8 *AESKey);
H2status hdcp2_Tx_SetRiv(const H2uint8 *riv);

#endif /*  */

#ifdef TEST_HDCP2_2_RX_DRIVER
typedef struct {
	unsigned char receiverId[RXID_SIZE];
	unsigned char kpubRx[KPUBRX_SIZE];
	unsigned char reserved[CERT_RESERVED_SIZE];
	unsigned char certRx[CERT_SIGN_SIZE];
} H2_ReceiverCert;
typedef struct {
	unsigned char rtx[RTX_SIZE];
	unsigned char rn[RN_SIZE];
	unsigned char rRx[RRX_SIZE];
	unsigned char m[M_SIZE];
	unsigned char hPrime[H_SIZE];
	unsigned char txcaps[TXCAPS_SIZE];
	unsigned char rxcaps[RXCAPS_SIZE];
	unsigned char ks[KS_SIZE];
	unsigned char lc128[LC128_SIZE];
	unsigned char certRx[CERT_RX_SIZE];
	unsigned char kPrivRx[KPRIVRX_SIZE];
	unsigned char kh[KH_SIZE];
	unsigned char km[KM_SIZE];
	unsigned char kd[KD_SIZE];
	unsigned char dkey2[DKEY_SIZE];
	unsigned char ksXorLc128[SRAM_KS_XOR_LC128_SIZE];
	unsigned char riv[RIV_SIZE];
	unsigned char km0[KM_SIZE];
	unsigned char km1[KM_SIZE];
	unsigned char km2[KM_SIZE];
	unsigned char km3[KM_SIZE];
	unsigned char km4[KM_SIZE];
} HDCP2_PM_PARAMTER;

/** More details of these functions are in hdcp2_interface.c */
H2status hdcp2_Rx_init(void);
H2status hdcp2_Rx_reset(void);
H2status hdcp2_Rx_GenrRx(void);
H2status hdcp2_Rx_Setrtx(const H2uint8 *rtx);
H2status hdcp2_Rx_Setrn(const H2uint8 *rn);
H2status hdcp2_Rx_SetRiv(const H2uint8 *riv);
H2status hdcp2_Rx_SetEKpubKm(const H2uint8 *EKpubKm);
H2status hdcp2_Rx_SetEKhKm(H2uint8 *EKhKm, H2uint8 *m);
H2status hdcp2_Rx_SetEdKeyKs(H2uint8 *EdKeyKs);
H2status hdcp2_Rx_GetrRx(H2uint8 *pOut, H2uint32 ulSize);
H2status hdcp2_Rx_SetAesStreamCtr(H2uint8 *pCtr, H2uint32 size);
H2status hdcp2_Rx_SetAesInputCtr(const H2uint8 *pCtr, H2uint32 size);
H2status hdcp2_Rx_SetAesKey(const H2uint8 *pIn, H2uint32 size);
H2status hdcp2_Rx_AesSetNonce(H2uint8 *pOut, H2uint32 size);
H2status hdcp2_Rx_AesDecrypt(H2uint8 *pOut, H2uint32 size);
H2status hdcp2_Rx_GetCertRx(H2uint8 *pOut, H2uint32 ulSize);
H2status hdcp2_Rx_GetEKhKm(H2uint8 *pOut, H2uint32 ulSize);
H2status hdcp2_Rx_GethPrime(H2uint8 *pOut, H2uint32 ulSize);
H2status hdcp2_Rx_GetlPrime(H2uint8 *pOut, H2uint32 ulSize);
H2status hdcp2_Rx_GetvPrime(H2uint8 *pOut, H2uint32 ulSize);
H2status hdcp2_Rx_CalvPrime(unsigned char *receiver_id, unsigned char *temp_rxinfor, unsigned char *temp_seq_num, unsigned char *Vprime);
H2status hdcp2_Rx_CalMPrime(unsigned char *bstream_id_type, unsigned char *bseq_num_M, unsigned char *Mprime);
H2status hdcp2_Rx_SetKsvs(unsigned char *pMsg, unsigned int len);
H2status hdcp2_Rx_GetKsvInfo(H2uint8 *Devices, H2uint8 *Depth,
			      H2uint8 *DevicesExceeded,
			      H2uint8 *DepthExceeded, H2uint8 *pKSVs,H2uint8 *repeater_down_stream,H2uint8 *repeater_hdcp1_down_stream);
H2status hdcp2_Rx_decrypt(H2uint8 InputCtr[12], H2uint8 *pData,
			    H2uint32 Len);
H2status hdcp2_Rx_SetKsXorLc128(const H2uint8 *AESKey);
H2status hdcp2_Rx_GetrTx(H2uint8 *pOut, H2uint32 ulSize);
H2status hdcp2_Rx_GetRn(H2uint8 *rn, H2uint32 ulSize);
H2status hdcp2_Rx_SetTxcaps(unsigned char *message);
H2status hdcp2_Rx_GetTxcaps(H2uint8 *txcaps, H2uint32 ulSize);
H2status hdcp2_Rx_GenRxcaps(void);
H2status hdcp2_Rx_GetRxcaps(H2uint8 *rxcaps, H2uint32 ulSize);
void	 hdcp2_load_from_flash(void);
H2status hdcp2_save_encrypted_keyset(unsigned char *pKeySet,
			const char *dst_file_path, int keyLength);
H2status hdcp2_load_encrypted_keyset(unsigned char *pKeySet,
			const char *src_file_path, int keyLength);
H2status hdcp2_load_from_file(unsigned char *pKeySet,
			const char *src_file_path, int keyLength);
void hdcp2_save_keyset(unsigned char *pKeySet);
H2status hdcp2_Rx_SetKs(const H2uint8 *ks);
H2status hdcp2_Rx_GetKs(H2uint8 *ks, H2uint32 ulSize);
H2status hdcp2_Verify_EdkeyKs(unsigned char *pEks, unsigned char *rrx,
			       unsigned char *rtx, unsigned char *rn,
			       int modeHDCP22);
int read_binary_file(const char *path, unsigned char *buff, unsigned int len);
H2status hdcp2_Rx_Compute_EKhKm(H2uint8 *m, H2uint8 *Ekhkm);
H2status hdcp2_Rx_ParseEKhKm(H2uint8 *EKhKm, H2uint8 *m);
H2status hdcp2_Rx_Compute_EdKeyKs(H2uint8 *rtx, H2uint8 *rrx, H2uint8 *rn,
				   H2uint8 *EdKeyKs, int modeHDCP22);
H2status hdcp2_GenKsXorLc128(void);
H2status hdcp2_copy_paramter(HDCP2_PM_PARAMTER *hdcp2_data);
H2status hdcp2_recover_paramter(HDCP2_PM_PARAMTER *hdcp2_data);

#endif /*  */
#endif
