# RELEASE NAME: 20180517_BT_ANDROID_9.0
# RTKBT_API_VERSION=2.1.1.0

BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_RTK := true
#BOARD_HAVE_BLUETOOTH_RTK_ADDON := bee2 vr_bee_hidraw_daemon audio_hal_bee_hidraw
BOARD_HAVE_BLUETOOTH_RTK_ADDON :=
BOARD_HAVE_BLUETOOTH_RTK_TV := true

ifneq ($(BOARD_HAVE_BLUETOOTH_RTK_ADDON),)
$(foreach item,$(BOARD_HAVE_BLUETOOTH_RTK_ADDON),$(call inherit-product,$(LOCAL_PATH)/addon/$(item)/addon.mk))
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_TV), true)
#Firmware For Tv
include $(LOCAL_PATH)/Firmware/TV/TV_Firmware.mk
else
#Firmware For Tablet
include $(LOCAL_PATH)/Firmware/BT/BT_Firmware.mk
endif

BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(LOCAL_PATH)/bluetooth

PRODUCT_COPY_FILES += \
       $(LOCAL_PATH)/vendor/etc/bluetooth/rtkbt.conf:vendor/etc/bluetooth/rtkbt.conf \
       $(LOCAL_PATH)/vendor/etc/bluetooth/dummy_addr:vendor/etc/bluetooth/dummy_addr \
       $(LOCAL_PATH)/vendor/usr/keylayout/Vendor_005d_Product_0002.kl:vendor/usr/keylayout/Vendor_005d_Product_0002.kl \
       $(LOCAL_PATH)/vendor/usr/keylayout/Vendor_0416_Product_0300.kl:vendor/usr/keylayout/Vendor_0416_Product_0300.kl \
       $(LOCAL_PATH)/vendor/usr/idc/Vendor_005d_Product_0002.idc:vendor/usr/idc/Vendor_005d_Product_0002.idc \
       $(LOCAL_PATH)/vendor/usr/idc/Vendor_0416_Product_0300.idc:vendor/usr/idc/Vendor_0416_Product_0300.idc \
       $(LOCAL_PATH)/system/etc/permissions/android.hardware.bluetooth_le.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.bluetooth_le.xml \
       $(LOCAL_PATH)/system/etc/permissions/android.hardware.bluetooth.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.bluetooth.xml \


# base bluetooth
PRODUCT_PACKAGES += \
    Bluetooth \
    libbt-vendor \
    rtkcmd \
    audio.a2dp.default \
    bluetooth.default \
    android.hardware.bluetooth@1.0-impl \
    android.hidl.memory@1.0-impl \
    android.hardware.bluetooth@1.0-service \
    android.hardware.bluetooth@1.0-service.rc \


PRODUCT_PROPERTY_OVERRIDES += \
                    persist.vendor.bluetooth.rtkcoex=true \
                    persist.vendor.rtkbt.bdaddr_path=none \
                    ro.bt.bdaddr_path=/vendor/etc/bluetooth/dummy_addr

PRODUCT_SYSTEM_DEFAULT_PROPERTIES += persist.bluetooth.btsnoopenable=false \
                    persist.bluetooth.btsnooppath=/data/misc/bluedroid/btsnoop_hci.cfa \
                    persist.service.bdroid.bdaddr=22:22:67:c6:69:73 \
                    persist.bluetooth.btsnoopsize=0xffff \
                    persist.bluetooth.prefferedrole=master \
                    persist.bluetooth.showdeviceswithoutnames=false \
                    vendor.bluetooth.enable_timeout_ms=11000
