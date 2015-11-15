#ifndef PhiOS_vga
#define PhiOS_vga

#include <sys/types.h>

enum vga_color
{
    COLOR_WHITE         = 15,
    COLOR_BLACK         = 0,
    COLOR_BLUE          = 1,
    COLOR_GREEN         = 2,
    COLOR_CYAN          = 3,
    COLOR_RED           = 4,
    COLOR_MAGENTA       = 5,
    COLOR_BROWN         = 6,
    COLOR_YELLOW        = 14,
    COLOR_DARK_GRAY     = 8,
    COLOR_LIGHT_GRAY    = 7,
    COLOR_LIGHT_BLUE    = 9,
    COLOR_LIGHT_GREEN   = 10,
    COLOR_LIGHT_CYAN    = 11,
    COLOR_LIGHT_RED     = 12,
    COLOR_LIGHT_MAGENTA = 13,
};

void vga_clearScreen();

void vga_putChar(const char);

void vga_putString(const char*);

void vga_putSignedNumber(p_s32int);

void vga_putUnsignedNumber(p_u32int);

void vga_changeBackground(enum vga_color);

void vga_changeForeground(enum vga_color);

void vga_putAddress(p_cuint32 x, p_cuint8 padding, p_cuint8 upperCase);

#endif

