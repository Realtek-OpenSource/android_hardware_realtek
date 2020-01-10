/*
 * rtk_hdcprx2p2.h - RTK hdcp2.2 rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 */

struct rx_hdcp22_msg {
	unsigned int bLen;
	unsigned char msg[864] ;
	unsigned char g_RX_state;
}__attribute__ ((packed));

struct rx_hdcp22_ks {
	unsigned char bks[16];
}__attribute__ ((packed));

#define HDCPRX22_DEV    "/dev/rxhdcp2p2"

#define HDCP22IOC_INIT				_IOWR('V', 0, int)
#define HDCP22IOC_GET_HDCP22_MSG	_IOWR('V', 1, struct rx_hdcp22_msg)
#define HDCP22IOC_WRITE_DATA_TO_TX	_IOWR('V', 2, struct rx_hdcp22_msg)
#define HDCP22IOC_GET_STREAM_MSG	_IOWR('V', 3, struct rx_hdcp22_msg)
#define HDCP22IOC_SET_KS			_IOWR('V', 4, struct rx_hdcp22_ks)
#define HDCP22IOC_CLR_MSG_DONE		_IOWR('V', 5, int)
#define HDCP22IOC_GET_MSG_DONE		_IOWR('V', 6, int)
#define HDCP22IOC_SET_STATUS_READY	_IOWR('V', 7, int)
#define HDCP22IOC_SET_DOWNSTREAM_DONE	_IOWR('V', 8, int)
#define HDCP22IOC_SET_SWITCH_STATE	_IOWR('V', 9, int)

#define DBG_LEVEL_1 1
#define DBG_LEVEL_2 2
#define DBG_LEVEL_3 3
//#define HDCP22_DBG_LEVEL	DBG_LEVEL_1
#ifdef HDCP22_DBG_LEVEL
void hdcp2p2rx_dump_buffer(unsigned char dbg_level,
	unsigned char *buf, unsigned int size, char *desc);
#else
#define hdcp2p2rx_dump_buffer(x, ...)
#endif
#define UNUSED(x) (void)x

void hdcp2p2rx_set_ks(unsigned char *bKs);
void hdcp2p2rx_clear_rd_msg_done(void);
int hdcp2p2rx_get_rd_msg_done(void);
void hdcp2p2rx_set_status_ready(void);
void hdcp2p2rx_downstream_done(void);
void hdcp2p2rx_write_msg(unsigned char* bSendData, unsigned int wLen);
