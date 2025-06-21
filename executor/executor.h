#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_ast	t_ast;
typedef struct s_andor	t_andor;
typedef struct s_env	t_env;

int						executor(t_andor *node, t_env *env);
int						exec_builtin(char **argv, t_env *env);
char					**convert_env(t_env *env);
char					*search_path(char *cmd, t_env *env);
char					*get_env_value(const char *name, t_env *env);
char					*ft_strjoin_path(char *dir, char *file);
int						env_size(t_env *env);
char					*ft_strjoin_3(char *s1, char *s2, char *s3);
int						executor(t_andor *node, t_env *env);

#endif