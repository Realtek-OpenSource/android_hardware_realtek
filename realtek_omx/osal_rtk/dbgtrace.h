/*
 *   **************
 *   ** features **
 *   **************
 *- several trace levels:
 *  - 4 bits are reserved for level selection (1 bit for each level)
 *  - unconditional : DBGT_ASSERT/DBGT_CRITICAL/DBGT_ERROR/DBGT_WARNING
 *    (automatic expansion of faulty function)
 *  - level 1: light traces (DBGT_PTRACE)
 *  - level 2: prolog/epilog of functions (DBGT_PROLOG/DBGT_EPILOG)
 *    (automatic expansion of short function name only, not prototype)
 *  - level 3: verbose mode (DBGT_PDEBUG)
 *  - level 4: for future use
 *  - Examples (warning, must be given in hexa):
 *    - 0x1: light traces
 *    - 0x2: prolog/epilog
 *    - 0x4: verbose debug
 *    - 0x3: light trace+prolog/epilog
 *    - 0xF: all
 *
 *- several layers can be traced:
 *  - up to 8 layers
 *  - DBGT_LAYER to select layer to trace, typically 1 layer by sub-function
 *  - prolog/epilog will then be indented regading layer depth
 *  - Examples:
 *    - 0xF   will enable all traces in top layer
 *    - 0xF0  will enable all traces in top-1 layer
 *    - 0xF00 will enable all traces in top-2 layer
 *
 *- dynamic selection of item to trace & level:
 *  - on Android environment:
 *    - setprop mechanism; setprop <property> <level>
 *    - traces will be persistent through reboot if /data/local.prop file
 *      contain <property>=<level>
 *    - giving name "g1dec" through DBGT_TRACE_INIT() macro
 *      will create trace name "debug.g1dec.trace" used through:
 *      setprop debug.g1dec.trace 0x600 (warning must be hexa)
 *      => this will set prolog/epilog+verbose traces in layer top - 2
 *  - on LBP environment: export mechanism: export <property>=<level>
 *    - giving name "g1dec" through DBGT_TRACE_INIT() macro
 *      will create trace name "debug_g1dec_trace" used through:
 *      export debug_g1dec_trace=0x600
 *      => this will set prolog/epilog+verbose traces in layer top - 2
 *  - automatic expansion of prop trace name giving basic name
 *
 *- all traces could be discarded at compile time:
 *  => disable switch ENABLE_DBGT_TRACE
*/
#ifndef RTK_DEBUG_TRACE_H
#define RTK_DEBUG_TRACE_H

#ifdef ANDROID
#include <utils/Log.h>
#include <cutils/properties.h>
//#include <utils/backtrace.h>
#else
#include <stdlib.h> /*strtoul*/
#include <stdio.h>
#endif

#ifdef ANDROID
#include <utils/Timers.h>
#include <cutils/trace.h>
#define DBG_ATRACE_BEGIN(name) ATRACE_BEGIN(name)
#define DBG_ATRACE_END() ATRACE_END()
#define DBG_ATRACE_INT(name, value) ATRACE_INT(name, value)
#define DBG_ATRACE_INT64(name, value) ATRACE_INT64(name, value)
#else
#define DBG_ATRACE_BEGIN(name)
#define DBG_ATRACE_END()
#define DBG_ATRACE_INT(name, value)
#define DBG_ATRACE_INT64(name, value)
#endif

#ifndef LOG_NDEBUG
#define LOG_NDEBUG 1
#endif

#undef DBGT_TAG
#undef DBGT_PREFIX
#undef DBGT_LAYER

/* HW decoders */
#ifdef IS_G1_DECODER
#define DBGT_TAG "G1"
#endif
#ifdef IS_8190
#define DBGT_TAG "81x0"
#endif

/* HW encoders */
#ifdef ENCH1
#define DBGT_TAG "H1"
#endif
#ifdef ENC8290
#define DBGT_TAG "8290"
#endif
#ifdef ENC8270
#define DBGT_TAG "8270"
#endif
#ifdef ENCH7280
#define DBGT_TAG "7280"
#endif
#ifndef PROPERTY_KEY_MAX
#define PROPERTY_KEY_MAX   32
#endif

