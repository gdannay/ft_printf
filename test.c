#include "includes/ft_printf.h"
#include <stdio.h>

int		main()
{
	unsigned char c;
	c = 0xe1;
	write(1, &c, 1);
	c = 0x88;
	write(1, &c, 1);
	c = 0xb4;
	write(1, &c, 1);
	c = 0x0a;
	write(1, &c, 1);
}
