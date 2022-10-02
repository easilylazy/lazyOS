#include <stdio.h>
#include "bootpack.h"
#include "display.h"

void LazyMain(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)0x0ff0;
    Display display = {binfo->vram, binfo->scrnx, binfo->scrny, COL16_RED};
    init_bg_color(display.vram, display.bgcolor, display.width, display.height);
    int idx;
    char mouse[256] = {0};
    char *s;
    sprintf(s, "scrnx=%d, scrny=%d", binfo->scrnx, binfo->scrny);
    for (idx = 0; idx <= 15; idx++)
    {
        putStr(binfo->vram, 0, idx * 20, s, idx);
    }
    for (;;)
    {
        io_hlt();
    }
}
