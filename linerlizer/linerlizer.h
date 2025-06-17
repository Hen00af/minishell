/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linerlizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:14:13 by shattori          #+#    #+#             */
/*   Updated: 2025/06/17 16:51:36 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINERIZER_H
# define LINERIZER_H

# include "../minishell.h"
# include <stdio.h>

typedef struct s_ast		t_ast;
typedef enum e_node_type	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*filename;
}							t_redirection;

typedef struct s_command
{
	char					**argv;
	t_list					*redirections;
	struct s_andor			*subshell_ast;
}							t_command;

typedef struct s_pipeline
{
	t_list					*commands;
}							t_pipeline;

typedef enum e_andor_type
{
	ANDOR_PIPELINE,
	ANDOR_AND,
	ANDOR_OR
}							t_andor_type;

typedef struct s_andor
{
	t_andor_type			type;
	union
	{
		struct
		{
			struct s_andor	*left;
			struct s_andor	*right;
		};
		t_pipeline			*pipeline;
	};
}							t_andor;

void						flatten_pipeline(t_ast *node, t_pipeline *pipeline);
t_andor						*linearize_simple_command(t_ast *ast);
t_andor						*linearizer(t_ast *ast);
t_redir_type				map_redir_type(t_node_type type);

//テスト用関数
void						print_linerlized_ast(t_andor *tree, int indent);
void						print_commands(t_pipeline *pipeline, int indent);
void						print_redirections(t_list *redir_list, int indent);

#endif
