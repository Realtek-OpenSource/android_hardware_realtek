
#ifndef RTK_OSAL_H
#define RTK_OSAL_H

#include <stdint.h>
#ifdef __LINARO_SDK__
#include <arpa/inet.h>
#else
#include <sys/endian.h>
#endif
#include "ion/ion.h"
#include "rpc_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Types compatible with OMX types */
typedef uint32_t OSAL_U32;
typedef uint8_t OSAL_U8;
typedef int32_t OSAL_S32;
typedef int8_t OSAL_S8;
typedef void * OSAL_PTR;
typedef uint32_t OSAL_ERRORTYPE;
//typedef int ion_user_handle_t;
//typedef unsigned long OSAL_BOOL;

typedef enum OSAL_BOOL {
    OSAL_FALSE = 0,
    OSAL_TRUE = !OSAL_FALSE,
    OSAL_BOOL_MAX = 0x7FFFFFFF
} OSAL_BOOL;

typedef enum RING_BUFFER_STYLE {
  STYLE_IPC,
  STYLE_LOCAL,
  STYLE_IPC_SHARE,  // the memory will be shared with other process
} RING_BUFFER_STYLE;

/* Error values compatible with OMX_ERRORTYPE */
#define OSAL_ERRORNONE                          0
#define OSAL_ERROR_INSUFFICIENT_RESOURCES       0x80001000
#define OSAL_ERROR_UNDEFINED                    0x80001001
#define OSAL_ERROR_BAD_PARAMETER                0x80001005
#define OSAL_ERROR_NOT_READY                    0x80001010
#define OSAL_ERROR_ALLOC_RING_UPPER_BOUND	0x80002001


typedef OSAL_U32 OSAL_BUS_WIDTH;

typedef enum DECODER_TYPE
{
	OSAL_VIDEO = 0,
	OSAL_IMAGE,
	OSAL_AUDIO
}DECODER_TYPE;

typedef struct OSAL_ALLOCATOR {
	ion_user_handle_t ionhdl;
    OSAL_S32          ionFd;
    OSAL_S32          shareFd;
} OSAL_ALLOCATOR;

typedef struct OSAL_RTKALLOCATOR {
	RING_BUFFER_STYLE	m_style;
	OSAL_U8				m_Flag;
	OSAL_BOOL			m_bNeedSizeNotifier;
	OSAL_S32			m_RequestSize;

	// header addresses
	OSAL_U8				*m_pBufferHeaderAddr;    // for free (free must use cache-able address)
	RINGBUFFER_HEADER	*m_pBufferHeader; // point to ring buffer property structure
	RINGBUFFER_HEADER	*m_pBufferHeader_ext; // point to ring buffer property structure
	OSAL_U32		m_BufferHeaderSize_ext;
	REFCLOCK		*m_pRefClock;
	OSAL_U32		m_RefClockSize;
	OSAL_U32			m_bufferHeaderPhyAddr;
	long			m_headerPhyAddrDiff;  // value = PhysicalAddress - VirtualAddress, for 64-bit addr, this has to be long type
	//OSAL_S32			m_headerPhyAddrDiff_ext;  // value = PhysicalAddress - VirtualAddress

	// ring buffer addresses and size
	OSAL_S32	m_bufferSize;
	OSAL_U8		*m_pBufferLower;
	OSAL_U8		*m_pBufferUpper;
	OSAL_U8		*m_pBufferNonCachedLower;
	OSAL_U32	m_bufferPhyAddr;

	ion_user_handle_t ionhdl;
	ion_user_handle_t ionhdl_headr;

    OSAL_S32 ionhdl_fd;
    OSAL_S32 ionhdl_header_fd;
} OSAL_RTKALLOCATOR;

