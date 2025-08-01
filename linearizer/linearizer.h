/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:14:13 by shattori          #+#    #+#             */
/*   Updated: 2025/07/30 09:34:17 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/* ************************************************************************** */

#ifndef LINEARIZER_H
# define LINEARIZER_H

# include "../minishell.h"
# include <stdbool.h>
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
	bool					need_expand;
}							t_redirection;

typedef struct s_command
{
	char					**argv;
	char					*heredoc_filename;
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

t_andor						*linearize_andor(t_ast *ast, t_shell *shell);
t_redir_type				map_redir_type(t_node_type type);
t_command					*linearize_simple_command_to_command(t_ast *ast,
								t_shell *shell);
void						flatten_pipeline(t_ast *node, t_pipeline *pipeline,
								t_shell *shell);
t_andor						*linearize_subshell(t_ast *ast, t_shell *shell);
t_andor						*linearize_simple_command(t_ast *ast,
								t_shell *shell);
t_andor						*linearizer(t_ast *ast, t_shell *shell);
t_andor						*linearize_pipeline(t_ast *ast, t_shell *shell);
void						free_andor_ast(t_andor *node);
t_redir_type				map_redir_type(t_node_type type);
t_andor						*linearize_andor(t_ast *ast, t_shell *shell);
#endif // LINEARIZER
