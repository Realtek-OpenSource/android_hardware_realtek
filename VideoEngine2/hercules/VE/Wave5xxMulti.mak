# ----------------------------------------------------------------------
#
# Project: C&M Video multi instance sample
#
# ----------------------------------------------------------------------
.PHONY: CREATE_DIR LIBTHEORA clean all

product := WAVE520

USE_FFMPEG  = no
USE_PTHREAD = yes

UNAME = $(shell uname -a)
ifneq (,$(findstring i386, $(UNAME)))
    USE_32BIT = yes
endif


ifeq ($(USE_32BIT), yes)
PLATFORM    = nativelinux
else
PLATFORM    = nativelinux_64bit
endif

CROSS_CC_PREFIX = 
VDI_C           = vdi/linux/vdi.c
VDI_OSAL_C      = vdi/linux/vdi_osal.c
MM_C            = 
PLATFORM_FLAGS  = 

ifeq ("$(BUILD_CONFIGURATION)", "NonOS")
    CROSS_CC_PREFIX = arm-none-eabi-
    VDI_C           = vdi/nonos/vdi.c
    VDI_OSAL_C      = vdi/nonos/vdi_osal.c
    MM_C            = vdi/mm.c
    USE_FFMPEG      = no
    USE_PTHREAD     = no
    PLATFORM        = none
    DEFINES         = -DLIB_C_STUB
    PLATFORM_FLAGS  = 
endif
ifeq ("$(BUILD_CONFIGURATION)", "EmbeddedLinux")
    CROSS_CC_PREFIX = arm-none-linux-gnueabi-
    PLATFORM        = armlinux
endif
ifeq ("$(BUILD_CONFIGURATION)", "RTD1295")
#    CROSS_CC_PREFIX = /home/fuchunyang/sourcecode/1295/gcc-linaro-aarch64-linux-gnu-4.8-2014.04_linux/bin/aarch64-linux-gnu-
	PLATFORM        = arm64
endif

CC  = $(CROSS_CC_PREFIX)gcc
CXX = $(CROSS_CC_PREFIX)g++
LINKING=$(CC)
AR  = $(CROSS_CC_PREFIX)ar

INCLUDES = -I./theoraparser/include -I./vpuapi -I./ffmpeg/include -I./sample/helper -I./vdi
DEFINES += -D$(product) -DSUPPORT_MULTI_INSTANCE_TEST

ifeq ($(SCALER), 1)
DEFINES += -DSUPPORT_MINI_PIPPEN
endif
ifeq ($(MINI_PIPPEN), 1)
DEFINES += -DSUPPORT_MINI_PIPPEN
endif


CFLAGS  += -g -I. -Wno-implicit-function-declaration -Wno-format -Wl,--fatal-warning $(INCLUDES) $(DEFINES) $(PLATFORM_FLAGS)
CFLAGS  += -DTEST_BINARY -DDISABLE_MULTI_ENCODER
ARFLAGS += cru


ifeq ($(USE_FFMPEG), yes)
LDLIBS  += -lavformat -lavcodec -lavutil
LDFLAGS += -L./ffmpeg/lib/$(PLATFORM)
CFLAGS  += -DSUPPORT_FFMPEG_DEMUX -Wno-deprecated-declarations
LDFLAGS  += $(PLATFORM_FLAGS) -L./theoraparser/
LDLIBS   += -ltheoraparser
ifneq ($(USE_32BIT), yes)
#LDLIBS  += -lz
endif #USE_32BIT
endif #USE_FFMPEG

ifeq ($(USE_PTHREAD), yes)
LDLIBS  += -lpthread
endif
LDLIBS  += -lm

TARGET=multi_instance_test
MAKEFILE=Wave5xxMulti.mak
OBJDIR=obj
ALLOBJS=*.o
ALLDEPS=*.dep
ALLLIBS=*.a
RM=rm -f
MKDIR=mkdir -p

SOURCES = sample/main_multi_instance_test.c
SOURCES += sample/main_w5_dec_test.c
SOURCES += sample/helper/main_helper.c                      \
          sample/helper/vpuhelper.c                         \
          sample/helper/bitstream/bitstreamfeeder.c         \
          sample/helper/bitstream/bitstreamreader.c         \
          sample/helper/bitstream/bsfeeder_fixedsize_impl.c \
          sample/helper/bitstream/bsfeeder_framesize_impl.c \
          sample/helper/bitstream/bsfeeder_size_plus_es_impl.c \
          sample/helper/comparator/bin_comparator_impl.c    \
          sample/helper/comparator/comparator.c             \
          sample/helper/comparator/md5_comparator_impl.c    \
          sample/helper/comparator/yuv_comparator_impl.c    \
          sample/helper/display/fbdev_impl.c                \
          sample/helper/display/hdmi_impl.c                 \
          sample/helper/display/simplerenderer.c            \
          sample/helper/misc/cfgParser.c                    \
          sample/helper/misc/cnm_fpga.c                     \
          sample/helper/misc/cnm_video_helper.c             \
          sample/helper/misc/container.c                    \
          sample/helper/misc/datastructure.c                \
          sample/helper/misc/platform.c                     \
          sample/helper/misc/debug.c                        \
          sample/helper/yuv/yuvfeeder.c                     \
          sample/helper/yuv/yuvLoaderfeeder.c
SOURCES += $(VDI_C)                                         \
          $(VDI_OSAL_C)                                     \
          $(MM_C)                                           \
          vpuapi/product.c                                  \
          vpuapi/vpuapifunc.c                               \
          vpuapi/vpuapi.c                                   \
          vpuapi/coda9/coda9.c                              \
          vpuapi/wave/wave5.c

VPATH  = sample:
VPATH += sample/helper:
VPATH += sample/helper/bitstream:
VPATH += sample/helper/comparator:
VPATH += sample/helper/display:sample/helper/misc:sample/helper/yuv:
VPATH += vdi:
ifeq ($(HAPS), 1)
VPATH += vdi/haps
endif
ifeq ($(HAPS), 2)
VPATH += vdi/haps
endif
VDI_VPATH = vdi/linux
VPATH += $(VDI_VPATH):vpuapi:vpuapi/coda9:vpuapi/wave

OBJECTNAMES=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))
OBJECTPATHS=$(addprefix $(OBJDIR)/,$(notdir $(OBJECTNAMES)))

all: CREATE_DIR $(OBJECTPATHS)
	$(LINKING) -o $(TARGET) $(LDFLAGS) -Wl,-gc-section -Wl,--start-group $(OBJECTPATHS) $(LDLIBS) -Wl,--end-group -static

-include $(OBJECTPATHS:.o=.dep)

clean: 
	$(RM) $(TARGET)
	$(RM) $(OBJDIR)/$(ALLOBJS)
	$(RM) $(OBJDIR)/$(ALLDEPS)
#	$(RM) theoraparser/$(ALLOBJS)
#	$(RM) theoraparser/$(ALLLIBS)
#	$(RM) theoraparser/$(ALLDEPS)

LIBTHEORA: 
	cd theoraparser; make clean; make

CREATE_DIR:
	-mkdir -p $(OBJDIR)

obj/%.o: %.c $(MAKEFILE)
	$(CC) $(CFLAGS) -Wall -Werror -c $< -o $@ -MD -MF $(@:.o=.dep)

