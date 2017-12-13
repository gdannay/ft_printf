/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 10:00:11 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/13 12:08:21 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_right(char *buff, char *str, int index, size_t length)
{
	int i;

	i = (int)ft_strlen(buff) + (int)length;
	if ((size_t)BUFF_SIZE - ft_strlen(buff) < length)
		buff = print_buff(buff);
	while (i - (int)length >= index)
	{
		buff[i] = buff[i - length];
		i--;
	}
	i = 0;
	while (length > 0)
	{
		buff[index] = str[i];
		index++;
		i++;
		length--;
	}
	return (buff);
}

char	*print_buff(char *buff)
{
	int		i;

	i = 0;
	if (ft_strlen(buff) == 0)
	{
//		dprintf(1, "TEST5");
		return (buff);
	}
//	dprintf(1, "TEST6");
	write(1, buff, ft_strlen(buff));
	while (buff && buff[i])
	{
		buff[i] = '\0';
		i++;
	}
	return (buff);
}

char	*manage_buff(char *buff, char *str, size_t length)
{
	if ((size_t)BUFF_SIZE - ft_strlen(buff) > length)
	{
//		dprintf(1, "TEST1");
		buff = ft_strncat(buff, str, length);
	}
	else if ((size_t)BUFF_SIZE - ft_strlen(buff) <= length)
	{
//		dprintf(1, "TEST2");
		buff = print_buff(buff);
		if (BUFF_SIZE <= length)
		{
//			dprintf(1, "TEST3");
			write(1, str, length);
		}
		else
		{
//			dprintf(1, "TEST4");
			buff = ft_strncat(buff, str, length);
		}
	}
	return (buff);

}
