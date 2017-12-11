#include "ft_printf.h"
#include <stdio.h>

int		main()
{
	printf("\n%d", ft_printf("%+-###42.6o", 543));
	printf("\n");
	printf("\n%d", printf("%+-###42.6o", 543));
	while(1);
}