#define DBGT_PREFIX "OMX  "

#ifndef DBGT_LAYER
  #define DBGT_LAYER 0
#endif

#define DBGT_INDENT_0 " "
#define DBGT_INDENT_1 "  "
#define DBGT_INDENT_2 "   "
#define DBGT_INDENT_3 "    "
#define DBGT_INDENT_4 "     "
#define DBGT_INDENT_5 "      "
#define DBGT_INDENT_6 "       "
#define DBGT_INDENT_(i) DBGT_INDENT_##i
#define DBGT_INDENT(i)  DBGT_INDENT_(i)

#ifndef ANDROID
  #define ALOGI(fmt, args...) printf(fmt "\n", ##args)
  #define ALOGD(fmt, args...) printf(fmt "\n", ##args)
  #define ALOGE(fmt, args...) printf(fmt "\n", ##args)
  #define ALOGW(fmt, args...) printf(fmt "\n", ##args)
  #include <assert.h>
  #ifndef LOG_ALWAYS_FATAL_IF
  #define LOG_ALWAYS_FATAL_IF(condition, ...)\
    do {                                     \
      if (condition) {                       \
        ALOGE(__VA_ARGS__);                   \
        assert(!condition);                  \
      }                                      \
    } while (0)
  #endif
#endif

/* Waiting to find macro which expands class/prototype  */
#ifndef __PRETTY_FUNCTION__
  #define __PRETTY_FUNCTION__ __FUNCTION__
#endif

