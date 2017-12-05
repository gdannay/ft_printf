/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:23:15 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/05 11:21:09 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*display_hash_blank(char *new, t_flag *tmp)
{
	char *tmptxt;

	tmptxt = new;
	if (tmp->type == 'x')
		new = ft_strjoin("0x", tmptxt);
	else if (tmp->type == 'X')
		new = ft_strjoin("0X", tmptxt);
	else if (tmp->type == 'o' || tmp->type == 'O')
		new = ft_strjoin("0", tmptxt);
	return (new);
}

static char			*display_hash_zero(char *new, t_flag *tmp)
{
	char *tmptxt;

	tmptxt = new;
	if (tmp->type == 'x' || tmp->type == 'X')
	{
		if (new[0] == '0' && new[1] == '0')
			new[1] = tmp->type;
		else if (new[0] == '0' && new[1] != '0')
		{
			new[0] = tmp->type;
			new = ft_strjoin("0", tmptxt);
		}
		else if (new[0] != 0)
		{
			if (tmp->type == 'x')
				new = ft_strjoin("0x", tmptxt);
			if (tmp->type == 'X')
				new = ft_strjoin("0X", tmptxt);
		}
	}
	return (new);
}

static char		*correction_sign(char *new, t_flag *tmp)
{
	int	i;

	i = 1;
	if (tmp->nb < 0 && tmp->zero == 1 && new[0] == '0')
	{
		new[0] = '-';
		while (new[i] && new[i] == '0')
			i++;
		new[i] = '0';
	}
	else if (tmp->nb < 0 && new[0] == '0')
	{
		while (new[i] && new[i] == '0')
			i++;
		new[i] = '0';
		new = ft_strjoin("-", new);
	}
	else if (tmp->nb >= 0 && tmp->plus == 1 && tmp->zero == 1 && new[0] == '0')
	{
		new[0] = '+';
		while (new[i] && new[i] != '0')
			i++;
		new[i] = '0';
	}
	else if (tmp->nb >= 0 && tmp->plus == 1 && new[0] == ' ')
	{
		while (new[i] && new[i] == ' ')
			i++;
		new[i - 1] = '+';
	}
	else if (tmp->nb >= 0 && tmp->plus == 1)
	{
		if ((int)ft_strlen(new) == tmp->width)
		{
			new = ft_strjoin("+", new);
			new[(int)ft_strlen(new) - 1] = '\0';
		}
		else
			new = ft_strjoin("+", new);
	}
	else if (tmp->space == 1 && tmp->nb >= 0 && tmp->width < (int)ft_strlen(new))
		new = ft_strjoin(" ", new);
	return (new);
}

char		*display_flag(char *new, t_flag *tmp)
{
	char *tmptxt;

	tmptxt = new;
	if ((int)ft_strlen(new) < tmp->precision && (tmp->intdisplay == 1 || tmp->intdisplay == 6))
	{
		new = ft_strjoin(ft_bchar('0', (size_t)tmp->precision - ft_strlen(new)), tmptxt);
		tmp->zero = 0;
	}	
	if ((tmp->nb == 0 && tmp->unb == 0) && (tmp->type == 'x' || tmp->type == 'X' || (tmp->type == 'o' && tmp->precision != 0)))
		tmp->hash = 0;
	if (tmp->intdisplay == 6 && tmp->hash == 1 && tmp->zero == 0)
		new = display_hash_blank(new, tmp);
	//	free(tmptxt);
	if ((int)ft_strlen(new) < tmp->width)
	{
		tmptxt = new;
		if (tmp->minus == 1)
			new = ft_strjoin(tmptxt, ft_bchar(' ', (size_t)tmp->width - ft_strlen(new)));
		else if (tmp->zero == 1)
			new = ft_strjoin(ft_bchar('0', (size_t)tmp->width - ft_strlen(new)), tmptxt);
		else
			new = ft_strjoin(ft_bchar(' ', (size_t)tmp->width - ft_strlen(new)), tmptxt);
		//		free(tmptxt);
	}
	if (tmp->intdisplay == 6 && tmp->hash == 1 && tmp->zero == 1)
		new = display_hash_zero(new, tmp);
	if (tmp->intdisplay == 1 && tmp->type != 'u' && tmp->type != 'U')
		new = correction_sign(new, tmp);
	return (new);
}
