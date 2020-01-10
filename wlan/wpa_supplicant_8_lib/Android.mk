LOCAL_PATH := $(call my-dir)

ifeq ($(WPA_SUPPLICANT_VERSION),VER_0_8_X)

################################################################################
include $(CLEAR_VARS)

LOCAL_PREBUILT_LIBS := lib_driver_cmd_rtl.a
LOCAL_MODULE_TAGS:= optional

include $(BUILD_MULTI_PREBUILT)

endif
