# SHELL=cmd.exe
TOOLPATH = ../z_tools/
FONTS_PATH = ./fonts/
INCPATH  = ../include/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGOUT	 = $(TOOLPATH)imgtol.com
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe


FDIMAGE0_BIN = ..\z_tools\qemu\fdimage0.bin

OBJS_BOOTPACK = bootpack.obj display.obj gdt.obj irq.obj naskfunc.obj $(FONTS_PATH)hankaku.obj

SUBDIRS := $(wildcard */.)

# 默认动作

default :
	$(MAKE) img

# 镜像文件生成

bootpack.bim : $(OBJS_BOOTPACK)  Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		$(OBJS_BOOTPACK)

bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

lazyos.sys : asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb lazyos.sys

lazyos.img : ipl.bin lazyos.sys Makefile
	$(EDIMG)   imgin:$(FDIMAGE0_BIN) \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		copy from:lazyos.sys to:@: \
		imgout:lazyos.img

%.nas : %.gas Makefile
	$(GAS2NASK) $*.gas $*.nas

%.gas : %.c Makefile
	$(CC1) -o $*.gas $*.c

%.bin : %.nas Makefile
	$(NASK) $*.nas $*.bin $*.lst

%.obj : %.nas Makefile
	$(NASK) $*.nas $*.obj $*.lst

# 其他指令

asm :
	$(MAKE) ipl.bin

img :
	$(MAKE) lazyos.img

run :
	$(MAKE) -C $(FONTS_PATH)
	$(MAKE) img
	copy lazyos.img $(FDIMAGE0_BIN)
	$(MAKE) -C $(TOOLPATH)qemu

install :
	$(MAKE) img
	$(IMGOUT) w a: lazyos.img

clean :
	$(MAKE) -C $(FONTS_PATH) clean
	-del bootpack.nas
	-del *.bin
	-del *.gas
	-del *.map
	-del *.hrb
	-del *.bim
	-del *.lst
	-del *.obj
	-del *.sys

src_only :
	$(MAKE) clean
	-del lazyos.img
