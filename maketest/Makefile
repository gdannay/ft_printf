# **************************************************************************** #
                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 10:47:14 by gdannay           #+#    #+#              #
#    Updated: 2017/12/09 11:57:19 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	printf

SRCS	=	./srcs/ft_printf.c		\
			./srcs/lib.c			\
			./srcs/manage_flag.c	\
			./srcs/display_uni.c		\
			./srcs/display.c		\
			./srcs/ltoa_base.c		\
			./srcs/display_flag.c	\
			./srcs/display_type.c	\
			./srcs/display_wps.c	


OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I./libft/ -I./includes/

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft
			$(CC) $(CFLAGS) $(OBJS) -L libft -lft -o $(NAME)

%.o		:	%.c
			$(CC) -o $@ -c $< $(CFLAGS)

clean	:	
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all
