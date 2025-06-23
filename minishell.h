#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "builtin/builtin.h"
# include "executor/executor.h"
# include "expander/expander.h"
# include "lexer/lexer.h"
# include "libft/libft.h"
# include "linerlizer/linerlizer.h"
# include "parser/parser.h"
# include "signal/signal.h"
# include "utils/utils.h"
# include <readline/history.h>
# include <readline/readline.h>

# define STDERROR_INT 2
# define STDOUT_INT 1


// typedef enum e_node_type
// {
// 	NODE_COMMAND,
// 	NODE_PIPE,
// 	NODE_REDIR_OUT,
// 	NODE_REDIR_IN,
// 	NODE_REDIR_APPEND,
// 	NODE_HEREDOC
// }					t_node_type;

// typedef struct s_ast
// {
// 	t_node_type		type;
// 	struct s_ast	*left;
// 	struct s_ast	*right;
// 	char			**argv;
// 	int				argc;
// }					t_ast;

typedef struct s_env
{
	char	*key;
	char	*value;
	int		flag;
	t_env	*next;
}			t_env;

typedef struct s_ctx
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	char	**key_value;
}			t_ctx;

#endif
