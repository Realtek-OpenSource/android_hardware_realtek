#ifndef CODEC_VORPC_H
#define CODEC_VORPC_H

#include "hresult.h"
#include "RPCBaseDS_data.h"
#include "VideoRPCBaseDS.h"
#include "VideoRPC_System.h"
#include "AudioRPC_System.h"
#include "AudioRPC_Agent.h"
#include "VideoRPC_Agent.h"
#include "RPCProxy.h"

#include <linux/ion.h>
#include <ion/ion.h>

#include <system/SystemMemory.h>
#include <allocator/Allocator.h>
#include <allocator/IonAllocator.h>
#include <allocator/MallocAllocator.h>
#include <system/RingBuffer.h>
#include <system/RingBufferBody.h>
#include <system/RingBufferHeader.h>

#include <OSAL_RTK.h>
#include <pthread.h>
#include "codec.h"
#include "codec_common.h"

#define VORPC_PRINT_DEBUG
#ifdef VORPC_PRINT_DEBUG
//#define VORPC_PRINT(fmt, args...)   printf("[CODEC_VORPC]%s:%d" fmt, __func__, __LINE__, ##args)
#define VORPC_PRINT(fmt, args...)   ALOGD("[CODEC_VORPC]%s:" fmt, __func__, ##args)
#else
#define VORPC_PRINT(fmt, args...)
#endif

//#define DUMP_VO_WRITEBACK_FRAME
#define WB_PINID                0x20140507
#define WBINBAND_VERSION        0x72746b30 //rtk0
#define WBINBAND_VERSION_ENB_FORMAT    0x72746b31 //rtk1
#define WBINBAND_VERSION_ENB_FORMAT_WIDTH    0x72746b32 //rtk2
#define WBINBAND_ENTRYNUM       10
#define WBBUFFER_MALLOC_SIZE    1024*1024*1.5 //64K temporarily
#define WRITEBACK_BUFNUM        20

#define PLOCK_VERSION           (0x72746B33)
#define YUV_STATE_VERSION3      (0x72746b33) //rtk3
#define YUV_STATE_VERSION4      (0x72746b34) //rtk4
#define YUV_STATE_VERSION5      (0x72746b35) //rtk5

#define YUV_V3_SIZE             (sizeof(YUV_STATE) - sizeof(unsigned int) * 10)
#define YUV_V4_SIZE             (sizeof(YUV_STATE) - sizeof(unsigned int) * 4)
#define YUV_V5_SIZE             (sizeof(YUV_STATE))
#define PLOCK_FREE              0

#define DEINTERLACE_FIRST_FRAME (0x12345678)

#ifndef MAX_REG_FRAME
#define MAX_REG_FRAME 255
#endif

#define PLOCK_BUFFER_SET_SIZE   (MAX_REG_FRAME) //bytes
#define PLOCK_BUFFER_SET        (2)  // 2 set of PLock buffer for sequence change
#define PLOCK_MAX_BUFFER_INDEX  (PLOCK_BUFFER_SET_SIZE*PLOCK_BUFFER_SET) //bytes  // seperate to 2 set of PLock buffer for sequence change
#define PLOCK_BUFFER_SIZE       (PLOCK_MAX_BUFFER_INDEX) //bytes

#define MAX_VPU_ST_NUM 20

typedef struct pLockList
{
    unsigned char  bpLockEnbFlg;
    unsigned char  pLockUseFlg;
} pLockList;
typedef struct pLockstr
{
    unsigned char *pAddr;
    unsigned int  pPhyAddr;
    int idx;
    int dFirstFlg;
} pLockstr;


#define PLOCK_INIT              0xFF
#define PLOCK_QPEND             0
#define PLOCK_RECEIVED          1

enum
{
    PLOCK_STATUS_INIT    = 0,       // 0  / PLOCK_RESET
    PLOCK_STATUS_QPEND   = 1,       // 0  / PLOCK_QPEND
    PLOCK_STATUS_LOCK    = 2,       // >0 / PLOCK_RESET || PLOCK_QPEND || PLOCK_RECEIVED
    PLOCK_STATUS_UNLOCK  = 3,       // 0  / PLOCK_RECEIVED
    PLOCK_STATUS_ERR	 = 4        // else
};

