extern char hankaku[4096];

#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

#define COL16_YELLOW 14
#define COL16_RED 12
#define COL16_GREEN 10
#define COL16_BLUE 1
#define COL16_WHITE 15
#define COL16_BLACK 0
#define COL16_GRAY 8
#define COL16_LIGHT_GRAY 7
#define COL16_DARK_GRAY 9
#define COL16_DARK_BLUE 4
#define COL16_DARK_GREEN 2
#define COL16_DARK_RED 5
#define COL16_DARK_YELLOW 6
#define COL16_DARK_PURPLE 13
#define COL16_DARK_CYAN 3

typedef struct Display
{
    char *vram;
    int width;
    int height;
    int bgcolor;
} Display;

void drawPixel(char *vram, int x, int y, int color);
void putChar(char *vram, int x, int y, char *fonts, int col, int row, char color);
void drawBox(char *vram, int x, int y, int w, int h, int color);
void putfont8(char *vram, int x, int y, char *fonts, char color);
void putStr(char *vram, int x, int y, char *s, char color);
void init_mouse_cursor8(char *mouse, char bc);
void init_bg_color(Display *display);
