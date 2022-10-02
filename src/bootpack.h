#define ADR_BOOTINFO 0x0ff0

struct BOOTINFO
{
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
};
