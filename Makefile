CC      := cc
CFLAGS  := -O2 -no-pie
INCLUDES := -Iinclude

NAME    := minishell
OBJDIR  := object
SRC_DIRS := \
	./expander \
	./parser \
	./lexer \
	./linearizer\
	./executor \
	./builtin \
	./utils \
	./signal \
	./heredoc\
	./

SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

OBJS := $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

LIBS := ./utils/fprintf/fprintf.a ./libft/libft.a -lreadline

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: all
	./$(NAME) $(HOME)

clean:
	@rm -rf $(OBJDIR)
	@echo "🧹 Object files removed"

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️ Executable removed"

re: fclean all
