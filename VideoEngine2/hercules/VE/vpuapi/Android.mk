LOCAL_PATH := $(call my-dir)

# Building the vpuapi
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
 	../vdi/linux/vdi.c \
   	../vdi/linux/vdi_osal.c

LOCAL_SRC_FILES += \
 	vpuapi.c \
	product.c \
	coda9/coda9.c \
	wave/wave5.c \
	vpuapifunc.c 

LOCAL_SRC_FILES += \
	../aes/aes.c

LOCAL_SRC_FILES += \
	../sample/helper/vpuhelper.c


LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libvpu

ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_CFLAGS := -DCONFIG_DEBUG_LEVEL=255 $(CNM_CFLAGS)

LOCAL_STATIC_LIBRARIES := 

LOCAL_SHARED_LIBRARIES :=       \
		libutils      \
		libdl  		 \
	   	liblog	

ifeq ($(ENABLE_TEE_DRM_FLOW),true)
LOCAL_CFLAGS += -DENABLE_TEE_DRM_FLOW
LOCAL_C_INCLUDES += \
    $(TOP)/device/realtek/proprietary/libs/Include/TEEapi
	LOCAL_SHARED_LIBRARIES += libTEEapi

ifeq ($(ENABLE_VMX_DRM), YES)
LOCAL_CFLAGS += -DENABLE_VMX_DRM
endif
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

LOCAL_SHARED_LIBRARIES += libRTK_lib
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include/
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/include/xdr
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/src/xdr
LOCAL_CFLAGS += -DCONFIG_RTK_RPC

VE1_CHECKSUM = false
VE1_CHECKSUM_LOG_TO_TMP = false
ifeq ($(VE1_CHECKSUM),true)
LOCAL_SHARED_LIBRARIES += libMCPControl
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libMCPControl/inc/
LOCAL_CFLAGS += -DVE1_CHECKSUM
ifeq ($(VE1_CHECKSUM_LOG_TO_TMP),true)
LOCAL_CFLAGS += -DVE1_CHECKSUM_LOG_TO_TMP
endif
endif

LOCAL_POST_INSTALL_CMD := cp -f $(TARGET_OUT_VENDOR)/lib/$(LOCAL_MODULE).so device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/proprietary/lib
include $(BUILD_SHARED_LIBRARY)
