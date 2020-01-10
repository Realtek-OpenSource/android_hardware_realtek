#ifndef __RTK_OMX_VIDEO_PORT_H__
#define __RTK_OMX_VIDEO_PORT_H__

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

#include <OSAL_RTK.h>
#include <basecomp.h>
#include <port.h>
#if defined(__LINARO_SDK__)
#include <generic_misc.h>
#endif

typedef struct VPORT VPORT;
typedef struct VPORT_OPS VPORT_OPS;

struct VPORT_OPS {
    BUFFER *    (*gen_buffer_from_alloc)    (VPORT * vport, OMX_PTR pAppPrivate, OMX_U32 nSizeBytes);
    BUFFER *    (*gen_buffer_from_use)      (VPORT * vport, OMX_PTR pAppPrivate, OMX_U32 nSizeBytes, OMX_U8 * pBuffer);
    void        (*release_buffer)           (VPORT * vport, BUFFER * buffer);
    OMX_BOOL    (*own_buffer)               (VPORT * vport, BUFFER * buffer);
    void        (*thread_mutex_destroy)     (VPORT * vport);
    void        (*thread_mutex_lock)        (VPORT * vport);
    void        (*thread_mutex_unlock)      (VPORT * vport);
};

struct VPORT {
    PORT                base;
    OMX_BOOL            bStoreMetaData;
    OMX_BOOL            bEnableAndroidNativeBuffers;
    OMX_BOOL            bEnableGlinuxNativeBuffers;
    OMX_BOOL            bAllocateNativeHandle;  /* bUseProtectBuffer */
    OMX_BOOL            bAllocateSecure;        /* bUseProtectBuffer */
    OMX_BOOL            bEnableThumbnailMode;   /* output */

    VPORT_OPS           ops;

    struct {
        pthread_mutex_t     mutex;
        pthread_cond_t      cond;
        pid_t               threadId;
        int                 active;
        int                 count;
    }                   thread_wait;

    PORT_OPS            parent_ops;
};

VPORT *     port_map_to_vport           (PORT * port);
OMX_U32     port_get_index              (PORT * port);
OMX_PARAM_PORTDEFINITIONTYPE *
            port_get_definition         (PORT * port);

OMX_ERRORTYPE vport_init                (VPORT* vport, OMX_U32 nBufferCountMin, OMX_U32 nBufferCountActual, OMX_U32 nBuffers, OMX_U32 buffersize);
OMX_U32     vport_get_index             (VPORT * vport);
PORT *      vport_map_to_port           (VPORT * vport);

BUFFER *    vport_gen_buffer_from_alloc (VPORT * vport, OMX_PTR pAppPrivate, OMX_U32 nSizeBytes);
BUFFER *    vport_gen_buffer_from_use   (VPORT * vport, OMX_PTR pAppPrivate, OMX_U32 nSizeBytes, OMX_U8 * pBuffer);
void        vport_release_buffer        (VPORT * vport, BUFFER * buffer);
OMX_BOOL    vport_own_buffer            (VPORT * vport, BUFFER * buffer);
void        vport_thread_mutex_lock     (VPORT * vport);
void        vport_thread_mutex_unlock   (VPORT * vport);

#endif /* __RTK_OMX_VIDEO_PORT_H__ */
