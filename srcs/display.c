/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:03:31 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/08 17:00:15 by gdannay          ###   ########.fr       */
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
	char *nbtmp;
	
	i = 0;
	while (i < rep)
	{
		mask = ft_strdup("10xxxxxx");
		nbtmp = mask_uni(mask, c);
		n[i] = atoi_base(nbtmp, BINA);
		ft_strdel(&mask);
		i++;
	}
	if (rep == 1)
		mask = ft_strdup("110xxxxx");
	if (rep == 2)
		mask = ft_strdup("1110xxxx");
	if (rep == 3)
		mask = ft_strdup("11110xxx");
	nbtmp = mask_uni(mask, c);
	n[i] = atoi_base(nbtmp, BINA);
	if (rep > 2)
		write(1, &(n[3]), 1);
	if (rep > 1)
		write(1, &(n[2]), 1);
	write(1, &(n[1]), 1);
	write(1, &(n[0]), 1);
}

static int	display_uni(t_flag *tmp)
{
	char *c;
	int rep;

	c = ltoa_base(tmp, BINA);
	if (ft_strlen(c) <= 7)
	{
		write(1, &(tmp->nb), 1);
		return (1);
	}
	else if (ft_strlen(c) <= 11)
		rep = 1;
	else if (ft_strlen(c) <= 16)
		rep = 2;
	else
		rep = 3;
	ft_putuni(c, rep);
	return (rep + 1); 
}

static int		manage_display(t_flag *tmp)
{
	int		length;
	char	*c;
	int i;

	length = 0;
	i = 0;
	if (tmp->intdisplay == 1 || tmp->intdisplay == 6)
		length = manage_nb(tmp);
	else if (tmp->intdisplay == 2)
		length = manage_char(tmp);
	else if (tmp->intdisplay == 9)
	{
		if (tmp->wst == NULL)
			return (manage_string(tmp));
		while (tmp->wst[i] != '\0')
		{
			tmp->nb = tmp->wst[i];
			length += display_uni(tmp);
			i++;
		}
	}
	else if (tmp->intdisplay == 8) 
		length = display_uni(tmp);
	else if (tmp->intdisplay == 2 || tmp->intdisplay == 9) 
		length = manage_char(tmp);
	else if (tmp->intdisplay == 3)
		length = manage_string(tmp);
	//	else if (tmp->intdisplay == 4)
	//		length = display_flag(utoa_base(tmp, HEXAMIN), tmp);
	else if (tmp->type == '%')
	{
		if ((c = chartostr('%')) == NULL)
			return (0);
		length = display_flag(c, tmp);
	}
	//	else if (tmp->intdisplay == 5) 
	//new = manage_db(tmp);
	return (length);
}

int			display(char *str, t_flag *flag)
{
	int	i;
	int length;
	int	j;
	t_flag	*tmp;

	i = 0;
	j = 0;
	length = 0;
	tmp = flag;
	while (str && str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] && tmp->inttype != 0)
		{
			if (tmp)
				length += manage_display(tmp);
			i++;
			while (str[i + 1] && str[i] != tmp->type)
				i++;
			tmp = tmp->next;
			i++;
		}
		else if (str[i] == '%' && ((!tmp) || tmp->inttype == 0))
		{
			i++;
			while (str[i] && str[i] != tmp->type)
				i++;
			if (tmp && str[i] == tmp->type)
				tmp = tmp->next;
		}
		else
		{
			j = i;
			while (str[i] && str[i] != '%')
			{
				length++;
				i++;
			}
			write(1, str + j, (size_t)(i - j));
		}
	}
	return (length);
}
