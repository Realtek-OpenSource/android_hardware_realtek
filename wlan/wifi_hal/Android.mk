# Copyright (C) 2011 The Android Open Source Project
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

LOCAL_PATH := $(call my-dir)

# Make the HAL library
# ============================================================
include $(CLEAR_VARS)

LOCAL_CFLAGS := \
    -Wall \
    -Werror \
    -Wno-format \
    -Wno-reorder \
    -Wno-unused-function \
    -Wno-unused-parameter \
    -Wno-unused-private-field \
    -Wno-unused-variable \
#    -DCONFIG_WIFI_HAL_DEBUG

LOCAL_C_INCLUDES += \
	external/libnl/include \
	$(call include-path-for, libhardware_legacy)/hardware_legacy \
	external/wpa_supplicant_8/src/drivers

LOCAL_HEADER_LIBRARIES := libutils_headers liblog_headers
LOCAL_SRC_FILES := \
	rtw_wifi_hal.cpp \
	rtw_wifi_rtt.cpp \
	common.cpp \
	cpp_bindings.cpp \
	rtw_wifi_gscan.cpp \
	rtw_wifi_llstats.cpp \
	rtw_wifi_logger.cpp \
	rtw_wifi_offload.cpp

LOCAL_MODULE := libwifi-hal-rtk
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_STATIC_LIBRARY)

