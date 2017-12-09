/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:23:15 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/09 16:44:05 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*display_hash_blank(char *new, t_flag *tmp)
{
	char *tmptxt;

	if (tmp->type == 'p' || (tmp->intdisplay == 6 && tmp->hash == 1 && tmp->zero == 0))
	{
		tmptxt = new;
		if (tmp->type == 'x' || tmp->type == 'p')
			new = ft_strjoin("0x", new);
		else if (tmp->type == 'X')
			new = ft_strjoin("0X", new);
		else if (tmp->type == 'o' || tmp->type == 'O')
			new = ft_strjoin("0", new);
		if (new == NULL)
			return (NULL);
		ft_strdel(&tmptxt);
	}
	return (new);
}

static char			*display_hash_zero(char *new, t_flag *tmp)
{
	char *tmptxt;

	if ((tmp->type == 'X' || tmp->type == 'x') && tmp->hash == 1 && tmp->zero == 1)
	{
		tmptxt = new;
		if (new[0] == '0' && new[1] == '0')
			new[1] = tmp->type;
		else if (new[0] == '0' && new[1] != '0')
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
	}
	return (new);
}

int				display_flag(char *new, t_flag *tmp)
{
	int		length;

	if ((new = display_precision(new, tmp)) == NULL && tmp->precision != 0)
		return (0);
	if ((tmp->nb == 0 && tmp->unb == 0) && (tmp->type == 'x' 
				|| tmp->type == 'X' || (tmp->type == 'o' && tmp->precision != 0)))
		tmp->hash = 0;
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
