# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shattori <shattori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/25 06:10:53 by shattori          #+#    #+#              #
#    Updated: 2025/07/25 06:11:37 by shattori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -O2
INCLUDES := -Iinclude

LIBFT_DIR := ./libft
LIBFT_AR := $(LIBFT_DIR)/libft.a
FT_FPRINTF_DIR := ./utils/fprintf
FT_FPRINTF_AR := $(FT_FPRINTF_DIR)/fprintf.a

NAME    := minishell
OBJDIR  := object

SRC_DIRS := \
    ./expander \
    ./parser \
    ./lexer \
    ./linearizer \
    ./executor \
    ./builtin \
    ./utils \
    ./utils/fprintf \
    ./signal \
    ./heredoc \
    ./get_next_line \
    ./

SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
LIBS := $(LIBFT_AR) $(FT_FPRINTF_AR) -lreadline

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_AR) $(FT_FPRINTF_AR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_AR):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_FPRINTF_AR):
	$(MAKE) -C $(FT_FPRINTF_DIR)

run: all
	./$(NAME)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBFT_DIR)/objects
	@echo "🧹 Object files removed"

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️ Executable removed"

re: fclean all
