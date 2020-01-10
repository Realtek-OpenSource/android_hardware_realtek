#ifndef __RTK_OMX_VIDEO_BUFFER_H__
#define __RTK_OMX_VIDEO_BUFFER_H__

#include <OSAL_RTK.h>
#include <port.h>
#include <base/vport.h>
#include <cutils/native_handle.h>
#include <utils/SecureHandle.h>
#ifdef ANDROID
#include <GrallocCMD.h>
#endif /*ANDROID*/

#define VBUFFER_PHYADDR_ERROR ((void *) -1)
#define VBUFFER_VIRADDR_ERROR (MAP_FAILED)

typedef struct VBUFFER      VBUFFER;
typedef struct VBUFFER_CB   VBUFFER_CB;
struct VBUFFER {
    BUFFER              base;

    enum BufferType {
        E_NONE_TYPE     = 0,
        E_ALLOC_SECURE_HANDLE,
        E_ALLOC_VIRTUAL_MEMORY,
        E_ALLOC_ION_MEMORY,
        E_ALLOC_STORE_METADATA,
        E_USE_BUFFER_HANDLE,
        E_USE_VIRTUAL_MEMORY,
    }                   eBufferType;

    enum /*VB_MEM_OPS*/ {
        VB_MOPS_NULL                = 0,
        VB_MOPS_FLUSH               = 1U << 0,
        VB_MOPS_INVALIDATE          = 1U << 1,
        VB_MOPS_UPDATE_V1_PRIV_DATA = 1U << 2,
    };

    int     eUseBeginOps;   /* enum VB_MEM_OPS */
    int     eUseEndOps;     /* enum VB_MEM_OPS */

    struct {
        void *              mAllocMemory; /* SystemMemory */
        void *              pSecureHandle;
        long                mAllocSize;
    }                   mAllocBuffer;

    struct {
        OMX_BOOL            bStoreMetaData;
        void *              pHandle;
        void *              pHandleDup;
        void *              pHandleDupPhyAddr;
        void *              pHandleIon;
        void *              pVirMemory;
        long                mUseSize;
        void *              pMetaDataVir;
        unsigned int        pMetaDataPhy;
        long                pMetaDataSize;
    }                   mUseBuffer;

    VBUFFER_CB *        mCb;
    void *              mCbData;

    void (*deinit       )  (VBUFFER * vbuffer);
    void (*wait_fence   )  (VBUFFER * vbuffer);
    void (*use_begin    )  (VBUFFER * vbuffer);
    void (*use_end      )  (VBUFFER * vbuffer);
    void (*signal_unlock)  (VBUFFER * vbuffer);
};

struct VBUFFER_CB {
    void (*onAllocCreated)  (VBUFFER * vbuffer, void * userData);
    void (*onUseImported)   (VBUFFER * vbuffer, void * userData);
    void (*onReleased)      (VBUFFER * vbuffer, void * userData);
};

VBUFFER *       vbuffer_alloc           (void);
void            vbuffer_freee           (VBUFFER * vbuffer);
BUFFER *        vbuffer_map_to_buffer   (VBUFFER * vbuffer);
VBUFFER *       buffer_map_to_vbuffer   (BUFFER * buffer);

void            vbuffer_init            (VBUFFER * vbuffer);
void            vbuffer_deinit          (VBUFFER * vbuffer);
void            vbuffer_prepare         (VBUFFER * vbuffer, VPORT * port);
void            vbuffer_set_cb          (VBUFFER * vbuffer, VBUFFER_CB * cb, void * cb_data);

private_rtk_v1_data *    vbuffer_get_gralloc_priv    (VBUFFER * vbuffer);
void *          vbuffer_get_handle      (VBUFFER * vbuffer);
void *          vbuffer_get_dup_handle  (VBUFFER * vbuffer);

void            vbuffer_wait_fence      (VBUFFER * vbuffer);
void            vbuffer_use_begin       (VBUFFER * vbuffer);
void            vbuffer_use_end         (VBUFFER * vbuffer);
void            vbuffer_signal_unlock   (VBUFFER * vbuffer);

int             vbuffer_alloc_buffer    (VBUFFER * vbuffer, OMX_U32 nSizeBytes);
int             vbuffer_use_buffer      (VBUFFER * vbuffer, OMX_U32 nSizeBytes, OMX_U8 * pBuffer);
int             vbuffer_use_buffer_import (VBUFFER * vbuffer, OMX_U32 nSizeBytes, OMX_U8 * pBuffer);
void *          vbuffer_get_virAddr     (VBUFFER * vbuffer);
void *          vbuffer_get_phyAddr     (VBUFFER * vbuffer);
long            vbuffer_get_size        (VBUFFER * vbuffer);
void *          vbuffer_get_metadataVir (VBUFFER * vbuffer);
unsigned int    vbuffer_get_metadataPhy (VBUFFER * vbuffer);
long            vbuffer_get_metadataSize(VBUFFER * vbuffer);
#endif /* __RTK_OMX_VIDEO_BUFFER_H__ */
