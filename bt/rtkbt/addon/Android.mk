ifneq ($(BOARD_HAVE_BLUETOOTH_RTK_ADDON),)
LOCAL_PATH := $(call my-dir)
include $(foreach item,$(BOARD_HAVE_BLUETOOTH_RTK_ADDON),$(LOCAL_PATH)/$(item)/Android.mk)
endif
