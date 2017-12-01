/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/01 20:14:18 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*manage_nb(t_flag *tmp)
{
	char *new;
	char *tmptxt;

	new = NULL;
	if ((tmp->type == 'x' || tmp->type == 'X') && tmp->nb < 0)
		tmp->nb = 4294967296 + tmp->nb;
	if (tmp->type == 'd' || tmp->type == 'D' ||
			tmp->type == 'i')
		new = ltoa_base(tmp, DECI);
	else if (tmp->type == 'u' || tmp->type == 'U')
		new = utoa_base(tmp, DECI);
	else if (tmp->type == 'f' || tmp->type == 'F')
		new = dtoa(tmp);
	else if (tmp->type == 'x')
		new = ltoa_base(tmp, HEXAMIN);
	else if (tmp->type == 'X')
		new = ltoa_base(tmp, HEXAMAJ);
	else if (tmp->type == 'o' || tmp->type == 'O')
		new = ltoa_base(tmp, OCTA);
	if (new == NULL)
		return NULL;
	tmptxt = new;
	if((new = display_flag(tmptxt, tmp)) == NULL)
		return (NULL);
//	free(tmptxt);
	return (new);
}

static char		*manage_display(t_flag *tmp)
{
	char	*new;

	new = NULL;
	if (tmp->type == 'd' || tmp->type == 'D' ||
			tmp->type == 'i' || tmp->type == 'u' || 
			tmp->type == 'U' || tmp->type == 'x' ||
			tmp->type == 'X' || tmp->type == 'o' || 
			tmp->type == 'O')
		new = manage_nb(tmp);
	else if (tmp->type == 's' || tmp->type == 'S')
	{
		if (tmp->precision >= 0)
			new = ft_strndup(tmp->st, (size_t)tmp->precision);
		else
			new = tmp->st;
	}
	else if (tmp->type == 'p')
		new = ft_strjoin("0x", utoa_base(tmp, HEXAMIN));
	else if (tmp->type == 'c' || tmp->type == 'C') 
		new = chartostr(tmp->nb);
	else if (tmp->type == '%')
		new = display_flag(chartostr('%'), tmp);
//	else if (tmp->type == 'a' || tmp->type == 'A' ||
//			tmp->type == 'g' || tmp->type == 'G' || 
//			tmp->type == 'e' || tmp->type == 'E' ||
//			tmp->type == 'f' || tmp->type == 'F') 
//		new = manage_db(tmp);
	return (new);
}

char			*display(char *str, t_flag *flag)
{
	int	i;
	char *new;
	char *strtmp;
	t_flag	*tmp;

	i = 0;
	tmp = flag;
	new = NULL;
//	dprintf(1,"ICI5 = %d %c\n", i, str[i]);
	while (str && str[i] != '\0')
	{
		strtmp = new;
//		dprintf(1,"IC4I = %d %c\n", i, str[i]);
		if (str[i] == '%')
		{
//			dprintf(1,"ICI3 = %d\n", i);
			new = ft_strjoin(strtmp, manage_display(tmp));
			i++;
			while (str[i + 1] && str[i] != tmp->type)
			{
//				dprintf(1,"ICI2 = %d\n", i);
				i++;
			}
			tmp = tmp->next;
		}
		else
			new = ft_strjoin(strtmp, chartostr(str[i]));
		free(strtmp);
//		dprintf(1,"ICI = %d %c\n", i, str[i]);
		i++;
	}
	return (new);
}
