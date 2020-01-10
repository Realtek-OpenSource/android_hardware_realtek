#ifndef CAM_HAL3_DEBUG_H
#define CAM_HAL3_DEBUG_H

#include <log/log.h>
#include <log/log_main.h>

//#include <media/stagefright/MediaCodec.h>

#define CHECK(condition)                                \
    LOG_ALWAYS_FATAL_IF(                                \
            !(condition),                               \
            "%s",                                       \
            __FILE__ ":" LITERAL_TO_STRING(__LINE__)    \
            " CHECK(" #condition ") failed.")

#endif

