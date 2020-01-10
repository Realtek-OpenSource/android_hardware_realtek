LOCAL_PATH := $(call my-dir)

################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libstagefrighthw.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libstagefrighthw
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
