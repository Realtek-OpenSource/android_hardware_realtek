#include <stdint.h>
#include <hdcp2_hal.h>
#include <sha2.h>
#define SHA256_DIGEST_SIZE (256 / 8)
#define SHA256_Tpre_SIZE 19
#define SHA256_T_SIZE (SHA256_Tpre_SIZE + SHA256_DIGEST_SIZE)

/** struct H2Sha256Ctx is defined in hdcp2_hal.h **/
typedef struct H2Sha256Ctx H2Sha256Ctx_t;
H2bool crypto_sha256Init(H2Sha256Ctx_t *pCtx);
H2bool crypto_sha256Update(H2Sha256Ctx_t *pCtx, H2uint8 const *pBuf,
			    H2uint32 len);
H2bool crypto_sha256Final(H2Sha256Ctx_t *pCtx, H2uint8 *pHash);
H2bool crypto_sha1Init(struct SHA1Context *context);
H2bool crypto_sha1Update(struct SHA1Context *context, const void *data,
			  unsigned int len);
H2bool crypto_sha1Final(unsigned char digest[20], struct SHA1Context *context);
extern unsigned int crypto_random32(void);
H2status EMSA_PKCSEncode(unsigned char *M, int emLen, unsigned char *EM);

H2status crypto_aesCtr128(unsigned char const *pIn, int len, unsigned char const *pSK, unsigned char const * pIV, unsigned char* pOut );
H2status Decrypt_EKpubKm_kPrivRx(const H2uint8 *KprivRx, H2uint8 *km,
				     const H2uint8 *EKpubKm);
H2status Compute_Hprime_22(unsigned char *kd, unsigned char *rtx,
			    unsigned char *txcaps, unsigned char *rxcaps,
			    unsigned char *Hprime);
H2status Compute_Hprime_Rx(const H2uint8 *Kd, const H2uint8 *rtx,
			    const H2uint8 Repeater, H2uint8 *Hprime);
H2status Compute_Lprime_Rx(const H2uint8 *Kd, const H2uint8 *rRx,
			    const H2uint8 *rn, H2uint8 *L);
H2status Compute_Kh(const H2uint8 *Kpriv_rx, int Kprivrx_len, H2uint8 *Kh);
H2status Sha256(const H2uint8 *pIn, int length, H2uint8 *pOut);
H2status Sha1(const H2uint8 *pIn, int length, H2uint8 *pOut);
H2status MGF1_SHA256(H2uint8 *mask, H2uint32 length, const H2uint8 *seed, int seedLen);
H2status crypt_xor(const uint8_t *s1, const uint8_t *s2, uint8_t *d,
		    int len);
H2status Compute_Vprime_22(unsigned char *kd, unsigned char *receiver_id, unsigned char *temp_rxinfor, unsigned char *temp_seq_num, unsigned char *Vprime);
H2status Compute_Mprime_22(unsigned char *kd, unsigned char *bstream_id_type,unsigned char *bseq_num_M, unsigned char *Mprime);
