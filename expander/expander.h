/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:20:02 by nando             #+#    #+#             */
/*   Updated: 2025/06/26 20:51:29 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_line		t_line;
typedef struct s_ast		t_ast;
typedef struct s_andor		t_andor;
typedef struct s_env		t_env;
typedef struct s_command	t_command;
typedef struct s_file_node
{
	char					*name;
	struct s_file_node		*next;
}							t_file_node;

typedef struct s_var
{
	int						start;
	int						len;
	char					*key;
	char					*value;
}							t_var;

typedef struct s_expand
{
	char					*expanded;
	char					**split_words;
	char					**new_argv;
	int						count_av;
	int						count_sw;
	int						expand_point;
	int						wild_flag;
}							t_expand;

t_var						*init_var(void);
t_file_node					*create_new_node(char *file_name);
bool						has_wildcard(char *arg);
void						expand_all_type(char *arg, t_env *env);
void						free_args(char **argv);
void						swap_name(t_file_node *current, t_file_node *next);
void						free_file_list(t_file_node *head);
void						create_env_key(char *arg, t_var *var, int i);
void						search_env_value(t_var *var, t_env *env);
void						expander(t_andor *ast, t_env *env);
void						expand_andor_arguments(t_andor *ast, t_env *env);
int							count_args(char **args);
int							search_variable(char *arg);
char						*remove_quote(bool need_expand, char *arg);
char						*make_new_arg(char *arg, t_var *var);
char						*expand_variables(char *arg, t_env *env_head);
char						*expand_tilda(char *arg, t_env *env);
char						*expand_wild_card(char *arg);
bool						is_match(const char *pattern, const char *str,
								int i, int j);
bool						append_file_node(t_file_node **head,
								t_file_node **tail, char *name);
void						create_new_args(t_expand *ctx, t_command *cmd,
								int i);
void						generate_wildcard_matches(t_expand *ctx,
								t_command *cmd, int *i);

#endif // EXPANDER_H