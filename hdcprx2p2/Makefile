#
# Makefile for the Realtek HDCP2.2 rx driver
#

ccflags-y += -I$(srctree)/drivers/media/platform/rtk_hdcprx2p2/include
ccflags-y += -I$(srctree)/drivers/tee

obj-$(CONFIG_RTK_HDCPRX_2P2) := core/crypto_spu.o core/hdmi.o \
  core/bigdigits.o core/crypto.o core/hmac.o core/rcp_api.o core/sha2.o \
  rx/hdcp2_interface.o rx/hdcp2_messages.o rx/hdcp2_session.o rx/sup_mail.o

obj-$(CONFIG_RTK_HDCPRX_2P2_TEE) += rx/TEE2p1_HDCP_ENTRY.o
