/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/09 19:31:04 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_wstrlen(wchar_t *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		manage_wstring(t_flag *tmp)
{
	char *tmptxt;
	char *new;
	int length;
	int i;
	int j;
	int rep;
	int prec;

	i = 0;
	j = 0;
	length = 0;
	rep = 0;
	prec = 0;
	if (tmp->wst == NULL)
	{
		if ((tmptxt = ft_strdup("(null)")) == NULL)
			return (0);
		return (display_flag(tmptxt, tmp));
	}
	if (tmp->precision == 0)
		return (display_flag(NULL, tmp));
	else if (tmp->precision > 0)
	{
		while (tmp->wst[prec] && rep <= tmp->precision)
		{
			tmp->nb = tmp->wst[prec];
			rep += compute_rep(ltoa_base(tmp, BINA));
			prec++;
		}
		if (rep > tmp->precision)
		{
			if ((tmptxt = ft_bchar(1, (size_t)prec - 1)) == NULL)
			return (0);
		}
		else
		{
			if ((tmptxt = ft_bchar(1, (size_t)prec)) == NULL)
				return (0);
		}
	}
	else
	{
		if ((tmptxt = ft_bchar(1, ft_wstrlen(tmp->wst))) == NULL)
			return (0);
	}
	rep = 0;
	while (tmptxt[i] && tmp->wst[i] != '\0')
	{
		tmp->nb = tmp->wst[i];
		rep += compute_rep(ltoa_base(tmp, BINA)) - 1;
		i++;
	}
	tmp->width -= rep;
	if ((new = display_width(tmptxt, tmp)) == NULL)
		return (0);
	i = 0;
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

static int		manage_display(t_flag *tmp)
{
	int		length;

	length = 0;
	if (tmp->intdisplay == 1 || tmp->intdisplay == 6)
		length = manage_nb(tmp);
	else if (tmp->intdisplay == 2)
		length = manage_char(tmp);
	else if (tmp->intdisplay == 9)
		length = manage_wstring(tmp);
	else if (tmp->intdisplay == 8) 
		length = manage_uni(tmp);
	else if (tmp->intdisplay == 2 || tmp->intdisplay == 9) 
		length = manage_char(tmp);
	else if (tmp->intdisplay == 3)
		length = manage_string(tmp);
	return (length);
}

int			display(char *str, t_flag *flag)
{
	int	i;
	int length;
	int	j;
	t_flag	*tmp;

	i = 0;
	j = 0;
	length = 0;
	tmp = flag;
	while (str && str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] && tmp->inttype != 0)
		{
			if (tmp)
				length += manage_display(tmp);
			i++;
			while (str[i + 1] && str[i] != tmp->type)
				i++;
			tmp = tmp->next;
			i++;
		}
		else if (str[i] == '%' && ((!tmp) || tmp->inttype == 0))
		{
			i++;
			while (str[i] && str[i] != tmp->type)
				i++;
			if (tmp && str[i] == tmp->type)
				tmp = tmp->next;
		}
		else
		{
			j = i;
			while (str[i] && str[i] != '%')
			{
				length++;
				i++;
			}
			write(1, str + j, (size_t)(i - j));
		}
	}
	return (length);
}
