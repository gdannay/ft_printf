/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:16 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/26 14:17:57 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

/*vioid				fill_content(t_flag **tmp, ...)
  {

  }*/

t_flag				*parse_str(char *str)
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
			tmp = check_carac(str, &i, &flag);
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
		if (tmp->width == 0 || tmp->precision == 0)
			fill_wp(&tmp, va_arg(va, int));
		if (tmp->inttype == 1)
			tmp->nb = va_arg(va, int);
		else if (tmp->inttype == 2)
			tmp->st = va_arg(va, char *);
		else if (tmp->inttype == 3)
			tmp->vd = va_arg(va, void *);
		else if (tmp->inttype == 4)
			tmp->unb = va_arg(va, int);
		else if (tmp->inttype == 5)
			tmp->db = va_arg(va, double);
		tmp = tmp->next;
	}

	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d, %d\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype, flag->nb);
	flag = flag->next;
	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype);
	flag = flag->next;
	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d, %s\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype, flag->st);
	flag = flag->next;
	va_end (va);
}

int		main()
{
	ft_printf("% 040i blrggf%lld %.*s", 42, 52, 10, "Blabla");
}
