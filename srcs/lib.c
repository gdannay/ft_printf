/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:24:19 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/09 19:14:21 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag		*create_flag(void)
{
	t_flag	*new;

	if ((new = (t_flag *)malloc(sizeof(t_flag))) == NULL)
		return (NULL);
	new->minus = 0;
	new->plus = 0;
	new->space = 0;
	new->zero = 0;
	new->hash = 0;
	new->width = -1;
	new->precision = -1;
	new->length = 0;
	new->type = 0;
	new->nb = 0;
	new->unb = 0;
	new->inttype = -1;
	new->db = 0;
	new->n = NULL;
	new->vd = NULL;
	new->st = NULL;
	new->next = NULL;
	new->wst = NULL;
	new->order = 0;
	return (new);
}

void		fill_wp(t_flag *tmp, va_list va)
{
	if (tmp->width == -2)
	{
		tmp->width = va_arg(va, int);
		if (tmp->width < 0)
		{
			tmp->minus = 1;
			tmp->width *= -1;
		}
	}
	if (tmp->width == -3)
	{
		va_arg(va, int);
		tmp->width = tmp->nb;
		if (tmp->width < 0)
		{
			tmp->minus = 1;
			tmp->width *= -1;
		}
	}
	if (tmp->precision == -2)
		tmp->precision = va_arg(va, int);
}
