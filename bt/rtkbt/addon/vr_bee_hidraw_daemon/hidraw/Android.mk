LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES += \
              voice_hidraw.c \
              voice_uipc.c \
              get_voice_app.c \
              ./sbc/sbc.c \
	      ./sbc/sbc_primitives.c \
	      ./sbc/sbc_primitives_armv6.c \
	      ./sbc/sbc_primitives_iwmmxt.c \
	      ./sbc/sbc_primitives_mmx.c \
	      ./sbc/sbc_primitives_neon.c \
              config.c

LOCAL_C_INCLUDES += \
                    $(LOCAL_PATH)/sbc \


LOCAL_CFLAGS += -Wno-unused-parameter -Wno-unused-variable  -Wno-unused-function -Wno-unused-label 

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils libc liblog libtinyalsa libutils
LOCAL_INIT_RC := hidraw.rc
LOCAL_MODULE := vr_bee_hidraw_daemon
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MULTILIB := 32

include $(BUILD_EXECUTABLE)
