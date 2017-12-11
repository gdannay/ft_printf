/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:23:15 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/11 16:20:49 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*display_precision(char *new, t_flag *tmp)
{
	char *tmptxt;
	char *t2;

	if (tmp->nb < 0 && tmp->precision > 0)
		tmp->precision = tmp->precision + 1;
	if (tmp->precision >= 0 && (tmp->intdisplay == 1 || tmp->intdisplay == 6))
		tmp->zero = 0;
	if ((int)ft_strlen(new) < tmp->precision
			&& (tmp->intdisplay == 1 || tmp->intdisplay == 6))
	{
		tmptxt = new;
		if ((t2 = ft_bchar('0',
						(size_t)tmp->precision - ft_strlen(new))) == NULL)
			return (NULL);
		if ((new = ft_strjoin(t2, tmptxt)) == NULL)
			return (NULL);
		ft_strdel(&t2);
		ft_strdel(&tmptxt);
	}
	return (new);
}

static char		*display_hash_blank(char *new, t_flag *tmp)
{
	char *tmptxt;

	if (tmp->type == 'p' ||
			(tmp->intdisplay == 6 && tmp->hash == 1 && tmp->zero == 0))
	{
		tmptxt = new;
		if (tmp->type == 'x' || tmp->type == 'p')
			new = ft_strjoin("0x", new);
		else if (tmp->type == 'X')
			new = ft_strjoin("0X", new);
		else if ((tmp->type == 'o' || tmp->type == 'O')
				&& ((int)ft_strlen(new) < tmp->precision
					|| tmp->precision <= 0))
			new = ft_strjoin("0", new);
		if (new == NULL)
			return (NULL);
		if (new != tmptxt)
			ft_strdel(&tmptxt);
	}
	return (new);
}

static char		*display_hash_zero_join(t_flag *tmp, char *new)
{
	char *tmptxt;

	tmptxt = new;
	if (new[0] == '0' && new[1] != '0')
	{
		new[0] = tmp->type;
		if ((new = ft_strjoin("0", tmptxt)) == NULL)
			return (NULL);
		ft_strdel(&tmptxt);
	}
	else if (new[0] != 0)
	{
		if (tmp->type == 'x')
			new = ft_strjoin("0x", tmptxt);
		else if (tmp->type == 'X')
			new = ft_strjoin("0X", tmptxt);
		if (new == NULL)
			return (NULL);
		ft_strdel(&tmptxt);
	}
	return (new);
}

static char		*display_hash_zero(char *new, t_flag *tmp)
{
	if ((tmp->type == 'X' || tmp->type == 'x')
			&& tmp->hash == 1 && tmp->zero == 1)
	{
		if (new[0] == '0' && new[1] == '0')
			new[1] = tmp->type;
		else
			new = display_hash_zero_join(tmp, new);
	}
	return (new);
}

int				display_flag(char *new, t_flag *tmp)
{
	int		length;

	if ((new = display_precision(new, tmp)) == NULL && tmp->precision != 0)
		return (0);
	if ((tmp->nb == 0 && tmp->unb == 0) && (tmp->type == 'x'
				|| tmp->type == 'X' ||
				(tmp->type == 'o' && tmp->precision != 0)))
		tmp->hash = 0;
	if (tmp->space == 1 && tmp->plus == 0
			&& (tmp->intdisplay == 1 || tmp->intdisplay == 6))
		tmp->width = tmp->width - 1;
	if (((new = display_hash_blank(new, tmp)) == NULL && tmp->precision != 0)
			|| (new = display_width(new, tmp)) == NULL
			|| (new = display_hash_zero(new, tmp)) == NULL
			|| (new = correction_sign(new, tmp)) == NULL)
		return (0);
	if (tmp->nb != 0 || (tmp->type != 'C' && tmp->type != 'c'))
		write(1, new, ft_strlen(new));
	length = (int)ft_strlen(new);
	ft_strdel(&new);
	return (length);
}
