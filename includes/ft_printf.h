/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:06:04 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/11 12:49:36 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <inttypes.h>
# include "../libft/libft.h"
# include <wchar.h>

# define BINA "01"
# define DECI "0123456789"
# define HEXAMIN "0123456789abcdef"
# define HEXAMAJ "0123456789ABCDEF"
# define OCTA "01234567"

typedef struct			s_flag
{
	int					minus;
	int					plus;
	int					space;
	int					zero;
	int					hash;
	int					width;
	int					precision;
	int					length;
	char				type;
	int					inttype;
	int					intdisplay;
	long long			nb;
	unsigned long long	unb;
	long double			ld;
	size_t				sizet;
	intmax_t			imt;
	double				db;
	int					*n;
	void				*vd;
	char				*st;
	int					order;
	wchar_t				*wst;
	struct s_flag		*next;
}						t_flag;

typedef struct			s_type
{
	char				type;
	int					conv;
	int					display;
}						t_type;

int						ft_printf(char *str, ...);
t_flag					*create_flag(void);
int						length_nbr(int n);
t_flag					*check_carac(char *str, int *i);
void					fill_wp(t_flag *tmp, va_list va);
int						display(char *str, t_flag *flag);
char					*ltoa_base(t_flag *tmp, char *base);
char					*utoa_base(t_flag *tmp, char *base);
char					*dtoa(t_flag *tmp);
char					*chartostr(long long c);
int						display_flag(char *new, t_flag *tmp);
int						manage_nb(t_flag *tmp);
int						manage_string(t_flag *tmp);
int						manage_char(t_flag *tmp);
char					*ft_bchar(char c, size_t length);
char					*display_precision(char *, t_flag *tmp);
char					*display_width(char *, t_flag *tmp);
char					*correction_sign(char *new, t_flag *tmp);
int						manage_uni(t_flag *tmp);
int						compute_rep(char *c);
int						manage_wstring(t_flag *tmp);
int						size_hexa(long long n);
int						display_0(t_flag *tmp, char *c);
int						compute_rep(char *c);

#endif
