#ifndef __RTK_HAL_H__
#define __RTK_HAL_H__

#include "hdmi_common.h"

#define HDMI_IOCTL_MAGIC 0xf1
#define HDMI_CHECK_LINK_STATUS			_IOR(HDMI_IOCTL_MAGIC,2, int)
#define HDMI_CHECK_Rx_Sense				_IOR(HDMI_IOCTL_MAGIC,11, int)
#define HDMI_SEND_VOUT_EDID_DATA			_IOWR(HDMI_IOCTL_MAGIC,15, struct VIDEO_RPC_VOUT_EDID_DATA)
// new added API from kernel 4.9
#define HDMI_GET_EDID_SUPPORT_LIST		_IOWR(HDMI_IOCTL_MAGIC, 16, struct hdmi_support_list)
#define HDMI_SET_OUTPUT_FORMAT			_IOWR(HDMI_IOCTL_MAGIC, 17, struct hdmi_format_setting)
#define HDMI_GET_OUTPUT_FORMAT          _IOWR(HDMI_IOCTL_MAGIC, 18, struct hdmi_format_setting)
#define HDMI_SET_VO_INTERFACE_TYPE      _IOW(HDMI_IOCTL_MAGIC, 19, int)
#define HDMI_GET_CONFIG_TV_SYSTEM		_IOR(HDMI_IOCTL_MAGIC, 20, struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM)

/* HDMI ioctl */
enum {
    HDMI_GET_SINK_CAPABILITY,
    HDMI_GET_RAW_EDID,
    HDMI_GET_LINK_STATUS,
    HDMI_GET_VIDEO_CONFIG,
    HDMI_SEND_AVMUTE,
    HDMI_CONFIG_TV_SYSTEM,
    HDMI_CONFIG_AVI_INFO,
    HDMI_SET_FREQUNCY,
    HDMI_SEND_AUDIO_MUTE,
    HDMI_SEND_AUDIO_VSDB_DATA,
    HDMI_SEND_AUDIO_EDID2,
	HDMI_CHECK_TMDS_SRC,
};

enum HDMI_AVMUTE{
	HDMI_CLRAVM =0,
	HDMI_SETAVM 
};

//synchronize with linux hdmitx driver.
//Reference of sink_capabilities_t.hdmi_mode
enum HDMI_MODE {
	HDMI_MODE_UNDEF= 0,
	HDMI_MODE_HDMI= 1,
	HDMI_MODE_DVI= 2,
    HDMI_MODE_MHL= 3, 
	HDMI_MODE_MAX
};



#endif
