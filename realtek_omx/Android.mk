LOCAL_PATH:= $(call my-dir)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX_Core.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX_Core
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)

################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libRTKOMX_OSAL_RTK.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libRTKOMX_OSAL_RTK
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.audio.dec.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.audio.dec
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.video.dec.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.video.dec
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.image.dec.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.image.dec
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.video.dec.avc.secure.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.video.dec.avc.secure
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.video.dec.vp9.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.video.dec.vp9
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.video.enc.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.video.enc
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.image.enc.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.image.enc
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.video.dec.dovi.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.video.dec.dovi
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)
################################################################################
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libOMX.realtek.video.so
LOCAL_MODULE_TAGS:= optional eng
LOCAL_MODULE_CLASS := VENDOR_SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE := libOMX.realtek.video
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_PREBUILT)


