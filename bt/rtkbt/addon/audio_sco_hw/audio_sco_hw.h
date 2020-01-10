/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
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

/*****************************************************************************
 *
 *  Filename:      audio_sco_hw.h
 *
 *  Description:
 *
 *****************************************************************************/
#ifndef AUDIO_SCO_HW_H
#define AUDIO_SCO_HW_H

/*****************************************************************************
**  Constants & Macros
******************************************************************************/
#define SCO_AUDIO_HARDWARE_INTERFACE "audio.sco"
//#define SCO_OUT_PATH "/data/misc/bluedroid/.sco_out"
//#define SCO_IN_PATH "/data/misc/bluedroid/.sco_in"
#define SCO_DATA_PATH "/data/misc/bluedroid/.sco_data"
#define SCO_CTRL_PATH "/data/misc/bluedroid/.sco_ctrl"

#define SCO_STREAM_DEFAULT_RATE          8000
#define SCO_STREAM_DEFAULT_FORMAT        AUDIO_FORMAT_PCM_16_BIT
#define SCO_STREAM_DEFAULT_CHANNEL_FLAG  AUDIO_CHANNEL_OUT_MONO
#define SCO_STREAM_OUTPUT_BUFFER_SZ      (240)
#define SCO_SKT_DISCONNECTED             (-1)


#define SCO_SAMPLE_RATE_8K              (8000)
#define SCO_SAMPLE_RATE_16K             (16000)

#define SCO_CTRL_GETSAMPLERATE  "GetSampleRate"

typedef enum {
    SCO_CTRL_CMD_NONE,
    SCO_CTRL_CMD_CHECK_READY,
    SCO_CTRL_CMD_OUT_START,
    SCO_CTRL_CMD_IN_START,
    SCO_CTRL_CMD_OUT_STOP,
    SCO_CTRL_CMD_IN_STOP,
    SCO_CTRL_CMD_SUSPEND,
    SCO_CTRL_GET_AUDIO_CONFIG,
    SCO_CTRL_CMD_OFFLOAD_START,
    SCO_CTRL_CMD_CLOSE,
} tSCO_CTRL_CMD;

#define SCO_OUT_BUFSIZE                 (960 * 2)
#define SCO_IN_BUFSIZE                  (960 * 2)

/*****************************************************************************
**  Type definitions for callback functions
******************************************************************************/

/*****************************************************************************
**  Type definitions and return values
******************************************************************************/

/*****************************************************************************
**  Extern variables and functions
******************************************************************************/

/*****************************************************************************
**  Functions
******************************************************************************/


/*****************************************************************************
**
** Function
**
** Description
**
** Returns
**
******************************************************************************/
#define AUDIO_NO_INTR(fn)  do {} while ((fn) == -1 && errno == EINTR)

#endif /* AUDIO_SCO_HW_H */

