/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:20:02 by nando             #+#    #+#             */
/*   Updated: 2025/07/09 11:33:32 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../lexer/lexer.h"
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
typedef struct s_shell		t_shell;

typedef enum e_qstate
{
	STA_NONE_Q,
	STA_DOUBLE_Q,
	STA_SINGLE_Q
}							t_qstate;

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
	t_buf					buf;
	t_qstate				state;
	char					*output;
}							t_expand;

t_var						*init_var(void);
int							count_args(char **args);
void						free_args(char **argv);
void						free_file_list(t_file_node *head);
bool						has_wildcard(char *arg);
void						generate_wildcard_matches(t_expand *ctx,
								t_command *cmd, int *i);
t_file_node					*create_new_node(char *file_name);
bool						append_file_node(t_file_node **head,
								t_file_node **tail, char *name);
void						swap_name(t_file_node *current, t_file_node *next);
char						*expand_wild_card(char *arg, t_expand *ctx);
int							search_variable(char *arg, int start);
void						create_env_key(char *arg, t_var *var, int i);
void						search_env_value(t_var *var, t_shell *shell);
char						*make_new_arg(char *arg, t_var *var);
char						*expand_variables(char *arg, t_shell *shell);
char						*expand_tilda(char *arg, t_env *env);
char						*remove_quote(char *arg);
char						*expand_all_type(char *arg, t_shell *shell,
								t_expand *ctx);
void						expander(t_andor *ast, t_shell *shell);
void						expand_andor_arguments(t_andor *ast,
								t_shell *shell);
void						expand_command_args(t_command *cmd, t_shell *shell,
								t_list *cmd_list);
char						*expand_string(char *arg, t_shell *shell,
								t_expand *ctx);
bool						is_match(const char *pattern, const char *str,
								int i, int j);

#endif // EXPANDER_H