/* Unconditional, logged as assert, current process killed */
#define DBGT_ASSERT(condition, args...)                            \
  do {                                                             \
    if (!(condition)) {                                            \
      ALOGE("%s" DBGT_INDENT(DBGT_LAYER)"! "                        \
           "assertion !(" #condition ") ""failed at %s, %s:%d",    \
           DBGT_PREFIX, __PRETTY_FUNCTION__,  __FILE__, __LINE__); \
      LOG_ALWAYS_FATAL_IF(!(condition), ## args);                  \
    }                                                              \
  } while (0)

/* Unconditional, logged as error, function with signature, file, line */
#define DBGT_CRITICAL(fmt, args...)                             \
    ALOGE( "%s" DBGT_INDENT(DBGT_LAYER)"! %s "                   \
          fmt " %s:%d", DBGT_PREFIX, __PRETTY_FUNCTION__,       \
          ## args, __FILE__, __LINE__)

/* Unconditional, logged as error, function with signature only */
#define DBGT_ERROR(fmt, args...)                                \
    ALOGE( "%s" DBGT_INDENT(DBGT_LAYER)"! %s "                   \
         fmt, DBGT_PREFIX, __PRETTY_FUNCTION__, ## args)

/* Unconditional, logged as warning, function with signature only */
#define DBGT_WARNING(fmt, args...)                              \
    ALOGW( "%s" DBGT_INDENT(DBGT_LAYER)"? %s "                   \
         fmt, DBGT_PREFIX, __PRETTY_FUNCTION__, ## args)

#ifndef ENABLE_DBGT_TRACE
  #define DBGT_PTRACE(...)
  #define DBGT_PROLOG(...)
  #define DBGT_EPILOG(...)
  #define DBGT_PDEBUG(...)
  #define DBGT_TRACE_INIT(name)                              \
    ALOGW("[DBGT] %s compiled without trace support"          \
         " (ENABLE_DBGT_TRACE switch not enabled)", #name);
#else

/*#ifndef DBGT_VAR
  #define DBGT_VAR 0xFFF
#endif*/

#ifdef DBGT_CONFIG_AUTOVAR
  #ifndef DBGT_VAR
    #define DBGT_VAR mDBGTvar
  #endif

  #ifndef DBGT_VAR_INIT
    #define DBGT_VAR_INIT 0
  #endif

  #ifdef DBGT_DECLARE_AUTOVAR
    int DBGT_VAR = DBGT_VAR_INIT;
  #else
    extern int DBGT_VAR;
  #endif
#else  /* #ifdef DBGT_CONFIG_AUTOVAR */
  #ifndef DBGT_VAR
    #error "[DBGT] DBGT_VAR needs to be defined when DBGT_CONFIG_AUTOVAR is not"
  #endif
#endif  /* #ifdef DBGT_CONFIG_AUTOVAR */

#define DBGT_PTRACE(fmt, args...)                       \
    do { if (DBGT_VAR & (0x1<<(DBGT_LAYER*4))) {        \
            ALOGI( "%s" DBGT_INDENT(DBGT_LAYER)          \
                  fmt, DBGT_PREFIX, ## args);           \
        } } while (0)

#define DBGT_PROLOG(fmt, args...)                               \
    do { if (DBGT_VAR & (0x2<<(DBGT_LAYER*4))) {                \
            ALOGD( "%s" DBGT_INDENT(DBGT_LAYER)"> %s()"          \
                  fmt, DBGT_PREFIX, __FUNCTION__, ## args);     \
        } } while (0)

#define DBGT_EPILOG(fmt, args...)                               \
    do { if (DBGT_VAR & (0x2<<(DBGT_LAYER*4))) {                \
            ALOGD( "%s" DBGT_INDENT(DBGT_LAYER)"< %s()"          \
                  fmt, DBGT_PREFIX, __FUNCTION__, ## args);     \
        } } while (0)

#define DBGT_PDEBUG(fmt, args...)                        \
    do { if (DBGT_VAR & (0x4<<(DBGT_LAYER*4))) {         \
            ALOGD( "%s" DBGT_INDENT(DBGT_LAYER)". "       \
                  fmt, DBGT_PREFIX, ## args);            \
        } } while (0)

#define STR(x) x

#ifndef DBGT_TRACE_NAME
#ifdef ANDROID
  #define DBGT_TRACE_NAME(a) "debug."a".trace"
#else
  /* '.' are not valid in bash variables */
  #define DBGT_TRACE_NAME(a) "debug_"a"_trace"
#endif
#endif

#ifdef ANDROID
#define GET_PROPERTY(key, value, default_value)   \
    char value[PROPERTY_VALUE_MAX];               \
    property_get(key, value, default_value);
#else
#define GET_PROPERTY(key, value, default_value)	  \
    char * value = getenv(key);                   \
    if (value == NULL) {                          \
	value = (char *) default_value;               \
    }
#endif

/* Warning, value to give to setprop is in hexadecimal! */
#define DBGT_TRACE_INIT(name)                                             \
    do {                                                                  \
        if (strlen(STR(DBGT_TRACE_NAME(#name))) > PROPERTY_KEY_MAX) {     \
            ALOGE("[DBGT]! Property key name [" STR(DBGT_TRACE_NAME(#name))\
                 "] exceed %d char length, will be cut to %d...",         \
                 PROPERTY_KEY_MAX, PROPERTY_KEY_MAX);                     \
        } else {                                                          \
            GET_PROPERTY(STR(DBGT_TRACE_NAME(#name)), value, "0");        \
            DBGT_VAR = strtoul(value, NULL, 16);                          \
            if (DBGT_VAR > 0) {                                           \
                ALOGI("[DBGT]["STR(DBGT_TRACE_NAME(#name))                 \
                     "] enabled with level 0x%x", DBGT_VAR);              \
            } else {                                                      \
                ALOGI("[DBGT]["STR(DBGT_TRACE_NAME(#name))                 \
                     "] disabled");                                       \
            }                                                             \
        }                                                                 \
    } while (0)

/* To allow update of trace level at run-time */
#define DBGT_SET_TRACE_LEVEL(level)                               \
    do {                                                          \
            DBGT_VAR = level;                                     \
            if (DBGT_VAR > 0) {                                   \
                ALOGI("[DBGT] trace set to level 0x%x", DBGT_VAR); \
            } else {                                              \
                ALOGI("[DBGT] trace set to 0, trace is disabled"); \
            }                                                     \
        }                                                         \
    } while (0)

#endif /* ENABLE_DBGT_TRACE */

#endif /* RTK_DEBUG_TRACE_H */
