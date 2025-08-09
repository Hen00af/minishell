/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:24:41 by shattori          #+#    #+#             */
/*   Updated: 2025/08/09 12:52:54 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	t_exec	exec;
	t_list	*cmd_list;
	int		exit_status;

	sigaction(SIGINT, NULL, &exec.old);
	if (save_std_fds(&exec))
	{
		printf("\n\n\n\n");
		return (1);
	}
	exec.prev_fd = -1;
	signal(SIGINT, SIG_IGN);
	cmd_list = pipeline->commands;
	if (!cmd_list)
		exit_status = 0;
	else if (!cmd_list->next)
		exit_status = exec_single_command(cmd_list, &exec, shell);
	else
		exit_status = exec_pipeline_loop(cmd_list, &exec, shell);
	restore_std_fds(&exec);
	sigaction(SIGINT, &exec.old, NULL);
	shell->exit_status = exit_status;
	return (exit_status);
}

static int	exec_andor(t_andor *node, t_shell *shell)
{
	int	left_status;
	int	right_status;

	left_status = executor(node->left, shell);
	if ((node->type == ANDOR_AND && left_status == 0) || (node->type == ANDOR_OR
			&& left_status != 0))
	{
		right_status = executor(node->right, shell);
		shell->exit_status = right_status;
		return (right_status);
	}
	shell->exit_status = left_status;
	return (left_status);
}

int	executor(t_andor *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == ANDOR_AND || node->type == ANDOR_OR)
		return (exec_andor(node, shell));
	if (node->type == ANDOR_PIPELINE)
		return (exec_pipeline(node->pipeline, shell));
	return (1);
}
