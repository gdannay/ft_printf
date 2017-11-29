/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/29 19:22:00 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		manage_display(t_flag *tmp)
{
	tmp->ld = 2563.12;
	printf("\n\n%s\n\n", dtoa(tmp));
//	display_flag(t_flag, length);

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
			manage_display(tmp);
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
