# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nando <nando@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/25 06:16:56 by shattori          #+#    #+#              #
#    Updated: 2025/08/01 19:28:52 by nando            ###   ########.fr        #
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

SPINNER = / - \\ \| 

$(NAME): $(OBJS) $(LIBFT_AR) $(FT_FPRINTF_AR)
	@echo "🔧 Linking $(NAME)..."
	@i=0; while [ $$i -lt 10 ]; do \
		printf "\r[%c] Linking..." "$$(echo "$(SPINNER)" | cut -c $$(( ($$i%4)*2 + 1 )))"; \
		sleep 0.1; \
		i=$$((i+1)); \
	done
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)
	@printf "\r✅ Build complete!            \n"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "🔨 Compiling %s\n" $<
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_AR):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_FPRINTF_AR):
	$(MAKE) -C $(FT_FPRINTF_DIR)

run: all
	./$(NAME)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBFT_DIR)/objects
	@rm -rf $(FT_FPRINTF_DIR)/*.o
	@rm -rf $(FT_FPRINTF_DIR)/conversions/*.o
	@echo "🧹 Object files removed"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(FT_FPRINTF_AR)
	@rm -f $(LIBFT_AR)
	@echo "🗑️ Executable removed"

re: fclean all
