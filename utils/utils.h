#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"
# include "./fprintf/ft_fprintf.h"

typedef struct s_env	t_env;
typedef struct s_ctx	t_ctx;

t_env					*create_env_node(char **key_value);
char					**env_split(char const *s, char c);
t_env					*init_env(char **envp);
void					print_env_list(t_env *head);
char					**env_to_array(t_env *list_head);
void					assign_shell_var(char *var_str, t_env *list_head);

#endif // UTILS_H