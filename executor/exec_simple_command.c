/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:50:34 by shattori          #+#    #+#             */
/*   Updated: 2025/07/28 18:11:36 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_subshell(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		exit(executor(cmd->subshell_ast, shell));
	wait(&status);
	return (WEXITSTATUS(status));
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

static void	setup_child_process(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	handle_redirections(cmd);
	envp = convert_env(shell->env);
	path = search_path(cmd->argv[0], shell->env);
	if (!path)
		exit(127);
	if (execve(path, cmd->argv, envp) == -1)
		handle_execve_error(envp);
}

int	exec_simple_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		setup_child_process(cmd, shell);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		ft_fprintf(2, "%s: command not found\n", cmd->argv[0]);
	return (WEXITSTATUS(status));
}
