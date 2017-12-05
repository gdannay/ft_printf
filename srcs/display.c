/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/05 15:40:43 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		manage_display(t_flag *tmp)
{
	int		length;

	length = 0;
	if (tmp->intdisplay == 1 || tmp->intdisplay == 6)
		length = manage_nb(tmp);
	else if (tmp->intdisplay == 2) 
		length = manage_char(tmp);
	else if (tmp->intdisplay == 3)
		length = manage_string(tmp);
	else if (tmp->intdisplay == 4)
		length = display_flag(utoa_base(tmp, HEXAMIN), tmp);
	else if (tmp->type == '%')
		length = display_flag(chartostr('%'), tmp);
//	else if (tmp->intdisplay == 5) 
		//new = manage_db(tmp);
	return (length);
}

int			display(char *str, t_flag *flag)
{
	int	i;
	int length;
	int	j;
	t_flag	*tmp;

	i = 0;
	j = 0;
	length = 0;
	tmp = flag;
	while (str && str[i] != '\0')
	{
		if (str[i] == '%')
		{
			length += manage_display(tmp);
			i++;
			while (str[i + 1] && str[i] != tmp->type)
				i++;
			tmp = tmp->next;
		i++;
		}
		else
		{
			j = i;
			while (str[i] && str[i] != '%')
			{
				length++;
				i++;
			}
			write(1, str + j, (size_t)(i - j));
		}
	}
	return (length);
}
