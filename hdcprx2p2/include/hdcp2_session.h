#ifndef HDCP2_SESSION_H
#define HDCP2_SESSION_H
#ifdef TEST_HDCP2_2_TX_DRIVER
#include <hdcp2_messages.h>

#define REPEATER_MASK 0x01
int hdcp2TxMessageSend(HDCPMsgId_t msg_type, unsigned char *message,
			unsigned int length);

#endif	/*  */

typedef enum {
	H2_STATE_INIT, /* H2 Initialized */
	H2_STATE_B0_UNAUTHENTICATED,
	H2_STATE_B1_AKE_INIT, /* AKE Init received from TX */
	H2_STATE_B2_LC_INIT, /* LC_INIT received from transmitter */
	H2_STATE_B3_SKE_SEND_EKS, /* Ske_Send_Eks message received */
	H2_STATE_B4_AUTHENTICATED, /* Authentication completed */
} h2State;

/**
 * Initialize M3 and supporting libraries.
 */
void h2Init(void);

/**
 * Process an incoming message
 */
int h2MessageParse(unsigned char *message, unsigned int length);

/**
 * Get State
 */
h2State h2StateGet(void);

/**
 * Poll for outgoing message
 */
int h2MessagePoll(unsigned char *message, unsigned int length);
int h2PairingStarted(void);

/** Set the attached KSV list
 */
int h2KsvsSet(unsigned char *pKsvs, unsigned int len);

#endif
