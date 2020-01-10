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

#ifndef ANDROID_HDMI_INTERFACE_H
#define ANDROID_HDMI_INTERFACE_H

#include <hardware/hardware.h>

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include "hdmi_common.h"

#define HDMI_HARDWARE_DEVICE "/dev/hdmitx"

/**
 * The id of this module
 */
#define HDMI_HARDWARE_MODULE_ID "hdmi"
#define HDMI_HARDWARE_HDMI0		"hdmi0"




/**
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 * followed by module specific information.
 */
struct hdmi_module_t {
    struct hw_module_t common;
};



/**
 * Every device data structure must begin with hw_device_t
 * followed by module specific public methods and attributes.
 */
struct hdmi_device_t {
    struct hw_device_t common;
    struct sink_capabilities_t sink_cap;
	struct raw_edid edid;

    int (*get_capability)(struct hdmi_device_t *dev);
    int (*is_connected)(struct hdmi_device_t *dev);
	int (*get_edid)(struct hdmi_device_t *dev);
	int (*send_avmute)(struct hdmi_device_t *dev, int select); 
	int (*check_tmds_src)(struct hdmi_device_t *dev, int *tmds); 
	int (*check_rx_sense)(struct hdmi_device_t *dev, int *rx_sense);
	
	//video RPC-related
	int (*config_tv_system)(struct hdmi_device_t *dev, struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM argp);
	int (*config_avi_info)(struct hdmi_device_t *dev, struct VIDEO_RPC_VOUT_CONFIG_HDMI_INFO_FRAME argp);
	int (*send_vout_edid_data)(struct hdmi_device_t *dev, struct VIDEO_RPC_VOUT_EDID_DATA argp);

	//audio RPC-related
	int (*set_frequency)(struct hdmi_device_t *dev, struct AUDIO_HDMI_SET argp);
	int (*send_audio_mute)(struct hdmi_device_t *dev, struct AUDIO_HDMI_MUTE_INFO argp);
	int (*send_audio_VSDB_data)(struct hdmi_device_t *dev, struct AUDIO_HDMI_OUT_VSDB_DATA argp);
    int (*send_audio_edid2)(struct hdmi_device_t *dev, struct AUDIO_HDMI_OUT_EDID_DATA2 argp);

    // new api added from kernel 4.9
    int (*get_edid_support_list)(struct hdmi_device_t *dev, struct hdmi_support_list *argp);
    int (*set_output_format)(struct hdmi_device_t *dev, struct hdmi_format_setting argp);
    int (*get_output_format)(struct hdmi_device_t *dev, struct hdmi_format_setting *argp);
    int (*set_interface_type)(struct hdmi_device_t *dev, int type);
    // to access some information of DP, get RAW config of fw from driver
    int (*get_tv_system_config)(struct hdmi_device_t *dev,
            struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *argp);
};


/** convenience API for opening and closing a device */

static inline int hdmi_dev_open(const struct hw_module_t* module, 
        struct hdmi_device_t** device) {
    return module->methods->open(module, 
            HDMI_HARDWARE_HDMI0, (struct hw_device_t**)device);
}

static inline int hdmi_dev_close(struct hdmi_device_t* device) {
    return device->common.close(&device->common);
}


//__END_DECLS

#endif  // ANDROID_HDMI_INTERFACE_H

