/**
 * Command definition header file
 *
 * INTEL CONFIDENTIAL
 * Copyright 2010-2011 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to
 * the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors.  Title to the Material remains with Intel
 * Corporation or its suppliers and licensors.  The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors.  The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material may
 * be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or
 * delivery of the Materials,  either expressly, by implication, inducement,
 * estoppel or otherwise.  Any license under such intellectual property
 * rights must be express and approved by Intel in writing.
 */

#ifndef __COMMAND_H_
#define __COMMAND_H_

#define COMMAND_VERSION (5)

#define COMMAND_SIZE (sizeof(Command_t))

/*
 * Commands
 *
 */

typedef enum {
	CID_STATUS = 1,
	CID_KILL,

	CID_INIT,		/* Initialize the xtask */
	CID_MESSAGE_SEND,	/* Pass a message from the RX to the XTASK */
	CID_MESSAGE_POLL,	/* Poll XTASK for a pending message */
	CID_STATE_GET,		/* Receive the HDCP2 state of the Xtask */
	CID_SEND_KSVS,
	CID_AUTH_EVENT,
	CID_UNAUTH_EVENT,
	CID_CHECK_HDCP1X,

	CID_AES_DECRYPT,

	CID_END
} CID_t;

/*
 * Direction to send/receive commands
 */
typedef enum {
	DIRECTION_CPU_TO_SPU = 0,
	DIRECTION_SPU_TO_CPU
} Direction_t;

/*
 * Definitaion of a command
 */
typedef struct {
	H2uint32 cid;		/* Command ID */
	H2uint32 ver;		/* Command Set Version */

	union {
		/* STATUS */
		struct {
			H2status result;
			H2uint32 data;
		} status;

		/* CID_GET / CID_SET */
		struct {
			H2uint8 *ga;
			H2uint32 size;
		} address;

		/* CID_AES_DECRYPT */
		struct {
			H2uint64 input_counter;
			H2uint8 *src;
			H2uint32 size;
			H2uint8 *dst;
		} buf;

	} data;

} Command_t;

/**
 * HDCP2 message sizes, used to verify that a full message has been received
 */
#define AKE_INIT_MSG_SIZE (64/8 + 1)
#define AKE_NO_STORED_EKM_SIZE (1024/8 + 1)
#define AKE_STORED_EKM_SIZE (128/8+128/8 + 1)
#define LC_INIT_SIZE (64/8 + 1)
#define SKE_SEND_EKS_SIZE (128/8 + 64/8 + 1)
#define AKE_SEND_CERT_SIZE (4176/8 + 2)
#define AKE_SEND_RRX_SIZE (64/8 + 1)
#define AKE_SEND_H_PRIME_SIZE (256/8 + 1)
#define AKE_SEND_PAIRING_INFO_SIZE (128/8 + 1)
#define AKE_SEND_L_PRIME_SIZE (256/8 + 1)

/**
 * SPU command status codes
 */

#define STATUS_OK 0
#define STATUS_ERROR_OUTGOING_MSG_TOO_LARGE -2
#define STATUS_OK 0
#define STATUS_OK_PENDING_MSG 1

/*
 * Prototypes for functions
 *
 * These are only for the HOST CPU!!!!
 *
 */
H2status command_init(void);
void command_close(void);
H2status command_send(Direction_t direction, Command_t *pCmdTx);
H2status command_receive(Direction_t direction, Command_t *pCmdRx,
			 int timeoutInMs);

#endif
