##----------------------------------------------------------------------------
-include ../../../../branch_src_sharedMemory_integration/Tools/MConfig/.config
include ../../../../include/MakeConfig

MYDEFS=
rm=/bin/rm -f
cp=/bin/cp -f
CC= $(MYCXX)
AR= $(MYAR) cq
RANLIB=$(MYRANLIB)
LIBNAME= ../../../../lib/libStreamingEngine.a

INCLUDES=  -I. -I../../../Include -I../include
INCLUDES+= -I../../../../../common/IPC/include  -I../../../../../common/IPC/generate/include/system -I../../../../../common/ -I../../../../../common

ifeq ($(TARGET_BOARD), YES)
MYDEFS+= -DTARGET_BOARD
endif

CFLAGS= $(INCLUDES) $(DEFINES) -DSYS_UNIX=1 $(MYDEFS)
ifeq ($(DFB_MULTI_APP), YES)
CFLAGS+= -fPIC
endif

ifeq ($(ENABLE_VSYNC_BLIT), YES)
SRCS = SeDrv_mmap.c
OBJS = SeDrv_mmap.o
else
SRCS = SeDrv.c
OBJS = SeDrv.o
endif

ifeq ($(filter 0x1%6, $(CHIP_MODEL)), $(CHIP_MODEL))
  SRCS += SeLibSaturn.c SeStretchUtils.c
  OBJS += SeLibSaturn.o SeStretchUtils.o
endif
ifeq ($(IS_DARWIN), YES)
  SRCS += SeLibSaturn.c SeStretchUtils.c
  OBJS += SeLibSaturn.o SeStretchUtils.o
endif
ifeq ($(IS_MACARTHUR), YES)
  SRCS += SeLibSaturn.c SeStretchUtils.c
  OBJS += SeLibSaturn.o SeStretchUtils.o
endif

#else
#  SRCS += SeLib.c
#  OBJS += SeLib.o
#endif

.cpp.o:
	$(rm) -f $@
	$(SHOW_COMMAND)echo -=--=--=- [$*.cpp] -=--=--=--=--=--=--=--=--=-
	$(SHOW_COMMAND)$(CC) $(CFLAGS) $(DEBUGFLAG) $(WARNING) -c $*.cpp

.c.o:
	$(rm) -f $@
	$(SHOW_COMMAND)echo -=--=--=- [$*.c] -=--=--=--=--=--=--=--=--=-
	$(SHOW_COMMAND)$(CC) $(CFLAGS) $(DEBUGFLAG) $(WARNING) -c $*.c

all: $(LIBNAME)

$(LIBNAME) : $(OBJS)
	$(rm) $@
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

clean:
	$(rm) $(OBJS) $(LIBNAME) core *~
