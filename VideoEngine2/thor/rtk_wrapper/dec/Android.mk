LOCAL_PATH := $(call my-dir)
RTK_TOP	:= hardware/realtek/realtek_omx
RTK_INC := $(RTK_TOP)/include
RTK_RPC := $(TOP)/device/realtek/proprietary/libs/rtk_libs/common
RTK_VE1:= $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/VE
RTK_JPG:= $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/JPEG

DECODER_TYPE = VE1

MAJOR_VERSION :=$(shell echo $(PLATFORM_VERSION) | cut -f1 -d.)
MINOR_VERSION :=$(shell echo $(PLATFORM_VERSION) | cut -f2 -d.)
USE_HEADER_LIBRARIES :=$(shell test $(MAJOR_VERSION) -gt 8 -o $(MAJOR_VERSION) -eq 8 && echo true || echo false)

# build video decoder
include $(CLEAR_VARS)

ifeq ($(DECODER_TYPE), VE1)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	codec_ve1.c \
	codec_common.c \
	codec_video_common.c

LOCAL_MODULE := libdecve1wrap
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK
LOCAL_SHARED_LIBRARIES += libRTK_lib
#LOCAL_SHARED_LIBRARIES += libhwse.$(TARGET_BOARD_PLATFORM)
LOCAL_SHARED_LIBRARIES += libvpu
LOCAL_SHARED_LIBRARIES += libRtkIpc
LOCAL_SHARED_LIBRARIES += libRTKAllocator
LOCAL_SHARED_LIBRARIES += librtk_ion

LOCAL_SYSLIBS := libc
LOCAL_SYSLIBS += libz
LOCAL_SYSLIBS += libdl
#LOCAL_SYSLIBS += libstdc++
LOCAL_SYSLIBS += libm
LOCAL_SYSLIBS += liblog
LOCAL_SYSLIBS += libcutils
LOCAL_SYSLIBS += libhardware
LOCAL_SYSLIBS += libion
LOCAL_SYSLIBS += libutils

LOCAL_SHARED_LIBRARIES += $(LOCAL_SYSLIBS)
LOCAL_EXPORT_SHARED_LIBRARY_HEADERS += $(LOCAL_SYSLIBS)

#LOCAL_STATIC_LIBRARIES += libskia

LOCAL_SRC_FILES += codec_HEVCHdrParameterParser.c
LOCAL_C_INCLUDES := \
	. \
	system/core/include \
	system/core/include/cutils \
    frameworks/native/headers/media_plugin \
    frameworks/native/headers/media_plugin/media/openmax \
	$(RTK_INC)/imagination \
	$(RTK_INC)/rtkext \
	$(RTK_RPC)/IPC/include \
	$(RTK_TOP)/osal_rtk \
	$(RTK_TOP)/core \
	$(RTK_VE1)/vpuapi \
	hardware/realtek/StreamingEngine2
LOCAL_C_INCLUDES += hardware/realtek/realtek_omx/component/video_$(TARGET_BOARD_PLATFORM)/dec
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion
#CODEC_VO_WRITEBACK
LOCAL_SRC_FILES += vo_writeback/codec_VORPC.c
LOCAL_C_INCLUDES += $(RTK_RPC)/IPC/generate/include/system

#Dolby
LOCAL_SHARED_LIBRARIES += librpu
LOCAL_SHARED_LIBRARIES += librtk_dolby_vision
LOCAL_C_INCLUDES += $(LOCAL_PATH)/dolby/include
LOCAL_C_INCLUDES += $(TOP)/device/realtek/proprietary/libs/libRtkDolbyVision/include
LOCAL_SRC_FILES += dolby/codec_metadata_parser.c
LOCAL_CFLAGS += -DOMX_DECODER_DOVI
LOCAL_CFLAGS += -DOMX_VO_REGISTER_ONLY

ifeq ($(ENABLE_TEE_DRM_FLOW),true)
LOCAL_CFLAGS += -DENABLE_TEE_DRM_FLOW
LOCAL_C_INCLUDES += \
	$(TOP)/device/realtek/proprietary/libs/Include/TEEapi
LOCAL_SHARED_LIBRARIES += libTEEapi
else
# For secureplayback workaround
LOCAL_CFLAGS += -DDISABLE_SECURE_PATH
endif
LOCAL_CFLAGS += -DOMX_DECODER_VE1

