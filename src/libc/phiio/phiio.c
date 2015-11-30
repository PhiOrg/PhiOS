#include <phiio.h>
#include <vga.h>


void printk(str) char str[];
{

  /* Now you can write the function.
     p_uint32 *p = &str;
     vga_putString(*p);
     p++;
     vga_putUnsignedNumber(*p);
     vga_putChar('\n');
     p++;
     vga_putString(*p);
     p++;
     vga_putUnsignedNumber(*p);
  */

  p_uint32 *p = &str;
  char *s = *p;
 
  int strlen = phistr_len(s); // Optimization: inlining the function call
  p++;
  int i;
  for (i = 1; i < strlen; i++) {
    // Obvious optimizations: storing s[i] in a variable
    if (s[i - 1] == '%' && (s[i] == 'p' || s[i] == 's' || s[i] == 'c' || s[i] == 'd' || s[i] == 'u')) {
      switch(s[i]) {
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
	vga_putAddress(*p, ' ', 1); // TODO: modify
	p++;
	break;
      }
      i++;
    }
    else
      vga_putChar(s[i - 1]);
  }
}

