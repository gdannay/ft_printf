/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:16 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/22 18:33:54 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

void				check_length(t_flag *new, char *str, int *i)
{
	if (str[*i] == 'h')
	{
		if (str[*i + 1] == 'h')
		{
			*i = *i + 1;
			new->length = 1;
		}
		else
			new->length = 2;
	}
	else if (str[*i] == 'l')
	{
		if (str[*i + 1] == 'l')
		{
			*i = *i + 1;
			new->length = 3;
		}
		else
			new->length = 4;
	}
	else if (str[*i] == 'L')
		new->length = 5;
	else if (str[*i] == 'z')
		new->length = 6;
	else if (str[*i] == 'j')
		new->length = 7;
	else if (str[*i] == 't')
		new->length = 8;
	*i = *i + 1;
}


void				check_wp(char *str, int *i, t_flag *new)
{
	if (str[*i] == '.')
	{
		if (str[*i + 1] == '*')
		{
			new->precision = 0;
			*i = *i + 2;
		}
		else
		{
			*i = *i + 1;
			new->precision = ft_atoi(str + *i);
			*i = *i + length_nbr(new->width);
		}
	}
	else if (str[*i] == '*')
	{
		printf("here3\n");
		new->width = 0;
		*i = *i + 1;
	}
	if (str[*i] > '0' && str[*i] <= '9')
	{
		printf("here5\n");
		new->width = ft_atoi(str + *i);
		*i = *i + length_nbr(new->width);	
	}
}

static t_flag		*check_carac(char *str, int *i, t_flag **flag)
{
	t_flag		*tmp;
	t_flag		*new;

	tmp = (*flag);
	new = create_flag();
//	printf("%c\n", str[*i]);
	while (str[*i] == '-' || str[*i] == '+' || str[*i] == ' ' || str[*i] == '0' || str[*i] == '#')
	{
		printf("here1\n");
		manage_flag(str, *i, &new);
		*i = *i + 1;
	}
	check_wp(str, i, new);
	check_length(new, str, i);
	new->type = str[*i];
//	printf("test = %c i = %d\n", str[*i], *i);

	return (new);
}

void				ft_printf(char *str, ...)
{
	va_list		va;
	va_start	(va, str);
	int			i;
	t_flag		*flag;
	t_flag		*tmp;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '%')
				ft_putchar('%');
			else
			{
				tmp = check_carac(str, &i, &flag);
				if (tmp->width = 0)
				   tmp->width = va_arg(va, int);
				else if (tmp->precision = 0)
				   tmp->precision = va_arg(va, int);
				
		}
		i++;
	}
	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, tzpe = %c\n", tmp->minus, tmp->plus, tmp->space, tmp->zero, tmp->hash, tmp->width, tmp->precision, tmp->length, tmp->type);
	va_end (va);
}

int		main()
{
	ft_printf("%# 40hhi");
}