typedef struct _private_rtk_v1_data
{
    unsigned int        yuv_mode;
    unsigned long long  pts[2];
    int                 delay_mode;
    int                 delay_depth;
    unsigned int        IsForceDIBobMode;
    int                 init_frame;
    int                 deintflag; // 0:AUTODEINT 1:FORCEDEINT 2:FORCEPROGRESSIVE
    int                 ssid;
    unsigned int        lumaOffTblAddr;
    unsigned int        chromaOffTblAddr;
    unsigned int        lumaOffTblAddrR;
    unsigned int        chromaOffTblAddrR;
    unsigned int        bufBitDepth;
    unsigned int        bufFormat;
    unsigned int        transferCharacteristics;
    unsigned int        display_primaries_x0;
    unsigned int        display_primaries_y0;
    unsigned int        display_primaries_x1;
    unsigned int        display_primaries_y1;
    unsigned int        display_primaries_x2;
    unsigned int        display_primaries_y2;
    unsigned int        white_point_x;
    unsigned int        white_point_y;
    unsigned int        max_display_mastering_luminance;
    unsigned int        min_display_mastering_luminance;
    unsigned int        display_width;
    unsigned int        display_height;
    union {
        unsigned int        flag;
        struct {
            unsigned int    isHDCP:1; // bit[0]
            unsigned int    isSWDEI:1; // bit[1]
            unsigned int    :2;
            unsigned int    isProtect:1; // bit[4]
        };
    } hdmi_flag;
    unsigned long long  hdmi_hdcp_key;
    unsigned long long  hdmi_hdcp_key_response;
    unsigned int        display_stride;
    unsigned int        video_full_range_flag; //default= 1
    unsigned int        matrix_coefficients; //default= 1
    unsigned int        is_tch_video;
    unsigned int        technicolor_data[152];
    unsigned int        hdr_metadata_addr;//'rtk9'
    unsigned int        hdr_metadata_size;//'rtk9'
    unsigned int        tch_metadata_addr;//'rtk9'
    unsigned int        tch_metadata_size;//'rtk9'
    unsigned int        dolby_register[3070];
    unsigned int        is_dolby_version;
    unsigned int        isAdaptive_playback;
    unsigned int        isLastFrmBfSeqChange;
    unsigned int        hdr_lightLevel[2];
    unsigned int        reserve[8192-3270];
} private_rtk_v1_data;

    OSAL_U8 OSAL_Getbits(
        OSAL_U8 *buffer,
        OSAL_U32 from,
        OSAL_U8 len
    );

    OSAL_U32 OSAL_GetMoreBits(
        OSAL_U8 *buffer,
        OSAL_U32 from,
        OSAL_U8 len
    );

    OSAL_U32 OSAL_GetUE(
        OSAL_U8 *buffer,
        OSAL_U32 from,
        OSAL_U8 *consum
    );

    OSAL_S32 OSAL_GetSE(
        OSAL_U8 *buffer,
        OSAL_U32 from,
        OSAL_U8 *consum
    );

    void OSAL_Setbits(
        OSAL_U8 *buffer,
        OSAL_U32 from,
        OSAL_U8 len,
        OSAL_U32 value,
        OSAL_U32 *byteBuffer,
        OSAL_U32 *bufferedBits,
        OSAL_U32 *zeroBytes,
        OSAL_U32 *byteCnt
    );

    OSAL_U32 OSAL_ReadGolomb(
        OSAL_U8 *buffer,
        OSAL_U32 *init
    );

    OSAL_S32 OSAL_ReadGolomb_s(
        OSAL_U8 *buffer,
        OSAL_U32 *init
    );

    OSAL_U32 OSAL_WriteGolomb(
        OSAL_U8 *buffer,
        OSAL_U32 init,
        OSAL_U32 value,
        OSAL_U32 *byteBuffer,
        OSAL_U32 *bufferedBits,
        OSAL_U32 *zeroBytes,
        OSAL_U32 *byteCnt
    );

    OSAL_U32 OSAL_WriteGolomb_s(
        OSAL_U8 *buffer,
        OSAL_U32 init,
        OSAL_S32 value,
        OSAL_U32 *byteBuffer,
        OSAL_U32 *bufferedBits,
        OSAL_U32 *zeroBytes,
        OSAL_U32 *byteCnt
    );

/*------------------------------------------------------------------------------
    Memory
------------------------------------------------------------------------------*/

