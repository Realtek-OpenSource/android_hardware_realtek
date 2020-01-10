/**
 * This product contains one or more programs protected under international
 * and U.S. copyright laws as unpublished works.  They are confidential and
 * proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
 * whole or in part, or the production of derivative works therefrom without
 * the express permission of Dolby Laboratories is prohibited.
 * Copyright 2011 - 2015 by Dolby Laboratories.
 * All rights reserved.
 *
 * @brief Includes debug macros and typedefs
 * @file rpu_debug.h
 *
 *
 * $Id$
 */

#ifndef _RPU_DEBUG_H_
#define _RPU_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Use this macro to print messages with a certain verbosity
 */
#define PRINT(severity, string, file, line, errno) \
    do if (msg_log) { \
        if (print_severity >= severity) { \
            msg_log(string, file, line, errno); \
        } \
    } while (0)

/**
 * @brief Log a message with a certain verbosity.
 * Usage example: LOG_MSG(("Error: %d\n", 1), S_ERROR);
 */
#define LOG_MSG(expr, severity) \
    do if (msg_log) { \
        if (print_severity >= severity) { \
            msg_log expr; \
        } \
    } while (0)


#define CHKREAD(len, espr) \
    do { \
        int ret_val = (espr); \
        if ((ret_val) < 0) { \
            PRINT(S_ERROR, "%s+%d: %s\n", \
            __FILE__, __LINE__, rpu_error_code_2_str(ret_val)); \
            return ret_val; \
        } \
        else \
        { \
            len += ret_val; \
        } \
    } while(0) \

#define CHKDATA(espr) \
    do { \
        if (!(espr)) { \
            PRINT(S_ERROR, "%s+%d: %s\n", \
            __FILE__, __LINE__, rpu_error_code_2_str(RPU_ERR_INVALID_DATA)); \
            return RPU_ERR_INVALID_DATA; \
        } \
    } while(0) \

#ifdef __cplusplus
}
#endif

#endif /* _RPU_DEBUG_H_ */
