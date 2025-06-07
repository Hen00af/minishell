# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nando <nando@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 14:52:53 by nando             #+#    #+#              #
#    Updated: 2025/06/07 20:55:30 by nando            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fprintf.a
SRCS = ft_fprintf.c \
	   conversions/ft_put_char_fd.c \
       conversions/ft_put_str_fd.c \
       conversions/ft_put_deci_fd.c \
       conversions/ft_put_int_fd.c \
       conversions/ft_put_per_fd.c \
       conversions/ft_put_unsigned_fd.c \
       conversions/ft_put_ptr_fd.c \
       conversions/ft_put_hexa_lower_fd.c \
       conversions/ft_put_hexa_upper_fd.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
%.o : %.c ft_fprintf.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY = all clean fclean re
