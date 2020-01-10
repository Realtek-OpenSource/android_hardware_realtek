LOCAL_PATH:= $(call my-dir)

################################################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES += CameraHardware3Base.cpp
LOCAL_SRC_FILES += CameraFactory.cpp
LOCAL_SRC_FILES += Hal3Base.cpp
LOCAL_SRC_FILES += CameraHal3_hidl.cpp
LOCAL_SRC_FILES += VOWBCallback.cpp
LOCAL_SRC_FILES += CameraHardware3v2.cpp
LOCAL_SRC_FILES += V4L2Device2Common.cpp
LOCAL_SRC_FILES += V4L2Device2.cpp
LOCAL_SRC_FILES += V4L2Device2DownFps.cpp
LOCAL_SRC_FILES += V4L2Device2DI.cpp
LOCAL_SRC_FILES += V4L2Device2MJPG.cpp
LOCAL_SRC_FILES += V4L2Device2Callback.cpp

LOCAL_SRC_FILES += misc/CameraMonitor.cpp
LOCAL_SRC_FILES += misc/ExifHelper.cpp
LOCAL_SRC_FILES += misc/FormatConvertHelper.cpp
LOCAL_SRC_FILES += misc/misc.cpp
LOCAL_SRC_FILES += misc/OMXDecodeHelper.cpp
LOCAL_SRC_FILES += misc/OMXDecodeHelperCallback.cpp
LOCAL_SRC_FILES += misc/OMXComponentDecodeHelper.cpp
LOCAL_SRC_FILES += misc/JPEGCompressHelper.cpp

#LOCAL_SRC_FILES += misc/NetlinkManager.cpp
#LOCAL_SRC_FILES += misc/NetlinkHandler.cpp
#LOCAL_SRC_FILES += ProviderPriv.cpp
#LOCAL_SRC_FILES += V4L2Device2MJPG_old.cpp
#LOCAL_SRC_FILES += legacy/CameraHardware3.cpp
#LOCAL_SRC_FILES += legacy/V4L2Device.cpp
#LOCAL_SRC_FILES += misc/Camera3VoWritebackHelper.cpp
#LOCAL_SRC_FILES += misc/YuvToJpegEncoder.cpp
#LOCAL_SRC_FILES += misc/MediaCodecDecodeHelper.cpp

# exif files
LOCAL_SRC_FILES += jpegexif/exif-i18n.c
LOCAL_SRC_FILES += jpegexif/jpeg-data.c
LOCAL_SRC_FILES += jpegexif/jpeg-marker.c

LOCAL_C_INCLUDES += external/libexif
LOCAL_C_INCLUDES += external/libyuv/files/include
LOCAL_C_INCLUDES += external/jpeg
LOCAL_C_INCLUDES += external/libjpeg-turbo
LOCAL_C_INCLUDES += external/jhead
LOCAL_C_INCLUDES += frameworks/base/include/ui
LOCAL_C_INCLUDES += frameworks/base/include/utils
LOCAL_C_INCLUDES += frameworks/av/include
LOCAL_C_INCLUDES += frameworks/av/include/media/stagefright
LOCAL_C_INCLUDES += frameworks/native/include
LOCAL_C_INCLUDES += frameworks/native/include/media/openmax
LOCAL_C_INCLUDES += frameworks/native/include/media/hardware
LOCAL_C_INCLUDES += frameworks/native/libs/nativewindow/include
LOCAL_C_INCLUDES += frameworks/native/opengl/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libRTKAllocator/include
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/libDeInterlace
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/generate/include/system
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_libs/common/IPC/include
LOCAL_C_INCLUDES += hardware/realtek
LOCAL_C_INCLUDES += hardware/libhardware_legacy/include
LOCAL_C_INCLUDES += hardware/interfaces/camera/common/1.0/default
LOCAL_C_INCLUDES += system/media/camera/include
LOCAL_C_INCLUDES += system/core/include
LOCAL_C_INCLUDES += system/core/libsync
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/rtk_ion

LOCAL_C_INCLUDES += $(LOCAL_PATH)/jpegexif
LOCAL_C_INCLUDES += $(LOCAL_PATH)/jpegexif/libjpeg
LOCAL_C_INCLUDES += $(LOCAL_PATH)/legacy
LOCAL_C_INCLUDES += $(LOCAL_PATH)/misc
LOCAL_C_INCLUDES += $(LOCAL_PATH)/jpegexif
LOCAL_C_INCLUDES += $(LOCAL_PATH)/jpegexif/libjpeg

#LOCAL_C_INCLUDES += frameworks/native/libs/gui
#LOCAL_C_INCLUDES += frameworks/native/libs/gui/include
#LOCAL_C_INCLUDES += system/libhidl/transport/token/1.0/utils/include
#LOCAL_C_INCLUDES += device/realtek/proprietary/libs/vo_writeback

LOCAL_SHARED_LIBRARIES += libui
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libcamera_metadata
LOCAL_SHARED_LIBRARIES += libexif
LOCAL_SHARED_LIBRARIES += libRtkIpc
LOCAL_SHARED_LIBRARIES += libhardware
LOCAL_SHARED_LIBRARIES += libhardware_legacy
LOCAL_SHARED_LIBRARIES += libsysutils
LOCAL_SHARED_LIBRARIES += libRTKAllocator
LOCAL_SHARED_LIBRARIES += libsync
LOCAL_SHARED_LIBRARIES += libjpeg.vendor
LOCAL_SHARED_LIBRARIES += libDeInterlace

#LOCAL_SHARED_LIBRARIES += libstagefright_foundation
#LOCAL_SHARED_LIBRARIES += libstagefright
#LOCAL_SHARED_LIBRARIES += libRTKVOWriteback
#LOCAL_SHARED_LIBRARIES += libskia

LOCAL_SHARED_LIBRARIES += android.hardware.power@1.0
LOCAL_SHARED_LIBRARIES += libhidlbase
LOCAL_SHARED_LIBRARIES += libhidltransport

LOCAL_STATIC_LIBRARIES += android.hardware.camera.common@1.0-helper.vendor
LOCAL_STATIC_LIBRARIES += libyuv_static

#LOCAL_STATIC_LIBRARIES := libjpeg_static_ndk

LOCAL_CFLAGS += -DUSE_RT_ION
#LOCAL_CFLAGS += -save-temps

LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_32_BIT_ONLY := true

LOCAL_MODULE:= camera.$(TARGET_BOARD_PLATFORM)
LOCAL_MODULE_TAGS:= optional
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_SHARED_LIBRARY)

################################################################################

