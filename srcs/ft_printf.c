/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:16 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/01 11:00:42 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static t_flag			*parse_str(char *str)
{
	t_flag		*flag;
	t_flag		*tmp;
	t_flag		*tmp2;
	int			i;

	flag = NULL;
	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			tmp = check_carac(str, &i);
			if (flag == NULL)
				flag = tmp;
			else
				tmp2->next = tmp;
			tmp2 = tmp;
		}
		i++;
	}
	return (flag);
}

static void			fill_content(va_list va, t_flag *tmp)
{
		if (tmp->width == 0 || tmp->precision == 0)
			fill_wp(&tmp, va_arg(va, int));
		if (tmp->length == 3 && tmp->inttype == 4)
			tmp->unb = va_arg(va, unsigned long long);
		else if (tmp->length == 3)
			tmp->nb = va_arg(va, long long);
		else if (tmp->length == 4)
			tmp->nb = va_arg(va, long);
		else if (tmp->length == 5)
			tmp->ld = va_arg(va, long double);
		else if (tmp->length == 6)
			tmp->sizet = va_arg(va, size_t);
		else if (tmp->length == 7)
			tmp->nb = va_arg(va, intmax_t);
		else if (tmp->inttype == 1)
			tmp->nb = va_arg(va, int);
		else if (tmp->inttype == 2)
			tmp->st = va_arg(va, char *);
		else if (tmp->inttype == 3)
			tmp->vd = va_arg(va, void *);
		else if (tmp->inttype == 4)
			tmp->unb = va_arg(va, unsigned int);
		else if (tmp->inttype == 5)
			tmp->db = va_arg(va, double);
}

void				ft_printf(char *str, ...)
{
	va_list		va;
	va_start	(va, str);
	t_flag		*flag;
	t_flag		*tmp;

	flag = parse_str(str);
	tmp = flag;
	while (tmp)
	{
		fill_content(va, tmp);
		tmp = tmp->next;
	}
	display(str, flag);

//	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d, %d\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype, flag->nb);
//	flag = flag->next;
//	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype);
//	flag = flag->next;
//	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d, %s\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype, flag->st);
//	flag = flag->next;
	va_end (va);
}

int		main()
{
	ft_printf("\n% 040i blrggf%lld %.*s", 42, 52, 10, "Blabla");
}
