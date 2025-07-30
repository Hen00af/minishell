/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:50:34 by shattori          #+#    #+#             */
/*   Updated: 2025/07/30 09:55:58 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_subshell(t_command *cmd, t_shell *shell, struct sigaction *old)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(executor(cmd->subshell_ast, shell));
	}
	waitpid(pid, &status, 0);
	if (old)
		sigaction(SIGINT, old, NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static void	handle_execve_error(char **envp)
{
	free_split(envp);
	if (errno == ENOENT || errno == EISDIR)
		exit(127);
	else
	{
		ft_fprintf(2, " Is a directory");
		exit(126);
	}
}

void	setup_child_process(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	handle_redirections(cmd);
	envp = convert_env(shell->env);
	path = search_path(cmd->argv[0], shell->env);
	if (!path)
	{
		ft_fprintf(2, "%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	if (execve(path, cmd->argv, envp) == -1)
		handle_execve_error(envp);
}
