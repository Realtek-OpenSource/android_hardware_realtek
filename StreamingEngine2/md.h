#ifndef _MD_DRIVER_H_
#define _MD_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "OSAL.h"
#include "hresult.h"
#include <pthread.h>
//#define USE_SEMAPHORE

//typedef uint64_t MD_CMD_HANDLE;

//#ifndef HANDLE
//typedef void * HANDLE;
//#endif

/*
 * Prototypes for shared functions
 */

HRESULT
md_open(void);

HRESULT
md_close(void);

size_t
md_write(uint32_t hQueue, uint8_t *pbyCommandBuffer, int dwCommandLength, int inst_count);

bool
md_checkfinish(uint32_t hQueue);

bool
md_poll(uint32_t hQueue);

void
md_go(uint32_t hQueue);

uint32_t md_get_handle(void);
void md_put_handle(uint32_t hQueue);
void md_mutex_lock(uint32_t hQueue);
void md_mutex_unlock(uint32_t hQueue);

#ifdef __cplusplus
}
#endif

#endif /* _MD_H_ */
