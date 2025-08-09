/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utiles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:48:28 by shattori          #+#    #+#             */
/*   Updated: 2025/08/09 13:16:01 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	save_std_fds(t_exec *exec)
{
	exec->in = dup(STDIN_FILENO);
	exec->out = dup(STDOUT_FILENO);
	if (exec->in == -1 || exec->out == -1)
	{
		perror("dup");
		if (exec->in != -1)
			close(exec->in);
		if (exec->out != -1)
			close(exec->out);
		return (1);
	}
	return (0);
}

int	restore_std_fds(t_exec *exec)
{
	dup2(exec->in, STDIN_FILENO);
	dup2(exec->out, STDOUT_FILENO);
	close(exec->in);
	close(exec->out);
	return (0);
}

int	exec_single_command(t_list *cmd_list, t_exec *exec, t_shell *shell)
{
	t_command	*cmd;

	cmd = cmd_list->content;
	if (cmd->subshell_ast)
		return (exec_subshell(cmd, shell, &exec->old, exec));
	else if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
		return (exec_single_builtin(cmd, exec, shell));
	return (exec_pipeline_loop(cmd_list, exec, shell));
}
