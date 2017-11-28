#include <ft_printf.h>



static void		manage_display(t_flag, int *length)
{
	display_flag(t_flag, length);

}

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
		if (str[i] == '%' && str[i + 1] != '%')
		{
//			manage_display(tmp, &length);
			while (str[i] && str[i] != tmp->type)
				i++;
		}
		else
			ft_putchar(str[i]);
		i++;
		length++;
	}
	return (length);
}
