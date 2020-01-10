LOCAL_PATH := $(call my-dir)
RTK_TOP	:= hardware/realtek/realtek_omx
RTK_INC := $(RTK_TOP)/include
RTK_RPC := $(TOP)/device/realtek/proprietary/libs/rtk_libs/common
RTK_VE1:= $(TOP)/hardware/realtek/VideoEngine2/hercules/VE
RTK_JPG:= $(TOP)/hardware/realtek/VideoEngine2/hercules/JPEG

DECODER_TYPE = VE1
OMX_DECODER_TUNNELING_SUPPORT = true

MAJOR_VERSION :=$(shell echo $(PLATFORM_VERSION) | cut -f1 -d.)
MINOR_VERSION :=$(shell echo $(PLATFORM_VERSION) | cut -f2 -d.)
USE_HEADER_LIBRARIES :=$(shell test $(MAJOR_VERSION) -gt 8 -o $(MAJOR_VERSION) -eq 8 && echo true || echo false)

# disable OMX_DECODER_TUNNELING_SUPPORT for KK - fix me later
ifneq ($(filter 4.%,$(PLATFORM_VERSION)),)
OMX_DECODER_TUNNELING_SUPPORT = false
endif

ifeq ($(DISABLE_RTK_GUI), YES)
OMX_DECODER_TUNNELING_SUPPORT = false
endif

# build video decoder
include $(CLEAR_VARS)

ifeq ($(DECODER_TYPE), VE1)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	decoder.c \
	codec.c \
	codec_ve1.c \
	codec_video_common.c \
	codec_jdec.c

LOCAL_MODULE := libOMX.realtek.video.dec
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK
LOCAL_SHARED_LIBRARIES += libRTK_lib
#LOCAL_SHARED_LIBRARIES += libhwse.$(TARGET_BOARD_PLATFORM)
LOCAL_SHARED_LIBRARIES += libvpu
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

LOCAL_CFLAGS = -DOMX_DECODER_VIDEO_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION

ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_CFLAGS += -DMOVE_SIDEBAND_CLIENT
endif

ifeq ($(OMX_DECODER_TUNNELING_SUPPORT), true)
LOCAL_SRC_FILES += sidebandOutput.c Sideband_C.cpp
LOCAL_SYSLIBS += libgui_rtk
LOCAL_SYSLIBS += libui
LOCAL_SYSLIBS += libbinder
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_SYSLIBS += libnativewindow
LOCAL_SHARED_LIBRARIES += libSidebandClient
endif
LOCAL_CFLAGS += -DOMX_DECODER_TUNNELING_SUPPORT
endif

LOCAL_SHARED_LIBRARIES += $(LOCAL_SYSLIBS)
LOCAL_EXPORT_SHARED_LIBRARY_HEADERS += $(LOCAL_SYSLIBS)

#LOCAL_STATIC_LIBRARIES += libskia

LOCAL_CFLAGS += -DOMX_DECODER_VIDEO_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION

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
	$(RTK_JPG)/include \
	$(RTK_JPG)/jpuapi \
	$(RTK_JPG) \
	hardware/realtek/StreamingEngine2
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion
ifeq ($(OMX_DECODER_TUNNELING_SUPPORT), true)
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES += vendor/realtek/libs/libSidebandClient/inc
LOCAL_C_INCLUDES += frameworks/native/opengl/include
endif
endif
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

ifeq ($(ENABLE_LOW_RAM), true)
LOCAL_CFLAGS += -DPRODUCT_1GB_1080P
endif

#LOCAL_LDLIBS += -lpthread
#
# create symbolic links to each decoders
#
DECODER_FORMATS = avc
DECODER_FORMATS += mpeg4
DECODER_FORMATS += vp8
DECODER_FORMATS += 3gpp
DECODER_FORMATS += mpeg2
DECODER_FORMATS += raw
DECODER_FORMATS += vc1
DECODER_FORMATS += rv
DECODER_FORMATS += divx3
DECODER_FORMATS += avs
DECODER_FORMATS += mjpg
DECODER_FORMATS += wvc1
DECODER_FORMATS += wmv3
DECODER_FORMATS += wmv
#DECODER_FORMATS += mp43
DECODER_FORMATS += flv
DECODER_FORMATS += rv30
DECODER_FORMATS += rv40
DECODER_FORMATS += avc.secure

ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
SYMLINKS := $(addsuffix .so,$(addprefix $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).,$(DECODER_FORMATS)))
else
SYMLINKS := $(addsuffix .so,$(addprefix $(TARGET_OUT)/lib/$(LOCAL_MODULE).,$(DECODER_FORMATS)))
endif

