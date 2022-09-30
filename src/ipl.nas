; lazy-os
; TAB=4

CYLS	EQU		10				; 声明CYLS
		ORG		0X7c00			; 指明程序装载地址

; 标准FAT12格式软盘专用的代码 Stand FAT12 format floppy code

		JMP		entry
		DB		0x90
		DB		"LAZY-IPL"		; 启动扇区名称（8字节）
		DW		512				; 每个扇区（sector）大小（必须512字节）
		DB		1				; 簇（cluster）大小（必须为1个扇区）
		DW		1				; FAT起始位置（一般为第一个扇区）
		DB		2				; FAT个数（必须为2）
		DW		224				; 根目录大小（一般为224项）
		DW		2880			; 该磁盘大小（必须为2880扇区1440*1024/512）
		DB		0xf0			; 磁盘类型（必须为0xf0）
		DW		9				; FAT的长度（必须为9扇区）
		DW		18				; 一个磁道（track）有几个扇区（必须为18）
		DW		2				; 磁头数（必须是2）
		DD		0				; 不使用分区，必须是0
		DD		2880			; 重写一次磁盘大小
		DB		0,0,0x29		; 意义不明（固定）
		DD		0xffffffff		; （可能是）卷标号码
		DB		"LAZY-OS    "	; 磁盘的名称（必须为11字，不足填空格）
		DB		"FAT12   "		; 磁盘格式名称（必须为8字，不足填空格）
		RESB	18				; 先空出18字节

; 程序主体

entry:
		MOV		AX,0			; 初始化寄存器
		MOV		SS,AX
		MOV		SP,0x7c00
		MOV		DS,AX
		MOV		ES,AX
; read disk
		MOV AH, 0X02
		MOV DL, 0	; DRIVE
		MOV CH, 0	; cylinder
		MOV DH, 0	; side
		MOV CL, 2	; sector(base=1), 1st sector is ipl (this file)
		MOV AL, 1	; num of sector
		MOV BX, 0X0820	; load here
		MOV ES, BX
		MOV BX, 0
		INT 0X13
readloop:
		MOV SI, 0
retry:
		MOV AH, 0X02
		MOV DL, 0x00	; DRIVE
		MOV AL, 1	; num of sector
		MOV BX, 0
		INT 0X13
		JNC next
		ADD SI, 1
		CMP SI, 5
		JAE error
		MOV AH, 0X00
		MOV DL, 0X00
		INT 0X13
		JMP retry
next:
		MOV AX, ES
		ADD AX, 0X0020 
		MOV ES, AX
		ADD CL, 1
		CMP CL, 18
		JBE readloop

		MOV CL, 1
		ADD	DH, 1	; another side
		CMP DH, 1	;
		JBE readloop
		
		MOV DH, 0
		ADD CH, 1
		CMP CH, CYLS
		JB readloop
		MOV SI, msg
		JBE putloop
error:
		MOV	SI, errmsg
putloop:
		MOV		AL,[SI]
		ADD		SI,1			; 给SI加1
		CMP		AL,0
		JE		fin
		MOV		AH,0x0e			; 显示一个文字
		MOV		BX,25			; 指定字符颜色
		INT		0x10			; 调用显卡BIOS
		MOV		AH,0x02			; 换行
		ADD		DL,1			; col++
		MOV		DH,20			; height
		INT		0x10			; 调用显卡BIOS
		JMP		putloop
fin:
		MOV		[0x0ff0],CH		; 引导扇区柱面数（见asmhead.nas)
		JMP		0xc200			; go to lazyos

msg:
		DB		0x0a, 0x0a		; 换行两次
		DB		"good morning, world"
		DB		0x0a, 0x0a		; 换行两次
		DB		0x0a			; 换行
		DB		0
errmsg:
		DB		0x0a, 0x0a		; 换行两次
		DB		"farewell, world"
		DB		0x0a			; 换行
		DB		0

		RESB	0x7dfe-$		; 填写0x00直到0x001fe

		DB		0x55, 0xaa
