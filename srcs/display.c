#include <ft_printf.h>

int			display(char *str, t_flag *flag)
{
	int	i;
	int length;
	t_flag	*tmp;

	i = 0;
	length = 0;
	tmp = flag;
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
				while (str[i] && str[i] != tmp->type)
					i++;
			}
		}
		else
			ft_putchar(str[i]);
		i++;
		length++;
	}
	return (length);
}
