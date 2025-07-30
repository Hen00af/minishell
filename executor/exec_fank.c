/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:24:41 by shattori          #+#    #+#             */
/*   Updated: 2025/07/30 10:51:44 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_pipeline_loop(t_list *cmd_list, t_exec *exec, t_shell *shell)
{
	t_command	*cmd;
	int			has_next;
	pid_t		pid;
	pid_t		last_pid;
	int			status;
	pid_t		wpid;

	last_pid = -1;
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (!cmd || (!cmd->argv && !cmd->subshell_ast))
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		has_next = (cmd_list->next != NULL);
		if (has_next && pipe(exec->pipefd) == -1)
			return (perror("pipe"), 1);
		pid = exec_child_process(exec, cmd, shell, has_next);
		if (pid == -1)
			return (1);
		last_pid = pid;
		if (exec->prev_fd != -1)
			close(exec->prev_fd);
		if (has_next)
			close(exec->pipefd[1]);
		exec->prev_fd = has_next ? exec->pipefd[0] : -1;
		cmd_list = cmd_list->next;
	}
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
	}
	return (shell->exit_status);
}

int	exec_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	t_exec		exec;
	t_list		*cmd_list;
	t_command	*cmd;

	sigaction(SIGINT, NULL, &exec.old);
	signal(SIGINT, SIG_IGN);
	exec.in = dup(STDIN_FILENO);
	exec.out = dup(STDOUT_FILENO);
	exec.prev_fd = -1;
	cmd_list = pipeline->commands;
	if (!cmd_list->next)
	{
		cmd = cmd_list->content;
		if (cmd->subshell_ast)
			shell->exit_status = exec_subshell(cmd, shell, &exec.old);
		else if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
			shell->exit_status = exec_single_builtin(cmd, &exec, shell);
		else
			shell->exit_status = exec_pipeline_loop(cmd_list, &exec, shell);
	}
	else
		shell->exit_status = exec_pipeline_loop(cmd_list, &exec, shell);
	dup2(exec.in, STDIN_FILENO);
	dup2(exec.out, STDOUT_FILENO);
	close(exec.in);
	close(exec.out);
	sigaction(SIGINT, &exec.old, NULL);
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
