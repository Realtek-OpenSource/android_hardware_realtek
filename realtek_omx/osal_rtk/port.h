#ifndef RTK_PORT_H
#define RTK_PORT_H

#include <OMX_Types.h>
#include <OMX_Component.h>
#include <OMX_Video.h>
#include "OSAL_RTK.h"
#if ! defined(__LINARO_SDK__)
#include <hardware/gralloc.h>
#include "native_handle.h"
#include "hal_public.h"
#endif
#include <system/SystemMemory.h>
#ifdef __cplusplus
extern "C" {
#endif 

#define BUFFER_FLAG_IN_USE      0x1
#define BUFFER_FLAG_MY_BUFFER   0x2
#define BUFFER_FLAG_IS_TUNNELED 0x4
#define BUFFER_FLAG_MARK        0x8
#define BUFFER_FLAG_ANDROID_NATIVE_BUFFER 0x10
#define BUFFER_FLAG_THUMBNAIL 0x20
#define BUFFER_FLAG_USE_BUFFER 0x30

#define PORT_INDEX_INPUT    0
#define PORT_INDEX_OUTPUT   1
#define PORT_INDEX_STATE_FLUSH    0x2379

typedef struct BUFFER
{
    OMX_BUFFERHEADERTYPE* header;
    OMX_BUFFERHEADERTYPE  headerdata;
    OMX_U32               flags;
    OMX_U32               allocsize;
    OSAL_BUS_WIDTH        bus_address;
    OMX_U8*               bus_data;
    ion_user_handle_t ionhdl;
    OMX_U32               ionFd;
    OMX_U32               shareFd;
    private_rtk_v1_data priv_data;
    void *pANativeWindowBuffer;
    SystemMemory          *mBufferMemory;
} BUFFER;

typedef struct BUFFERLIST
{
    BUFFER** list;
    OMX_U32  size; // list size
    OMX_U32  capacity;
}BUFFERLIST;

OMX_ERRORTYPE RTKOmx_bufferlist_init(BUFFERLIST* list, OMX_U32 size);
OMX_ERRORTYPE RTKOmx_bufferlist_reserve(BUFFERLIST* list, OMX_U32 newsize);
void          RTKOmx_bufferlist_destroy(BUFFERLIST* list);
OMX_U32       RTKOmx_bufferlist_get_size(BUFFERLIST* list);
OMX_U32       RTKOmx_bufferlist_get_capacity(BUFFERLIST* list);
BUFFER**      RTKOmx_bufferlist_at(BUFFERLIST* list, OMX_U32 i);
void          RTKOmx_bufferlist_remove(BUFFERLIST* list, OMX_U32 i);
void          RTKOmx_bufferlist_clear(BUFFERLIST* list);
OMX_BOOL      RTKOmx_bufferlist_push_back(BUFFERLIST* list, BUFFER* buff);

typedef BUFFER *    port_buffer_alloc (void * pAllocatorData);
typedef void        port_buffer_free  (BUFFER * buffer, void * pAllocatorData);

typedef struct PORT PORT;
typedef struct PORT_OPS PORT_OPS;

struct PORT_OPS
{
    OMX_ERRORTYPE   (*buffers_init)             (PORT* p, OMX_U32 nBufferCountMin, OMX_U32 nBufferCountActual, OMX_U32 nBuffers, OMX_U32 nBufferSize);
    void            (*setup_buffer_allocator)   (PORT* p, port_buffer_alloc * pBufferAlloc, port_buffer_free * pBufferFree, void * pAllocatorData);
    void            (*destroy)                  (PORT* p);
    OMX_BOOL        (*is_allocated)             (PORT* p);
    OMX_BOOL        (*is_ready)                 (PORT* p);
    OMX_BOOL        (*is_enabled)               (PORT* p);
    OMX_BOOL        (*has_buffers)              (PORT* p);
    OMX_BOOL        (*is_supplier)              (PORT* p);
    OMX_BOOL        (*is_tunneled)              (PORT* p);
    OMX_BOOL        (*has_all_supplied_buffers) (PORT* p);
    void            (*setup_tunnel)             (PORT* p, OMX_HANDLETYPE comp, OMX_U32 port, OMX_BUFFERSUPPLIERTYPE type);
    BUFFER*         (*find_buffer)              (PORT* p, OMX_BUFFERHEADERTYPE* header);
    OMX_BOOL        (*allocate_next_buffer)     (PORT* p, BUFFER** buff);
    OMX_BOOL        (*release_buffer)           (PORT* p, BUFFER* buff);
    OMX_BOOL        (*release_all_allocated)    (PORT* p);
    OMX_U32         (*buffer_count)             (PORT* p);
    OMX_BOOL        (*get_allocated_buffer_at)  (PORT* p, BUFFER** buff, OMX_U32 i);
    OMX_ERRORTYPE   (*push_buffer)              (PORT* p, BUFFER* buff);
    OMX_BOOL        (*get_buffer)               (PORT* p, BUFFER** buff);
    OMX_BOOL        (*get_buffer_at)            (PORT* P, BUFFER** buff, OMX_U32 i);
    OMX_BOOL        (*pop_buffer)               (PORT* p);
    OMX_BOOL        (*pop_buffer_at)            (PORT* p, OMX_U32 i);
    OMX_ERRORTYPE   (*lock_buffers)             (PORT* p);
    OMX_ERRORTYPE   (*unlock_buffers)           (PORT* p);
    OMX_U32         (*buffer_queue_count)       (PORT* p);
    void            (*buffer_queue_clear)       (PORT* p);
    BUFFER*         (*create_buffer_entry)      (PORT* p);                  // For inherit class
    void            (*destroy_buffer_entry)     (PORT* p, BUFFER* buffer);  // For inherit class
};

struct PORT
{
    OMX_PARAM_PORTDEFINITIONTYPE def;          // OMX port definition
    OMX_TUNNELSETUPTYPE          tunnel;
    OMX_HANDLETYPE               tunnelcomp;   // handle to the tunneled component
    OMX_U32                      tunnelport;   // port index of the tunneled components port
    BUFFERLIST                   buffers;      // buffers for this port
    BUFFERLIST                   bufferqueue;  // buffers queued up for processing
    OMX_HANDLETYPE               buffermutex;  // mutex to protect the buffer queue
    OMX_HANDLETYPE               bufferevent;  // event object for buffer queue
    OMX_BOOL                     useAndroidNativeBuffer;  // android stagefright flag for buffer type
    OMX_U32                      nTempBufferCountActual;  // for temp buffer count actual

    port_buffer_alloc   *        pBufferAlloc;
    port_buffer_free    *        pBufferFree;
    void *                       pAllocatorData;

    PORT_OPS                     ops;
};


// nBufferCountMin is a read-only field that specifies the minimum number of
// buffers that the port requires. The component shall define this non-zero default
// value.

// nBufferCountActual represents the number of buffers that are required on
// this port before it is populated, as indicated by the bPopulated field of this
// structure. The component shall set a default value no less than
// nBufferCountMin for this field.

// nBufferSize is a read-only field that specifies the minimum size in bytes for
// buffers that are allocated for this port. .
OMX_ERRORTYPE RTKOmx_port_init(PORT* p, OMX_U32 nBufferCountMin, OMX_U32 nBufferCountActual, OMX_U32 nBuffers, OMX_U32 buffersize);
OMX_ERRORTYPE RTKOmx_port_buffers_init(PORT* p, OMX_U32 nBufferCountMin, OMX_U32 nBufferCountActual, OMX_U32 nBuffers, OMX_U32 nBufferSize);

void RTKOmx_port_setup_buffer_allocator(PORT* p, port_buffer_alloc * pBufferAlloc, port_buffer_free * pBufferFree, void * pAllocatorData);

void     RTKOmx_port_destroy(PORT* p);

OMX_BOOL RTKOmx_port_is_allocated(PORT* p);

OMX_BOOL RTKOmx_port_is_ready(PORT* p);

OMX_BOOL RTKOmx_port_is_enabled(PORT* p);

// Return true if port has allocated buffers, otherwise false.
OMX_BOOL RTKOmx_port_has_buffers(PORT* p);

OMX_BOOL RTKOmx_port_is_supplier(PORT* p);
OMX_BOOL RTKOmx_port_is_tunneled(PORT* p);

OMX_BOOL RTKOmx_port_has_all_supplied_buffers(PORT* p);

void     RTKOmx_port_setup_tunnel(PORT* p, OMX_HANDLETYPE comp, OMX_U32 port, OMX_BUFFERSUPPLIERTYPE type);


BUFFER*  RTKOmx_port_find_buffer(PORT* p, OMX_BUFFERHEADERTYPE* header);


// Try to allocate next available buffer from the array of buffers associated with
// with the port. The finding is done by looking at the associated buffer flags and
// checking the BUFFER_FLAG_IN_USE flag.
//
// Returns OMX_TRUE if next buffer could be found. Otherwise OMX_FALSE, which
// means that all buffer headers are in use. 
OMX_BOOL RTKOmx_port_allocate_next_buffer(PORT* p, BUFFER** buff);



// 
OMX_BOOL RTKOmx_port_release_buffer(PORT* p, BUFFER* buff);

//
OMX_BOOL RTKOmx_port_release_all_allocated(PORT* p);


// Return how many buffers are allocated for this port.
OMX_U32 RTKOmx_port_buffer_count(PORT* p);


// Get an allocated buffer. 
OMX_BOOL RTKOmx_port_get_allocated_buffer_at(PORT* p, BUFFER** buff, OMX_U32 i);


/// queue functions


// Push next buffer into the port's buffer queue. 
OMX_ERRORTYPE RTKOmx_port_push_buffer(PORT* p, BUFFER* buff);


// Get next buffer from the port's buffer queue. 
OMX_BOOL RTKOmx_port_get_buffer(PORT* p, BUFFER** buff);


// Get a buffer at a certain location from port's buffer queue
OMX_BOOL RTKOmx_port_get_buffer_at(PORT* P, BUFFER** buff, OMX_U32 i);


// Pop off the first buffer from the port's buffer queue
OMX_BOOL      RTKOmx_port_pop_buffer(PORT* p);
OMX_BOOL      RTKOmx_port_pop_buffer_at(PORT* p, OMX_U32 i);

// Lock the buffer queue
OMX_ERRORTYPE RTKOmx_port_lock_buffers(PORT* p);
// Unlock the buffer queue
OMX_ERRORTYPE RTKOmx_port_unlock_buffers(PORT* p);


// Return how many buffers are queued for this port.
OMX_U32 RTKOmx_port_buffer_queue_count(PORT* p);

void RTKOmx_port_buffer_queue_clear(PORT* p);

#ifdef __cplusplus
} 
#endif
#endif // RTK_PORT_H
