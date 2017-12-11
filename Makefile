NAME	=	libftprintf.a

SRCS	=	./srcs/ft_printf.c		\
			./srcs/lib.c			\
			./srcs/manage_flag.c	\
			./srcs/check_wp.c		\
			./srcs/display.c		\
			./srcs/ltoa_base.c		\
			./srcs/display_type.c	\
			./srcs/display_flag.c	\
			./srcs/display_wps.c	\
			./srcs/display_uni.c	\
			./srcs/display_wstr.c	\
			./libft/ft_strndup.c	\
			./libft/ft_atoi.c		\
			./libft/ft_putstr.c		\
			./libft/ft_putchar.c	\
			./libft/ft_strjoin.c	\
			./libft/ft_strlen.c		\
			./libft/ft_strdup.c		\
			./libft/ft_strncmp.c	\
			./libft/ft_strdel.c		\
			./libft/ft_strsub.c		\
			./libft/ft_chartostr.c	\
			./libft/ft_bchar.c		\
			./libft/ft_lennbr.c		\
			./libft/ft_atoi_base.c	\
			./libft/ft_wstrlen.c	

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
			make clean -C libft
			rm -rf $(OBJS)

fclean	:	clean
			make fclean -C libft
			rm -rf $(NAME)

re		:	fclean all
