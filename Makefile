NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Wextra
HEADER = ft_printf.h
OPTION = -c -I $(HEADER)
SRCS =	ft_printf.c\
		ft_atoi.c\
		ft_isdigit.c\
		ft_itoa.c\
		ft_putchar.c\
		ft_putnbr.c\
		ft_puthex.c\
		ft_putstr.c

OBJS_SRCS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME) : $(OBJS_SRCS)
		$(CC) $(FLAGS) $(OPTION) $(SRCS)
		ar rc $(NAME) $(OBJS_SRCS)
		ranlib $(NAME)

clean:
		rm -f $(OBJS_SRCS) $(OBJS_BONUS)
fclean: clean
		rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
