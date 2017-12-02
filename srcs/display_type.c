/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:22:57 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/02 18:38:58 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		manage_hexa(t_flag *tmp)
{
	tmp->nb = 4294967296 + tmp->nb;
}

char		*manage_nb(t_flag *tmp)
{
	char *new;
	char *tmptxt;

	new = NULL;
	if ((tmp->inttype == 6) && tmp->nb < 0)
		manage_hexa(tmp);
	if (tmp->inttype == 1)
		new = ltoa_base(tmp, DECI);
	else if (tmp->type == 'u' || tmp->type == 'U')
		new = utoa_base(tmp, DECI);
	else if (tmp->type == 'x')
		new = ltoa_base(tmp, HEXAMIN);
	else if (tmp->type == 'X')
		new = ltoa_base(tmp, HEXAMAJ);
	else if (tmp->type == 'o' || tmp->type == 'O')
		new = utoa_base(tmp, OCTA);
	if (new == NULL)
		return NULL;
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
