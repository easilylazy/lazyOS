#include <stdio.h>
#include "bootpack.h"
#include "display.h"
#include "irq.h"
#include "gdt.h"

void LazyMain(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)0x0ff0;
    Display display = {binfo->vram, binfo->scrnx, binfo->scrny, COL16_RED};
    init_bg_color(&display);
    // init gdt
    init_gdtidt();
    // init pic
    init_pic();
    io_sti();                /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */
    io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
    for (;;)
    {
        io_hlt();
    }
}
