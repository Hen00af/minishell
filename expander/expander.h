#ifndef EXPANDER_H
# define EXPANDER_H

//# include "../minishell.h"
# include "../libft/libft.h"
# include "../utils/utils.h"
# include <dirent.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define NOTHING -1

typedef struct s_line	t_line;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_OUT,
	NODE_REDIR_IN,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
}						t_node_type;

typedef struct s_ast
{
	t_node_type			type;
	struct s_ast		*left;
	struct s_ast		*right;
	char				**argv;
	int					argc;
}						t_ast;

typedef struct s_env
{
	char				*key;
	char				*value;
	int					flag;
	t_env				*next;
}						t_env;

typedef struct s_line
{
	t_node_type			type;
	char				**argv;
	t_line				*next;
	char				*filename;
}						t_line;

typedef struct s_var
{
	int					start;
	int					len;
	char				*key;
	char				*value;
}						t_var;

t_var					*init_var(void);
int						search_variable(char *arg);
void					create_env_key(char *arg, t_var *var, int i);
void					search_env_value(t_var *var, t_env *env);
char					*make_new_arg(char *arg, t_var *var);
char					*expand_variables(char *arg, t_env *env_head);
char					*expand_tilda(char *arg, t_env *env);
char					*expand_wild_card(char *arg);

#endif // EXPANDER_H