#ifndef __RCP_API_H__
#define __RCP_API_H__

#ifdef __cplusplus
extern "C" {

#endif				/*  */

#define REG_SET_WR_EN3      BIT(16)
#define REG_SET_MODE(x)     ((x & 0x7) << 13)
#define REG_SET_MODE_AES    REG_SET_MODE(0)
#define REG_SET_MODE_TDES   REG_SET_MODE(1)
#define REG_SET_MODE_DES    REG_SET_MODE(2)
#define REG_SET_MODE_MASK   REG_SET_MODE(7)
#define REG_SET_WR_EN2      BIT(5)
#define REG_SET_CBC         BIT(4)
#define REG_SET_ECB         0x0
#define REG_SET_WR_EN1      BIT(3)
#define REG_SET_FIRST_128   BIT(2)
#define REG_SET_WR_EN0      BIT(1)
#define REG_SET_ENC         BIT(0)
#define REG_SET_DEC         0x0

#define RCP_AES_128_ECB_ENC      (REG_SET_WR_EN3 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_ECB | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_ENC)
#define RCP_AES_128_ECB_DEC      (REG_SET_WR_EN3 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_ECB | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_DEC)
#define RCP_AES_128_CBC_ENC      (REG_SET_WR_EN3 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_CBC | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_ENC)
#define RCP_AES_128_CBC_DEC      (REG_SET_WR_EN3 | REG_SET_MODE_AES | REG_SET_WR_EN2 | REG_SET_CBC | REG_SET_WR_EN1 | REG_SET_FIRST_128 | REG_SET_WR_EN0 | REG_SET_DEC)

#define REG_SET1_KEY_MODE(x)         ((x & 0x3)<<6)
#define REG_SET1_KEY_MODE_REGISTER   REG_SET1_KEY_MODE(0)
#define REG_SET1_KEY_MODE_CW         REG_SET1_KEY_MODE(1)
#define REG_SET1_KEY_MODE_OTP        REG_SET1_KEY_MODE(2)
#define REG_SET1_KEY_MODE_MASK       REG_SET1_KEY_MODE(3)

#define REG_SET1_IV_MODE(x)          ((x & 0x3) << 4)
#define REG_SET1_IV_MODE_REG         REG_SET1_IV_MODE(0)
#define REG_SET1_IV_MODE_CW          REG_SET1_IV_MODE(1)

#define REG_SET1_INPUT_MODE(x)       ((x & 0x3) << 2)
#define REG_SET1_INPUT_MODE_REG      REG_SET1_INPUT_MODE(0)
#define REG_SET1_INPUT_MODE_CW       REG_SET1_INPUT_MODE(1)

#define REG_SET1_OUTPUT_MODE(x)      ((x & 0x3))
#define REG_SET1_OUTPUT_MODE_REG     REG_SET1_OUTPUT_MODE(0)
#define REG_SET1_OUTPUT_MODE_CW      REG_SET1_OUTPUT_MODE(1)

#define REG_SET2_OUTPUT_ENTRY(x)     ((x & 0x7F) << 24)
#define REG_SET2_INPUT_ENTRY(x)      ((x & 0x7F) << 16)
#define REG_SET2_KEY_ENTRY(x)        ((x & 0x7F) << 8)
#define REG_SET2_IV_ENTRY(x)         ((x & 0x7F))

#define KEY_OTP                      NULL
#define KEY_CW(x)                    ((unsigned char *) (1 + x))
	int RCP_Init(void);
	void RCP_UnInit(void);
	int RCP_AES_ECB_Cipher(unsigned char EnDe, unsigned char Key[16],
			       unsigned char *pDataIn,
			       unsigned char *pDataOut, unsigned long DataLen);

#define RCP_AES_ECB_Encryption(Key, pDataIn, pDataOut, DataLen)       RCP_AES_ECB_Cipher(1, Key, pDataIn, pDataOut, DataLen)
#define RCP_AES_ECB_Decryption(Key, pDataIn, pDataOut, DataLen)       RCP_AES_ECB_Cipher(0, Key, pDataIn, pDataOut, DataLen)
	int RCP_AES_CBC_Cipher(unsigned char EnDe, unsigned char Key[16],
			       unsigned char IV[16], unsigned char *pDataIn,
			       unsigned char *pDataOut, unsigned long DataLen);

#define RCP_AES_CBC_Encryption(Key, IV, pDataIn, pDataOut, DataLen)       RCP_AES_CBC_Cipher(1, Key, IV, pDataIn, pDataOut, DataLen)
#define RCP_AES_CBC_Decryption(Key, IV, pDataIn, pDataOut, DataLen)       RCP_AES_CBC_Cipher(0, Key, IV, pDataIn, pDataOut, DataLen)
	int RCP_AES_CTR_Cipher(unsigned char Key[16], unsigned char IV[16],
			       unsigned char *pDataIn,
			       unsigned char *pDataOut, unsigned long DataLen);

#define RCP_AES_CTR_Encryption(Key, IV, pDataIn, pDataOut, DataLen)       RCP_AES_CTR_Cipher(Key, IV, pDataIn, pDataOut, DataLen)
#define RCP_AES_CTR_Decryption(Key, IV, pDataIn, pDataOut, DataLen)       RCP_AES_CTR_Cipher(Key, IV, pDataIn, pDataOut, DataLen)
	int RCP_SET_CW(unsigned int id, unsigned char *pCW, unsigned int len);
	int RCP_GET_CW(unsigned int id, unsigned char *pCW, unsigned int len);
	void RCP_CW_XOR(int CwIn1, int CwIn2, int CwOut);
	void xor_array(unsigned char *in1, unsigned char *in2,
		       unsigned char *out, unsigned long len);

/*//////////////////////// Functions for HDCP2 /////////////////////////////*/
	void RCP_HDCP2_EkhKm(int KhCw, int KmCw, unsigned char *Rtx,
			     unsigned char *pEkhKm);
	void RCP_HDCP2_GenDKey(int KmCw, unsigned char *Rtx,
			       unsigned char *Rrx, unsigned char *Rn,
			       unsigned char ctr, int DKeyCW, int modeHDCP22);
	void RCP_HDCP2_GenKd(int KmCw, unsigned char *Rtx, unsigned char *Rrx,
			     unsigned char *Rn, int KdCW, int modeHDCP22);
	void RCP_HDCP2_GenKs(int dKey2CW, unsigned char *EdKeyKs,
			     unsigned char *Rrx, int KsCW);
	void RCP_HDCP2_GenKsXorLc128(int Lc128CW, int KsCW, int KsXorLc128CW);
	void RCP_HDCP2_DataDecrypt(int KsXorLs128CW,  int DatadecryptoCW, unsigned char *key, unsigned char *pcounter);
#ifdef __cplusplus
}
#endif				/*  */
#endif
