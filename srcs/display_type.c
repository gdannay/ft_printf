/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:22:57 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/06 19:01:48 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*manage_hexa(t_flag *tmp)
{
	char *new;
	long long n;
	long long n2;
	long long taille;
	char *t2;
	char *tmptxt;

	new = NULL;
	n = tmp->nb;
	n2 = tmp->nb;
	taille = 0;
	t2 = NULL;
	if (tmp->nb <= -4294967296)
	{
		tmptxt = new;
		while (n)
		{
			n /= 4294967297;
			taille++;
		}
		tmp->nb = 4294967296 - taille;
		if (tmp->type == 'x')
			new = ltoa_base(tmp, HEXAMIN);
		else if (tmp->type == 'X')
			new = ltoa_base(tmp, HEXAMAJ);
		tmp->nb = n2 + 4294967296 * taille;
		if (tmp->nb == 0)
			new = ft_strjoin(new, t2 = ft_bchar('0', 8));
		else if (tmp->type == 'x')
			new = ft_strjoin(new, ltoa_base(tmp, HEXAMIN));
		else if (tmp->type == 'X')
			new = ft_strjoin(new, ltoa_base(tmp, HEXAMAJ));
		ft_strdel(&tmptxt);
		ft_strdel(&t2);
	}
	else
	{
		tmp->nb += 4294967296;
		if (tmp->type == 'x')
			new = ltoa_base(tmp, HEXAMIN);
		else if (tmp->type == 'X')
			new = ltoa_base(tmp, HEXAMAJ);
	}
	if (new == NULL)
		return (NULL);
	return (new);
}

int			manage_nb(t_flag *tmp)
{
	char	*new;
	int		length;

	new = NULL;
	if (tmp->inttype == 6 && tmp->nb < 0)
		new = manage_hexa(tmp);
	else if (tmp->inttype == 1)
		new = ltoa_base(tmp, DECI);
	else if (tmp->type == 'x' && tmp->length == 0)
		new = ltoa_base(tmp, HEXAMIN);
	else if (tmp->type == 'X' && tmp->length == 0)
		new = ltoa_base(tmp, HEXAMAJ);
	else if (tmp->type == 'x')
		new = utoa_base(tmp, HEXAMIN);
	else if (tmp->type == 'X')
		new = utoa_base(tmp, HEXAMAJ);
	else if (tmp->type == 'p')
		new = utoa_base(tmp, HEXAMIN);
	else if (tmp->type == 'u' || tmp->type == 'U')
		new = utoa_base(tmp, DECI);
	else if (tmp->type == 'o' || tmp->type == 'O')
		new = utoa_base(tmp, OCTA);
	if (new == NULL)
		return (0);
	if (tmp->precision == 0 && ft_strncmp(new, "0", 1) == 0)
	{
		free(new);
		new = NULL;
	}
	length = display_flag(new, tmp);
	return (length);
}

int		manage_string(t_flag *tmp)
{
	char *tmptxt;
	int length;

	if (tmp->st == NULL)
	{
		if ((tmp->st = ft_strdup("(null)")) == NULL)
			return (0);
	}
	if (tmp->precision == 0)
		return (display_flag(NULL, tmp));
	else if (tmp->precision > 0)
	{
		if ((tmptxt = ft_strndup(tmp->st, (size_t)tmp->precision)) == NULL)
			return (0);
		length = display_flag(tmptxt, tmp);
		return (length);
	}
	else
	{
		if ((tmptxt = ft_strdup(tmp->st)) == NULL)
			return (0);
		return (display_flag(tmptxt, tmp));
	}
}

int			manage_char(t_flag *tmp)
{
	int 	i;
	char	*new;
	char	*c;

	i = 0;
	if (tmp->nb == 0)
	{
		tmp->nb = 1;
		if ((c = chartostr(tmp->nb)) == NULL
			|| (new = display_precision(c, tmp)) == NULL
			|| (new = display_width(c, tmp)) == NULL)
			return (0);
		while (new[i] != '\0')
		{
			if (new[i] == 1)
				ft_putchar(0);
			else
				ft_putchar(new[i]);
			i++;
		}
		tmp->nb = 0;
		ft_strdel(&new);
	}
	else
	{
		if ((c = chartostr(tmp->nb)) == NULL)
			return (0);
		return (display_flag(c, tmp));
	}
	return (i);
}
