#ifndef EXPANDER_H
# define EXPANDER_H

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