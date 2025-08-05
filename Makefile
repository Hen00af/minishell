# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shattori <shattori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/25 06:16:56 by shattori          #+#    #+#              #
#    Updated: 2025/08/05 15:04:35 by shattori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -O2 -g
INCLUDES := -Iinclude

LIBFT_DIR := ./libft
LIBFT_AR := $(LIBFT_DIR)/libft.a
FT_FPRINTF_DIR := ./utils/fprintf
FT_FPRINTF_AR := $(FT_FPRINTF_DIR)/fprintf.a

NAME    := minishell
OBJDIR  := object

SRCS := \
    main.c \
    builtin/cd.c \
    builtin/cd2.c \
    builtin/echo.c \
    builtin/env.c \
    builtin/exit.c \
    builtin/export.c \
    builtin/export2.c \
    builtin/pwd.c \
    builtin/unset.c \
    builtin/unset2.c \
    executor/exec_builtin.c \
    executor/exec_child.c \
    executor/exec_fank.c \
    executor/exec_pipeline_loop.c \
    executor/exec_pipeline_utiles.c \
    executor/exec_redirectioin_builtin.c \
    executor/exec_redirection.c \
    executor/exec_searchpath.c \
    executor/exec_simple_command.c \
    executor/exec_util.c \
    expander/expander.c \
    expander/tilda.c \
    expander/utils.c \
    expander/utils2.c \
    expander/utils3.c \
    expander/utils4.c \
    expander/variables.c \
    expander/wildcard.c \
    get_next_line/get_next_line.c \
    get_next_line/get_next_line_utils.c \
    heredoc/heredoc.c \
    heredoc/heredoc2.c \
    heredoc/heredoc3.c \
    lexer/buf.c \
    lexer/buf2.c \
    lexer/lexer.c \
    lexer/lexer_actions.c \
    lexer/token.c \
    lexer/utils.c \
    linearizer/free_linearizer.c \
    linearizer/free_linerizer2.c \
    linearizer/linearizer.c \
    linearizer/linearizer2.c \
    linearizer/linearizer3.c \
    linearizer/linearlizer4.c \
    parser/free_parse.c \
    parser/parse_append.c \
    parser/parser.c \
    parser/parser2.c \
    parser/parser3.c \
    signal/signal.c \
    utils/assign_shell_var.c \
    utils/env_to_array.c \
    utils/env_utils.c \
    utils/env_utils2.c \
    utils/fprintf/conversions/ft_put_char_fd.c \
    utils/fprintf/conversions/ft_put_deci_fd.c \
    utils/fprintf/conversions/ft_put_hexa_lower_fd.c \
    utils/fprintf/conversions/ft_put_hexa_upper_fd.c \
    utils/fprintf/conversions/ft_put_int_fd.c \
    utils/fprintf/conversions/ft_put_per_fd.c \
    utils/fprintf/conversions/ft_put_ptr_fd.c \
    utils/fprintf/conversions/ft_put_str_fd.c \
    utils/fprintf/conversions/ft_put_unsigned_fd.c \
    utils/fprintf/ft_fprintf.c \
    utils/init_env.c \
    utils/run_readline.c \
    utils/safe_exit.c \
    utils/syntax_check.c \
    utils/xunistd.c

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
