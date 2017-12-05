/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 13:40:36 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/05 11:48:42 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_type	typeconv[] =
{
	{'d', 1, 1},
	{'D', 1, 1},
	{'i', 1, 1},
	{'c', 1, 2},
	{'C', 1, 2},
	{'s', 2, 3},
	{'S', 2, 3},
	{'p', 3, 4},
	{'o', 4, 6},
	{'O', 4, 6},
	{'u', 4, 1},
	{'U', 4, 1},
	{'x', 6, 6},
	{'X', 6, 6},
	{'e', 5, 5},
	{'E', 5, 5},
	{'f', 5, 5},
	{'F', 5, 5},
	{'g', 5, 5},
	{'G', 5, 5},
	{'a', 5, 5},
	{'A', 5, 5},
};

static void		check_length(t_flag *new, char *str, int *i)
{
	if (str[*i] == 'h' && str[*i + 1] == 'h')
	{
		*i = *i + 1;
		new->length = 1;
	}
	else if (str[*i] == 'h')
		new->length = 2;
	else if (str[*i] == 'l' && str[*i + 1] == 'l')
	{
		*i = *i + 1;
		new->length = 3;
	}
	else if (str[*i] == 'l')
		new->length = 4;
	else if (str[*i] == 'L')
		new->length = 5;
	else if (str[*i] == 'z')
		new->length = 6;
	else if (str[*i] == 'j')
		new->length = 7;
	else if (str[*i] == 't')
		new->length = 8;
	else
		return;
	*i = *i + 1;
}

static void		check_wp(char *str, int *i, t_flag *new)
{
	if (str[*i] > '0' && str[*i] <= '9')
	{
		new->width = ft_atoi(str + *i);
		*i = *i + length_nbr(new->width);
	}
	else if (str[*i] == '*')
	{
		new->width = -2;
		*i = *i + 1;
	}
	if (str[*i] == '.')
	{
		*i = *i + 1;
		if (str[*i] == '*')
		{
			new->precision = -2;
			*i = *i + 1;
		}
		else if (str[*i] >= '0' && str[*i] <= '9')
		{
			new->precision = ft_atoi(str + *i);
			*i = *i + length_nbr(new->precision);
		}
		else
			new->precision = 0;
	}
}

static void		manage_flag(char *str, int i, t_flag **new)
{
	if (str[i] == '-')
		(*new)->minus = 1;
	if (str[i] == '+')
		(*new)->plus = 1;
	if (str[i] == ' ')
		(*new)->space = 1;
	if (str[i] == '0')
		(*new)->zero = 1;
	if (str[i] == '#')
		(*new)->hash = 1;
	if ((*new)->minus == 1)
		(*new)->zero = 0;
}

t_flag		*check_carac(char *str, int *i)
{
	t_flag		*new;
	int			j;

	new = create_flag();
	j = 0;
/*	if (str[*i] > '0' && str[*i] <= '9')
	{
		if (str[*i + length_nbr(ft_atoi(str[*i]))] == '$')
		{
			new->order = ft_atoi(str[*i]);
			i = *i + length_nbr(new->order);
		}
	}*/
	while (str[*i] == '-' || str[*i] == '+' || str[*i] == ' ' || str[*i] == '0' || str[*i] == '#')
	{
		manage_flag(str, *i, &new);
		*i = *i + 1;
	}
	check_wp(str, i, new);
	check_length(new, str, i);
	new->type = str[*i];
	while (j < 22)
	{
		if (new->type == typeconv[j].type)
		{
			new->inttype = typeconv[j].conv;
			new->intdisplay = typeconv[j].display;
		}
		j++;
	}
	return (new);
}
