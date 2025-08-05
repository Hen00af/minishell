/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:50:12 by shattori          #+#    #+#             */
/*   Updated: 2025/08/05 15:45:06 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	spawn_pipeline_cmd(t_list *cmd_list, t_exec *exec, t_shell *shell,
		pid_t *last_pid)
{
	t_command	*cmd;
	int			has_next;
	pid_t		pid;

	cmd = cmd_list->content;
	if (!cmd || (!cmd->argv && !cmd->subshell_ast))
		return (0);
	has_next = (cmd_list->next != NULL);
	if (has_next && pipe(exec->pipefd) == -1)
		return (perror("pipe"), 1);
	pid = exec_child_process(exec, cmd, shell, has_next);
	if (pid == -1)
		return (1);
	*last_pid = pid;
	if (exec->prev_fd != -1)
		close(exec->prev_fd);
	if (has_next)
		close(exec->pipefd[1]);
	if (has_next)
		exec->prev_fd = exec->pipefd[0];
	else
		exec->prev_fd = -1;
	return (0);
}

static void	wait_for_pipeline(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	wpid;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		wpid = wait(&status);
	}
}

int	exec_pipeline_loop(t_list *cmd_list, t_exec *exec, t_shell *shell)
{
	pid_t	last_pid;

	last_pid = -1;
	while (cmd_list)
	{
		if (spawn_pipeline_cmd(cmd_list, exec, shell, &last_pid))
			return (1);
		cmd_list = cmd_list->next;
	}
	wait_for_pipeline(last_pid, shell);
	return (shell->exit_status);
}
