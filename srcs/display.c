#include <ft_printf.h>

int			display(char *str, t_flag *flag)
{
	int	i;
	int j;
	int length;
	//	t_flag	*tmp;

	i = 0;
	length = 0;
	printf("Test %d", flag->nb);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '%')
				ft_putchar('%');
			else
			{
				//		manage_display(tmp);
				while (str[i] != typeconv[j])
				{
					j = 0;
					while (j < 22 && str[i] != typeconv[j])
						j++;
					if (str[i] != typeconv[j])
						i++;
				}
			}
		}
		else
			ft_putchar(str[i]);
		i++;
		length++;
	}
	return (length);
}
