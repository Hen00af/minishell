// parser.h

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC,
	NODE_SUBSHELL
}					t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	char			**argv;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*filename;
}					t_ast;

t_ast				*parse_command(t_token **cur);
t_ast				*parse_command_or_subshell(t_token **cur);
t_ast				*parse_pipeline(t_token **cur);
t_ast				*parse_subshell(t_token **cur);
t_ast				*start_parse(t_token *tokens);
static t_ast		*create_ast_node(t_node_type type, t_ast *left,
						t_ast *right);
static t_ast		*parse_and_or(t_token **cur);
static t_ast		*parse_simple_command(t_token **cur);
void				print_ast(t_ast *node, int depth);
void				free_ast(t_ast *node);

#endif
