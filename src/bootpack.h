#define ADR_BOOTINFO 0x0ff0

struct BOOTINFO
{
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
};

// naskfunc.nas
void inthandler21(int *esp);
void inthandler27(int *esp);
void io_out8(int port, int data);
int io_in8(int port);
void io_sti(void);
void load_gdtr(int limit, int addr);
void load_idtr(int limit, int addr);
