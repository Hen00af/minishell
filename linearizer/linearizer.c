/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:14:37 by shattori          #+#    #+#             */
/*   Updated: 2025/07/03 20:59:51 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./linearizer.h"

// ====== AND/OR ======
t_andor	*linearize_andor(t_ast *ast, t_shell *shell)
{
	t_andor	*node;

	node = malloc(sizeof(t_andor));
	if (!node)
		return (NULL);
	if (ast->type == NODE_AND)
		node->type = ANDOR_AND;
	else
		node->type = ANDOR_OR;
	node->left = linearizer(ast->left, shell);
	node->right = linearizer(ast->right, shell);
	return (node);
}

t_redir_type	map_redir_type(t_node_type type)
{
	if (type == NODE_REDIR_IN)
		return (REDIR_IN);
	if (type == NODE_REDIR_OUT)
		return (REDIR_OUT);
	if (type == NODE_REDIR_APPEND)
		return (REDIR_APPEND);
	if (type == NODE_HEREDOC)
		return (REDIR_HEREDOC);
	ft_fprintf(STDERROR_INT, "Unknown redirection type!\n");
	exit(1);
}

// ====== SIMPLE COMMAND ======
t_command	*linearize_simple_command_to_command(t_ast *ast, t_shell *shell)
{
	t_command		*cmd;
	t_command		*child;
	t_redirection	*redir;
	t_list			*redir_node;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = ast->argv;
	cmd->redirections = NULL;
	cmd->subshell_ast = NULL;
	if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
	{
		child = linearize_simple_command_to_command(ast->left, shell);
		redir = malloc(sizeof(t_redirection));
		redir->type = map_redir_type(ast->type);
		redir_node = ft_lstnew(redir);
		ft_lstadd_back(&child->redirections, redir_node);
		redir->filename = ast->filename;
		if (ast->type == NODE_HEREDOC)
			redir->filename = process_heredoc(redir_node, shell);
		free(cmd);
		return (child);
	}
	return (cmd);
}

t_andor	*linearize_simple_command(t_ast *ast, t_shell *shell)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	cmd = linearize_simple_command_to_command(ast, shell);
	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = ft_lstnew(cmd);
	andor = malloc(sizeof(t_andor));
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	return (andor);
}

// ====== PIPELINE ======
void	flatten_pipeline(t_ast *node, t_pipeline *pipeline, t_shell *shell)
{
	t_command	*cmd;
	t_list		*new_node;

	if (node->type == NODE_PIPE)
	{
		flatten_pipeline(node->left, pipeline, shell);
		flatten_pipeline(node->right, pipeline, shell);
	}
	else if (node->type == NODE_SUBSHELL)
	{
		cmd = malloc(sizeof(t_command));
		cmd->argv = NULL;
		cmd->redirections = NULL;
		cmd->subshell_ast = linearizer(node->left, shell);
		new_node = ft_lstnew(cmd);
		ft_lstadd_back(&pipeline->commands, new_node);
	}
	else
	{
		cmd = linearize_simple_command_to_command(node, shell);
		new_node = ft_lstnew(cmd);
		ft_lstadd_back(&pipeline->commands, new_node);
	}
}

t_andor	*linearize_pipeline(t_ast *ast, t_shell *shell)
{
	t_pipeline	*pipeline;
	t_andor		*node;

	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = NULL;
	flatten_pipeline(ast, pipeline, shell);
	node = malloc(sizeof(t_andor));
	node->type = ANDOR_PIPELINE;
	node->pipeline = pipeline;
	return (node);
}

// ====== SUBSHELL ======
t_andor	*linearize_subshell(t_ast *ast, t_shell *shell)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	cmd = malloc(sizeof(t_command));
	cmd->argv = NULL;
	cmd->redirections = NULL;
	cmd->subshell_ast = linearizer(ast->left, shell);
	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = ft_lstnew(cmd);
	andor = malloc(sizeof(t_andor));
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	return (andor);
}

// ====== DISPATCH ======
t_andor	*linearizer(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (NULL);
	if (ast->type == NODE_AND || ast->type == NODE_OR)
		return (linearize_andor(ast, shell));
	if (ast->type == NODE_PIPE)
		return (linearize_pipeline(ast, shell));
	if (ast->type == NODE_SUBSHELL)
		return (linearize_subshell(ast, shell));
	return (linearize_simple_command(ast, shell));
}

