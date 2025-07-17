/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:24:41 by shattori          #+#    #+#             */
/*   Updated: 2025/07/12 14:50:51 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <errno.h>

static int open_files(int *fd, char *last_tmpfile,t_redirection *redir)
{
		if (redir->type == REDIR_IN)
			*fd = open(redir->filename, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			*fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			*fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_HEREDOC)
		{
			if (!last_tmpfile)
			{
				fprintf(stderr, "heredoc error: heredoc filename is NULL\n");
				exit(1);
			}
			*fd = open(last_tmpfile, O_RDONLY);
		}
		if (*fd < 0)
		{
			perror("redirection");
			exit(1);
		}
}

static void	handle_redirections(t_command *cmd)
{
	t_list			*redir_list;
	t_redirection	*redir;
	int				fd;
	char			*last_tmpfile;

	redir_list = cmd->redirections;
	while (redir_list)
	{
		redir = redir_list->content;
		last_tmpfile = cmd->heredoc_filename;
		fd = -1;
		open_files(&fd,last_tmpfile,redir);
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir_list = redir_list->next;
	}
}

static int	handle_redirections_builtin(t_command *cmd)
{
	t_list			*redir_list;
	t_redirection	*redir;
	int				fd;
	char			*last_tmpfile;

	redir_list = cmd->redirections;
	while (redir_list)
	{
		redir = redir_list->content;
		last_tmpfile = cmd->heredoc_filename;
		fd = -1;
		open_files(&fd,last_tmpfile,redir);
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir_list = redir_list->next;
	}
	return (0);
}

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

char	*search_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_var = get_env_value("PATH", env);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ":");
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
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

static int	exec_subshell(t_command *cmd, t_shell *shell)
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

int	exec_simple_command(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		handle_redirections(cmd);
		envp = convert_env(shell->env);
		path = search_path(cmd->argv[0], shell->env);
		if (!path)
			exit(127);
		if (execve(path, cmd->argv, envp) == -1)
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
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
		ft_fprintf(2, "%s: command not found\n", cmd->argv[0]);
	return (WEXITSTATUS(status));
}

static int	exec_pipeline(t_pipeline *pipeline, t_shell *shell)
{
	int			pipefd[2];
	int			prev_fd;
	pid_t		pid;
	t_list		*cmd_list;
	t_command	*cmd;
	int			in;
	int			out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	prev_fd = -1;
	cmd_list = pipeline->commands;
	if (!cmd_list->next)
	{
		cmd = cmd_list->content;
		if (cmd->subshell_ast)
			return (exec_subshell(cmd, shell));
		if (is_builtin(cmd->argv[0]))
		{
			if (handle_redirections_builtin(cmd))
			{
				shell->exit_status = 1;
				dup2(in, STDIN_FILENO);
				dup2(out, STDOUT_FILENO);
				return (shell->exit_status);
			}
			shell->exit_status = exec_builtin(cmd->argv, shell->env);
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			return (shell->exit_status);
		}
	}
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (!cmd || !cmd->argv || !cmd->argv[0])
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		if (cmd_list->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		else if (pid == 0)
		{
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			if (cmd_list->next)
				dup2(pipefd[1], STDOUT_FILENO);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd_list->next)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			handle_redirections(cmd);
			if (cmd->subshell_ast)
			{
				exit(exec_subshell(cmd, shell));
			}
			else if (is_builtin(cmd->argv[0]))
				exit(exec_builtin(cmd->argv, shell->env));
			else
				exit(exec_simple_command(cmd, shell));
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd_list->next)
			close(pipefd[1]);
		prev_fd = cmd_list->next ? pipefd[0] : -1;
		cmd_list = cmd_list->next;
	}
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
 