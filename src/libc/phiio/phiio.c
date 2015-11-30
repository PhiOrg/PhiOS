#include <phiio.h>
#include <vga.h>
#include <phistr.h>


void printk(str) char str[];
{


  p_uint32 *p = &str;
 
  int strlen = phistr_len(str);
  p++;
  p_uint32 i;
  for (i = 1; i < strlen; i++) {

    if (str[i - 1] == '%' && (str[i] == 'p'
                           || str[i] == 's'
                           || str[i] == 'c'
                           || str[i] == 'd'
                           || str[i] == 'u')) {
      switch (str[i]) {
      case 's':
        	vga_putString(*p);
        	p++;
        	break;
      case 'd':
        	vga_putSignedNumber(*p);
        	p++;
        	break;
      case 'u':
          vga_putUnsignedNumber(*p);
          p++;
          break;
      case 'c':
        	vga_putChar(*p);
        	p++;
        	break;
      case 'p':
        	vga_putAddress(*p, 1, 1);
        	p++;
        	break;
      }

      i++;
    }
    else
      vga_putChar(str[i - 1]);
  }
}

