/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:36:01 by shattori          #+#    #+#             */
/*   Updated: 2025/08/04 21:41:48 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linearizer.h"

t_andor	*linearize_free_simple_command(t_command *cmd, t_pipeline *pipeline)
{
	free_command(cmd);
	free(pipeline);
	return (NULL);
}

t_andor	*linearize_simple_command(t_ast *ast, t_shell *shell)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	(void)shell;
	cmd = linearize_ast_to_command(ast, shell);
	if (!cmd)
		return (NULL);
	process_heredoc(cmd, shell);
	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
	{
		free_command(cmd);
		return (NULL);
	}
	pipeline->commands = ft_lstnew(cmd);
	if (!pipeline->commands)
		return (linearize_free_simple_command(cmd, pipeline));
	andor = ft_calloc(1, sizeof(t_andor));
	if (!andor)
		return (linearize_free_simple_command(cmd, pipeline));
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	return (andor);
}

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

t_andor	*linearize_pipeline(t_ast *ast, t_shell *shell)
{
	t_pipeline	*pipeline;
	t_andor		*node;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	pipeline->commands = NULL;
	flatten_pipeline(ast, pipeline, shell);
	node = ft_calloc(1, sizeof(t_andor));
	node->type = ANDOR_PIPELINE;
	node->pipeline = pipeline;
	return (node);
}