enum {
    ENUM_VO_RESET = 0,
    ENUM_VO_INIT,
    ENUM_VO_READY,
    ENUM_VO_UNINIT,
};

enum PlockStatus { /* size : unsigned char */
    PLOCK_STATUS_RESET      = 0xFF,
    PLOCK_STATUS_Q_PEND     = 0x99,
    PLOCK_STATUS_VO_LOCK    = 0x01,
    PLOCK_STATUS_VO_LOCK2   = 0x02,
    PLOCK_STATUS_VO_UNLOCK  = 0x00,
    PLOCK_ERR               = 0xFE,
};

enum Format_Set{
    FORMAT_SET_DISABLE   = 0,
    FORMAT_SET_ENABLE    = 1,
    FORMAT_SET_16ALIGN   = 1<<1,
    FORMAT_SET_32ALIGN   = 1<<2,
    FORMAT_SET_MAX       = 1<<3,
};


#define CODEC_ALIGN(x, y)     ((x + y - 1) & ~(y - 1))
#define CODEC_ALIGN16(x)      CODEC_ALIGN(x, 16)
#define CODEC_ALIGN32(x)      CODEC_ALIGN(x, 32)

#define H_FLAG_SUCCESS                  (0x10000000)
#define S_OK                            ((H_FLAG_SUCCESS) |     (0x00000000))

#define REFCLOCK_SIZE sizeof(REFCLOCK)

typedef struct {
    unsigned int version;
    unsigned int mode;
    unsigned int Y_addr;
    unsigned int U_addr;
    unsigned int pLock;
    unsigned int width;
    unsigned int height;
    unsigned int Y_pitch;
    unsigned int C_pitch;
    unsigned int RPTSH;
    unsigned int RPTSL;
    unsigned int PTSH;
    unsigned int PTSL;

    /* for send two interlaced fields in the same packet,
     *     valid only when mode is INTERLEAVED_TOP_BOT_FIELD or INTERLEAVED_BOT_TOP_FIELD*/
    unsigned int RPTSH2;
    unsigned int RPTSL2;
    unsigned int PTSH2;
    unsigned int PTSL2;

    unsigned int context;
    unsigned int pRefClock;  /* not used now */

    unsigned int pixelAR_hor; /* pixel aspect ratio hor, not used now */
    unsigned int pixelAR_ver; /* pixel aspect ratio ver, not used now */

    unsigned int Y_addr_Right; /* for mvc */
    unsigned int U_addr_Right; /* for mvc */
    unsigned int pLock_Right; /* for mvc */
    unsigned int mvc;         /* 1: mvc */
    unsigned int subPicOffset;/* 3D Blu-ray dependent-view sub-picture plane offset metadata as defined in BD spec sec. 9.3.3.6.
                                 Valid only when Y_BufId_Right and C_BufId_Right are both valid */
    unsigned int pReceived;         // fix bug 44329 by version 0x72746B30 'rtk0'
    unsigned int pReceived_Right;   // fix bug 44329 by version 0x72746B30 'rtk0'

    unsigned int fps;   // 'rtk1'
    unsigned int IsForceDIBobMode; // force vo use bob mode to do deinterlace, 'rtk2'.

    unsigned int lumaOffTblAddr;    // 'rtk3'
    unsigned int chromaOffTblAddr;  // 'rtk3'
    unsigned int lumaOffTblAddrR; /* for mvc, 'rtk3' */
    unsigned int chromaOffTblAddrR; /* for mvc, 'rtk3' */

    unsigned int bufBitDepth;   // 'rtk3'
    unsigned int bufFormat;     // 'rtk3', according to VO spec: 10bits Pixel Packing mode selection, "0": use 2 bytes to store 1 components. MSB justified. "1": use 4 bytes to store 3 components. LSB justified.

    // VUI (Video Usability Information)
    unsigned int transferCharacteristics;   // 0:SDR, 1:HDR, 2:ST2084, 'rtk3'

    // Mastering display colour volume SEI, 'rtk3'
    unsigned int display_primaries_x0;
    unsigned int display_primaries_y0;
    unsigned int display_primaries_x1;
    unsigned int display_primaries_y1;
    unsigned int display_primaries_x2;
    unsigned int display_primaries_y2;
    unsigned int white_point_x;
    unsigned int white_point_y;
    unsigned int max_display_mastering_luminance;
    unsigned int min_display_mastering_luminance;

    /*for transcode interlaced feild use.*/ //'rtk4'
    unsigned int Y_addr_prev;
    unsigned int U_addr_prev;
    unsigned int Y_addr_next;
    unsigned int U_addr_next;

    unsigned int video_full_range_flag; //'rtk4'
    unsigned int matrix_coefficients; //'rtk4

    /*for transcode interlaced feild use.*/  //'rtk5'
    unsigned int pLock_prev;
    unsigned int pReceived_prev;
    unsigned int pLock_next;
    unsigned int pReceived_next;
} YUV_STATE;

