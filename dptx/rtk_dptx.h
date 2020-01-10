/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_DPTX_INTERFACE_H
#define ANDROID_DPTX_INTERFACE_H

#include <hardware/hardware.h>

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include "hdmi_common.h"

#define DPTX_HARDWARE_DEVICE "/dev/dptx"

/**
 * The id of this module
 */
#define DPTX_HARDWARE_MODULE_ID "dptx"
#define DPTX_HARDWARE_HDMI0		"dptx0"

/* DPTX ioctl */
enum {
    DPTX_GET_SINK_CAPABILITY,
    DPTX_GET_RAW_EDID,
    DPTX_GET_LINK_STATUS,
    DPTX_GET_VIDEO_CONFIG,
    DPTX_SEND_AVMUTE,
    DPTX_CONFIG_TV_SYSTEM,
    DPTX_CONFIG_AVI_INFO,
    DPTX_SET_FREQUNCY,
    DPTX_SEND_AUDIO_MUTE,
    DPTX_SEND_AUDIO_VSDB_DATA,
    DPTX_SEND_AUDIO_EDID2,
	DPTX_CHECK_TMDS_SRC,
    // new added ioctl from kernel 4.9
    DPTX_GET_EDID_SUPPORT_LIST,
    DPTX_GET_OUTPUT_FORMAT,
    DPTX_SET_OUTPUT_FORMAT,
};

#if 0
(> 29 enum {
   30     DPTX_GET_SINK_CAPABILITY,
   31     DPTX_GET_RAW_EDID,
   32     DPTX_GET_LINK_STATUS,
   33     DPTX_GET_VIDEO_CONFIG,
   34     DPTX_SEND_AVMUTE,
   35     DPTX_CONFIG_TV_SYSTEM,
   36     DPTX_CONFIG_AVI_INFO,
   37     DPTX_SET_FREQUNCY,
   38     DPTX_SEND_AUDIO_MUTE,
   39     DPTX_SEND_AUDIO_VSDB_DATA,
   40     DPTX_SEND_AUDIO_EDID2,
5> 41     DPTX_CHECK_TMDS_SRC,
2> 42     // new added ioctl from kernel 4.9
   43     DPTX_GET_EDID_SUPPORT_LIST,
   44     DPTX_GET_OUTPUT_FORMAT,
   45     DPTX_SET_OUTPUT_FORMAT,
   46 };
#endif



struct dptx_sink_capabilities_t {

	unsigned int hdmi_mode;
	//basic
	unsigned int est_modes;

	//audio
	//unsigned int max_channel_cap;
	//unsigned int sampling_rate_cap;
	unsigned char eld[MAX_ELD_BYTES];
	struct Audio_Data audio_data;

	//Vendor-Specific Data Block(VSDB)
	unsigned char cec_phy_addr[2];
	bool support_AI;  // needs info from ACP or ISRC packets
	bool DC_Y444;	// 4:4:4 in deep color modes
	unsigned char color_space;
	bool dvi_dual;	//DVI Dual Link Operation
	int max_tmds_clock;	/* in MHz */
	bool latency_present[2];
	unsigned char video_latency[2];	/* [0]: progressive, [1]: interlaced */
	unsigned char audio_latency[2];

	bool _3D_present;
	__u16 structure_all;
	unsigned char _3D_vic[16];

	//video
	struct drm_display_info display_info;
	__u64 vic;//VIC 1~64, BIT0=VIC1
	unsigned char extended_vic;
	__u64 vic2;//VIC 65~128, BIT0=VIC65
	__u64 vic2_420;//YCbCr420 format, VIC 65~128, BIT0=VIC65
//	struct VIDEO_RPC_VOUT_EDID_DATA vout_edid_data;
};


/**
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 * followed by module specific information.
 */
struct dptx_module_t {
    struct hw_module_t common;
};

/**
 * struct dptx_format_support
 * @vic: Video ID Code
 */
struct dptx_format_support {
    unsigned char vic;
    unsigned char reserved1;
    unsigned char reserved2;
    unsigned char reserved3;
};

struct dptx_support_list {
    struct dptx_format_support tx_support[25];
    unsigned int tx_support_size;
};

/**
 * struct dptx_format_setting - DPTX output format setting
 * @vic: Video ID code
 */
struct dptx_format_setting {
    unsigned char mode;
    unsigned char vic;
    unsigned char display_mode; // same source, different source..
    unsigned char reserved1;
};

/**
 * Every device data structure must begin with hw_device_t
 * followed by module specific public methods and attributes.
 */
struct dptx_device_t {

    struct hw_device_t common;
    struct dptx_sink_capabilities_t sink_cap;

    int (*get_capability)(struct dptx_device_t *dev);
	int (*config_tv_system)(struct dptx_device_t *dev,
            struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM argp);

    // new api added from kernel 4.9
    int (*get_edid_support_list)(struct dptx_device_t *dev,
            struct dptx_support_list *argp);
    int (*set_output_format)(struct dptx_device_t *dev,
            struct dptx_format_setting argp);
    int (*get_output_format)(struct dptx_device_t *dev,
            struct dptx_format_setting *argp);
};


/** convenience API for opening and closing a device */

static inline int dptx_dev_open(const struct hw_module_t* module, 
        struct dptx_device_t** device) {
    return module->methods->open(module, 
            DPTX_HARDWARE_HDMI0, (struct hw_device_t**)device);
}

static inline int dptx_dev_close(struct dptx_device_t* device) {
    return device->common.close(&device->common);
}


//__END_DECLS

#endif  // ANDROID_DPTX_INTERFACE_H

