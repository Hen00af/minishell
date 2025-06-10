# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nando <nando@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 14:52:53 by nando             #+#    #+#              #
#    Updated: 2025/01/17 16:09:02 by nando            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_printf.c \
	   conversions/ft_put_char.c \
       conversions/ft_put_str.c \
       conversions/ft_put_deci.c \
       conversions/ft_put_int.c \
       conversions/ft_put_per.c \
       conversions/ft_put_unsigned.c \
       conversions/ft_put_ptr.c \
       conversions/ft_put_hexa_lower.c \
       conversions/ft_put_hexa_upper.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
%.o : %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY = all clean fclean re
