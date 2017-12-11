/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:13:23 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/11 16:30:10 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*manage_zero(t_flag *tmp, char *tmptxt, char *t2)
{
	char *new;

	new = NULL;
	if (tmp->type == 'p')
		new = ft_strjoin(tmptxt, t2);
	else
		new = ft_strjoin(t2, tmptxt);
	if (new == NULL)
		return (NULL);
	return (new);
}

char			*display_width(char *new, t_flag *tmp)
{
	char *tmptxt;
	char *t2;

	if ((int)ft_strlen(new) < tmp->width)
	{
		tmptxt = new;
		if ((t2 = ft_bchar(' ', (size_t)tmp->width - ft_strlen(new))) == NULL)
			return (NULL);
		if (tmp->minus == 1)
			new = ft_strjoin(tmptxt, t2);
		else if (tmp->zero == 1)
		{
			ft_strdel(&t2);
			if (!(t2 = ft_bchar('0', (size_t)tmp->width - ft_strlen(new))))
				return (NULL);
			new = manage_zero(tmp, tmptxt, t2);
		}
		else
			new = ft_strjoin(t2, tmptxt);
		if (new == NULL)
			return (NULL);
		ft_strdel(&tmptxt);
		ft_strdel(&t2);
	}
	return (new);
}

static char		*display_plus(char *new, t_flag *tmp)
{
	int		i;
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

static char		*correction_neg(char *new, t_flag *tmp, int i, char *tmptxt)
{
	while (new[i] && new[i] == new[0])
		i++;
	if (new[0] == '0')
	{
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
	else if (new[0] == ' ')
	{
		if (new[i] && new[i] == '0')
			new[i] = '-';
		i++;
		while (new[i] && new[i] != '-')
			i++;
		if (new[i])
			new[i] = '0';
	}
	return (new);
}

char			*correction_sign(char *s, t_flag *tmp)
{
	int		i;
	char	*tmptxt;

	i = 1;
	if (tmp->intdisplay == 1 && tmp->type != 'u' && tmp->type != 'U')
	{
		tmptxt = s;
		if (tmp->nb < 0)
		{
			if ((s = correction_neg(s, tmp, 1, tmptxt)) == NULL)
				return (NULL);
		}
		else if (tmp->nb >= 0 && tmp->plus == 1)
		{
			if ((s = display_plus(s, tmp)) == NULL)
				return (NULL);
		}
		else if (tmp->space && tmp->nb >= 0 && tmp->width <= (int)ft_strlen(s))
		{
			if ((s = ft_strjoin(" ", tmptxt)) == NULL)
				return (NULL);
			ft_strdel(&tmptxt);
		}
	}
	return (s);
}
