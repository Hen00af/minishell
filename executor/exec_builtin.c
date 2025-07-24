/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:55:03 by shattori          #+#    #+#             */
/*   Updated: 2025/07/24 17:18:33 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

int	exec_builtin(char **argv, t_env *env)
{
	if (!argv || !argv[0])
		return (1);
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv, env));
	else if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, env));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd(argv, env));
	else if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, &env));
	else if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, &env));
	else if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(argv, env));
	else if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv));
	return (1);
}

int	exec_single_builtin(t_command *cmd, t_exec *exec, t_shell *shell)
{
	if (handle_redirections_builtin(cmd))
	{
		shell->exit_status = 1;
		dup2(exec->in, STDIN_FILENO);
		dup2(exec->out, STDOUT_FILENO);
		return (1);
	}
	shell->exit_status = exec_builtin(cmd->argv, shell->env);
	dup2(exec->in, STDIN_FILENO);
	dup2(exec->out, STDOUT_FILENO);
	return (1);
}
