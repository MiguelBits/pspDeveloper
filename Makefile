TARGET = Tutorial
OBJS = src/main.o src/gfx.o

CFLAGS =
CXXFLAGS = $(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS = $(CFLAGS)

#PSP STUFF
BUILD_PRX = 1
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Our Application
#144x80
PSP_EBOOT_ICON = img/ICON0.png
#480x272
PSP_EBOOT_PIC1= img/PIC1.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
