/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:14:37 by shattori          #+#    #+#             */
/*   Updated: 2025/08/01 15:45:40 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./linearizer.h"

t_command	*linearize_handle_subshell(t_ast *ast, t_shell *shell,
		t_command *cmd)
{
	cmd = ft_calloc(1, sizeof(t_command));
	cmd->argv = NULL;
	cmd->redirections = NULL;
	cmd->subshell_ast = linearizer(ast->left, shell);
	return (cmd);
}

t_command	*linearize_ast_to_command(t_ast *ast, t_shell *shell)
{
	t_command		*cmd;
	t_command		*child;
	t_redirection	*redir;
	t_list			*redir_node;

	if (!ast)
		return (NULL);
	cmd = NULL;
	if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
	{
		child = linearize_ast_to_command(ast->left, shell);
		if (!child)
			return (NULL);
		redir = ft_calloc(1, sizeof(t_redirection));
		redir->type = map_redir_type(ast->type);
		redir->filename = ast->filename;
		redir_node = ft_lstnew(redir);
		ft_lstadd_back(&child->redirections, redir_node);
		return (child);
	}
	else if (ast->type == NODE_SUBSHELL)
		return (linearize_handle_subshell(ast, shell, cmd));
	else
		return (linearize_simple_command_to_command(ast, shell));
}

// ====== SIMPLE COMMAND ======
t_command	*linearize_simple_command_to_command(t_ast *ast, t_shell *shell)
{
	t_command		*cmd;
	t_command		*child;
	t_redirection	*redir;
	t_list			*redir_node;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = ast->argv;
	cmd->redirections = NULL;
	cmd->subshell_ast = NULL;
	if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
	{
		child = linearize_simple_command_to_command(ast->left, shell);
		redir = ft_calloc(1, sizeof(t_redirection));
		redir->type = map_redir_type(ast->type);
		redir_node = ft_lstnew(redir);
		ft_lstadd_back(&child->redirections, redir_node);
		redir->filename = ast->filename;
		free(cmd);
		return (child);
	}
	return (cmd);
}

void	flatten_pipeline(t_ast *node, t_pipeline *pipeline, t_shell *shell)
{
	t_command	*cmd;
	t_list		*new_node;

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
		ft_lstadd_back(&pipeline->commands, new_node);
	}
}

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
		return (NULL);
	pipeline->commands = ft_lstnew(cmd);
	if (!pipeline->commands)
		return (NULL);
	andor = ft_calloc(1, sizeof(t_andor));
	if (!andor)
		return (NULL);
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	return (andor);
}