LOCAL_POST_INSTALL_CMD := $(hide) $(foreach t,$(SYMLINKS),ln -sf $(LOCAL_MODULE).so $(t);)
LOCAL_POST_INSTALL_CMD += cp -f $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).so device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/lib

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
LOCAL_SRC_FILES  += base/vport.c
LOCAL_SRC_FILES  += base/vbuffer.c
LOCAL_SRC_FILES  += utils/Feature.c
LOCAL_SRC_FILES  += utils/env.c
LOCAL_SRC_FILES	 += utils/SecureHandle.c
LOCAL_SRC_FILES  += utils/BWControl.cpp
LOCAL_SRC_FILES  += utils/PWControl.cpp
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES       += hardware/realtek/power
LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase libhidltransport libhwbinder
endif
LOCAL_SRC_FILES  += utils/list.c
LOCAL_C_INCLUDES += vendor/realtek/libs/libsync_rtk
LOCAL_SHARED_LIBRARIES += libsync_rtk
ifeq ($(USE_HEADER_LIBRARIES),true)
LOCAL_HEADER_LIBRARIES += libnativebase_headers
LOCAL_CFLAGS += -DUSE_HEADER_LIBRARIES
endif
include $(BUILD_SHARED_LIBRARY)
endif # end of DECODER_TYPE

###########################################################################

DECODER_TYPE = VE2
OMX_DECODER_TUNNELING_SUPPORT = true
# disable OMX_DECODER_TUNNELING_SUPPORT for KK - fix me later
ifneq ($(filter 4.%,$(PLATFORM_VERSION)),)
OMX_DECODER_TUNNELING_SUPPORT = false
endif

ifeq ($(DISABLE_RTK_GUI), YES)
OMX_DECODER_TUNNELING_SUPPORT = false
endif

# build video decoder
include $(CLEAR_VARS)

ifeq ($(DECODER_TYPE), VE2)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	decoder.c \
	codec.c \
	codec_ve2.c \
	codec_video_common.c

LOCAL_MODULE := libOMX.realtek.video
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK
LOCAL_SHARED_LIBRARIES += libRTK_lib
#LOCAL_SHARED_LIBRARIES += libhwse.$(TARGET_BOARD_PLATFORM)
LOCAL_SHARED_LIBRARIES += libvpu
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

LOCAL_CFLAGS = -DOMX_DECODER_VIDEO_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_CFLAGS += -DMOVE_SIDEBAND_CLIENT
endif

ifeq ($(OMX_DECODER_TUNNELING_SUPPORT), true)
LOCAL_SRC_FILES += sidebandOutput.c Sideband_C.cpp
LOCAL_SYSLIBS += libgui_rtk
LOCAL_SYSLIBS += libui
LOCAL_SYSLIBS += libbinder
LOCAL_C_INCLUDES += frameworks/native/opengl/include
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_SYSLIBS += libnativewindow
LOCAL_SHARED_LIBRARIES += libSidebandClient
endif
LOCAL_CFLAGS += -DOMX_DECODER_TUNNELING_SUPPORT
endif

LOCAL_SHARED_LIBRARIES += $(LOCAL_SYSLIBS)
LOCAL_EXPORT_SHARED_LIBRARY_HEADERS += $(LOCAL_SYSLIBS)

#LOCAL_STATIC_LIBRARIES += libskia

LOCAL_CFLAGS += -DOMX_DECODER_VIDEO_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION

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
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion
ifeq ($(OMX_DECODER_TUNNELING_SUPPORT), true)
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES += vendor/realtek/libs/libSidebandClient/inc
LOCAL_C_INCLUDES += frameworks/native/opengl/include
endif
endif
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

ifeq ($(ENABLE_LOW_RAM), true)
LOCAL_CFLAGS += -DPRODUCT_1GB_1080P
endif

