/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:24:41 by shattori          #+#    #+#             */
/*   Updated: 2025/07/28 18:04:02 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exec_pipeline_loop(t_list *cmd_list, t_exec *exec, t_shell *shell)
{
	t_command	*cmd;
	int			has_next;

	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (!cmd || !cmd->argv || !cmd->argv[0])
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		has_next = (cmd_list->next != NULL);
		if (has_next && pipe(exec->pipefd) == -1)
			return (perror("pipe"), 1);
		if (handle_child_and_parent(exec, cmd, shell, has_next))
			return (1);
		cmd_list = cmd_list->next;
	}
	return (0);
}

static int	exec_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	t_exec		exec;
	t_list		*cmd_list;
	t_command	*cmd;
	int			i;

	exec.in = dup(STDIN_FILENO);
	exec.out = dup(STDOUT_FILENO);
	exec.prev_fd = -1;
	cmd_list = pipeline->commands;
	if (!cmd_list->next)
	{
		cmd = cmd_list->content;
		if (cmd->subshell_ast)
			return (exec_subshell(cmd, shell));
		if (is_builtin(cmd->argv[0]))
		{
			i = exec_single_builtin(cmd, &exec, shell);
			printf("builtin exit = %d\n", i);
			return (i);
		}
	}
	if (exec_pipeline_loop(cmd_list, &exec, shell) != 0)
		return (1);
	while (wait(&shell->exit_status) > 0)
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	printf("exit = %d\n", shell->exit_status);
	return (shell->exit_status);
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
