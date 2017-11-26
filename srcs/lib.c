/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:24:19 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/26 14:15:47 by gdannay          ###   ########.fr       */
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
	new->lnb = 0;
	new->inttype = 0;
	new->db = 0;
	new->unb = 0;
	new->n = NULL;
	new->vd = NULL;
	new->st = NULL;
	new->next = NULL;
	new->order = 0;
	return (new);
}

int			length_nbr(int n)
{
	int		taille;

	taille = 0;
	if (n <= 0)
		taille++;
	while (n)
	{
		n /= 10;
		taille++;
	}
	return (taille);
}

void		fill_wp(t_flag **tmp, int n)
{
	if ((*tmp)->width == 0)
		(*tmp)->width = n;
	if ((*tmp)->precision == 0)
		(*tmp)->precision = n;
}
