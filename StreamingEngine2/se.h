/*
 * se.h -- definitions for the char module
 *
 * Copyright (C) 2001 Alessandro Rubini and Jonathan Corbet
 * Copyright (C) 2001 O'Reilly & Associates
 *
 * The source code in this file can be freely used, adapted,
 * and redistributed in source or binary form, so long as an
 * acknowledgment appears in derived source files.  The citation
 * should list that the code comes from the book "Linux Device
 * Drivers" by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.   No warranty is attached;
 * we cannot take responsibility for errors or fitness for use.
 *
 * $Id: se.h,v 1.15 2004/11/04 17:51:18 rubini Exp $
 */

#ifndef _SE_DRIVER_H_
#define _SE_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "OSAL.h"
#include "hresult.h"
#include <pthread.h>
//#include "SeLib.h"
#ifdef __LINUX_MEDIA_NAS__
#define USE_SEMAPHORE
#else
//#define USE_SEMAPHORE
#endif

typedef uint64_t SE_CMD_HANDLE;

//#ifndef HANDLE
//typedef void * HANDLE;
//#endif

#ifndef __SEINFO_CORNER__
#define __SEINFO_CORNER__
typedef enum _SEINFO_CORNER
{
    SEINFO_BITBLT_CORNER_TOP_LEFT = 0,       			//The Definition of Starting Corner: Top-Left
    SEINFO_BITBLT_CORNER_TOP_RIGHT = 1,       			//The Definition of Starting Corner: Top-Right
    SEINFO_BITBLT_CORNER_BOTTOM_LEFT = 2,       		//The Definition of Starting Corner: Bottom-Left
    SEINFO_BITBLT_CORNER_BOTTOM_RIGHT = 3,       		//The Definition of Starting Corner: Bottom-Right
    SEINFO_BITBLT_CORNER_NONE = 4       				//The Definition of Starting Corner: Disable

} SEINFO_CORNER;
#endif
/**
 * @enum PIXEL_FORMAT
 */
#ifndef _HAS_PIXELFORMAT_
#define _HAS_PIXELFORMAT_
typedef enum _PIXELFORMAT
{
    Format_8,           ///< 332
    Format_16,          ///< 565
    Format_32,          ///< 8888 ARGB
    Format_32_888A,			///< 8888 RGBA
    Format_2_IDX,
    Format_4_IDX,
    Format_8_IDX,
    Format_1555,
    Format_4444_ARGB,
    Format_4444_YUVA,
    Format_8888_YUVA,
    Format_5551,
    Format_4444_RGBA,
    Format_YUV420,
    Format_YUV422,
    Format_YUV444,
    NO_OF_PIXEL_FORMAT
} PIXEL_FORMAT;
#endif

/*
 * Prototypes for shared functions
 */

HRESULT
se_open(void);

HRESULT
se_close(void);

size_t
se_write(uint32_t hQueue, uint8_t *pbyCommandBuffer, int dwCommandLength, int inst_count);

HRESULT
se_ioctl(unsigned int cmd, void *arg);

bool
se_checkfinish(uint32_t hQueue);

void
se_go(uint32_t hQueue);

#ifdef USE_SEMAPHORE
void se_lock(void);
void se_unlock(void);
void check_poll(void);
#else
#define se_lock()       do{ }while(0)
#define se_unlock()     do{ }while(0)
#define check_poll()    do{ }while(0)
#endif

uint32_t se_get_handle(void);
void se_put_handle(uint32_t hQueue);
void se_mutex_lock(uint32_t hQueue);
void se_mutex_unlock(uint32_t hQueue);
int se_set_hratio(uint32_t hQueue, uint32_t hRatio);
int se_set_vratio(uint32_t hQueue, uint32_t vRatio);

#ifdef __cplusplus
}
#endif

#endif /* _SE_H_ */
