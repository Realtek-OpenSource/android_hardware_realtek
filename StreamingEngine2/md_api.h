#ifndef _MD_ENGINE_H_
#define _MD_ENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "OSAL.h"
#include "hresult.h"

typedef uint64_t MD_CMD_HANDLE;

/*
 * Prototypes for shared functions
 */
void
md_open(void);

void
md_close(void);

/* return zero means the command is not issued or issued but failed */
MD_CMD_HANDLE
md_memcpy(void *lpDst, void *lpSrc, int len, bool forward);

/* return zero means the command is not issued or issued but failed */
MD_CMD_HANDLE
md_memset(void *lpDst, uint8_t data, int len);

bool
md_checkfinish(MD_CMD_HANDLE handle);

void md_WaitComplete();

MD_CMD_HANDLE
md_seq_blk_cpy(int addr_idx, int h_in_pixels, int w_in_bytes, int x_in_bytes, int y_in_bytes, void *src, int len);

MD_CMD_HANDLE
md_blk_seq_cpy(int addr_idx, int h_in_pixels, int w_in_bytes, int x_in_bytes, int y_in_bytes, void *src);

//=================================================================================================
MD_CMD_HANDLE
md_memcpyex(
	void 		*pvDestAddress, 
	void 		*pvSrcAddress, 
	uint32_t 	dwDataLength, 
	bool 		bForward, 
	uint32_t 	dwSrcPitchValue,
	uint32_t 	dwDestPitchValue,
	uint32_t 	dwDataHeight,
	uint32_t 	dwDataWidth
	);

MD_CMD_HANDLE
md_memsetex(
	void		*pvDestAddress, 
	uint8_t		dwConstData,
	uint32_t	dwDataLength, 
	uint32_t	dwSrcPitchValue,
	uint32_t	dwDestPitchValue,
	uint32_t	dwDataHeight,
	uint32_t	dwDataWidth
	);

MD_CMD_HANDLE
md_seq_blk_cpyex(
	uint32_t 	dwAddrIdx, 
	void 		*pvSeqAddr, 
	uint32_t 	dwSeqLen,
	uint32_t	dwSeqPitch,
	uint32_t 	dwPixelHeight, 
	uint32_t 	dwByteWidth, 
	uint32_t 	dwByteX, 
	uint32_t 	dwByteY 
	);

MD_CMD_HANDLE
md_blk_seq_cpyex(
	uint32_t 	dwAddrIdx, 
	void 		*pvSeqAddr,
	uint32_t	dwSeqPitch,
	uint32_t 	dwPixelHeight, 
	uint32_t 	dwByteWidth, 
	uint32_t 	dwByteX, 
	uint32_t 	dwByteY 
	);

#define SWAP_DATA_2B 0
#define SWAP_DATA_4B 1

MD_CMD_HANDLE
md_mem_swap_cpyex(
	void 		*pvDestAddress, 
	void 		*pvSrcAddress, 
	uint32_t 	dwDataLength, 
	uint32_t 	dwDestPitchValue,
	uint32_t 	dwSrcPitchValue,
	uint32_t 	dwDataHeight,
	uint32_t 	dwDataWidth,
	uint32_t 	dwByteMode
	);


#ifdef __cplusplus
}
#endif

#endif /* _MD_ENGINE_H_ */
