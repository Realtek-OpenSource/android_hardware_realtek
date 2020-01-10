#ifndef VOICE_UIPC_H
#define VOICE_UIPC_H

#define UIPC_CH_ID_VOICE_CTRL   0
#define UIPC_CH_ID_VOICE_DATA   1
#define UIPC_CH_NUM             2
#define UIPC_CH_ID_ALL          3   /* used to address all the ch id at once */


#define DEFAULT_READ_POLL_TMO_MS 100

typedef unsigned char tUIPC_CH_ID;

/* Events generated */
typedef enum {
    UIPC_OPEN_EVT           = 0x0001,
    UIPC_CLOSE_EVT          = 0x0002,
    UIPC_RX_DATA_EVT        = 0x0004,
    UIPC_RX_DATA_READY_EVT  = 0x0008,
    UIPC_TX_DATA_READY_EVT  = 0x0010
} tUIPC_EVENT;

/*
 * UIPC IOCTL Requests
 */

#define UIPC_REQ_RX_FLUSH               1
#define UIPC_REG_CBACK                  2
#define UIPC_REG_REMOVE_ACTIVE_READSET  3
#define UIPC_SET_READ_POLL_TMO          4

#define UIPC_SET_SNDBUFSIZE  5


typedef void (tUIPC_RCV_CBACK)(tUIPC_CH_ID ch_id, tUIPC_EVENT event); /* points to BT_HDR which describes event type and length of data; len contains the number of bytes of entire message (sizeof(BT_HDR) + offset + size of data) */

const char* dump_uipc_event(tUIPC_EVENT event);

/*******************************************************************************
**
** Function         UIPC_Init
**
** Description      Initialize UIPC module
**
** Returns          void
**
*******************************************************************************/
void UIPC_Init(void *);

/*******************************************************************************
**
** Function         UIPC_Open
**
** Description      Open UIPC interface
**
** Returns          void
**
*******************************************************************************/
int UIPC_Open(tUIPC_CH_ID ch_id, tUIPC_RCV_CBACK *p_cback);

/*******************************************************************************
**
** Function         UIPC_Close
**
** Description      Close UIPC interface
**
** Returns          void
**
*******************************************************************************/
void UIPC_Close(tUIPC_CH_ID ch_id);

/*******************************************************************************
**
** Function         UIPC_Send
**
** Description      Called to transmit a message over UIPC.
**
** Returns          void
**
*******************************************************************************/
int UIPC_Send(tUIPC_CH_ID ch_id, unsigned short msg_evt, unsigned char *p_buf, unsigned short msglen);
int UIPC_Send_noblock(tUIPC_CH_ID ch_id, unsigned short msg_evt, unsigned char *p_buf, unsigned short msglen);

/*******************************************************************************
**
** Function         UIPC_Read
**
** Description      Called to read a message from UIPC.
**
** Returns          void
**
*******************************************************************************/
int UIPC_Read(tUIPC_CH_ID ch_id, unsigned short *p_msg_evt, unsigned char *p_buf, unsigned int len);
extern int UIPC_Read_noblock(tUIPC_CH_ID ch_id, unsigned short *p_msg_evt, unsigned char *p_buf, unsigned int len);


/*******************************************************************************
**
** Function         UIPC_Ioctl
**
** Description      Called to control UIPC.
**
** Returns          void
**
*******************************************************************************/
int UIPC_Ioctl(tUIPC_CH_ID ch_id, unsigned int request, void *param);

#endif  /* UIPC_H */
