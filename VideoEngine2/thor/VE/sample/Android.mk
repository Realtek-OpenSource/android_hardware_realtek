
LOCAL_PATH := $(call my-dir)

#Building vpurun binary which will be placed in the /system/bin folder

SRC_FILES := helper/main_helper.c \
          helper/vpuhelper.c \
          helper/bitstream/bitstreamfeeder.c \
          helper/bitstream/bitstreamreader.c \
          helper/bitstream/bsfeeder_fixedsize_impl.c \
          helper/bitstream/bsfeeder_framesize_impl.c \
          helper/bitstream/bsfeeder_size_plus_es_impl.c \
          helper/misc/picture_meta_data.c \
          helper/misc/debug.c \
          helper/comparator/bin_comparator_impl.c \
          helper/comparator/comparator.c \
          helper/comparator/md5_comparator_impl.c \
          helper/comparator/yuv_comparator_impl.c \
          helper/display/fbdev_impl.c \
          helper/display/hdmi_impl.c \
          helper/display/simplerenderer.c \
          helper/misc/cfgParser.c \
          helper/misc/cnm_fpga.c \
          helper/misc/cnm_video_helper.c \
          helper/misc/container.c \
          helper/misc/datastructure.c \
          helper/misc/platform.c \
          helper/yuv/yuvfeeder.c \
          helper/yuv/yuvLoaderfeeder.c





C_INCLUDES := $(LOCAL_PATH) \
        $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/VE \
        $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/VE/vpuapi \
        $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/VE/sample \
        $(TOP)/hardware/realtek/VideoEngine2/$(TARGET_BOARD_PLATFORM)/VE/sample/helper
 


SHARED_LIBRARIES :=       \
        libvpu          \
        libutils 

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(C_INCLUDES)
LOCAL_SHARED_LIBRARIES := $(SHARED_LIBRARIES)
LOCAL_SRC_FILES := main_coda980_dec_test.c
LOCAL_SRC_FILES += $(SRC_FILES)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := coda980_dec_test
#LOCAL_CLANG := false
LOCAL_CFLAGS := $(CNM_CFLAGS)
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(C_INCLUDES)
LOCAL_SHARED_LIBRARIES := $(SHARED_LIBRARIES)
LOCAL_SRC_FILES := main_coda980_enc_test.c
LOCAL_SRC_FILES += $(SRC_FILES)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := coda980_enc_test
#LOCAL_CLANG := false
LOCAL_CFLAGS := $(CNM_CFLAGS)
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(C_INCLUDES)
LOCAL_SHARED_LIBRARIES := $(SHARED_LIBRARIES)
LOCAL_SRC_FILES := main_w5_dec_test.c
LOCAL_SRC_FILES += $(SRC_FILES)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := w5_dec_test
#LOCAL_CLANG := false
LOCAL_CFLAGS := $(CNM_CFLAGS)
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(C_INCLUDES)
LOCAL_SHARED_LIBRARIES := $(SHARED_LIBRARIES)
LOCAL_SRC_FILES := main_sw_uart.c
LOCAL_SRC_FILES += $(SRC_FILES)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := sw_uart_test
#LOCAL_CLANG := false
LOCAL_CFLAGS := $(CNM_CFLAGS)
ifneq ($(filter 8% 9%,$(PLATFORM_VERSION)),)
LOCAL_PROPRIETARY_MODULE := true
endif
include $(BUILD_EXECUTABLE)

