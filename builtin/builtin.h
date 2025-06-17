#ifndef BUILTIN_H
# define BUILTIN_H

# define NG 1
# define OK 0

#include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env	t_env;

typedef struct s_echo
{
	int					option_flag;
	int					print_flag;
	int					count;
	int					i;
}						t_echo;

int						ft_strcmp(const char *string1, const char *string2);
int						builtin_cd(char **args, t_env *list_head);
int						builtin_echo(char **args);
int						builtin_env(char **args, t_env *list_head);
int						builtin_exit(char **args);
int						builtin_export(char **args, t_env **list_head);
int						builtin_pwd(char **args, t_env *list_head);
int						builtin_unset(char **args, t_env **list_head);

#endif // BUILTIN_H