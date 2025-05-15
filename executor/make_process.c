/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:39:08 by shattori          #+#    #+#             */
/*   Updated: 2025/05/15 16:33:26 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char **environ)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(environ[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(environ[i] + 5, ":");
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	noting_path(paths);
	return (NULL);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	exit(127);
}

void	execute(char *cmd)
{
	extern char	**environ;
	char		**args;
	char		*path;

	if (environ == NULL)
	{
		error();
		exit(1);
	}
	args = ft_split(cmd, " ");
	if (!args || !args[0])
		free_split(args);
	if (execve(args[0], args, environ) == -1)
	{
		path = find_path(args[0], environ);
		if (path == NULL)
			free_split(args);
		if (execve(path, args, environ) == -1)
		{
			free(path);
			free_split(args);
		}
	}
}

void	handle_child(t_pipe_fd pipe_fds, char *cmd, int is_last, char *outfile)
{
	int	fd_out;

	if (dup2(pipe_fds.fd_in, STDIN_FILENO) == -1)
		error();
	close(pipe_fds.fd_in);
	if (!is_last)
	{
		close(pipe_fds.pipe_fd[0]);
		if (dup2(pipe_fds.pipe_fd[1], STDOUT_FILENO) == -1)
			error();
		close(pipe_fds.pipe_fd[1]);
	}
	else
	{
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			error_output_fd(pipe_fds.fd_in, fd_out);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			error();
		close(fd_out);
	}
	execute(cmd);
	exit(0);
}

int	make_process(int argc, char **argv, int i)
{
	t_pipe_fd	pipe_fds;

	pipe_fds.fd_in = open(argv[1], O_RDONLY);
	if (pipe_fds.fd_in < 0)
		error_pipe(pipe_fds);
	while (i < argc - 1)
	{
		if (i < argc - 2 && pipe(pipe_fds.pipe_fd) == -1)
			error();
		pipe_fds.pid = fork();
		if (pipe_fds.pid == -1)
			error();
		if (pipe_fds.pid == 0)
			handle_child(pipe_fds, argv[i], i == argc - 2, argv[argc - 1]);
		if (pipe_fds.fd_in != 0)
			close(pipe_fds.fd_in);
		if (i < argc - 2)
			close(pipe_fds.pipe_fd[1]);
		pipe_fds.fd_in = pipe_fds.pipe_fd[0];
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
