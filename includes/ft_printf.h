/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:06:04 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/26 14:08:12 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

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
	int					nb;
	unsigned int		unb;
	long				lnb;
	double				db;
	int					*n;
	void				*vd;
	char				*st;
	struct s_flag		*next;
}						t_flag;

typedef struct			s_type
{
	char				type;
	int					conv;
}						t_type;

t_flag					*create_flag(void);
void					manage_flag(char *str, int i, t_flag **flag);
int						length_nbr(int n);
void					check_length(t_flag *new, char *sstr, int *i);
void					check_wp(char *str, int *i, t_flag *new);
t_flag					*check_carac(char *str, int *i, t_flag **flag);
void					fill_wp(t_flag **tmp, int n);

#endif
