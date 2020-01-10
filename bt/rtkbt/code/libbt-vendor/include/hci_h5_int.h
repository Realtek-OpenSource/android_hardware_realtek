/******************************************************************************
 *
 *  Copyright (C) 2009-2018 Realtek Corporation.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/


#ifndef RTK_HCI_H5_INT_H
#define RTK_HCI_H5_INT_H

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "bt_hci_bdroid.h"
#include "bt_vendor_lib.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "rtk_hcidefs.h"
#include "rtk_common.h"

//HCI Command opcodes
#define HCI_LE_READ_BUFFER_SIZE     0x2002
#define DATA_TYPE_H5                0x05

//HCI VENDOR Command opcode
#define HCI_VSC_H5_INIT                 0xFCEE
#define HCI_VSC_UPDATE_BAUDRATE         0xFC17
#define HCI_VSC_DOWNLOAD_FW_PATCH       0xFC20
#define HCI_VSC_READ_ROM_VERSION        0xFC6D
#define HCI_VSC_READ_CHIP_TYPE          0xFC61
#define HCI_VSC_SET_WAKE_UP_DEVICE      0xFC7B
#define HCI_VSC_BT_OFF                  0xFC28
#define HCI_READ_LMP_VERSION            0x1001
#define HCI_VENDOR_RESET                0x0C03
#define HCI_VENDOR_FORCE_RESET_AND_PATCHABLE 0xFC66

void ms_delay (uint32_t timeout);


typedef enum {
  DATA_TYPE_COMMAND = 1,
  DATA_TYPE_ACL     = 2,
  DATA_TYPE_SCO     = 3,
  DATA_TYPE_EVENT   = 4
} serial_data_type_t;


typedef struct hci_h5_callbacks_t{
    uint16_t    (*h5_int_transmit_data_cb)(serial_data_type_t type, uint8_t *data, uint16_t length);
    void        (*h5_data_ready_cb)(serial_data_type_t type, unsigned int total_length);
} hci_h5_callbacks_t;

typedef struct hci_h5_t {
     void     (*h5_int_init)(hci_h5_callbacks_t *h5_callbacks);
     void     (*h5_int_cleanup)(void);
     uint16_t (*h5_send_cmd)(serial_data_type_t type, uint8_t *data, uint16_t length);
     uint8_t  (*h5_send_sync_cmd)(uint16_t opcode, uint8_t *data, uint16_t length);
     uint16_t (*h5_send_acl_data)(serial_data_type_t type, uint8_t *data, uint16_t length);
     uint16_t (*h5_send_sco_data)(serial_data_type_t type, uint8_t *data, uint16_t length);
     bool     (*h5_recv_msg)(uint8_t *byte, uint16_t length);
     size_t   (*h5_int_read_data)(uint8_t *data_buffer, size_t max_size);
} hci_h5_t;

const hci_h5_t *hci_get_h5_int_interface(void);

#endif
