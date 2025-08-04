/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:36:01 by shattori          #+#    #+#             */
/*   Updated: 2025/08/04 13:08:04 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linearizer.h"

t_andor	*linearize_simple_command(t_ast *ast, t_shell *shell)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	(void)shell;
	printf("linearize_simple_command: \n");
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

t_andor	*linearizer(t_ast *ast, t_shell *shell)
{
	printf("linearizer: \n");
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

	printf("linearize_pipeline: \n");
	pipeline = ft_calloc(1, sizeof(t_pipeline));
	pipeline->commands = NULL;
	flatten_pipeline(ast, pipeline, shell);
	node = ft_calloc(1, sizeof(t_andor));
	node->type = ANDOR_PIPELINE;
	node->pipeline = pipeline;
	return (node);
}
