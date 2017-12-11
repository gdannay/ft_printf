/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/11 18:14:58 by gdannay          ###   ########.fr       */
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
	else if (tmp->intdisplay == 9)
		length = manage_wstring(tmp);
	else if (tmp->intdisplay == 8)
		length = manage_uni(tmp);
	else if (tmp->intdisplay == 2 || tmp->intdisplay == 9)
		length = manage_char(tmp);
	else if (tmp->intdisplay == 3)
		length = manage_string(tmp);
	return (length);
}

static int		display_normal(char *str, int *i)
{
	int length;
	int j;

	length = 0;
	j = *i;
	while (str[*i] && str[*i] != '%')
	{
		length++;
		*i = *i + 1;
	}
	write(1, str + j, (size_t)(*i - j));
	return (length);
}

static void		manage_undefined(char *str, int *i, t_flag *tmp)
{
	*i = *i + 1;
	while (str[*i] && str[*i] != tmp->type)
		*i = *i + 1;
	if (tmp && str[*i] == tmp->type)
		tmp = tmp->next;
}

int				display(char *str, t_flag *flag)
{
	int		i;
	int		length;
	t_flag	*tmp;

	i = 0;
	length = 0;
	tmp = flag;
	while (str && str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] && tmp->inttype != 0)
		{
			if (tmp)
				length += manage_display(tmp);
			i++;
			while (str[i + 1] && str[i] != tmp->type)
				i++;
			tmp = tmp->next;
			i++;
		}
		else if (str[i] == '%' && ((!tmp) || tmp->inttype == 0))
			manage_undefined(str, &i, tmp);
		else
			length += display_normal(str, &i);
	}
	return (length);
}
