################################################

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := rtkcmd
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAGS := optional eng
LOCAL_MODULE := rtkcmd
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