#LOCAL_LDLIBS += -lpthread
#
# create symbolic links to each decoders
#
DECODER_FORMATS = dec.hevc
DECODER_FORMATS += dec.hevc.secure
DECODER_FORMATS += dec.vp9
DECODER_FORMATS += dec.vp9.secure

ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
SYMLINKS := $(addsuffix .so,$(addprefix $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).,$(DECODER_FORMATS)))
else
SYMLINKS := $(addsuffix .so,$(addprefix $(TARGET_OUT)/lib/$(LOCAL_MODULE).,$(DECODER_FORMATS)))
endif

LOCAL_POST_INSTALL_CMD := $(hide) $(foreach t,$(SYMLINKS),ln -sf $(LOCAL_MODULE).so $(t);)
LOCAL_POST_INSTALL_CMD += cp -f $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).so device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/lib

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
LOCAL_SRC_FILES  += base/vport.c
LOCAL_SRC_FILES  += base/vbuffer.c
LOCAL_SRC_FILES  += utils/Feature.c
LOCAL_SRC_FILES  += utils/env.c
LOCAL_SRC_FILES	 += utils/SecureHandle.c
LOCAL_SRC_FILES  += utils/BWControl.cpp
LOCAL_SRC_FILES  += utils/PWControl.cpp
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES       += hardware/realtek/power
LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase libhidltransport libhwbinder
endif
LOCAL_SRC_FILES  += utils/list.c
LOCAL_C_INCLUDES += vendor/realtek/libs/libsync_rtk
LOCAL_SHARED_LIBRARIES += libsync_rtk
ifeq ($(USE_HEADER_LIBRARIES),true)
LOCAL_HEADER_LIBRARIES += libnativebase_headers
LOCAL_CFLAGS += -DUSE_HEADER_LIBRARIES
endif
include $(BUILD_SHARED_LIBRARY)
endif # end of DECODER_TYPE

###########################################################################

DECODER_TYPE = IMAGE
OMX_DECODER_TUNNELING_SUPPORT = false
# build image decoder
include $(CLEAR_VARS)

ifeq ($(DECODER_TYPE), IMAGE)
LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	decoder.c \
	codec.c \
	codec_jdec.c

LOCAL_MODULE := libOMX.realtek.image.dec
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

LOCAL_CFLAGS = -DOMX_DECODER_IMAGE_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION
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
LOCAL_SRC_FILES  += base/vport.c
LOCAL_SRC_FILES  += base/vbuffer.c
LOCAL_SRC_FILES  += utils/Feature.c
LOCAL_SRC_FILES  += utils/env.c
LOCAL_SRC_FILES	 += utils/SecureHandle.c
LOCAL_SRC_FILES  += utils/BWControl.cpp
LOCAL_SRC_FILES  += utils/PWControl.cpp
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES       += hardware/realtek/power
LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase libhidltransport libhwbinder
endif
LOCAL_SRC_FILES  += utils/list.c
LOCAL_C_INCLUDES += vendor/realtek/libs/libsync_rtk
LOCAL_SHARED_LIBRARIES += libsync_rtk
ifeq ($(USE_HEADER_LIBRARIES),true)
LOCAL_HEADER_LIBRARIES += libnativebase_headers
LOCAL_CFLAGS += -DUSE_HEADER_LIBRARIES
endif

LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).so device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/lib

include $(BUILD_SHARED_LIBRARY)
endif # end of DECODER_TYPE

###########################################################################
# For KitKat
DECODER_TYPE = DOVI
OMX_DECODER_TUNNELING_SUPPORT = true
ifneq ($(filter 4.%,$(PLATFORM_VERSION)),)
OMX_DECODER_TUNNELING_SUPPORT = false
endif

ifeq ($(DISABLE_RTK_GUI), YES)
OMX_DECODER_TUNNELING_SUPPORT = false
endif

# build video DECODER_TYPE
include $(CLEAR_VARS)

ifeq ($(DECODER_TYPE), DOVI)
	LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES := \
	decoder.c \
	codec.c \
	codec_ve1.c \
	codec_ve2.c \
	codec_video_common.c \

	LOCAL_MODULE := libOMX.realtek.video.dec.dovi
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE_TAGS := optional
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_SHARED_LIBRARIES += libRTKOMX_OSAL_RTK
LOCAL_SHARED_LIBRARIES += libRTK_lib
#LOCAL_SHARED_LIBRARIES += libhwse.$(TARGET_BOARD_PLATFORM)
LOCAL_SHARED_LIBRARIES += libvpu
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

