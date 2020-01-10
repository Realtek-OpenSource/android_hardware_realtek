/**
 * This product contains one or more programs protected under international
 * and U.S. copyright laws as unpublished works.  They are confidential and
 * proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
 * whole or in part, or the production of derivative works therefrom without
 * the express permission of Dolby Laboratories is prohibited.
 * Copyright 2011 - 2015 by Dolby Laboratories.
 * All rights reserved.
 *
 * @brief Writing functions.
 * @file rpu_writer.h
 *
 * $Id$
 */

#ifndef _RPU_WRITER_H_
#define _RPU_WRITER_H_

#include <rpu_api_common.h>
#include <rpu_api_encoder.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bitstream_struct
{
    uint64_t ui64_bit_buffer;
    int32_t i_free_bits;
    int32_t i_bytes_in_buffer;
    uint8_t *pui8_out_buffer;
    int32_t i_buffer_size;

} bit_stream_t;

struct rpu_encoder_ctx_s
{
    /* buffer for the rpu bit stream
       add 4 byte for length before nalu_buffer */
    unsigned char nalu_buffer_mem[MAX_BITSTREAM_SIZE + 4];
    unsigned char *nalu_buffer;

    unsigned char* bs_buffer;
    bit_stream_t rpu_bitstream;
    rpu_context_t* rpu_context;
    rpu_msg_log_func_t msg_log;
    print_severity_t print_severity;

    /* buffer for the last sequence header info */
    vdr_rpu_sequence_header_t rpu_sequence_header_store;
    int  prev_sequence_header_available;
};

/*!
    @brief
    Writes the rpu header to the RPU RBSP.
    @param [in/out]  rpu_data
    pointer to the RPU data structure
    @return
        @li >=0     Size of writen header in bits.
        @li < 0     Failure.
*/
int rpu_header_write(rpu_encoder_ctx_t* rec, rpu_data_t *rpu_data);

/*!
    @brief
    Writes the rpu payload to the RPU RBSP.
    @param [in/out]  rpu_data
    pointer to the RPU data structure
    @return
        @li >=0     Size of writen payload in bits.
        @li < 0     Failure.
*/
int rpu_payload_write(rpu_encoder_ctx_t* rec, rpu_data_t *rpu_data);

/*!
    @brief
    Writes the dm metadata to the RPU RBSP.
    @param [in/out]  rpu_data
    pointer to the RPU data structure
    @return
        @li >=0     Size of writen ,etadata in bits..
        @li < 0     Failure.
*/
int dm_data_payload_write(rpu_encoder_ctx_t* rec, rpu_data_t *rpu_data);


int write_rpu_nalu(unsigned char* input_buffer, unsigned char* output_buffer, int startcode_len, int rbsp_len);

void SODBtoRBSP(bit_stream_t *bs);

int RBSPtoEBSP(unsigned char *out_buffer, unsigned char *rbsp, int rbsp_size);

int write_ue_v (uint32_t value, bit_stream_t *bitstream);

int write_se_v (int32_t value, bit_stream_t *bitstream);

int write_u_1 (uint8_t value, bit_stream_t *bitstream);

int write_u_v (int n, uint32_t value, bit_stream_t *bitstream);

int write_i_v (int n, int32_t value, bit_stream_t *bitstream);



#ifdef __cplusplus
}
#endif

#endif /* _RPU_WRITER_H_ */