OSAL_PTR        OSAL_Malloc( OSAL_U32 size );
void            OSAL_Free( OSAL_PTR pData );

OSAL_ERRORTYPE  OSAL_AllocatorInit(OSAL_ALLOCATOR* alloc);

void            OSAL_AllocatorDestroy(OSAL_ALLOCATOR* alloc);

OSAL_ERRORTYPE  OSAL_AllocatorAllocMem(OSAL_ALLOCATOR* alloc,
                    OSAL_U32* size, OSAL_U8** bus_data,
                    OSAL_BUS_WIDTH* bus_address, OSAL_U32 heap_mask, OSAL_U32 flags);

OSAL_ERRORTYPE  OSAL_AllocatorAllocMemProtected(OSAL_ALLOCATOR* alloc,
                    OSAL_U32* size, OSAL_U8** bus_data,
                    OSAL_BUS_WIDTH* bus_address);

void            OSAL_AllocatorFreeMem(OSAL_ALLOCATOR* alloc,
                    OSAL_U32 size, OSAL_U8* bus_data,
                    OSAL_BUS_WIDTH bus_address);

int     OSAL_AllocatorGetIonFd      (OSAL_ALLOCATOR* alloc);
int     OSAL_AllocatorGetShareFd    (OSAL_ALLOCATOR* alloc);

void    OSAL_AllocatorSetIonFd      (OSAL_ALLOCATOR* alloc, int fd);
void    OSAL_AllocatorSetShareFd    (OSAL_ALLOCATOR* alloc, int fd);

void    OSAL_AllocatorSyncFd        (OSAL_ALLOCATOR* alloc);
void    OSAL_AllocatorFlushFd       (OSAL_ALLOCATOR* alloc);
void    OSAL_AllocatorInvalidateFd  (OSAL_ALLOCATOR* alloc);

OSAL_BOOL       OSAL_AllocatorIsReady(const OSAL_ALLOCATOR* alloc);

/*------------------------------------------------------------------------------
    RTK function
------------------------------------------------------------------------------*/
OSAL_U32 OSAL_RTKGetPhysicalWriteAddress(OSAL_RTKALLOCATOR* alloc);
#define OSAL_RTKWriteUINT32(des, data)  do{ des = htonl(data); }while(0)
#define OSAL_RTKReadUINT32(src)         ntohl(src)
void OSAL_RTKSetWritePtr(OSAL_RTKALLOCATOR* alloc, OSAL_U8 *writePtr);
void OSAL_RTKSetReadPtr(OSAL_RTKALLOCATOR* alloc, OSAL_S32 readPtrIndex, OSAL_U8 *readPtr);
OSAL_U8* OSAL_RTKGetReadPtr(OSAL_RTKALLOCATOR* alloc, OSAL_S32 readPtrIndex);
OSAL_U8* OSAL_RTKGetWritePtr(OSAL_RTKALLOCATOR* alloc);
OSAL_S32 OSAL_RTKGetReadableSize(OSAL_RTKALLOCATOR* alloc, OSAL_S32 readPtrIndex);
OSAL_S32 OSAL_RTKGetWritableSize(OSAL_RTKALLOCATOR* alloc, OSAL_S32 readPtrIndex);
OSAL_S32 OSAL_RTKGetReadSize(OSAL_RTKALLOCATOR* alloc);
OSAL_S32 OSAL_RTKGetWriteSize(OSAL_RTKALLOCATOR* alloc);
OSAL_S32 OSAL_RTKCopyFromBuffer(OSAL_RTKALLOCATOR* alloc, OSAL_S32 readPtrIndex, void *dst, OSAL_S32 size);
OSAL_S32 OSAL_RTKCopyToBuffer(OSAL_RTKALLOCATOR* alloc, OSAL_S32 readPtrIndex, void *src, OSAL_S32 size);
void OSAL_RTKSyncRingBuffer(OSAL_RTKALLOCATOR* alloc);
OSAL_ERRORTYPE OSAL_RTKConstructor(OSAL_RTKALLOCATOR* alloc, RING_BUFFER_STYLE style, OSAL_U32 heap_mask, OSAL_U32 flags);
void OSAL_RTKDestory(OSAL_RTKALLOCATOR* alloc);
void OSAL_RTKDestory_ext(OSAL_RTKALLOCATOR* alloc);
OSAL_ERRORTYPE OSAL_RTKSetBuffer(OSAL_RTKALLOCATOR* alloc, OSAL_U32 size);
OSAL_ERRORTYPE OSAL_RTKCommit(OSAL_RTKALLOCATOR* alloc, OSAL_U32 heap_mask, OSAL_U32 flags);
OSAL_ERRORTYPE OSAL_RTKCommit_ext(OSAL_RTKALLOCATOR* alloc);
OSAL_ERRORTYPE OSAL_RTKGetBufferHeader(OSAL_RTKALLOCATOR* alloc, RINGBUFFER_HEADER **virtualAddress, OSAL_U32 *physicalAddress);
OSAL_ERRORTYPE OSAL_RTKGetBuffer(OSAL_RTKALLOCATOR* alloc, OSAL_U8** ppBuffer, OSAL_S32* pSize);
OSAL_ERRORTYPE OSAL_RTKRequestWriteSpace(OSAL_RTKALLOCATOR* alloc, OSAL_U8** ppWritePointer, OSAL_S32* pWriteBufferSize, OSAL_S32 RequestSize, OSAL_S32 MilliTimeOut);
OSAL_ERRORTYPE AllocateOSAL_RTKALLOCATOR(OSAL_RTKALLOCATOR **pRTKAllocator, OSAL_U32 nAllocSize, OSAL_U32 heap_mask, OSAL_U32 flags);

