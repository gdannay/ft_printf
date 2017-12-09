/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:13:23 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/09 18:52:13 by gdannay          ###   ########.fr       */
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
	if ((int)ft_strlen(new) < tmp->precision && (tmp->intdisplay == 1 || tmp->intdisplay == 6))
	{
		tmptxt = new;
		if ((t2 = ft_bchar('0', (size_t)tmp->precision - ft_strlen(new))) == NULL)
			return (NULL);
		if ((new = ft_strjoin(t2, tmptxt)) == NULL)
			return (NULL);
		ft_strdel(&t2);
		ft_strdel(&tmptxt);
	}
	return (new);
}

char			*display_width(char *new, t_flag *tmp)
{
	char *tmptxt;
	char *t2;

	if (tmp->space == 1 && tmp->plus == 0 && (tmp->intdisplay == 1 || tmp->intdisplay == 6))
		tmp->width = tmp->width - 1;
	if ((int)ft_strlen(new) < tmp->width)
	{
		tmptxt = new;
		if (tmp->minus == 1)
			new = ft_strjoin(tmptxt, t2 = ft_bchar(' ', (size_t)tmp->width - ft_strlen(new)));
		else if (tmp->zero == 1 && tmp->type == 'p')
			new = ft_strjoin(tmptxt, t2 = ft_bchar('0', (size_t)tmp->width - ft_strlen(new)));
		else if (tmp->zero == 1)
			new = ft_strjoin(t2 = ft_bchar('0', (size_t)tmp->width - ft_strlen(new)), tmptxt);
		else
			new = ft_strjoin(t2 = ft_bchar(' ', (size_t)tmp->width - ft_strlen(new)), tmptxt);
		if (t2 == NULL || new == NULL)
			return (NULL);
		if (tmptxt && ft_strncmp(tmptxt, "", 1) != 0)
			ft_strdel(&tmptxt);
		ft_strdel(&t2);
	}
	return (new);
}

static char		*display_plus(char *new, t_flag *tmp)
{
	int i;
	char	*tmptxt;

	i = 0;
	if (tmp->zero == 1 && new[0] == '0')
		new[0] = '+';
	else if (new[0] == ' ')
	{
		while (new[i] && new[i] == ' ')
			i++;
		new[i - 1] = '+';
	}
	else
	{
		tmptxt = new;
		if ((int)ft_strlen(new) == tmp->width)
			new[(int)ft_strlen(new) - 1] = '\0';
		if ((new = ft_strjoin("+", tmptxt)) == NULL)
			return (NULL);
		ft_strdel(&tmptxt);
	}
	return (new);
}

char			*correction_sign(char *new, t_flag *tmp)
{
	int	i;
	char *tmptxt;

	i = 1;
	if (tmp->intdisplay == 1 && tmp->type != 'u' && tmp->type != 'U')
	{
		tmptxt = new;
		if (tmp->nb < 0 && new[0] == '0')
		{
			while (new[i] && new[i] == '0')
				i++;
			new[i] = '0';
			if (tmp->zero == 1 || (int)ft_strlen(new) == tmp->precision)
				new[0] = '-';
			else
			{
				if ((new = ft_strjoin("-", tmptxt)) == NULL)
					return (NULL);
				ft_strdel(&tmptxt);
			}
		}
		else if (tmp->nb < 0 && new[0] == ' ')
		{
			while (new[i] && new[i] == ' ')
				i++;
			if (new[i] && new[i] == '0')
				new[i] = '-';
			i++;
			while (new[i] && new[i] != '-')
				i++;
			if (new[i])
				new[i] = '0';
		}
		else if (tmp->nb >= 0 && tmp->plus == 1)
		{
			if ((new = display_plus(new, tmp)) == NULL)
				return (NULL);
		}
		else if (tmp->space == 1 && tmp->nb >= 0 && tmp->width <= (int)ft_strlen(new))
		{
			if ((new = ft_strjoin(" ", tmptxt)) == NULL)
				return (NULL);
			ft_strdel(&tmptxt);
		}
	}
	return (new);
}
