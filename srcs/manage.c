/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:24:19 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/22 13:44:13 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag		*create_flag(void)
{
	t_flag	*new;

	if ((new = (t_flag *)malloc(sizeof(t_flag))) == NULL)
		return (NULL);
	new->minus = 0;
	new->plus = 0;
	new->space = 0;
	new->zero = 0;
	new->hash = 0;
	new->width = -1;
	new->precision = -1;
	new->length = 0;
	new->type = 0;
	new->content = NULL;
	new->next = NULL;
	return (new);

}

void		manage_flag(char *str, int i, t_flag **new)
{
	if (str[i] == '-')
		(*new)->minus = 1;
	if (str[i] == '+')
		(*new)->plus = 1;
	if (str[i] == ' ')
		(*new)->space = 1;
	if (str[i] == '0')
		(*new)->zero = 1;
	if (str[i] == '#')
		(*new)->hash = 1;
}

int			length_nbr(int n)
{
	int		taille;

	taille = 0;
	if (n <= 0)
		taille++;
	while (n)
	{
		n /= 10;
		taille++;
	}
	return (taille);
}
