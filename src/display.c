#include "display.h"

void init_bg_color(Display *display)
{
    drawBox(display->vram, 0, 0, display->width, display->height, display->bgcolor);
}

void init_mouse_cursor8(char *mouse, char bc)
{
    static char cursor[16][16] = {
        "**************..",
        "*OOOOOOOOOOO*...",
        "*OOOOOOOOOO*....",
        "*OOOOOOOOO*.....",
        "*OOOOOOOO*......",
        "*OOOOOOO*.......",
        "*OOOOOOO*.......",
        "*OOOOOOOO*......",
        "*OOOO**OOO*.....",
        "*OOO*..*OOO*....",
        "*OO*....*OOO*...",
        "*O*......*OOO*..",
        "**........*OOO*.",
        "*..........*OOO*",
        "............*OO*",
        ".............***"};
    int x, y;

    for (y = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++)
        {
            if (cursor[y][x] == '*')
            {
                mouse[y * 16 + x] = COL8_000000;
            }
            if (cursor[y][x] == 'O')
            {
                mouse[y * 16 + x] = COL8_FFFFFF;
            }
            if (cursor[y][x] == '.')
            {
                mouse[y * 16 + x] = bc;
            }
        }
    }
    return;
}

void putImg(char *vram, int x, int y, char *img, int col, int row, char color)
{
    char ch;
    int i, j, k;

    for (j = 0; j < row; j++)
    {
        for (i = 0; i < col; i++)
        {
            ch = img[j * col + i];
            drawPixel(vram, x + i, y + j, img[j * col + i]);
        }
    }
}

void putChar(char *vram, int x, int y, char *fonts, int col, int row, char color)
{
    char ch;
    int i, j, k;

    for (j = 0; j < row; j++)
    {
        for (i = 0; i < col; i++)
        {
            ch = fonts[j * col + i];
            for (k = 0; k < 8; k++)
            {
                if ((ch & (0x80 >> k)) != 0)
                {
                    drawPixel(vram, x + i * 8 + k, y + j, color);
                }
            }
        }
    }
}

void putStr(char *vram, int x, int y, char *s, char color)
{
    int idx;

    for (s, idx = 0; *s != '\0'; s++, idx++)
    {
        puthankaku(vram, x + 8 * idx, y, *s, color);
    }
}

/*
hankaku
*/
void puthankaku(char *vram, int x, int y, char ch, char color)
{
    putfont8(vram, x, y, hankaku + ch * 16, color);
}
/*
8x16
*/
void putfont8(char *vram, int x, int y, char *fonts, char color)
{
    putChar(vram, x, y, fonts, 1, 16, color);
}

void drawBox(char *vram, int x, int y, int w, int h, int color)
{
    int i, j;
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            drawPixel(vram, x + j, y + i, color);
        }
    }
}

void drawPixel(char *vram, int x, int y, int color)
{
    int i = (y * 320 + x);
    vram[i] = color;
}
