# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(USE_RTK_HDCPRX1x_CONTROL),YES)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := rtk_hdcprx2p2.c
LOCAL_SRC_FILES += core/crypto_spu.c core/crypto.c \
	core/bigdigits.c core/hmac.c core/rcp_api.c \
	rx/hdcp2_interface.c rx/hdcp2_messages.c rx/hdcp2_session.c

LOCAL_CFLAGS += -fPIC

LOCAL_C_INCLUDES += \
	hardware/realtek/hdcprx2p2/include \
	external/openssl/include \
	hardware/realtek/realtek_omx/rtk_libs/common \
	hardware/realtek/realtek_omx/rtk_libs/common/IPC/generate/include/system \
	hardware/realtek/realtek_omx/rtk_libs/common/IPC/include \
	device/realtek/proprietary/libs/libMCPControl/inc
	#device/realtek/proprietary/libs/Include/Platform_Lib/MCPControl

#LOCAL_CFLAGS := -DCEC_HAL_TRACE

LOCAL_SHARED_LIBRARIES += libcrypto
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libcutils
#LOCAL_SHARED_LIBRARIES += libRTK_lib
LOCAL_SHARED_LIBRARIES += libcutils

LOCAL_C_INCLUDES += device/realtek/proprietary/libs/RtkHWMBinderapi
LOCAL_SHARED_LIBRARIES += libRTKHWMBinderapi

ifeq ($(USE_RTK_HDCPRX_TEE),YES)
LOCAL_CFLAGS += -DCONFIG_RTK_HDCPRX_1P4_TEE
endif

ifeq ($(USE_RTK_HDCPRX22_CONTROL),YES)
LOCAL_CFLAGS += -DCONFIG_RTK_HDCPRX_2P2

ifeq ($(USE_RTK_HDCPRX_TEE),YES)
##### TEE #####
LOCAL_SRC_FILES += rx/hdcp2_tee_entry.c
LOCAL_C_INCLUDES += device/realtek/proprietary/libs/Include/TEEapi
TEELIB_PATH = device/realtek/$(TARGET_BOARD_PLATFORM)/common/prebuilt/tee/lib/
LOCAL_LDFLAGS += -L$(TEELIB_PATH) -lteec
LOCAL_CFLAGS += -DCONFIG_RTK_HDCPRX_2P2_TEE
endif

endif


#LOCAL_MODULE_PATH_32 := $(TARGET_OUT)/lib/hw
#LOCAL_MODULE_PATH_64 := $(TARGET_OUT)/lib64/hw
#LOCAL_MULTILIB := both

LOCAL_MODULE := rtk_hdcprx2p2
LOCAL_INIT_RC := rtk_hdcprx2p2.rc
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_TAGS := optional	

include $(BUILD_EXECUTABLE)

endif