LOCAL_CFLAGS = -DOMX_DECODER_VIDEO_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_CFLAGS += -DMOVE_SIDEBAND_CLIENT
endif

ifeq ($(OMX_DECODER_TUNNELING_SUPPORT), true)
LOCAL_SRC_FILES += sidebandOutput.c Sideband_C.cpp
LOCAL_SYSLIBS += libgui_rtk
LOCAL_SYSLIBS += libui
LOCAL_SYSLIBS += libbinder
LOCAL_C_INCLUDES += frameworks/native/opengl/include
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_SYSLIBS += libnativewindow
LOCAL_SHARED_LIBRARIES += libSidebandClient
endif
LOCAL_CFLAGS += -DOMX_DECODER_TUNNELING_SUPPORT
endif

LOCAL_SHARED_LIBRARIES += $(LOCAL_SYSLIBS)
LOCAL_EXPORT_SHARED_LIBRARY_HEADERS += $(LOCAL_SYSLIBS)

#LOCAL_STATIC_LIBRARIES += libskia

LOCAL_CFLAGS += -DOMX_DECODER_VIDEO_DOMAIN -DUSE_OUTPUT_CROP
LOCAL_CFLAGS += -DUSE_RT_ION

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
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion
ifeq ($(OMX_DECODER_TUNNELING_SUPPORT), true)
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES += vendor/realtek/libs/libSidebandClient/inc
LOCAL_C_INCLUDES += frameworks/native/opengl/include
endif
endif
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

ifeq ($(ENABLE_TEE_DRM_FLOW),true)
	LOCAL_CFLAGS += -DENABLE_TEE_DRM_FLOW
	LOCAL_C_INCLUDES += \
							$(TOP)/device/realtek/proprietary/libs/Include/TEEapi
	LOCAL_SHARED_LIBRARIES += libTEEapi
else
# For secureplayback workaround
LOCAL_CFLAGS += -DDISABLE_SECURE_PATH
endif

ifeq ($(TARGET_PRODUCT),atv1gb)
#LOCAL_CFLAGS += -DPRODUCT_1GB_1080P
LOCAL_CFLAGS += -DPRODUCT_ATV1GB
endif

ifeq ($(ENABLE_LOW_RAM), true)
LOCAL_CFLAGS += -DPRODUCT_1GB_1080P
endif

GIT_SHA_NAME := $(shell cd $(LOCAL_PATH) && git rev-parse --short HEAD)
$(shell test -e $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c || echo "#include <RTKRevision.h>" > $(LOCAL_PATH)/.RTKRevision.$(GIT_SHA_NAME).c)
LOCAL_CFLAGS           += -D'GIT_VERSION="$(GIT_SHA_NAME)"'
LOCAL_SRC_FILES        += .RTKRevision.$(GIT_SHA_NAME).c
LOCAL_C_INCLUDES       += device/realtek/proprietary/libs/RTKRevision/include
LOCAL_SRC_FILES  += base/vport.c
LOCAL_SRC_FILES  += base/vbuffer.c
LOCAL_SRC_FILES  += utils/Feature.c
LOCAL_SRC_FILES  += utils/env.c
LOCAL_SRC_FILES	 += utils/SecureHandle.c
LOCAL_SRC_FILES  += utils/BWControl.cpp
LOCAL_SRC_FILES  += utils/PWControl.cpp
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_C_INCLUDES       += hardware/realtek/power
LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase libhidltransport libhwbinder
endif
LOCAL_SRC_FILES  += utils/list.c
LOCAL_C_INCLUDES += vendor/realtek/libs/libsync_rtk
LOCAL_SHARED_LIBRARIES += libsync_rtk
ifeq ($(USE_HEADER_LIBRARIES),true)
LOCAL_HEADER_LIBRARIES += libnativebase_headers
LOCAL_CFLAGS += -DUSE_HEADER_LIBRARIES
endif
LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).so device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/lib
include $(BUILD_SHARED_LIBRARY)
endif # end of DECODER_TYPE
