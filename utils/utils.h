/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:19:52 by nando             #+#    #+#             */
/*   Updated: 2025/07/28 11:53:18 by shattori         ###   ########.fr       */
/*   Updated: 2025/07/25 09:31:31 by shattori         ###   ########.fr       */
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
int						has_syntax_error(t_token *tokens);
int						print_syntax_error(const char *token_text,
							t_tokentype type);

#endif // UTILS_H