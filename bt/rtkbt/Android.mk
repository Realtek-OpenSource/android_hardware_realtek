ifeq ($(BOARD_HAVE_BLUETOOTH_RTK),true)
LOCAL_PATH := $(call my-dir)
include $(call all-subdir-makefiles)
endif
