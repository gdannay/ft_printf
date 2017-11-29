/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:06:04 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/29 18:22:07 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <inttypes.h>
# include "../libft/libft.h"

# define BINA "01"
# define DECI "0123456789"
# define HEXAMIN "0123456789abcdef"
# define HEXAMAJ "0123456789ABCDEF"

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
	struct s_flag		*next;
}						t_flag;

typedef struct			s_type
{
	char				type;
	int					conv;
}						t_type;

t_flag					*create_flag(void);
int						length_nbr(int n);
t_flag					*check_carac(char *str, int *i);
void					fill_wp(t_flag **tmp, int n);
int						display(char *str, t_flag *flag);
char					*ltoa_base(t_flag *tmp, char *base);
char					*dtoa(t_flag *tmp);

#endif
