#include <vga.h>
#include <memcpy.h>

#ifdef PhiArchi386
#include <common.h>
#endif

#define MAX_ROWS 25
#define MAX_COLUMNS 80

static p_uint16 *vga_videoMemory = (p_uint16*)0xb8000;
static p_uint16 row = 0, column = 0, tabSize = 4;
enum vga_color background = COLOR_BLACK;
enum vga_color foreground = COLOR_LIGHT_GRAY;

static void __vga_moveCursor(void)
{
    p_uint16 cursorPosition = row * MAX_COLUMNS + column;
    outb(0x3D4, 14);
    outb(0x3D5, cursorPosition >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorPosition);
}

static p_uint8 __vga_getColorCode(void)
{
    return (background << 4) | foreground;
}

static void __vga_clearLine(void)
{
    p_uint16 i = 0, x = row * MAX_COLUMNS;
    p_uint16 colorCode = ((p_uint16) __vga_getColorCode()) << 8;

    for (; i < MAX_COLUMNS; i++)
        vga_videoMemory[x + i] = colorCode;
}

static void __vga_scroll(void)
{
    row--;
    for (p_uint8 i = 1; i < MAX_ROWS; i++)
        libc_memcpy((char*)(vga_videoMemory + i * MAX_COLUMNS),
                    (char*)(vga_videoMemory + (i - 1) * MAX_COLUMNS),
                    2 * MAX_COLUMNS);

    __vga_clearLine();
}

static void __vga_putChar(const char ch)
{
    vga_videoMemory[row * MAX_COLUMNS + column] = ((p_uint16) ch) |
                                                  (((p_uint16)__vga_getColorCode()) << 8);

    column++;
    if (column >= MAX_COLUMNS)
    {
        column = 0;
        row++;

        if (row >= MAX_ROWS)
        {
            __vga_scroll();
        }
    }

}

void vga_clearScreen(void)
{
    p_uint16 k = 0;
    for (p_uint16 i = 0; i < MAX_ROWS; i++)
        for (p_uint16 j = 0; j < MAX_COLUMNS; j++)
            vga_videoMemory[k++] = __vga_getColorCode() << 8;

    row = 0;
    column = 0;
    __vga_moveCursor();
}

void vga_putChar(const char ch)
{
    switch (ch)
    {
        case '\b':
            if (column > 0)
            {
                column--;
                __vga_putChar(' ');
                column--;
            }
            break;

        case '\n':
            row++;
            if (row >= MAX_ROWS)
                __vga_scroll();
            column = 0;
            break;

        case '\t':
            for (p_uint8 i = 0; i < tabSize; i++)
                __vga_putChar(' ');
            break;

        default:
            __vga_putChar(ch);
    };

    __vga_moveCursor();
}

void vga_putString(const char *str)
{
    if (str == 0)
        return;

    p_uint32 i = 0;
    while (str[i])
        vga_putChar(str[i++]);
}

void vga_putSignedNumber(p_s32int number)
{
    if (number < 0)
        vga_putChar('-');

    p_u32int num = -number;
    vga_putUnsignedNumber(num);
}

void vga_putUnsignedNumber(p_u32int number)
{
    p_s8int i = 0;
    char str[20];

    do
    {
        str[i++] = number % 10 + '0';
        number /= 10;
    } while (number);

    i--;
    while (i >= 0)
        vga_putChar(str[i--]);
}

void vga_changeBackground(enum vga_color bg)
{
    background = bg;
}

void vga_changeForeground(enum vga_color fg)
{
    foreground = fg;
}

void vga_putAddress(p_uint32 x, p_uint8 padding, p_uint8 upperCase)
{
    char digits[] = "0123456789ABCDEF";
    char result[10], t;
    p_uint8 i = 0, j;

    if(!upperCase)
        for(j = 10; j < 16; ++j)
            digits[j] += 32;

    while(x)
    {
        result[i++] = digits[x % 16];
        x /= 16;
    }

    if(padding)
        for(; i < 8; ++i) result[i] = '0';
    else
        if(i == 0) result[i++] = '0';

    result[i++] = 'x';
    result[i++] = '0';

    for(j = 0, --i; j < i; ++j, --i)
    {
        t = result[i];
        result[i] = result[j];
        result[j] = t;
    }

    for (i = 0; i < 10; i++)
        vga_putChar(result[i]);
}

