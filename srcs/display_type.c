/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:22:57 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/04 14:40:19 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



static char		*manage_hexa(t_flag *tmp)
{
	char *new;
	long long n;
	long long n2;
	long long taille;

	new = NULL;
	n = tmp->nb;
	n2 = tmp->nb;
	taille = 0;
	if (tmp->nb <= -4294967296)
	{
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
		if (tmp->type == 'x')
			new = ft_strjoin(new, ltoa_base(tmp, HEXAMIN));
		else if (tmp->type == 'X')
			new = ft_strjoin(new, ltoa_base(tmp, HEXAMAJ));
	}
	else
	{
		tmp->nb += 4294967296;
		if (tmp->type == 'x')
			new = ltoa_base(tmp, HEXAMIN);
		else if (tmp->type == 'X')
			new = ltoa_base(tmp, HEXAMAJ);
	}
	return (new);
}

char		*manage_nb(t_flag *tmp)
{
	char *new;
	char *tmptxt;

	new = NULL;
	if (tmp->inttype == 6 && tmp->nb < 0)
		new = manage_hexa(tmp);
	else if (tmp->inttype == 1)
		new = ltoa_base(tmp, DECI);
	else if (tmp->type == 'x')
		new = ltoa_base(tmp, HEXAMIN);
	else if (tmp->type == 'X')
		new = ltoa_base(tmp, HEXAMAJ);
	else if (tmp->type == 'u' || tmp->type == 'U')
		new = utoa_base(tmp, DECI);
	else if (tmp->type == 'o' || tmp->type == 'O')
		new = utoa_base(tmp, OCTA);
	if (new == NULL)
		return NULL;
	if (tmp->precision == 0 && ft_strncmp(new, "0", 1) == 0)
		new = "";
	if ((int)ft_strlen(new) < tmp->precision)
	{
		while ((int)ft_strlen(new) < tmp->precision)
			new = ft_strjoin("0", new);
		tmp->zero = 0;
	}
	tmptxt = new;
	if((new = display_flag(tmptxt, tmp)) == NULL)
		return (NULL);
//	free(tmptxt);
	return (new);
}

char		*manage_string(t_flag *tmp)
{
	if (tmp->st == NULL)
		tmp->st = ft_strdup("(null)");
	if (tmp->precision >= 0)
		return (display_flag(ft_strndup(tmp->st, (size_t)tmp->precision), tmp));
	else
		return (display_flag(tmp->st, tmp));
}

char		*manage_char(t_flag *tmp)
{
	char 	*new;
	int 	i;

	i = 0;
	if (tmp->nb == 0)
	{
		tmp->nb = 1;
		new = display_flag(chartostr(tmp->nb), tmp);
		while (new[i] != '\0')
		{
			if (new[i] == 1)
				ft_putchar(0);
			else
				ft_putchar(new[i]);
			i++;
		}
		tmp->nb = 0;
	}
	else
		new = display_flag(chartostr(tmp->nb), tmp);
	return (new);
}
