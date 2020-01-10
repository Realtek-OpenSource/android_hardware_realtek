LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := rtw_fwloader.c 
LOCAL_MODULE := rtw_fwloader
LOCAL_INIT_RC := rtw_fwloader.rc
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/bin/$(LOCAL_MODULE) device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/bin; \
                          cp -f $(LOCAL_PATH)/$(LOCAL_INIT_RC) device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/bin
include $(BUILD_EXECUTABLE)

