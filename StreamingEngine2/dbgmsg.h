
#ifndef _DBGMSG_H_
#define _DBGMSG_H_

#ifdef __ANDROID__

#include <utils/Log.h>
#define MSGD(...)     ALOGD(__VA_ARGS__)
#define MSGV(...)     ALOGV(__VA_ARGS__)

#define DEBUG_INTERVAL
#ifdef DEBUG_INTERVAL
#define INTERVAL(cond, min, tprev)  do{ \
        nsecs_t t = systemTime(SYSTEM_TIME_MONOTONIC); \
        nsecs_t interval = t - tprev; \
        if((cond) && (interval > min)) ALOGD("%s:%d: %.3fms", __func__, __LINE__, interval/1000000.0); \
        tprev = t; \
    }while(0)
#else
#define INTERVAL(tprev)  do{ }while(0)
#endif

#else
#if defined(__LINARO_SDK__)
#define MSGD(...)
#define MSGV(...)
#else
#define MSGD(...)     printf(__VA_ARGS__)
#define MSGV(...)     printf(__VA_ARGS__)
#endif
#endif

#endif //_DBGMSG_H_
