/**
 * This product contains one or more programs protected under international
 * and U.S. copyright laws as unpublished works.  They are confidential and
 * proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
 * whole or in part, or the production of derivative works therefrom without
 * the express permission of Dolby Laboratories is prohibited.
 * Copyright 2011 - 2015 by Dolby Laboratories.
 * All rights reserved.
 *
 * @brief RPU decoder API.
 * @file rpu_api_decoder.h
 *
 * $Id$
 */

#ifndef _RPU_API_DECODER_H_
#define _RPU_API_DECODER_H_

#include <rpu_std.h>
#include <rpu_api_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Defines
 ****************************************************************************/

/****************************************************************************
 * Enumerations
 ****************************************************************************/




/****************************************************************************
 * Type definitions
 ****************************************************************************/

/*!
    @brief
    The RPU decoder context.
    This context is used for all RPU decoder functions.
*/
typedef struct rpu_decoder_ctx_s rpu_decoder_ctx_t;

/****************************************************************************
 * Function definitions
 ****************************************************************************/

/*!
    @brief Query memory of rpu decoder library.
    This function needs to be called before rpu_decoder_init(). It returns the amount of memory
    to be allocated by the caller of the library.
    @param [in]  flags  flags for the decoder initialization
                 see definition of \ref rpu_init_flags_t for details
    @return  number of bytes to be allocated to the rpu_decoder context.
*/
LIBRPU_API size_t rpu_decoder_mem_query(rpu_init_flags_t* flags);

/*!
    @brief Initialize the RPU decoder.
    This function needs to be called before using the rpu decoder.
    @param [in]  rdc    pointer to the RPU decoder context
    @param [in]  flags  flags for the decoder initialization
                 see definition of \ref rpu_init_flags_t for details
    @return
        @li >=0     number of bytes allocated by rpu_decoder_init.
        @li  <0     error code
*/
LIBRPU_API int rpu_decoder_init(rpu_decoder_ctx_t* rdc, rpu_init_flags_t* flags);

/*!
    @brief
    Cleanup the RPU decoder.
    This function needs to be called to free all resources used by the rpu decoder.
    @param [in]  rdc  pointer to the RPU decoder context
*/
LIBRPU_API int rpu_decoder_cleanup(rpu_decoder_ctx_t* rdc);

/*!
    @brief Push a bitstream chunk into the rpu decoder.
    @details The bitstream chunk can be any size up to RPU_PRE_BUFFER_SIZE.
    If rpu_decoder_push_data is called repeatedly without calling rpu_decoder_get_output the input buffer might overflow. In this case rpu_decoder_push_data returns RPU_ERR_INPUT_BUFFER_FULL. No data is written to the input buffer.
    @param [in]  rdc          pointer to the RPU decoder context
    @param [in]  buffer       ponter to the input buffer
    @param [in]  buffer_size  size of the input buffer
    @param [in]  last         indicates the last buffer of the stream
    @return
        @li =0     no error
        @li <0     error code

*/
LIBRPU_API int rpu_decoder_push_data(rpu_decoder_ctx_t* rdc, unsigned char *buffer, int buffer_size, int last);


/*!
    @brief
    Read a rpu packet from the rpu decoder.
    @param [in]  rdc
        Pointer to the RPU decoder context.
    @param [out]  rpu_header
        Pointer to the rpu data structure.
    @param [out]  rpu_payload
        Pointer to the rpu payload data structure.
    @param [out]  rpu_payload_size
        Size of the rpu payload.
    @param [out]  dm_data_payload
        Pointer to the dm_data payload data structure.
    @param [out]  dm_data_payload_size
        Size of the dm_data payload.
    @return
        @li >=0    number of bits read from the bitstream
        @li <0     error code
*/
LIBRPU_API int rpu_decoder_get_output(rpu_decoder_ctx_t* rdc, rpu_data_header_t** rpu_header,
                                vdr_rpu_data_payload_t** rpu_payload, int* rpu_payload_size,
                                vdr_dm_data_payload_t** dm_data_payload, int* dm_data_payload_size);

/*!
    @brief
    Core function to process one RPU buffer.
    This API function can be use instead of the pair rpu_decoder_push_data() and rpu_decoder_get_output().
    The input needs to be one full RPU buffer without startcode, nal unit type and without startcode prevention bytes.
    This function will return immediatly with the parsed RPU.
    @param [in]  rdc
        Pointer to the RPU decoder context.
    @param [out]  buffer
        Pointer to the rpu input buffer. This buffer needs to be one full RPU without startcode,
        nal unit type and start code prevention bytes removed.
    @param [out]  buffer_size
        Size of the rpu_buffer.
    @param [out]  rpu_header
        Pointer to the rpu data structure.
    @param [out]  rpu_payload
        Pointer to the rpu payload data structure.
    @param [out]  rpu_payload_size
        Size of the rpu payload.
    @param [out]  dm_data_payload
        Pointer to the dm_data payload data structure.
    @param [out]  dm_data_payload_size
        Size of the dm_data payload.
    @return
        @li >=0    number of bits read from the bitstream
        @li <0     error code
*/
LIBRPU_API int rpu_decoder_process_buffer(rpu_decoder_ctx_t* rdc,
                            unsigned char* buffer, int buffer_size,
                            rpu_data_header_t** header,
                            vdr_rpu_data_payload_t** rpu_payload, int* rpu_payload_size,
                            vdr_dm_data_payload_t** dm_data_payload, int* dm_data_payload_size);
/*!
    @brief
    Flushes the rpu decoder. After a flush all remaining RPU units in the decoder buffer can be read out.
    No data can be pushed in until the decoder receives a reset.
    @param [in]  rdc          pointer to the RPU decoder context
    @return
        @li =0     no error
        @li <0     error code
*/
LIBRPU_API int rpu_decoder_flush(rpu_decoder_ctx_t* rdc);

/*!
    @brief
    Resets the rpu decoder.
    The state of the decoder after a reset is the same as after initializing the decoder.
    No additional resources are allocated.
    @param [in]  rdc          pointer to the RPU decoder context
    @return
        @li =0     no error
        @li <0     error code
*/
LIBRPU_API int rpu_decoder_reset(rpu_decoder_ctx_t* rdc);


/*!
    @brief
    Indicate if the last RPU packet has been output
    @param [in]  rdc          pointer to the RPU decoder context
    @return
        @li 1     the last RPU packet has been output
        @li 0     either last RPU packet has not been output or we are not at end of stream yet
*/
LIBRPU_API int rpu_decoder_last_rpu_output(rpu_decoder_ctx_t* rdc);


/*!
    @brief
    Set the internal message log function pointer.
    Using the message log is optional. If no message log is assigned no error messages will be printed.
    @param [in]  rdc          pointer to the RPU decoder context
    @param [in]  msg_log      pointer to the message log function
    @param [in]  print_severity print severity
*/
LIBRPU_API void rpu_decoder_set_msg_log(rpu_decoder_ctx_t* rdc, rpu_msg_log_func_t msg_log, print_severity_t print_severity);

/*!
    @brief
    Construct the composer metadata structure from the RPU fixed-point MAIN
    profile metadata.
*/
LIBRPU_API void comp_rpu_2_main_cfg(rpu_data_header_t *rh, vdr_rpu_data_payload_t *rpu_payload, rpu_ext_config_fixpt_main_t *comp_cfg);

#ifdef __cplusplus
}
#endif

#endif /* _RPU_API_DECODER_H_ */
