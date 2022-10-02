# SHELL=cmd.exe
TOOLPATH = ../../z_tools/

MAKE     = $(TOOLPATH)make.exe -r
MAKEFONT = $(TOOLPATH)makefont.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe

# 默认动作

default :
	$(MAKE) hankaku.obj

# 镜像文件生成

hankaku.bin : hankaku.txt Makefile
	$(MAKEFONT) hankaku.txt hankaku.bin

hankaku.obj : hankaku.bin Makefile
	$(BIN2OBJ) hankaku.bin hankaku.obj _hankaku

# 其他指令

clean :
	-del *.bin
	-del *.obj

src_only :
	$(MAKE) clean
