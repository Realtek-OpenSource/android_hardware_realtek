#ifndef RTK_BASECOMP_H
#define RTK_BASECOMP_H

#include "msgque.h"
#include "OSAL_RTK.h"
#include <OMX_Types.h>
#include <OMX_Component.h>
#include <OMX_Video.h>
#include <OMX_Image.h>
#include "android_ext.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct BASECOMP
{
    OMX_HANDLETYPE    thread;
    msgque            queue;
} BASECOMP;

typedef enum CMD_TYPE
{
    CMD_SEND_COMMAND,
    CMD_EXIT_LOOP
} CMD_TYPE;

typedef struct SEND_COMMAND_ARGS
{
    OMX_COMMANDTYPE cmd;
    OMX_U32         param1;
    OMX_PTR         data;
    OMX_ERRORTYPE (*fun)(OMX_COMMANDTYPE, OMX_U32, OMX_PTR, OMX_PTR);
} SEND_COMMAND_ARGS ;


typedef struct CMD
{
    CMD_TYPE          type;
    SEND_COMMAND_ARGS arg;
}CMD;


typedef OMX_U32 (*thread_main_fun)(BASECOMP*, OMX_PTR);

OMX_ERRORTYPE RTKOmx_basecomp_init(BASECOMP* b, thread_main_fun f, OMX_PTR arg);
OMX_ERRORTYPE RTKOmx_basecomp_destroy(BASECOMP* b);
OMX_ERRORTYPE RTKOmx_basecomp_send_command(BASECOMP* b, CMD* c);
OMX_ERRORTYPE RTKOmx_basecomp_recv_command(BASECOMP* b, CMD* c);
OMX_ERRORTYPE RTKOmx_basecomp_try_recv_command(BASECOMP* b, CMD* c, OMX_BOOL* ok);

void RTKOmx_generate_uuid(OMX_HANDLETYPE comp, OMX_UUIDTYPE* uuid);


OMX_ERRORTYPE RTKOmx_cmd_dispatch(CMD* cmd, OMX_PTR arg);


#define CHECK_PARAM_NON_NULL(param)    \
  if ((param) == 0)                    \
  {                                    \
      DBGT_CRITICAL("Null parameter"); \
      DBGT_EPILOG("");                 \
      return OMX_ErrorBadParameter;    \
  }

#define CHECK_STATE_INVALID(state)    \
  if ((state) == OMX_StateInvalid)    \
  {                                   \
      DBGT_CRITICAL("Invalid state"); \
      DBGT_EPILOG("");                \
      return OMX_ErrorInvalidState;   \
  }

#define CHECK_STATE_IDLE(state)       \
  if ((state) == OMX_StateIdle)       \
  {                                   \
      DBGT_CRITICAL("State is idle"); \
      DBGT_EPILOG("");                \
      return OMX_ErrorIncorrectStateOperation; \
  }

#define CHECK_STATE_LOADED(state)     \
  if ((state) != OMX_StateLoaded)     \
  {                                   \
      DBGT_CRITICAL("State is not loaded"); \
      DBGT_EPILOG("");                \
      return OMX_ErrorIncorrectStateOperation; \
  }

#define CHECK_PARAM_VERSION(param) \
  if ((param).nVersion.s.nVersionMajor != 1 || \
      (param).nVersion.s.nVersionMinor != 1) \
      return OMX_ErrorVersionMismatch

#define INIT_OMX_VERSION_PARAM(param)   \
  (param).nSize = sizeof(param);        \
  (param).nVersion.s.nVersionMajor = 1; \
  (param).nVersion.s.nVersionMinor = 1; \
  (param).nVersion.s.nRevision     = 2; \
  (param).nVersion.s.nStep         = 0

#define INIT_EXIT_CMD(cmd)        \
  memset((&cmd), 0, sizeof(CMD)); \
  cmd.type = CMD_EXIT_LOOP

#define INIT_SEND_CMD(cmd_, omxc, param, data_, fun_)   \
  memset(&cmd_, 0, sizeof(CMD));                        \
  cmd_.type         = CMD_SEND_COMMAND;                 \
  cmd_.arg.cmd    = omxc;                               \
  cmd_.arg.param1 = param;                              \
  cmd_.arg.data   = data_;                              \
  cmd_.arg.fun    = fun_

#define DECLARE_STUB(x) static OMX_ERRORTYPE x(OMX_HANDLETYPE,   ...)
#define DEFINE_STUB(x)  static OMX_ERRORTYPE x(OMX_HANDLETYPE h, ...) { return OMX_ErrorNotImplemented; }

#ifdef __cplusplus
}
#endif
#endif /* RTK_BASECOMP_H */
