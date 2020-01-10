/**
 * This product contains one or more programs protected under international
 * and U.S. copyright laws as unpublished works.  They are confidential and
 * proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
 * whole or in part, or the production of derivative works therefrom without
 * the express permission of Dolby Laboratories is prohibited.
 * Copyright 2011 - 2015 by Dolby Laboratories.
 * All rights reserved.
 *
 * @brief Parsing functions.
 * @file rpu_parser.h
 *
 * $Id$
 */

#ifndef _RPU_PARSER_H_
#define _RPU_PARSER_H_

#include <rpu_common.h>
#include <rpu_api_common.h>
#include <rpu_api_decoder.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bit_stream_s
{
    /* current 32 bit working set */
    unsigned int ui_buf;

    /* used bits in working set */
    int i_bits;

    /* buffer with stream data */
    unsigned char* pui8_ptr;

    unsigned char* pui8_buffer_end;

    /* number of bits in the last byte of buffer */
    int i_end_bits;

    /* number of total read bits */
    int i_len;

} bit_stream_t;




#define get16Bits( ui_buffer, i_bits, pui8_ptr, pui8_buffer_end )   		        \
    if ( ( i_bits > 0 ) )                                                           \
    {                                                                               \
        if( pui8_ptr > ( pui8_buffer_end + 4 ) )                                    \
        {                                                                           \
            pui8_ptr = pui8_buffer_end;                                             \
        }                                                                           \
        ui_buffer |= ( unsigned int ) (( ( pui8_ptr[ 0 ] << 8 ) | pui8_ptr[ 1 ] ) << ( i_bits ));      \
        pui8_ptr += 2;                                                              \
        i_bits -= 16;                                                               \
    }


/* remove num valid i_bits from ui_buffer */
#define flushBits( ui_buffer, i_bits, num )									\
	ui_buffer <<= ( num );													\
	i_bits += ( num );


/* take num i_bits from the high part of ui_buffer and zero extend them */
#define getUBits( ui_buffer, num ) ( ( ( unsigned int )( ui_buffer ) ) >> ( 32 - ( num ) ) )

/*!
    @brief
    Convetrts from EBSP to RBSP (removing Startcode prevention).
    @param [in/out]  nalu_buffer
    pointer to the nalu buffer
    @param [in]  length
    length of RPU bitstream including startcode.
    @return
        @li >0     Size of the RBSP.
        @li -1     Failure.
*/
int rpu_get_RBSP(unsigned char* nalu_buffer, int length);

/*!
    @brief
    Reads an RPU RBSP and fill the rpu_data header structure.
    @param [in/out]  rpu_data
    pointer to the RPU data structure
    @return
        @li >=0     Size of read header in bits.
        @li < 0     Failure.
*/
int rpu_header_read(rpu_decoder_ctx_t *rdc);

/*!
    @brief
    Reads an RPU RBSP and fills the rpu_data payload structure.
    @param [in/out]  rpu_data
    pointer to the RPU data structure
    @return
        @li >=0     Size of read payload in bits..
        @li < 0     Failure.
*/
int rpu_payload_read(rpu_decoder_ctx_t *rdc);

/*!
    @brief
    Reads dm metadata from the RPU RBSP.
    @param [in/out]  rpu_data
    pointer to the RPU data structure
    @return
        @li >=0     Size of read dm metadata in bits.
        @li < 0     Failure.
*/
int dm_data_payload_read(rpu_decoder_ctx_t *rdc);


int EBSPtoRBSP(unsigned char* streamBuffer, int end_bytepos, int begin_bytepos);



void bitstream_init( bit_stream_t* p_bitstrm, unsigned char* pui8_buf, int ui_buffer_size );

uint32_t read_ue_v (bit_stream_t *bitstream);

int32_t read_se_v (bit_stream_t *bitstream);

uint32_t read_u_v (int LenInBits, bit_stream_t *bitstream);

int32_t read_i_v (int LenInBits, bit_stream_t *bitstream);

uint8_t read_u_1 (bit_stream_t *bitstream);


#ifdef __cplusplus
}
#endif

#endif /* _RPU_PARSER_H_ */
