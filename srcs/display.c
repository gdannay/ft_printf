/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/01 11:12:47 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char		*manage_display(t_flag *tmp)
{
	char	*new;

	if (tmp->type == 'd' || tmp->type == 'D' ||
			tmp->type == 'i')
		new = ltoa_base(tmp, DECI);
	else if (tmp->type == 'u' || tmp->type == 'U')
		new = utoa_base(tmp, DECI);
	else if (tmp->type == 'f' || tmp->type == 'F')
		new = dtoa(flag);
	else if (tmp->type == 'x')
		new = ltoa_base(tmp, HEXAMIN);
	else if (tmp->type == 'X')
		new = ltoa_base(tmp, HEXAMAX);
	else if (tmp->type == 'o' || tmp->type == 'O')
		new = ltoa_base(tmp, OCTA);
	else if (tmp->type == 's' || tmp->type == 'S')
		new = tmp->st;
	else if (tmp->type == 'p')
		
	else if (tmp->type == 'c' || tmp->type == 'C') 

	else 

	display_flag(&new, tmp);
	return (new);
}

char			*display(char *str, t_flag *flag)
{
	int	i;
	char *new;
	char *strtmp;
	t_flag	*tmp;

	i = 0;
	length = 0;
	tmp = flag;
	while (str[i] != '\0')
	{
		strtmp = new;
		if (str[i] == '%' && str[i + 1] != '%')
		{
			new = ft_strjoin(strtmp, manage_display(tmp));
			tmp = tmp->next;
			while (str[i] && str[i] != tmp->type)
				i++;
		}
		else
			new = ft_strjoin(strtmp, &str[i]);
		free(strtmp);
		i++;
	}
	return (new);
}
