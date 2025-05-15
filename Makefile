CC = cc
CFLAGS = -O2 -Wall -Wextra -Werror 
OBJDIR = object
# sub dir
DIRS = lexer parser expander builtin \
	   executor utils
# transfer .c to .o
SRCS := $(wildcard main.c $(foreach dir, $(DIRS),$(dir)/*.c))
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o, $(OBJDIR)/%.o, $(OBJS))
# header
INCLUDES = -Iinclude
#name of exe file
NAME = minishell

# rules
all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) -lreadline 

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	
clean:
	@rm -rf $(OBJDIR)
	@echo "All object files are deleted !!"

fclean: clean
	@rm -f $(NAME)
	@echo "Exe file is deleted !!"

re: fclean all

.PHONY: all clean fclean re
