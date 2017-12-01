/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:23:15 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/01 19:25:34 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*display_flag(char *new, t_flag *tmp)
{
	char *tmptxt;

	tmptxt = new;
	if (tmp->zero == 1 && new[0] != '-' && tmp->type != '%')
	{
		new = ft_strjoin("+", tmptxt);
//		free(tmptxt);
	}
	else if (tmp->space == 1 && new[0] != '-' && tmp->type != '%')
	{
		new = ft_strjoin(" ", tmptxt);
//		free(tmptxt);
	}
	while ((int)ft_strlen(new) < tmp->width)
	{
		tmptxt = new;
		if (tmp->minus == 1)
			new = ft_strjoin(tmptxt, " ");
		else if (tmp->zero == 1)
			new = ft_strjoin("0", tmptxt);
		else
			new = ft_strjoin(" ", tmptxt);
//		free(tmptxt);
	}
	return (new);
}
