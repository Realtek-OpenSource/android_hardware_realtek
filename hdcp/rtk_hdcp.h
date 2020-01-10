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

#ifndef ANDROID_HDCP_INTERFACE_H
#define ANDROID_HDCP_INTERFACE_H

#include <hardware/hardware.h>

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#define HDCP_HARDWARE_DEVICE "/dev/hdcp"

/**
 * The id of this module
 */
#define HDCP_HARDWARE_MODULE_ID "hdcp"
#define HDCP_HARDWARE_HDCP0		"hdcp0"

/* HDCP state */
//#define HDCP_STATE_DISABLED             0
//#define HDCP_STATE_INIT                 1
//#define HDCP_STATE_AUTH_1ST_STEP        2
//#define HDCP_STATE_AUTH_2ND_STEP        3
//#define HDCP_STATE_AUTH_3RD_STEP        4
//#define HDCP_STATE_AUTH_FAIL_RESTARTING 5
//#define HDCP_STATE_AUTH_FAILURE         6

/* HDCP key size in 32-bit words */
#define DESHDCP_KEY_SIZE 160
#define HDCP_PK_SIZE 280
#define HDCP_Aksv_SIZE 5
#define KSVLIST_SIZE   640

/* HDCP ioctl */
enum {
    HDCP_ENABLE,
    HDCP_DISABLE,	
    HDCP_QUERY_STATUS,
	HDCP_QUERY_SINK_HDCP_CAPABLE,
	HDCP_GET_DOWNSTREAM_KSVLIST,
	HDCP_SET_22_CIPHER,
	HDCP_CONTROL_22_CIPHER,
};


enum {
	HDCP_22_CIPHER_DEFAULT,
    HDCP_22_CIPHER_PAUSE,
    HDCP_22_CIPHER_RESUME,	
};


struct hdcp_enable_control {
       // unsigned char key[DESHDCP_KEY_SIZE];
		unsigned char PK[HDCP_PK_SIZE];
		unsigned char Aksv[HDCP_Aksv_SIZE];
        int nb_retry;
};

struct hdcp_ksvlist_info {
        unsigned char Aksv[HDCP_Aksv_SIZE];
        unsigned char ksvlist[KSVLIST_SIZE];
		unsigned char bstatus[2];
		unsigned int device_count;
        unsigned char Bksv[HDCP_Aksv_SIZE];
};

/**
 * riv           : hw_riv_1_(1-2)
 * ks_xor_lc128  : sw_key_1_(1-4)
 * frame_num     : frame_num_(1-2)
 * frame_num_add : frame_num_add_(1-2)
 * data_num      : data_num
 * data_num_add  : data_num_add
 * hdcp_22_en    : hdcp_22_ctrl:hdcp_22_en
 * aes_sw_en     : hdcp_22_ctrl:aes_sw_en
 */

typedef struct{
    unsigned long long frame_num;
    unsigned long long frame_num_add;
    unsigned int data_num;
    unsigned int data_num_add;
	unsigned int rsvd_1;
    unsigned int rsvd_2;
	unsigned int rsvd_3;	
    unsigned char riv[8];
    unsigned char ks_xor_lc128[16];
    unsigned char hdcp_22_en;
    unsigned char aes_sw_en;
	unsigned char rsvd_4;
    unsigned char rsvd_5;
}HDCP_22_CIPHER_INFO;

/**
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 * followed by module specific information.
 */
struct hdcp_module_t {
    struct hw_module_t common;
};



/**
 * Every device data structure must begin with hw_device_t
 * followed by module specific public methods and attributes.
 */
struct hdcp_device_t {
    struct hw_device_t common;

    int (*enable_module)(struct hdcp_device_t *dev, struct hdcp_enable_control *argp);
    int (*disable_module)(struct hdcp_device_t *dev);
	int (*query_status)(struct hdcp_device_t *dev, int *argp);
    int (*query_sink)(struct hdcp_device_t *dev, int *capable); 
	int (*get_ksvlist)(struct hdcp_device_t *dev, struct hdcp_ksvlist_info *info); 
	int (*set_2_2_cipher)(struct hdcp_device_t *dev, HDCP_22_CIPHER_INFO *info);
	int (*control_2_2_cipher)(struct hdcp_device_t *dev, int flag);	
		
};


/** convenience API for opening and closing a device */

static inline int hdcp_dev_open(const struct hw_module_t* module,struct hdcp_device_t** device) 
{
    
	return module->methods->open(module,HDCP_HARDWARE_HDCP0, (struct hw_device_t**)device);
}

static inline int hdcp_dev_close(struct hdcp_device_t* device) 
{
    return device->common.close(&device->common);
}


//__END_DECLS

#endif  // ANDROID_HDCP_INTERFACE_H

