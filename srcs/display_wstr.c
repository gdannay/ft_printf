/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_wstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:50:28 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/11 11:10:49 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*zero_precision(t_flag *tmp)
{
	char	*tmptxt;
	int		rep;
	int		prec;

	tmptxt = NULL;
	rep = 0;
	prec = 0;
	while (tmp->wst[prec] && rep <= tmp->precision)
	{
		tmp->nb = tmp->wst[prec];
		rep += compute_rep(ltoa_base(tmp, BINA));
		prec++;
	}
	if (rep > tmp->precision)
	{
		if ((tmptxt = ft_bchar(1, (size_t)prec - 1)) == NULL)
			return (NULL);
	}
	else
	{
		if ((tmptxt = ft_bchar(1, (size_t)prec)) == NULL)
			return (NULL);
	}
	return (tmptxt);
}

static int		display_wstring(char *new, t_flag *tmp)
{
	int length;
	int i;
	int j;

	i = 0;
	length = 0;
	j = 0;
	while (new[i] != '\0')
	{
		if (new[i] == 1)
		{
			tmp->nb = (long long)tmp->wst[j];
			length += manage_uni(tmp);
			j++;
		}
		else
		{
			ft_putchar(new[i]);
			length++;
		}
		i++;
	}
	return (length);
}

static char		*manage_tmptxt(t_flag *tmp)
{
	char *tmptxt;

	tmptxt = NULL;
	if (tmp->wst == NULL)
		tmptxt = ft_strdup("(null)");
	else if (tmp->precision > 0)
		tmptxt = zero_precision(tmp);
	else
		tmptxt = ft_bchar(1, ft_wstrlen(tmp->wst));
	if (tmptxt == NULL)
		return (NULL);
	return (tmptxt);
}

int				manage_wstring(t_flag *tmp)
{
	char	*tmptxt;
	char	*new;
	int		i;
	int		rep;
	int		prec;

	i = 0;
	rep = 0;
	prec = 0;
	if (tmp->precision == 0)
		return (display_flag(NULL, tmp));
	if ((tmptxt = manage_tmptxt(tmp)) == NULL)
		return (0);
	if (tmp->wst == NULL)
		return (display_flag(tmptxt, tmp));
	while (tmptxt[i] && tmp->wst[i] != '\0')
	{
		tmp->nb = tmp->wst[i];
		rep += compute_rep(ltoa_base(tmp, BINA)) - 1;
		i++;
	}
	tmp->width -= rep;
	if ((new = display_width(tmptxt, tmp)) == NULL)
		return (0);
	return (display_wstring(new, tmp));
}
