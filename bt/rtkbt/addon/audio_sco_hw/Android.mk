# Copyright (C) 2012 The Android Open Source Project
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
include $(call all-subdir-makefiles)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := audio.sco.default

#LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_SRC_FILES := \
    audio_sco_hw.c

LOCAL_CFLAGS += -Wno-error=unused-parameter
#LOCAL_SHARED_LIBRARIES := liblog libcutils libtinyalsa libandroid_runtime libutils libaudioutils
LOCAL_SHARED_LIBRARIES := liblog libcutils libtinyalsa libutils libaudioutils libhardware

LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true

LOCAL_MULTILIB := 32
include $(BUILD_SHARED_LIBRARY)

