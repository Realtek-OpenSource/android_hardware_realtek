LOCAL_PATH := $(call my-dir)

# Building the jpuapi
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
 	jpuapi.c \
	jpuapifunc.c \
	../src/jpuhelper.c \
	../src/jpulog.c

 LOCAL_SRC_FILES += \
	../jdi/linux/jdi.c \


LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libjpu

ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES :=       \
		libutils		\
		libcutils		\
		libdl  			\
		liblog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src		\
					$(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/JPEG	\
					$(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/JPEG/include

MJPG_CHECKSUM = false
MJPG_CHECKSUM_LOG_TO_TMP = false
ifeq ($(MJPG_CHECKSUM), true)
LOCAL_SHARED_LIBRARIES += libMCPControl
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libMCPControl/inc/
LOCAL_CFLAGS += -DMJPG_CHECKSUM
ifeq ($(MJPG_CHECKSUM_LOG_TO_TMP), true)
LOCAL_CFLAGS += -DMJPG_CHECKSUM_LOG_TO_TMP
endif
endif

include $(BUILD_SHARED_LIBRARY)

