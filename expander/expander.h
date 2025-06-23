#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"
# include <dirent.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define NOTHING -1

typedef struct s_line	t_line;
typedef struct s_ast	t_ast;
typedef struct s_andor	t_andor;
typedef struct s_var
{
	int					start;
	int					len;
	char				*key;
	char				*value;
}						t_var;
typedef struct s_env	t_env;

t_var					*init_var(void);
int						search_variable(char *arg);
void					create_env_key(char *arg, t_var *var, int i);
void					search_env_value(t_var *var, t_env *env);
char					*make_new_arg(char *arg, t_var *var);
char					*expand_variables(char *arg, t_env *env_head);
char					*expand_tilda(char *arg, t_env *env);
char					*expand_wild_card(char *arg);
void					expander(t_andor *ast, t_env *env);


#endif // EXPANDER_H