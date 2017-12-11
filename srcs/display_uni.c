/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_uni.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 11:14:17 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/11 14:39:37 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*mask_uni(char *output, char *bin)
{
	int i;
	int j;

	i = 7;
	j = (int)ft_strlen(bin) - 1;
	while (output[i] == 'x' && j >= 0)
	{
		output[i] = bin[j];
		i--;
		j--;
	}
	while (output[i] == 'x')
	{
		output[i] = '0';
		i--;
	}
	bin[j + 1] = '\0';
	return (output);
}

static char		*mask_rep(char *mask, int rep, char *c)
{
	if (rep == 2)
		mask = ft_strdup("110xxxxx");
	if (rep == 3)
		mask = ft_strdup("1110xxxx");
	if (rep == 4)
		mask = ft_strdup("11110xxx");
	if (mask == NULL)
		return (NULL);
	mask = mask_uni(mask, c);
	return (mask);
}

static int		ft_putuni(char *c, int rep)
{
	int			i;
	long long	n[4];
	char		*mask;

	i = 0;
	while (i < rep - 1)
	{
		if ((mask = ft_strdup("10xxxxxx")) == NULL)
			return (0);
		mask = mask_uni(mask, c);
		n[i] = atoi_base(mask, BINA);
		ft_strdel(&mask);
		i++;
	}
	mask = mask_rep(mask, rep, c);
	n[i] = atoi_base(mask, BINA);
	ft_strdel(&mask);
	if (rep > 3)
		write(1, &(n[3]), 1);
	if (rep > 2)
		write(1, &(n[2]), 1);
	write(1, &(n[1]), 1);
	write(1, &(n[0]), 1);
	return (1);
}

static int		manage_wc(t_flag *tmp, char *c, int rep)
{
	char	*new;
	char	*c2;
	int		i;

	new = NULL;
	c2 = NULL;
	i = 0;
	if ((c2 = chartostr(tmp->nb)) == NULL
			|| (new = display_precision(c2, tmp)) == NULL
			|| (new = display_width(c2, tmp)) == NULL)
		return (0);
	while (new[i] != '\0')
	{
		if (new[i] == 1)
		{
			if (ft_putuni(c, rep) == 0)
				return (0);
		}
		else
			ft_putchar(new[i]);
		i++;
	}
	ft_strdel(&c2);
	ft_strdel(&new);
	return (1);
}

int				manage_uni(t_flag *tmp)
{
	char	*c;
	int		rep;

	c = ltoa_base(tmp, BINA);
	rep = compute_rep(c);
	if (tmp->intdisplay == 8 && rep == 1)
	{
		ft_strdel(&c);
		return (manage_char(tmp));
	}
	else if (tmp->intdisplay == 9 && rep == 1)
		write(1, &(tmp->nb), 1);
	else if (tmp->type == 'C' && (tmp->precision >= 0 || tmp->width >= 0))
	{
		tmp->nb = 1;
		if (manage_wc(tmp, c, rep) == 0)
			return (0);
	}
	else
	{
		if ((ft_putuni(c, rep)) == 0)
			return (0);
	}
	ft_strdel(&c);
	return (rep);
}
