/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:32:05 by nando             #+#    #+#             */
/*   Updated: 2025/07/10 19:32:07 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define NG 1
# define OK 0

# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
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
void					set_key_value(char **key_value, char *pwd, char *cwd);
int						update_pwd_value(t_env *node, const char *cwd);
int						create_pwd_node(t_env *node, char **key_value);
int						check_cd_args(char **args);
void					free_key_value(char **key_value);
void					sort_array(char **array);
int						sort_and_print_environ(t_env *env);
int						is_valid_key(char *key);
t_env					*create_env_node_only_key(char *key);
int						is_valid_initial(char c);
int						ft_strcmp(const char *string1, const char *string2);
void					delete_list_head(t_env **env);
int						delete_env_node(t_env *prev, const char *target_key);
int						builtin_cd(char **args, t_env *env);
int						builtin_echo(char **args, t_env *env);
int						builtin_env(char **args, t_env *env);
int						builtin_pwd(char **args, t_env *env);
int						builtin_env(char **args, t_env *env);
int						builtin_export(char **args, t_env **env);
int						builtin_unset(char **args, t_env **env);
int						builtin_exit(char **args);

#endif // BUILTIN_H