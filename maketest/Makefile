NAME	=	libftprintf.a

SRCS	=	./srcs/ft_printf.c		\
			./srcs/lib.c			\
			./srcs/manage_flag.c	\
			./srcs/display.c		\
			./srcs/ltoa_base.c		\
			./srcs/display_type.c	\
			./srcs/display_flag.c	\
			./libft/ft_strndup.c	\
			./libft/ft_atoi.c		\
			./libft/ft_putstr.c		\
			./libft/ft_putchar.c	\
			./libft/ft_strjoin.c	\
			./libft/ft_strlen.c		\
			./libft/ft_strdup.c		\
			./libft/ft_strncmp.c

OBJS	=	$(SRCS:.c=.o)

LIBft	=	libft/libft.a

CFLAGS	=	-Wall -Werror -Wextra -I./libft/ -I./includes/

CC		=	gcc

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(LIBFT)
	make -C libft
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o		:	%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean	:	
	rm -rf $(OBJS)

fclean	:	clean
	rm -rf $(NAME)

re		:	fclean all