/*------------------------------------------------------------------------------
    Thread
------------------------------------------------------------------------------*/

OSAL_ERRORTYPE  OSAL_ThreadCreate(OSAL_U32 (*pFunc)(OSAL_PTR pParam),
                    OSAL_PTR pParam, OSAL_U32 nPriority, OSAL_PTR *phThread );

OSAL_ERRORTYPE  OSAL_ThreadDestroy(OSAL_PTR hThread );
void            OSAL_ThreadSleep(OSAL_U32 ms);

/*------------------------------------------------------------------------------
    Mutex
------------------------------------------------------------------------------*/

OSAL_ERRORTYPE  OSAL_MutexCreate(OSAL_PTR *phMutex);
OSAL_ERRORTYPE  OSAL_MutexDestroy(OSAL_PTR hMutex);
OSAL_ERRORTYPE  OSAL_MutexLock(OSAL_PTR hMutex);
OSAL_ERRORTYPE  OSAL_MutexUnlock(OSAL_PTR hMutex);

OSAL_ERRORTYPE  OSAL_pWaitEvent(OSAL_PTR osal_cond, OSAL_PTR osal_mtx);
OSAL_ERRORTYPE  OSAL_pWaitEventTimeout(OSAL_PTR osal_cond, OSAL_PTR osal_mtx, unsigned int sec);
void            OSAL_pWakeUp(OSAL_PTR osal_cond, OSAL_PTR osal_mtx);

/*------------------------------------------------------------------------------
    Events
------------------------------------------------------------------------------*/

#define INFINITE_WAIT 0xffffffff

OSAL_ERRORTYPE  OSAL_EventCreate(OSAL_PTR *phEvent);
OSAL_ERRORTYPE  OSAL_EventDestroy(OSAL_PTR hEvent);
OSAL_ERRORTYPE  OSAL_EventReset(OSAL_PTR hEvent);
OSAL_ERRORTYPE  OSAL_EventSet(OSAL_PTR hEvent);
OSAL_ERRORTYPE  OSAL_EventWait(OSAL_PTR hEvent, OSAL_U32 mSec,
                    OSAL_BOOL *pbTimedOut);

OSAL_ERRORTYPE  OSAL_EventWaitMultiple(OSAL_PTR* hEvents, OSAL_BOOL* bSignaled,
                    OSAL_U32 nCount, OSAL_U32 mSec, OSAL_BOOL* pbTimedOut);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
