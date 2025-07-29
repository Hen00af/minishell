/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:44:15 by shattori          #+#    #+#             */
/*   Updated: 2025/07/30 07:09:37 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	core_dumped_out(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	write(STDERR_FILENO, "Quit (core dumped)\n", 20);
}

int	exec_child_process(t_exec *exec, t_command *cmd, t_shell *shell,
		int has_next)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		sa.sa_sigaction = core_dumped_out;
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, NULL);
		if (exec->prev_fd != -1)
			dup2(exec->prev_fd, STDIN_FILENO);
		if (has_next)
			dup2(exec->pipefd[1], STDOUT_FILENO);
		if (exec->prev_fd != -1)
			close(exec->prev_fd);
		if (has_next)
		{
			close(exec->pipefd[0]);
			close(exec->pipefd[1]);
		}
		if (!g_ack_status)
			handle_redirections(cmd);
		if (cmd->subshell_ast)
			exit(exec_subshell(cmd, shell, NULL));
		else if (is_builtin(cmd->argv[0]))
			exit(exec_builtin(cmd->argv, shell));
		else
			setup_child_process(cmd, shell);
	}
	return (pid);
}

int	handle_child_and_parent(t_exec *exec, t_command *cmd, t_shell *shell,
		int has_next)
{
	exec->pid = fork();
	if (exec->pid == -1)
		return (perror("fork"), 1);
	if (exec->pid == 0)
		exec_child_process(exec, cmd, shell, has_next);
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
