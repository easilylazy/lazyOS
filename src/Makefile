TOOLPATH = ../z_tools/

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGOUT	 = $(TOOLPATH)imgtol.com

FDIMAGE0_BIN = ..\z_tools\qemu\fdimage0.bin

# 默认动作

default :
	$(MAKE) img

# 镜像文件生成

ipl.bin : ipl.nas Makefile
	$(NASK) ipl.nas ipl.bin ipl.lst

lazyos.sys : lazyos.nas Makefile
	$(NASK) lazyos.nas lazyos.sys lazyos.lst

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
	-del lazyos.bin
	-del lazyos.lst

src_only :
	$(MAKE) clean
	-del lazyos.img