ifeq ($(TARGET_PRODUCT),atv1gb)
#LOCAL_CFLAGS += -DPRODUCT_1GB_1080P
LOCAL_CFLAGS += -DPRODUCT_ATV1GB
endif

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
LOCAL_SRC_FILES  += utils/BWControl.cpp
LOCAL_SRC_FILES  += utils/PWControl.cpp
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES       += hardware/realtek/power
LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase libhidltransport libhwbinder
endif
ifneq ($(filter 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES += vendor/realtek/libs/libsync_rtk
LOCAL_SHARED_LIBRARIES += libsync_rtk
LOCAL_CFLAGS += -DPLATFORM_P
else
LOCAL_C_INCLUDES += system/core/libsync/
LOCAL_SHARED_LIBRARIES += libsync
endif
ifeq ($(USE_HEADER_LIBRARIES),true)
LOCAL_HEADER_LIBRARIES += libnativebase_headers
LOCAL_CFLAGS += -DUSE_HEADER_LIBRARIES
endif
include $(BUILD_SHARED_LIBRARY)
endif # end of DECODER_TYPE

###########################################################################

DECODER_TYPE = VE2

# build video decoder
include $(CLEAR_VARS)

ifeq ($(DECODER_TYPE), VE2)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	codec_ve2.c \
	codec_common.c \
	codec_video_common.c

LOCAL_MODULE := libdecve2wrap
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK
LOCAL_SHARED_LIBRARIES += libRTK_lib
#LOCAL_SHARED_LIBRARIES += libhwse.$(TARGET_BOARD_PLATFORM)
LOCAL_SHARED_LIBRARIES += libvpu
LOCAL_SHARED_LIBRARIES += libRtkIpc
LOCAL_SHARED_LIBRARIES += libRTKAllocator
LOCAL_SHARED_LIBRARIES += librtk_ion
LOCAL_SYSLIBS := libc
LOCAL_SYSLIBS += libz
LOCAL_SYSLIBS += libdl
#LOCAL_SYSLIBS += libstdc++
LOCAL_SYSLIBS += libm
LOCAL_SYSLIBS += liblog
LOCAL_SYSLIBS += libcutils
LOCAL_SYSLIBS += libhardware
LOCAL_SYSLIBS += libion
LOCAL_SYSLIBS += libutils

LOCAL_SHARED_LIBRARIES += $(LOCAL_SYSLIBS)
LOCAL_EXPORT_SHARED_LIBRARY_HEADERS += $(LOCAL_SYSLIBS)

#LOCAL_STATIC_LIBRARIES += libskia

LOCAL_SRC_FILES += codec_HEVCHdrParameterParser.c
LOCAL_SRC_FILES += codec_vpxparser.c
LOCAL_C_INCLUDES := \
	. \
	system/core/include \
	system/core/include/cutils \
    frameworks/native/headers/media_plugin \
    frameworks/native/headers/media_plugin/media/openmax \
	$(RTK_INC)/imagination \
	$(RTK_INC)/rtkext \
	$(RTK_RPC)/IPC/include \
	$(RTK_TOP)/osal_rtk \
	$(RTK_TOP)/core \
	$(RTK_VE1)/vpuapi \
	$(RTK_VE1)/sample/helper \
	hardware/realtek/StreamingEngine2
LOCAL_C_INCLUDES += hardware/realtek/realtek_omx/component/video_$(TARGET_BOARD_PLATFORM)/dec
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion
#CODEC_VO_WRITEBACK
LOCAL_SRC_FILES += vo_writeback/codec_VORPC.c
LOCAL_C_INCLUDES += $(RTK_RPC)/IPC/generate/include/system

#Dolby
LOCAL_SHARED_LIBRARIES += librpu
LOCAL_SHARED_LIBRARIES += librtk_dolby_vision
LOCAL_C_INCLUDES += $(LOCAL_PATH)/dolby/include
LOCAL_C_INCLUDES += $(TOP)/device/realtek/proprietary/libs/libRtkDolbyVision/include
LOCAL_SRC_FILES += dolby/codec_metadata_parser.c
LOCAL_CFLAGS += -DOMX_DECODER_DOVI
LOCAL_CFLAGS += -DOMX_VO_REGISTER_ONLY

ifeq ($(ENABLE_TEE_DRM_FLOW),true)
LOCAL_CFLAGS += -DENABLE_TEE_DRM_FLOW
LOCAL_C_INCLUDES += \
	$(TOP)/device/realtek/proprietary/libs/Include/TEEapi
LOCAL_SHARED_LIBRARIES += libTEEapi
else
# For secureplayback workaround
LOCAL_CFLAGS += -DDISABLE_SECURE_PATH
endif
LOCAL_CFLAGS += -DOMX_DECODER_VE2

ifeq ($(TARGET_PRODUCT),atv1gb)
#LOCAL_CFLAGS += -DPRODUCT_1GB_1080P
LOCAL_CFLAGS += -DPRODUCT_ATV1GB
endif

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
LOCAL_SRC_FILES  += utils/BWControl.cpp
LOCAL_SRC_FILES  += utils/PWControl.cpp
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES       += hardware/realtek/power
LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase libhidltransport libhwbinder
endif
ifneq ($(filter 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES += vendor/realtek/libs/libsync_rtk
LOCAL_SHARED_LIBRARIES += libsync_rtk
LOCAL_CFLAGS += -DPLATFORM_P
else
LOCAL_C_INCLUDES += system/core/libsync/
LOCAL_SHARED_LIBRARIES += libsync
endif
ifeq ($(USE_HEADER_LIBRARIES),true)
LOCAL_HEADER_LIBRARIES += libnativebase_headers
LOCAL_CFLAGS += -DUSE_HEADER_LIBRARIES
endif
include $(BUILD_SHARED_LIBRARY)
endif # end of DECODER_TYPE

###########################################################################

DECODER_TYPE = IMAGE
# build image decoder
include $(CLEAR_VARS)

ifeq ($(DECODER_TYPE), IMAGE)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	codec_jdec.c \
	codec_common.c

LOCAL_MODULE := libdecjpgwrap
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK
LOCAL_SHARED_LIBRARIES += libRTK_lib
#LOCAL_SHARED_LIBRARIES += libhwse.$(TARGET_BOARD_PLATFORM)
LOCAL_SHARED_LIBRARIES += libjpu
LOCAL_SHARED_LIBRARIES += libRtkIpc
LOCAL_SHARED_LIBRARIES += libRTKAllocator
LOCAL_SHARED_LIBRARIES += librtk_ion

LOCAL_SYSLIBS := libc
LOCAL_SYSLIBS += libz
LOCAL_SYSLIBS += libdl
#LOCAL_SYSLIBS += libstdc++
LOCAL_SYSLIBS += libm
LOCAL_SYSLIBS += liblog
LOCAL_SYSLIBS += libcutils
LOCAL_SYSLIBS += libhardware
LOCAL_SYSLIBS += libion
LOCAL_SYSLIBS += libutils

LOCAL_SHARED_LIBRARIES += $(LOCAL_SYSLIBS)
LOCAL_EXPORT_SHARED_LIBRARY_HEADERS += $(LOCAL_SYSLIBS)

LOCAL_CFLAGS += -Wno-unused-function

LOCAL_C_INCLUDES := \
	. \
	system/core/include \
	system/core/include/cutils \
    frameworks/native/headers/media_plugin \
    frameworks/native/headers/media_plugin/media/openmax \
	$(RTK_INC)/imagination \
	$(RTK_INC)/rtkext \
	$(RTK_RPC)/IPC/include \
	$(RTK_TOP)/osal_rtk \
	$(RTK_TOP)/core \
	$(RTK_JPG)/include \
	$(RTK_JPG)/jpuapi \
	$(RTK_JPG) \
	hardware/realtek/StreamingEngine2
LOCAL_C_INCLUDES += hardware/realtek/realtek_omx/component/video_$(TARGET_BOARD_PLATFORM)/dec
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion
#LOCAL_LDLIBS += -lpthread

LOCAL_SRC_FILES += vo_writeback/codec_VORPC.c
LOCAL_C_INCLUDES += $(RTK_RPC)/IPC/generate/include/system

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
LOCAL_SRC_FILES  += utils/BWControl.cpp
LOCAL_SRC_FILES  += utils/PWControl.cpp
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES       += hardware/realtek/power
LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase libhidltransport libhwbinder
endif
ifneq ($(filter 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES += vendor/realtek/libs/libsync_rtk
LOCAL_SHARED_LIBRARIES += libsync_rtk
LOCAL_CFLAGS += -DPLATFORM_P
else
LOCAL_C_INCLUDES += system/core/libsync/
LOCAL_SHARED_LIBRARIES += libsync
endif
ifeq ($(USE_HEADER_LIBRARIES),true)
LOCAL_HEADER_LIBRARIES += libnativebase_headers
LOCAL_CFLAGS += -DUSE_HEADER_LIBRARIES
endif
include $(BUILD_SHARED_LIBRARY)
endif # end of DECODER_TYPE

