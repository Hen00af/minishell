/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:24:41 by shattori          #+#    #+#             */
/*   Updated: 2025/07/29 21:29:38 by shattori         ###   ########.fr       */
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
		shell->exit_status = exec_child_process(exec, cmd, shell, has_next);
		printf("exit status = %d(before)\n", shell->exit_status);
		if (shell->exit_status)
			return (1);
		printf("exit status = %d\n", shell->exit_status);
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

	sigaction(SIGINT, NULL, &exec.old);
	signal(SIGINT, SIG_IGN);
	printf("exec_pipeline \n");
	exec.in = dup(STDIN_FILENO);
	exec.out = dup(STDOUT_FILENO);
	exec.prev_fd = -1;
	cmd_list = pipeline->commands;
	printf("%d\n", shell->exit_status);
	if (!cmd_list->next)
	{
		cmd = cmd_list->content;
		if (cmd->subshell_ast)
			return (exec_subshell(cmd, shell, &exec.old));
		if (is_builtin(cmd->argv[0]))
		{
			i = exec_single_builtin(cmd, &exec, shell);
			printf("builtin exit = %d\n", i);
			return (i);
		}
	}
	if (exec_pipeline_loop(cmd_list, &exec, shell) != 0)
		return (1);
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
