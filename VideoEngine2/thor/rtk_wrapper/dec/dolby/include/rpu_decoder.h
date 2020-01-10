/**
 * This product contains one or more programs protected under international
 * and U.S. copyright laws as unpublished works.  They are confidential and
 * proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
 * whole or in part, or the production of derivative works therefrom without
 * the express permission of Dolby Laboratories is prohibited.
 * Copyright 2011 - 2015 by Dolby Laboratories.
 * All rights reserved.
 *
 * @brief RPU decoding functions.
 * @file rpu_decoder.h
 *
 * $Id$
 */



#ifndef _RPU_DECODER_H_
#define _RPU_DECODER_H_

#include "rpu_api_common.h"
#include "rpu_parser.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum rbsp_parse_state_e
{
    RBSP_SEARCH_RPU,
    RBSP_FOUND_START_00,
    RBSP_FOUND_START_0000,
    RBSP_FOUND_START_000001,
    RBSP_FOUND_RPU,
    RBSP_FOUND_00,
    RBSP_FOUND_0000
} rbsp_parse_state_t;


struct rpu_decoder_ctx_s
{
    rpu_data_t *rpu_data;
    rpu_context_t *rpu_context;
    unsigned char (*rpu_buffer)[MAX_BITSTREAM_SIZE];
    int *rpu_buffer_level;
    unsigned int rpu_input_buffer;
    unsigned int rpu_output_buffer;
    int last;
    int disable_crc_check;
    int payload_only;
    unsigned int num_rpu_buffers;
    /* the current bit stream */
    bit_stream_t rpu_bitstream;
    int allow_changing_sequence_header;
    /* buffer for the last sequence header info */
    vdr_rpu_sequence_header_t rpu_sequence_header_store;
    int  prev_sequence_header_available;
    vdr_dm_data_payload_t dm_data_payload_store;
    int  prev_dm_data_payload_available;
    ext_content_adaptive_metadata_t tmp_ext_blocks[16];
#if ENABLE_FLOAT
    int  convert_to_float;
    int  convert_to_fxp;
#endif

    rpu_msg_log_func_t msg_log;
    print_severity_t print_severity;
    rbsp_parse_state_t rbsp_parse_state;
    /* buffer for the rpu bit stream */
    vdr_rpu_data_payload_t *payload_buffer[(MAX_RPU_ID + 1)];
    vdr_rpu_data_payload_t *payload_handle[(MAX_RPU_ID)];
    vdr_rpu_data_payload_t *payload_handle_empty;
};

int rpu_decoder_read_rpu_nalu(rpu_decoder_ctx_t* rdc);

#ifdef __cplusplus
}
#endif

#endif /* _RPU_DECODER_H_ */
