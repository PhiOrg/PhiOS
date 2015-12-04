#include <keyboard_key.h>
#include <keyboard.h>
#include <vga.h>

#ifdef PhiArch_i386
#include <common.h>
#include <irq.h>
#endif

unsigned char keyboardMap[] = {
                      0, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                      '-', '=', BACKSPACE, TAB, 'q', 'w', 'e', 'r', 't', 'y',
                      'u', 'i', 'o', 'p', '[', ']', ENTER, CTRL, 'a', 's', 'd',
                      'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', LSHIFT, '\\',
                      'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', RSHIFT,
                      '*', ALT, ' ', CAPSLOCK, F1, F2, F3, F4, F5, F6, F7, F8,
                      F9, F10, NUMLOCK, 0, HOME, UP, PGUP,'-', LEFT, '5', RIGHT,
                      '+', END, DOWN, PGDN, INS, DEL, 0, 0, 0, F11, F12
                      };

unsigned char keyboardMapShift[] = { 
                            0, ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(',
                            ')', '_', '+', BACKSPACE, TAB, 'Q', 'W', 'E', 'R',
                            'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', ENTER, CTRL,
                            'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
                            '\"', '~', LSHIFT, '|', 'Z', 'X', 'C', 'V', 'B', 'N',
                            'M', '<', '>', '?', RSHIFT, '*', ALT, ' ', CAPSLOCK,
                            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUMLOCK, 0,
                            HOME, UP, PGUP, '-', LEFT, '5', RIGHT, '+', END, DOWN,
                            PGDN, INS, DEL, 0, 0, 0, F11, F12
                            };

p_uint8 shift = 0, capslock = 0;

static void keyboard_handler(__attribute__ ((unused)) Registers regs)
{
    p_uint8 code;

    code = inb(0x60);

    if (code == 170 || code == 182)
    {
        shift = 0;
        return;
    }

    if (code > 88)
        return;
    
    unsigned char key;
    if (shift)
        key = keyboardMapShift[code];
    else
        key = keyboardMap[code];

    if (key == LSHIFT || key == RSHIFT)
    {
        shift = 1;
        return;
    }

    if (key == BACKSPACE || key == ENTER || key == TAB)
    {
        vga_putChar(key);
        return;
    }

    if (key > 31 && key < 127)
        vga_putChar(key);
}

void keyboard_init(void)
{
    shift = 0;
    isr_registerInterruptHandler(IRQ1, &keyboard_handler);
}

