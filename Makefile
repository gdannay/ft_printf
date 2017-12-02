# **************************************************************************** #
                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdannay <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 10:47:14 by gdannay           #+#    #+#              #
#    Updated: 2017/12/02 18:34:08 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	printf

SRCS	=	./srcs/ft_printf.c		\
			./srcs/lib.c			\
			./srcs/manage_flag.c	\
			./srcs/display.c		\
			./srcs/ltoa_base.c		\
			./srcs/display_flag.c	\
			./srcs/display_type.c		

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra -I./libft/ -I./includes/

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
