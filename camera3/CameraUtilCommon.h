#ifndef _CAMERA_UTIL_COMMON_H_
#define _CAMERA_UTIL_COMMON_H_

#define HDMIRX_STATE        "/sys/devices/virtual/switch/rx_video/state"
#define HDMITX_STATE        "/sys/devices/virtual/switch/hdmi/state"

#define HDCP_STATE_PATH     "/sys/devices/platform/98037000.hdmirx/hdcp_status"
#define HDCP_1X_PATH        "/sys/devices/platform/98037000.hdmirx/hdcp1x_en"
#define HDCP_22_PATH        "/sys/devices/platform/98037000.hdmirx/hdcp2p2_en"

#define HDMIRX_SWITCH       "devices/virtual/switch/rx_video"

static inline bool _readLine(
        const char *path,
        char *line,
        ssize_t len)
{
    FILE *fd = fopen(path, "r");

    if(fd != NULL) {
        memset(line,0x0,len);
        fread(line,1,len,fd);
        fclose(fd);
        return true;
    }else{
        return false;
    }
}

static inline int32_t _readState(const char *path)
{
    char line[128];
    memset(line,0x0,128);
    if(_readLine(path,line,128)) {
        return atoi(line);
    } else {
        return 0;
    }
}

static inline bool _isUsbCamConnected(int32_t id)
{
    char path[128];
    memset(&(path[0]),0,128);
    sprintf(path,"/dev/video%d",id);
    if(access(path,R_OK) != 0) {
        return false;
    } else {
        return true;
    }
}


#endif
