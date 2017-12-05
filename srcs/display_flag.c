/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:23:15 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/05 17:03:05 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*display_hash_blank(char *new, t_flag *tmp)
{
	char *tmptxt;

	if ((tmp->intdisplay == 6 || tmp->intdisplay == 4) && tmp->hash == 1 && tmp->zero == 0)
	{
		tmptxt = new;
		if (tmp->type == 'x' || tmp->type == 'p')
			new = ft_strjoin("0x", tmptxt);
		else if (tmp->type == 'X')
			new = ft_strjoin("0X", tmptxt);
		else if (tmp->type == 'o' || tmp->type == 'O')
			new = ft_strjoin("0", tmptxt);
		if (tmptxt)
			free(tmptxt);
	}
	return (new);
}

static char			*display_hash_zero(char *new, t_flag *tmp)
{
	char *tmptxt;

	if ((tmp->type == 'X' || tmp->type == 'x') && tmp->hash == 1 && tmp->zero == 1)
	{
		tmptxt = new;
			if (new[0] == '0' && new[1] == '0')
				new[1] = tmp->type;
			else if (new[0] == '0' && new[1] != '0')
			{
				new[0] = tmp->type;
				new = ft_strjoin("0", tmptxt);
				if (tmptxt)
					free(tmptxt);
			}
			else if (new[0] != 0)
			{
				if (tmp->type == 'x')
					new = ft_strjoin("0x", tmptxt);
				else if (tmp->type == 'X')
					new = ft_strjoin("0X", tmptxt);
				if (tmptxt)
					free(tmptxt);
			}
	}
	return (new);
}

char			*display_plus(char *new, t_flag *tmp)
{
	int i;
	char	*tmptxt;

	i = 0;
	if (tmp->zero == 1 && new[0] == '0')
		new[0] = '+';
	else if (new[0] == ' ')
	{
		while (new[i] && new[i] == ' ')
			i++;
		new[i - 1] = '+';
	}
	else
	{
		tmptxt = new;
		if ((int)ft_strlen(new) == tmp->width)
			new[(int)ft_strlen(new) - 1] = '\0';
		new = ft_strjoin("+", tmptxt);
		if (tmptxt)
			free(tmptxt);
	}
	return (new);
}

static char		*correction_sign(char *new, t_flag *tmp)
{
	int	i;
	char *tmptxt;

	i = 1;
	if (tmp->intdisplay == 1 && tmp->type != 'u' && tmp->type != 'U')
	{
		tmptxt = new;
		if (tmp->nb < 0 && new[0] == '0')
		{
			while (new[i] && new[i] == '0')
				i++;
			new[i] = '0';
			if (tmp->zero == 1)
				new[0] = '-';
			else
			{
				new = ft_strjoin("-", tmptxt);
				if (tmptxt)
					free(tmptxt);
			}
		}
		else if (tmp->nb >= 0 && tmp->plus == 1)
			new = display_plus(new, tmp);
		else if (tmp->space == 1 && tmp->nb >= 0 && tmp->width < (int)ft_strlen(new))
		{
			new = ft_strjoin(" ", tmptxt);
			if (tmptxt)
				free(tmptxt);
		}
	}
	return (new);
}

char			*display_precision(char *new, t_flag *tmp)
{
	char *tmptxt;

	if ((int)ft_strlen(new) < tmp->precision && (tmp->intdisplay == 1 || tmp->intdisplay == 6))
	{
		tmptxt = new;
		new = ft_strjoin(ft_bchar('0', (size_t)tmp->precision - ft_strlen(new)), tmptxt);
		tmp->zero = 0;
		if (tmptxt)
			free(tmptxt);
	}	
	return (new);
}

char			*display_width(char *new, t_flag *tmp)
{
	char *tmptxt;
	char *t2;

	if ((int)ft_strlen(new) < tmp->width)
	{
		tmptxt = new;
		if (tmp->minus == 1)
			new = ft_strjoin(tmptxt, t2 = ft_bchar(' ', (size_t)tmp->width - ft_strlen(new)));
		else if (tmp->zero == 1)
			new = ft_strjoin(t2 = ft_bchar('0', (size_t)tmp->width - ft_strlen(new)), tmptxt);
		else
			new = ft_strjoin(t2 = ft_bchar(' ', (size_t)tmp->width - ft_strlen(new)), tmptxt);
		if (new == NULL || t2 == NULL)
			return (NULL);
//		if (tmptxt && ft_strncmp(tmptxt, "", 1) != 0 && tmptxt != new)
//			free(tmptxt);
//		if (t2)
//			free(t2);
	}
	return (new);
}

int				display_flag(char *new, t_flag *tmp)
{
	int		length;

	if (tmp->precision != 0 && (new = display_precision(new, tmp)) == NULL)
		return (0);
	if ((tmp->nb == 0 && tmp->unb == 0) && (tmp->type == 'x' 
				|| tmp->type == 'X' || (tmp->type == 'o' && tmp->precision != 0)))
		tmp->hash = 0;
	if (((new = display_hash_blank(new, tmp)) == NULL && tmp->precision != 0)
			|| (new = display_width(new, tmp)) == NULL
			|| (new = display_hash_zero(new, tmp)) == NULL
			|| (new = correction_sign(new, tmp)) == NULL)
		return (0);
	if (tmp->nb != 0 || (tmp->type != 'C' && tmp->type != 'c'))
		write(1, new, ft_strlen(new));
	length = (int)ft_strlen(new);
//	if (new)
//		free(new);
	return (length);
}