/***************************************************rvsd_OSAL*/
typedef struct {
    unsigned int bufferNum;
    unsigned int bufferId;
    unsigned int bufferSize;
    unsigned int addrY;
    unsigned int addrC;
    unsigned int pitchY;
    unsigned int pitchC; //version >='rtk3': use height = pitchC ; if version <'rtk3', height =buffer Size/pitchY;
    unsigned int version;//version='rtk0' has pLock, pReceived; 'rtk1' has targetFormat; 'rtk2' has width;
    unsigned int pLock;
    unsigned int pReceived;
    unsigned int targetFormat;  //'rtk1'  bit 0=>NV21, 1:NV21, 0:NV12; bit 1=>422, 1:422, 0:420
    //bit 0=>NV21, 1:NV21, 0:NV12;
    //bit 1=>422, 1:422, 0:420;
    //bit 2=>bit depth, 1:10 bits, 0: 8 bits;
    //bit 3=>mode_10b, 0: use 2 bytes to store 1 components. MSB justified. 1: use 4 bytes to store 3 components, LSB justified;
    unsigned int width;
    unsigned int reserved[2];
} YUV_BUFFER;
/****************************************************/

typedef struct
{
    int                 wbBufEnb;
    ion_user_handle_t   wbIonHandle;
    unsigned char       *wbVirtAddr;
    unsigned int        wbPhysAddr;
    int                 wbMmapFd;

    int                 idx;
    SystemMemory        *wbIonHandleMemory;

} VOWBbuf_Struct;

typedef struct
{
    int                 Size;
    unsigned int        PhyAddr;
    unsigned char       *VirtAddr;
    SystemMemory        *SysMemoryHandle;
} VOWB_RTKALLOCATOR;
typedef struct
{
    RingBuffer          *pHandle;
    unsigned int        HeaderPhyAddr;
} VOWB_RTKRINGBUFFER;

