#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin/builtin.h"
# include "executor/executor.h"
# include "expander/expander.h"
# include "lexer/lexer.h"
# include "libft/libft.h"
# include "parser/parser.h"
# include "signal/signal.h"
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_OUT,
	NODE_REDIR_IN,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
}					t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**argv;
	int				argc;
}					t_ast;

#endif
