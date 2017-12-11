/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:02:16 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/11 10:00:17 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static t_flag			*parse_str(char *str)
{
	t_flag		*flag;
	t_flag		*tmp;
	t_flag		*tmp2;
	int			i;

	flag = NULL;
	tmp = NULL;
	tmp2 = NULL;
	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if ((tmp = check_carac(str, &i)) == NULL)
				return (NULL);
			if (flag == NULL)
				flag = tmp;
			else
				tmp2->next = tmp;
			tmp2 = tmp;
		}
		i++;
	}
	return (flag);
}

static void			fill_unsigned(va_list va, t_flag *tmp)
{
	if (tmp->type == 'U')
		tmp->unb = (unsigned long long)va_arg(va, unsigned long long);
	else if (tmp->type == 'O')
		tmp->unb = va_arg(va, unsigned long);
	else if (tmp->length == 1)
		tmp->unb = (unsigned char)va_arg(va, int);
	else if (tmp->length == 2)
		tmp->unb = (unsigned short)va_arg(va, int);
	else if (tmp->length == 3)
		tmp->unb = va_arg(va, unsigned long);
	else if (tmp->length == 4)
		tmp->unb = va_arg(va, unsigned long long);
	else if (tmp->length == 6)
		tmp->unb = va_arg(va, size_t);
	else if (tmp->length == 7)
		tmp->unb = va_arg(va, intmax_t);
	else
		tmp->unb = va_arg(va, unsigned int);
}

static void			fill_int(va_list va, t_flag *tmp)
{
	if (tmp->type == 'D')
		tmp->nb = va_arg(va, long);
	else if (tmp->length == 1)
		tmp->nb = (char)va_arg(va, int);
	else if (tmp->length == 2)
		tmp->nb = (short)va_arg(va, int);
	else if (tmp->length == 3)
		tmp->nb = va_arg(va, long);
	else if (tmp->length == 4)
		tmp->nb = va_arg(va, long long);
	else if (tmp->length == 5)
		tmp->ld = va_arg(va, long double);
	else if (tmp->length == 6)
		tmp->nb = va_arg(va, size_t);
	else if (tmp->length == 7)
		tmp->nb = va_arg(va, intmax_t);
	else
		tmp->nb = va_arg(va, int);
}

static void			fill_content(va_list va, t_flag *tmp)
{
	if (tmp->width == -2 || tmp->precision == -2 || tmp->width == -3)
		fill_wp(tmp, va);
	if (tmp->inttype == 1 || (tmp->inttype == 6 && tmp->length == 0))
		fill_int(va, tmp);
	else if (tmp->inttype == 4 || tmp->inttype == 6)
		fill_unsigned(va, tmp);
	else if (tmp->inttype == 2)
		tmp->st = ft_strdup(va_arg(va, char *));
	else if (tmp->inttype == 3)
		tmp->unb = (unsigned long long)va_arg(va, void *);
	else if (tmp->inttype == 5)
		tmp->db = va_arg(va, double);
	else if (tmp->inttype == 8)
		tmp->nb = va_arg(va, wchar_t);
	else if (tmp->inttype == 9)
		tmp->wst = va_arg(va, wchar_t *);
}

void				free_lst(t_flag **flag)
{
	t_flag *tmp;

	while (*flag)
	{
		tmp = (*flag)->next;
		if ((*flag)->st != NULL)
			free((*flag)->st);
		free(*flag);
		(*flag) = tmp;
	}
}

int					ft_printf(char *str, ...)
{
	va_list		va;
	va_start	(va, str);
	t_flag		*flag;
	t_flag		*tmp;
	int			length;

	length = 0;
	if ((flag = parse_str(str)) == NULL && str == NULL)
		return (0);
	tmp = flag;
	while (tmp)
	{
		fill_content(va, tmp);
		tmp = tmp->next;
	}
	length = display(str, flag);
	free_lst(&flag);

	//	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d, %d\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype, flag->nb);
	//	flag = flag->next;
	//	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype);
	//	flag = flag->next;
	//	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d, %s\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype, flag->st);
	//	flag = flag->next;
	//	printf("minus = %d, plus = %d, space = %d, zero = %d, hash = %d, width = %d, precision = %d, length = %d, type = %c, inttype = %d, %s\n", flag->minus, flag->plus, flag->space, flag->zero, flag->hash, flag->width, flag->precision, flag->length, flag->type, flag->inttype, flag->st);
	va_end (va);
	//	printf("%s", new);
	//	ft_putstr(new);
	return (length);
}

/*int main(void)
  {
  ft_printf("\n");
  ft_printf("%%\n");
  ft_printf("%d\n", 42);
  ft_printf("%d%d\n", 42, 41);
  ft_printf("%d%d%d\n", 42, 43, 44);
  ft_printf("%ld\n", 2147483647);
  ft_printf("%lld\n", 9223372036854775807);
  ft_printf("%x\n", 505);
  ft_printf("%X\n", 505);
  ft_printf("%p\n", &ft_printf);
  ft_printf("%20.15d\n", 54321);
  ft_printf("%-10d\n", 3);
  ft_printf("% d\n", 3);
  ft_printf("%+d\n", 3);
  ft_printf("%010d\n", 1);
  ft_printf("%hhd\n", 0);
  ft_printf("%jd\n", 9223372036854775807);
  ft_printf("%zd\n", 4294967295);
  ft_printf("%\n");
  ft_printf("%U\n", 4294967295);
  ft_printf("%u\n", 4294967295);
  ft_printf("%o\n", 40);
  ft_printf("%%#08x\n", 42);
  ft_printf("%x\n", 1000);
  ft_printf("%#X\n", 1000);
  ft_printf("%s\n", NULL);
  ft_printf("%s%s\n", "test", "test");
  ft_printf("%s%s%s\n", "test", "test", "test");
  ft_printf("%C\n", 15000);
  while (1);
  return (0);
  }*/

#include "limits.h"

#include <locale.h>

/*int		main()
{
	char* l = setlocale(LC_ALL, "");
//	if (l == NULL) {
//		printf("Locale not set\n");
//	} else {
//		printf("Locale set to %s\n", l);
//	}
	printf("\n%d", ft_printf("%5+d", 42));
	printf("\n");
	printf("\n%d", printf("%5+d", 42));

}*/
