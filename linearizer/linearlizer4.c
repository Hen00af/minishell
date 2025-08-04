/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearlizer4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:33:18 by shattori          #+#    #+#             */
/*   Updated: 2025/08/04 14:42:36 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linearizer.h"

t_command	*linearize_handle_subshell(t_ast *ast, t_shell *shell)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirections = NULL;
	cmd->subshell_ast = linearizer(ast->left, shell);
	return (cmd);
}

t_command	*linearize_ast_to_command(t_ast *ast, t_shell *shell)
{
	t_command	*child;

	if (!ast)
		return (NULL);
	if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
	{
		child = linearize_ast_to_command(ast->left, shell);
		if (!child)
			return (NULL);
		if (!add_redirection(child, ast))
		{
			free_command(child);
			return (NULL);
		}
		return (child);
	}
	else if (ast->type == NODE_SUBSHELL)
	{
		return (linearize_handle_subshell(ast, shell));
	}
	else
	{
		return (linearize_simple_command_to_command(ast, shell));
	}
}

t_command	*linearize_simple_command_to_command(t_ast *ast, t_shell *shell)
{
	t_command	*cmd;

	(void)shell;
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = copy_argv_line(ast->argv);
	if (!cmd->argv && ast->argv)
	{
		free_command(cmd);
		return (NULL);
	}
	cmd->redirections = NULL;
	cmd->subshell_ast = NULL;
	return (cmd);
}

void	flatten_pipeline(t_ast *node, t_pipeline *pipeline, t_shell *shell)
{
	t_command	*cmd;
	t_list		*new_node;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		flatten_pipeline(node->left, pipeline, shell);
		flatten_pipeline(node->right, pipeline, shell);
	}
	else
	{
		cmd = linearize_ast_to_command(node, shell);
		if (!cmd)
			return ;
		process_heredoc(cmd, shell);
		new_node = ft_lstnew(cmd);
		if (!new_node)
		{
			free_command(cmd);
			return ;
		}
		ft_lstadd_back(&pipeline->commands, new_node);
	}
}

// void free_command_and_pipe()
// {
	
// }

t_andor	*linearize_subshell(t_ast *ast, t_shell *shell)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	cmd = linearize_ast_to_command(ast, shell);
	if (!cmd)
		return (NULL);
	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
	{
		free_command(cmd);
		return (NULL);
	}
	pipeline->commands = ft_lstnew(cmd);
	if (!pipeline->commands)
	{
		free_command(cmd);
		free(pipeline);
		return (NULL);
	}
	andor = ft_calloc(1, sizeof(t_andor));
	if (!andor)
	{
		free_command(cmd);
		free(pipeline);
		return (NULL);
	}
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	return (andor);
}
