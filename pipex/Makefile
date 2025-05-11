# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shattori <shattori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 19:42:34 by shattori          #+#    #+#              #
#    Updated: 2025/04/04 16:32:04 by shattori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS := -O2 -g -Wall -Wextra -Werror
NAME = pipex
SRC_DIR := ./srcs
INC := ./include
LIBFT_DIR := ./libft
LIBFT_AR := $(LIBFT_DIR)/libft.a
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/error_handling.c $(SRC_DIR)/make_process.c $(SRC_DIR)/error_calls.c $(LIBFT_AR) $(FT_PRINTF_AR)	

IFLAGS := -I$(INC)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(IFLAGS) $(CFLAGS) $(OBJS)  -o $(NAME) 

$(LIBFT_AR):
	make -C $(LIBFT_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_AR)

re: fclean all
