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

lazyos.img : ipl.bin Makefile
	$(TOOLPATH)edimg.exe   imgin:$(TOOLPATH)fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0   imgout:lazyos.img

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

src_only :
	$(MAKE) clean
	-del lazyos.img
