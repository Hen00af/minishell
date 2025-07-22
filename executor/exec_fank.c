/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:24:41 by shattori          #+#    #+#             */
/*   Updated: 2025/07/22 10:56:58 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	exec_child_process(t_exec *exec, t_command *cmd, t_shell *shell,
				int has_next)
{
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
	handle_redirections(cmd);
	if (cmd->subshell_ast)
		exit(exec_subshell(cmd, shell));
	else if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd->argv, shell->env));
	exit(exec_simple_command(cmd, shell));
}

static int	exec_pipeline_loop(t_list *cmd_list, t_exec *exec, t_shell *shell)
{
	t_command	*cmd;

	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (!cmd || !cmd->argv || !cmd->argv[0])
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		if (cmd_list->next && pipe(exec->pipefd) == -1)
			return (perror("pipe"), 1);
		exec->pid = fork();
		if (exec->pid == -1)
			return (perror("fork"), 1);
		else if (exec->pid == 0)
			exec_child_process(exec, cmd, shell, !!cmd_list->next);
		if (exec->prev_fd != -1)
			close(exec->prev_fd);
		if (cmd_list->next)
			close(exec->pipefd[1]);
		exec->prev_fd = cmd_list->next ? exec->pipefd[0] : -1;
		cmd_list = cmd_list->next;
	}
	return (0);
}

static int	exec_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	t_exec	exec;
	t_list	*cmd_list;
	t_command	*cmd;

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
			return (exec_single_builtin(cmd, &exec, shell));
	}
	if (exec_pipeline_loop(cmd_list, &exec, shell) != 0)
		return (1);
	while (wait(&shell->exit_status) > 0)
		shell->exit_status = WEXITSTATUS(shell->exit_status);
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
