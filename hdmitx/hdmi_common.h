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

#ifndef ANDROID_HDMI_COMMON_H
#define ANDROID_HDMI_COMMON_H

//#include <hardware/hardware.h>

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include "drm_crtc.h"
#include <AudioRPCBaseDS_data.h>


#define MAX_ELD_BYTES	128

struct Audio_desc
{
	unsigned char	coding_type;
	unsigned char	channel_count;
	unsigned char	sample_freq_all;
	unsigned char	sample_size_all;
	unsigned char	max_bit_rate_divided_by_8KHz;
}__attribute__((packed));

struct Audio_Data
{
	char ADB_length;	// Audio Data Block
	struct Audio_desc ADB[10];
	char SADB_length;	// Speaker Allocation Data Block
	unsigned char SADB[3];	
}__attribute__((packed));

struct Specific_3D
{
	unsigned char vic;
	unsigned char format;// 0:Frame packing, 6:Top-and-Bottom, 8:Side-by-Side(Half)
}__attribute__((packed));

struct Video_Display_Info {
 	/* Physical size */
	unsigned int width_mm;
	unsigned int height_mm;
	unsigned int pixel_clock;
	unsigned int bpc;
	__u32 color_formats;
	__u8 cea_rev;
}__attribute__ ((packed));

struct sink_capabilities_t {
	
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
	struct Specific_3D spec_3d[18];
		
	//video
	struct Video_Display_Info display_info;
	__u64 vic;
	unsigned char extended_vic;
	__u64 vic2;//VIC 65~128, BIT0=VIC65 
	__u64 vic2_420;//YCbCr420 format, VIC 65~128, BIT0=VIC65 
	struct VIDEO_RPC_VOUT_EDID_DATA vout_edid_data;

}__attribute__((packed));

struct raw_edid{
	unsigned char edid_data[256];
};

/* -------- Following struct is copied from kernel driver --------- */
// linux-kernel/drivers/media/platform/rtk_hdmitx/hdmitx.h

/**
 * struct hdmi_format_support - Color format and 3D support for specific VIC
 * @vic: Video ID Code
 * @rgb444: b'0-Support RGB444, b'1-RGB444/8bit, b'2-RGB444/10bit, b'3-RGB444/12bit
 * @yuv422: b'0-Support YUV422, b'1-YUV422/8bit, b'2-YUV422/10bit, b'3-YUV422/12bit
 * @yuv444: b'0-Support YUV444, b'1-YUV444/8bit, b'2-YUV444/10bit, b'3-YUV444/12bit
 * @yuv420: b'0-Support YUV420, b'1-YUV420/8bit, b'2-YUV420/10bit, b'3-YUV420/12bit
 * @support_3d: b'0-Support 3D, b'1-FramePacking, b'2-TopAndBottom, b'3-SideBySideHalf
 * @support_fs: b'0-Support Frequency-Shift, b'1-Support FS 3D
 */
struct hdmi_format_support {
	unsigned char vic;
	unsigned char rgb444;
	unsigned char yuv422;
	unsigned char yuv444;
	unsigned char yuv420;
	unsigned char support_3d;
	unsigned char support_fs;
	unsigned char reserved;
};

struct hdmi_support_list {
	struct hdmi_format_support tx_support[25];
	unsigned int tx_support_size;
};

/**
 * struct hdmi_format_setting - HDMI output format setting
 * @mode: 0-OFF; 1-DVI; 2-HDMI
 * @vic: Video ID code
 * @freq_shift:
 * @color: 0-RGB444; 1-YUV422; 2-YUV444; 3-YUV420
 * @color_depth: 8-8bit, 10-10bit, 12-12bit
 * @_3d_format:
 * @hdr: 0-No hdr; 1-Dolby Vision; 2-HDR10
 */
struct hdmi_format_setting {
	unsigned char mode;
	unsigned char vic;
	unsigned char freq_shift;
	unsigned char color;
	unsigned char color_depth;
	unsigned char _3d_format;
	unsigned char hdr;
	unsigned char reserved;
};

#endif  

