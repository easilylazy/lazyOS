; lazy-os
; TAB=4
		ORG		0Xc200			; 指明程序装载地址
		MOV		DL,1
		MOV	SI, msg
putloop:
		MOV		AH,0x02			; 换行
		ADD		DL,1			; col++
		MOV		DH,18			; height
		INT		0x10			; 调用显卡BIOS
		MOV		AL,[SI]
		ADD		SI,1			; 给SI加1
		CMP		AL,0
		JE		fin
		MOV		AH,0x0e			; 显示一个文字
		MOV		BX,25			; 指定字符颜色
		INT		0x10			; 调用显卡BIOS

		JMP		putloop
fin:
		HLT						; 让CPU停止，等待指令
		JMP		fin				; 无限循环

msg:
		DB		0x0a, 0x0a		; 换行两次
		DB		"good night!"
		DB		0x0a			; 换行
		DB		0
