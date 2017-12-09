/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_uni.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 11:14:17 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/09 17:43:05 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long		atoi_base(char *str, char *input_b)
{
	int i;
	int neg;
	long long n;

	i = 0;
	neg = 0;
	n = 0;
	if (str[i] == '-')
	{
		i++;
		neg = 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * ft_strlen(input_b) - (str[i] - '0');
		i++;
	}
	if (neg)
		return (n);
	return (-n);
}

char			*mask_uni(char *output, char *bin)
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

void			ft_putuni(char *c, int rep)
{
	int i;
	long long n[4];
	char *mask;

	i = 0;
	while (i < rep - 1)
	{
		mask = ft_strdup("10xxxxxx");
		mask = mask_uni(mask, c);
		n[i] = atoi_base(mask, BINA);
		ft_strdel(&mask);
		i++;
	}
	if (rep == 2)
		mask = ft_strdup("110xxxxx");
	if (rep == 3)
		mask = ft_strdup("1110xxxx");
	if (rep == 4)
		mask = ft_strdup("11110xxx");
	mask = mask_uni(mask, c);
	n[i] = atoi_base(mask, BINA);
	ft_strdel(&mask);
	if (rep > 3)
		write(1, &(n[3]), 1);
	if (rep > 2)
		write(1, &(n[2]), 1);
	write(1, &(n[1]), 1);
	write(1, &(n[0]), 1);
}

int		compute_rep(char *c)
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

int		manage_uni(t_flag *tmp)
{
	char *c;
	char *c2;
	int rep;
	char *new;
	int i;

	c = ltoa_base(tmp, BINA);
	i = 0;
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
		if ((c2 = chartostr(tmp->nb)) == NULL
				|| (new = display_precision(c2, tmp)) == NULL
				|| (new = display_width(c2, tmp)) == NULL)
			return (0);
		while (new[i] != '\0')
		{
			if (new[i] == 1)
				ft_putuni(c, rep);
			else
				ft_putchar(new[i]);
			i++;
		}
		ft_strdel(&c2);
		ft_strdel(&new);
	}
	else
		ft_putuni(c, rep);
	ft_strdel(&c);
	return (rep);
}
