#ifndef CONFIG_H
#define CONFIG_H

typedef struct tVoice_Hidraw_Settings
{
    struct tVoice_Hidraw_Settings * next;
    char * group;
    char * item;
    char * val;
} tVoice_Hidraw_Settings;

int voice_loadconfig(const char * path);
int voice_get_int_config(const char *group, const char *item);
int voice_get_byte_array_config(const char *group, const char *item, char* arr, int len);
int voice_conf_exit();


#define CONFIG_GROUP_RCU  "Rcu"
#define CONFIG_ITEM_RCU_VID  "Vid"
#define CONFIG_ITEM_RCU_PID  "Pid"
#define CONFIG_ITEM_RCU_VER  "Ver"

#define CONFIG_GROUP_REPORTID  "ReportID"
#define CONFIG_ITEM_REPORTID_KEY  "Key"
#define CONFIG_ITEM_REPORTID_DATA  "Data"
#define CONFIG_ITEM_REPORTID_CMD  "Cmd"

#define CONFIG_GROUP_REPORTVALUE  "ReportValue"
#define CONFIG_ITEM_REPORTVALUE_KEYDOWNLEN  "KeyDownLen"
#define CONFIG_ITEM_REPORTVALUE_KEYDOWN  "KeyDown"
#define CONFIG_ITEM_REPORTVALUE_KEYUPLEN  "KeyUpLen"
#define CONFIG_ITEM_REPORTVALUE_KEYUP  "KeyUp"

#define CONFIG_GROUP_SETTINGS  "Settings"
#define CONFIG_ITEM_SETTINGS_DECODETYPE "DecodeType"
#define CONFIG_ITEM_SETTINGS_DATAMASK "DataMask"
#define CONFIG_ITEM_SETTINGS_AUTOCMD "AutoCmd"


#endif