typedef struct //VORPCGlobal
{
    unsigned char bVOReady;
    unsigned int out_id;
    int ion_fd;
    CLNT_STRUCT clnt;
//    VIDEO_RPC_VOUT_SET_MIXER_ORDER  mixer;

    VOWB_RTKALLOCATOR   mwbpLk;
    VOWB_RTKALLOCATOR   mScaleBuf;
    VOWB_RTKALLOCATOR   mpLock_ion;

    VOWB_RTKRINGBUFFER  mICQRingBuffer;
    VOWB_RTKRINGBUFFER  mWBRingBuffer;

    VOWBbuf_Struct      wbBufSt[WRITEBACK_BUFNUM];

    int                 wbIonSize;
    int                 wbBufNum;
    int                 wbBufIdx;
    unsigned int        wbInit;             //0:uninit 1:tvsystem 2:ringbuffer 3:wbbuffers
    int                 wbWidth;
    int                 wbHeight;
    struct timeval      timeStamp;
    unsigned int        wbFCnt;
    struct timeval      DectimeStamp;
    unsigned int        DecFCnt;

    pLockList           *stpLockList;
    pLockList           *stpLockphyList;
    int                 dpLockNumIdx;
    unsigned char       *pLockvirAddr;
    int                 FbCount;
    DataQueue           *pLockR_queue;
    int                 dInterlaceNeedFirstFlg;

    VOWBbuf_Struct      stVPUFrmIdx[WRITEBACK_BUFNUM];
    int                 dstRdptr;
    int                 dstWtptr;

    int                 dEnbSetFormat;
    int                 targetFormat; //'rtk1'  bit 0=>NV21, 1:NV21, 0:NV12; bit 1=>422, 1:422, 0:420
    int                 wbStride;
    int                 wbSliceHeight;
    int                 DecFormat;

    OMX_HANDLETYPE      wb_mutex;

} VORPCGlobal;

HRESULT codec_vo_initICQRingBuffer(VORPCGlobal *pVORPC);
unsigned int process_InbandCmd(VORPCGlobal *pVORPC, int cmd_type, void *packet, unsigned int packet_size_in_bytes);
unsigned int codec_vo_sendInbandCmd(void* p, void *cmd_endian_swapped, unsigned int cmd_size);

HRESULT codec_vo_initWriteBackRingBuffer(VORPCGlobal *pVORPC);
HRESULT codec_vo_initWriteBackBuffers(VORPCGlobal *pVORPC, int width, int height);
HRESULT codec_vo_getWriteBackFrame(VORPCGlobal *pVORPC, YUV_STATE *frame);
HRESULT codec_vo_SyncWriteBackBuffers(VORPCGlobal *pVORPC, int width, int height);
//static void buffer_endian_swap_4bytes(void *addr, unsigned int byte_size);
void _dbg_check_vo_inband_queue(OSAL_RTKALLOCATOR *alloc);
VORPCGlobal *codec_vo_init(void);
HRESULT codec_vo_uninit(VORPCGlobal *pVORPC);
HRESULT codec_vo_config(VORPCGlobal *pVORPC);
HRESULT codec_vo_releasepLock(VORPCGlobal *pVORP ,unsigned char *pLockphyAddr);
unsigned int codec_vo_getpLockphyAddr(VORPCGlobal *pVORPC, int idx , int fieldidx , int dFBCount, int dIsInterlaceFrm);
int codec_vo_rpc_ready(VORPCGlobal *pVORPC);

HRESULT codec_vo_ConfigWriteBackBuffers(VORPCGlobal *pVORPC, int width, int height,int dEnbSetFormat, int targetFormat);
HRESULT codec_vo_AddWriteBackBuffers(VORPCGlobal *pVORPC,int i, unsigned long phyAddress, unsigned char * virtAddress, int IsUseAllocBuff);
HRESULT codec_vo_ClearWriteBackBuffers(VORPCGlobal *pVORPC, unsigned long phyAddress, unsigned char * virtAddress);
HRESULT codec_vo_UnSetWriteBackBuffers(VORPCGlobal *pVORPC, unsigned long phyAddress, unsigned char * virtAddress);
HRESULT codec_vo_ReleaseWriteBackBuffers(VORPCGlobal *pVORPC);
HRESULT codec_vo_pause(VORPCGlobal *pVORPC);
HRESULT codec_vo_LockAllWriteBackBuffers(VORPCGlobal *pVORPC);

int codec_vo_GetWBNum(VORPCGlobal *pVORPC);

HRESULT codec_vo_GetReleasedBufIdx(VORPCGlobal *pVORPC, int *Idx, int eos);

//rvsd_OSAL
//void    pli_IPCCopyMemory(unsigned char* src, unsigned char* des, unsigned long len);
int codec_vo_GetDecLockInfo(VORPCGlobal *pVORPC);
int codec_vo_getbuf(VORPCGlobal *pVORPC,int wid,int hei);

#endif
