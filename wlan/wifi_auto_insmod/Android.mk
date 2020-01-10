LOCAL_PATH:= $(call my-dir)

########################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := wifi_auto_insmod
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_REQUIRED_MODULES := wifi_module_mapper.json
LOCAL_MODULE := wifi_auto_insmod
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
#######################################################
include $(CLEAR_VARS)
LOCAL_SRC_FILES := wifi_module_mapper.json
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := wifi_module_mapper.json
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR)/etc/wifi
#LOCAL_SRC_FILES := $(LOCAL_MODULE)
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
