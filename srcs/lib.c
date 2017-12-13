/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:24:19 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/13 10:39:57 by gdannay          ###   ########.fr       */
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
	new->nb = 0;
	new->unb = 0;
	new->inttype = 0;
	new->db = 0;
	new->n = NULL;
	new->vd = NULL;
	new->st = NULL;
	new->next = NULL;
	new->wst = NULL;
	new->order = 0;
	return (new);
}

void		free_lst(t_flag **flag)
{
	t_flag *tmp;

	while (*flag)
	{
		tmp = (*flag)->next;
		if ((*flag)->st != NULL)
			free((*flag)->st);
		if ((*flag)->wst != NULL)
			free((*flag)->wst);
		free(*flag);
		(*flag) = tmp;
	}
}

int			size_hexa(long long n)
{
	int taille;

	taille = 0;
	while (n)
	{
		n /= 4294967297;
		taille++;
	}
	return (taille);
}

int			display_0(t_flag *tmp, char *c, char *buff)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	tmp->nb = 1;
	buff = print_buff(buff);
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
	ft_strdel(&new);
	return (i);
}

int			compute_rep(char *c)
{
	if (ft_strlen(c) <= 7)
		return (1);
	else if (ft_strlen(c) <= 11)
		return (2);
	else if (ft_strlen(c) <= 16)
		return (3);
	else
		return (4);
}
