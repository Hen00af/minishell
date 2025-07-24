/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:19:52 by nando             #+#    #+#             */
/*   Updated: 2025/07/24 19:34:52 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../expander/expander.h"
# include "../minishell.h"
# include "./fprintf/ft_fprintf.h"

typedef struct s_env	t_env;
typedef struct s_ctx	t_ctx;

void					free_env_list(t_env *env_list);
void					free_inserted_memory(char **result, int j);
char					*create_key(char const *s, char c);
char					*create_value(char const *s);
char					*create_key_value(t_env *list_head, char *tmp);
char					**create_split(char const *s, char **result, char c);
char					**env_split(char const *s, char c);
t_env					*create_env_node(char **key_value);
t_env					*init_env(char **envp);
char					**env_to_array(t_env *list_head);
void					assign_shell_var(char *var_str, t_env *list_head);
int						xclose(int *fd);

#endif // UTILS_H