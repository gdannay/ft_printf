#include "string.h"
#include "stdio.h"
#include "libft/libft.h"
# define BUFF_SIZE 4096

void		add_right(char *buff, char *str, int index, size_t length)
{
	int i;

	i = (int)ft_strlen(buff) + (int)length;
	dprintf(1, "i = %d\n", i);
	while (i - length >= index)
	{
		buff[i] = buff[i - length];
		dprintf(1, "c = %c\n", buff[i - length]);
		i--;
	}
	i = 0;
	while (length > 0)
	{
		buff[index] = str[i];
		index++;
		i++;
		length--;
	}
}

int		main()
{
	char buff[4096];

	buff[0] = 'S';
	buff[1] = 'a';
	buff[2] = 'l';
	buff[3] = 'u';
	buff[4] = 't';
	buff[5] = ' ';
	buff[6] = 'j';
	buff[7] = 'e';
	buff[8] = '\0';
	printf("buff = %s\n", buff);
	add_right(buff, "te", 3, 2);
	printf("buff = %s\n", buff);
}
