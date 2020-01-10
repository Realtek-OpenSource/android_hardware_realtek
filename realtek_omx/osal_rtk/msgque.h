#ifndef RTK_MSGQUE_H
#define RTK_MSGQUE_H

#if defined(__LINARO_SDK__)
#include "OMX_Types.h"
#include "OMX_Core.h"
#else
#include <media/openmax/OMX_Types.h>
#include <media/openmax/OMX_Core.h>
#endif

#include "OSAL_RTK.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct msg_node msg_node;

struct msg_node
{
    msg_node* next;
    msg_node* prev;
    OMX_PTR   data;
};

typedef struct msgque
{ 
    msg_node*      head;
    msg_node*      tail;
    OMX_U32        size;
    OMX_HANDLETYPE mutex; 
    OMX_HANDLETYPE event;
} msgque;

// Initialize a new message queue instance 
OMX_ERRORTYPE RTKOmx_msgque_init(OMX_IN msgque* q);

// Destroy the message queue instance, free allocated resources
void RTKOmx_msgque_destroy(OMX_IN msgque* q);

// Push a new message at the end of the queue. 
// Function provides commit/rollback semantics.
OMX_ERRORTYPE RTKOmx_msgque_push_back(OMX_IN msgque* q, OMX_IN OMX_PTR ptr);

// Get a message from the front, returns always immediately but 
// ptr will point to NULL if the queue is empty. 
// Function provides commit/rollback semantics.
OMX_ERRORTYPE RTKOmx_msgque_get_front(OMX_IN msgque* q, OMX_OUT OMX_PTR* ptr);

// Get current queue size
OMX_ERRORTYPE RTKOmx_msgque_get_size(OMX_IN msgque* q, OMX_OUT OMX_U32* size);

#ifdef __cplusplus
}
#endif
#endif // RTK_MSGQUE_H
