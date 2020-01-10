
LOCAL_PATH := $(call my-dir)

#Building jpurun binary which will be placed in the /system/bin folder
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	main.c \
	jpurun.c \
	mixer.c

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := jpurun

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/JPEG/include \
                    $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/JPEG/jpuapi



LOCAL_SHARED_LIBRARIES :=       \
        libjpu					\
        libutils

ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

include $(BUILD_EXECUTABLE)

