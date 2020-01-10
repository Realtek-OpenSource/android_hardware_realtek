LOCAL_PATH:= $(call my-dir)

########################################################
include $(CLEAR_VARS)
# LOCAL_PREBUILT_LIBS := wifi_auto_insmod.a
LOCAL_MODULE_TAGS:= optional eng
LOCAL_VENDOR_MODULE := true
LOCAL_MODULE := wifi_auto_insmod
LOCAL_MODULE_SUFFIX := .a
LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_SRC_FILES := wifi_auto_insmod.a
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)
include $(BUILD_PREBUILT)
########################################################
#######################################################
include $(CLEAR_VARS)
LOCAL_SRC_FILES := wifi_module_mapper.json
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := wifi_module_mapper.json
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR)/etc/wifi
#LOCAL_PROPRIETARY_MODULE := true
LOCAL_VENDOR_MODULE := true

include $(BUILD_PREBUILT)

