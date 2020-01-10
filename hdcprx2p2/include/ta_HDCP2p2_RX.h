/*
 * Copyright (c) 2014, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TA_HELLO_WORLD_H
#define TA_HELLO_WORLD_H

#include "tee_client_api.h"

/* This UUID is generated with uuidgen
   the ITU-T UUID generator at http://www.itu.int/ITU-T/asn1/uuid.html */
#define TA_HELLO_WORLD_UUID { 0x8aaaf200, 0x2450, 0x11e4, \
		{ 0xab, 0xe2, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b} }

/* The TAFs ID implemented in this TA */
//command

#define LC_128      0x0
#define CERT_RX    0x1
#define KPRIVRX     0x2
#define RRX             0x3


#define Rrx_SIZE (8)

#define TA_HELLO_WORLD_CMD_INC_VALUE 0xff
#define TA_HDCP2p2_SETLC128                    0x01
#define TA_HDCP2p2_CERT_RX                    0x02
#define TA_HDCP2p2_SETKPRIVRX                    0x03
#define TA_HDCP2p2_GetCertRx                 0x04
#define TA_HDCP2p2_GETKPRIVRX                    0x05
#define TA_HDCP2p2_GenRrx                      0x06
#define TA_HDCP2p2_GetRrx                      0x07
#define TA_processAkeInit_Command                      0x08
#define TA_processAkeNoStoredEkm_Command                      0x09
#define TA_processAkeStoredEkm_Command                      0xa
#define TA_hdcp2_Rx_GetEKhKm_Command                      0xb
#define TA_processLcInit_Command                      0xc
#define TA_processSkeSendEks_Command                      0xd
enum WIDEVINE_CMD_FOR_TA
{
	TA_TEE_OpenKeybox 			= 0x1,
	TA_TEE_IsKeyboxValid 		= 0x2,
	TA_TEE_GetKeyData			= 0x3,
	TA_TEE_GetDeviceID 			= 0x4,
	TA_TEE_RandomData 			= 0x5,
	TA_TEE_SetIVBuffer			= 0x6,
	TA_TEE_SetEntitlementKey 	= 0x7,
	TA_TEE_DeriveControlWord 	= 0x8,
	TA_TEE_DecryptAVContent 	= 0x9
};

#define AES_BLOCK_SIZE 16


TEEC_Result hdcprx22_init_ta(void);
TEEC_Result hdcprx22_deint_ta(void);
int CA_hdcp2_load_from_TEE(void);


#endif /*TA_HELLO_WORLD_H*/
