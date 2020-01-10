#ifndef VOICE_HIDRAW_H
#define VOICE_HIDRAW_H

#include <log/log.h>


#define DECODE_TYPE_MSBC 1
#define DECODE_TYPE_SBC 2
#define DECODE_TYPE_MAX 2

#define DATA_TYPE_MASK_VOICE (0x01)
#define DATA_TYPE_MASK_RAW (0x02)

#define AUTOCMD_AUTO 1
#define AUTOCMD_NONE 2
#define AUTOCMD_SOCKET 3

#define SW_VERSION (0x0000)

#define CONFIG_PATH "/system/etc/hidraw_setting"
#define CONFIG_VENDOR_PATH "/vendor/etc/hidraw_setting"

#define warn(fmt, ...) ALOGW ("## WARNING : %s(L%d):  " fmt "##",__FUNCTION__, __LINE__, ## __VA_ARGS__)
#define error(fmt, ...) ALOGE ("## ERROR : %s(L%d): " fmt "##",__FUNCTION__, __LINE__, ## __VA_ARGS__)

#define info(fmt, ...)  ALOGI ("%s(L%d): " fmt,__FUNCTION__, __LINE__,  ## __VA_ARGS__)
#define debug(fmt, ...) ALOGD ("%s(L%d): " fmt,__FUNCTION__, __LINE__,  ## __VA_ARGS__)


#define VOICE_DATA_PATH     "/data/misc/bluedroid/.voice_data"
#define VOICE_CTRL_PATH     "/data/misc/bluedroid/.voice_ctrl"



//supported opcode

#define OPCODE_SETTING_RESET                0   //cmd(1)
#define OPCODE_VOICE_START_CMD              1   //cmd(1)
#define OPCODE_VOICE_STOP_CMD               2   //cmd(1)
#define OPCODE_SET_RCU_INFO                 3   //cmd(1) + vid(2) + pid(2) + vers(2)
#define OPCODE_SET_VOICE_DATA_REPORT_ID     4   //cmd(1) + reportID(1)
#define OPCODE_SET_VOICE_CMD_REPORT_ID      5   //cmd(1) + reportID(1)
#define OPCODE_SET_VOICE_KEY_REPORT_ID      6   //cmd(1) + reportID(1)
#define OPCODE_SET_VOICE_KEYPRESS_DATA      7   //cmd(1) + len(1) + data(n)
#define OPCODE_SET_VOICE_KEYRELEASE_DATA    8   //cmd(1) + len(1) + data(n)
#define OPCODE_SET_VOICE_STARTCMD_DATA      9   //cmd(1) + len(1) + data(n)
#define OPCODE_SET_VOICE_STOPCMD_DATA       10  //cmd(1) + len(1) + data(n)
#define OPCODE_SET_ENCODE_TYPE              11  //cmd(1) + type(1)
#define OPCODE_SET_DATA_TYPE_MASK           12  //cmd(1) + type(1)
#define OPCODE_SET_AUTO_CMD                 13  //cmd(1) + auto(1)
#define OPCODESEND_HIDRAW_DATA              14  //cmd(1) + reportID(1) + len(1) + data(n)
#define OPCODE_EXIT                         15  //cmd(1)

#define OPCODE_MAX                          15

#endif
