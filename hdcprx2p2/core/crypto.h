/**
 * Crypto interface for HDCP2 XTASK.
 *
 * This file contains function prototypes used for HDCP2.
 *
 * @author Buddy Smith <bsmith@vtilt.com>
 * 2014.08.04
 * @author Bruce copied from Realtek HDCP2 Rx implementation
 */

#include "hdcp2_hal.h"
#include "bigdigits.h"

#define SHA256_DIGEST_SIZE (256/8)

/**
 * size of the key components for RSA decryption.
 * This should equal key size / 32.
 */
#define MOD_SIZE (1024/32)

typedef struct {
	DIGIT_T *p;
	DIGIT_T *q;
	DIGIT_T *dP;
	DIGIT_T *dQ;
	DIGIT_T *Qinv;
} crypto_RSAKey;

/** Helper functions */
H2status crypto_swapBytes( H2uint8 *ptr, int length );

/** 
 * Implementation specific functions 
 *
 **/

/** struct H2Sha256Ctx is defined in hdcp2_hal.h **/
typedef struct H2Sha256Ctx H2Sha256Ctx_t; 

H2bool crypto_sha256Init( H2Sha256Ctx_t* pCtx );
H2bool crypto_sha256Update( H2Sha256Ctx_t* pCtx, H2uint8 const * pBuf, H2uint32 len );
H2bool crypto_sha256Final( H2Sha256Ctx_t* pCtx, H2uint8* pHash );

H2uint32 crypto_random32( void );

H2status crypto_aesCtr128(H2uint8 const *pIn, int len, H2uint8 const * pSK, H2uint8 const * pIV, H2uint8* pOut );

void crypto_DCacheFlush( void* pAddr, int size );

H2status MGF1_SHA256( H2uint8 *mask, H2uint32 length, const H2uint8 *seed, int seedLen );
H2status crypt_XOR( const uint8_t *s1, const uint8_t *s2, uint8_t *d, int len );
