LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := RTK_OMX_Core.c

LOCAL_CFLAGS := $(PV_CFLAGS_MINUS_VISIBILITY)

LOCAL_PRELINK_MODULE := false

LOCAL_C_INCLUDES += frameworks/native/headers/media_plugin/media/openmax
LOCAL_C_INCLUDES += hardware/realtek/realtek_omx/include/rtkext

LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/OSAL/include
	
LOCAL_SHARED_LIBRARIES += libRTK_lib

LOCAL_SHARED_LIBRARIES += libdl
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libutils

LOCAL_MODULE := libOMX_Core

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

ifneq ($(filter 4.%,$(PLATFORM_VERSION)),)
LOCAL_CFLAGS += -DOMX_COMPONENTS_LEGACY_SUPPORT
endif

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include

ifneq ($(TARGET_2ND_ARCH),)
LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/lib64/$(LOCAL_MODULE).so device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/lib64
else
LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).so device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/lib
endif

include $(BUILD_SHARED_LIBRARY)
