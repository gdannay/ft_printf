/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/05 11:11:52 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*manage_display(t_flag *tmp)
{
	char	*new;

	new = NULL;
	if (tmp->intdisplay == 1 || tmp->intdisplay == 6)
		new = manage_nb(tmp);
	else if (tmp->intdisplay == 2) 
		new = manage_char(tmp);
	else if (tmp->intdisplay == 3)
		new = manage_string(tmp);
	else if (tmp->intdisplay == 4)
		new = ft_strjoin("0x", utoa_base(tmp, HEXAMIN));
	else if (tmp->type == '%')
		new = display_flag(chartostr('%'), tmp);
//	else if (tmp->intdisplay == 5) 
		//new = manage_db(tmp);
	if (new == NULL)
		return (NULL);
	if (tmp->nb != 0 || (tmp->type != 'C' && tmp->type != 'c'))
		ft_putstr(new);
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
	while (str && str[i] != '\0')
	{
		strtmp = new;
		if (str[i] == '%')
		{
			new = ft_strjoin(strtmp, manage_display(tmp));
			i++;
			while (str[i + 1] && str[i] != tmp->type)
				i++;
			tmp = tmp->next;
		}
		else
		{
			ft_putchar(str[i]);
			new = ft_strjoin(strtmp, chartostr(str[i]));
		}
		if (new == NULL)
			return (NULL);
		free(strtmp);
		i++;
	}
	return (new);
}
