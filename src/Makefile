TOOLPATH = ../z_tools/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGOUT	 = $(TOOLPATH)imgtol.com
CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul

FDIMAGE0_BIN = ..\z_tools\qemu\fdimage0.bin

# 默认动作

default :
	$(MAKE) img

# 镜像文件生成

ipl.bin : ipl.nas Makefile
	$(NASK) ipl.nas ipl.bin ipl.lst

asmhead.bin : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

bootpack.gas : bootpack.c Makefile
	$(CC1) -o bootpack.gas bootpack.c

bootpack.nas : bootpack.gas Makefile
	$(GAS2NASK) bootpack.gas bootpack.nas

bootpack.obj : bootpack.nas Makefile
	$(NASK) bootpack.nas bootpack.obj bootpack.lst

bootpack.bim : bootpack.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj

bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

lazyos.sys : asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb lazyos.sys

lazyos.img : ipl.bin lazyos.sys Makefile
	$(EDIMG)   imgin:$(FDIMAGE0_BIN) \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		copy from:lazyos.sys to:@: \
		imgout:lazyos.img

# 其他指令

asm :
	$(MAKE) ipl.bin

img :
	$(MAKE) lazyos.img

run :
	$(MAKE) img
	copy lazyos.img $(FDIMAGE0_BIN)
	$(MAKE) -C $(TOOLPATH)qemu

install :
	$(MAKE) img
	$(IMGOUT) w a: lazyos.img

clean :
	-del ipl.bin
	-del ipl.lst
	-del asmhead.bin
	-del asmhead.lst
	-del bootpack.gas
	-del bootpack.nas
	-del bootpack.obj
	-del bootpack.bim
	-del bootpack.map
	-del bootpack.hrb

src_only :
	$(MAKE) clean
	-del lazyos.img
