#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin/builtin.h"
# include "executor/executor.h"
# include "expander/expander.h"
# include "lexer/lexer.h"
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

typedef enum e_tokentype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_REDIR_APP,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_EOF
}	t_token_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**argv;
	int				argc;
}					t_ast;

typedef struct s_token
{
	TokenType type;
	char *text;
	struct s_token *next;
}	t_token;

#endif
