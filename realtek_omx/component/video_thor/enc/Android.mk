LOCAL_PATH := $(call my-dir)
RTK_TOP := hardware/realtek/realtek_omx
RTK_INC := $(RTK_TOP)/include
RTK_RPC := $(TOP)/device/realtek/proprietary/libs/rtk_libs/common

ENCODER_TYPE := VIDEO
# build video encoder
include $(CLEAR_VARS)

ifeq ($(ENCODER_TYPE), VIDEO)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	encoder.c


LOCAL_MODULE := libOMX.realtek.video.enc
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK

LOCAL_SHARED_LIBRARIES += libc
LOCAL_SHARED_LIBRARIES += libz
LOCAL_SHARED_LIBRARIES += libdl
#LOCAL_SHARED_LIBRARIES += libstdc++
LOCAL_SHARED_LIBRARIES += libm
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libhardware
LOCAL_SHARED_LIBRARIES += libRtkIpc
LOCAL_SHARED_LIBRARIES += libRTKAllocator

LOCAL_CFLAGS = -DOMX_ENCODER_VIDEO_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION

LOCAL_C_INCLUDES := \
	. \
	frameworks/native/include \
	frameworks/native/headers/media_plugin/media/openmax \
	$(RTK_INC)/imagination \
	$(RTK_INC)/rtkext \
	system/core/include/cutils \
	system/core/libion/include \
	$(RTK_RPC)/IPC/include \
	$(RTK_TOP)/osal_rtk \
	$(RTK_TOP)/core

LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include

#LOCAL_LDLIBS += -lpthread

#LOCAL_LDLIBS += -lpthread
#
# create symbolic links to each encoders
#
ENCODER_FORMATS += avc
ENCODER_FORMATS += mpeg4

ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
SYMLINKS := $(addsuffix .so,$(addprefix $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).,$(ENCODER_FORMATS)))
else
SYMLINKS := $(addsuffix .so,$(addprefix $(TARGET_OUT)/lib/$(LOCAL_MODULE).,$(ENCODER_FORMATS)))
endif

LOCAL_POST_INSTALL_CMD = \
	$(foreach t,$(SYMLINKS),ln -sf $(LOCAL_MODULE).so $(t);)

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
include $(BUILD_SHARED_LIBRARY)
endif # end of ENCODER_TYPE

ENCODER_TYPE = IMAGE
# build image encoder
include $(CLEAR_VARS)

ifeq ($(ENCODER_TYPE), IMAGE)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	encoder.c

LOCAL_MODULE := libOMX.realtek.image.enc
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK

LOCAL_SHARED_LIBRARIES += libc
LOCAL_SHARED_LIBRARIES += libz
LOCAL_SHARED_LIBRARIES += libdl
#LOCAL_SHARED_LIBRARIES += libstdc++
LOCAL_SHARED_LIBRARIES += libm
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libhardware
LOCAL_SHARED_LIBRARIES += libRTKAllocator

LOCAL_CFLAGS = -DOMX_ENCODER_IMAGE_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION

LOCAL_C_INCLUDES := \
	. \
	frameworks/native/include \
	frameworks/native/headers/media_plugin/media/openmax \
	$(RTK_INC)/imagination \
	$(RTK_INC)/rtkext \
	system/core/include/cutils \
	system/core/libion/include \
	$(RTK_RPC)/IPC/include \
	$(RTK_TOP)/osal_rtk \
	$(RTK_TOP)/core
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
#LOCAL_LDLIBS += -lpthread

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
include $(BUILD_SHARED_LIBRARY)
endif # end of ENCODER_TYPE
