/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:00:40 by nando             #+#    #+#             */
/*   Updated: 2025/07/31 22:40:24 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

void	write_heredoc_lines(int fd, char *clean_delimiter, int need_expand,
		t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_ack_status == 1 || !line)
		{
			free(line);
			break ;
		}
		if (ft_strcmp(line, clean_delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (need_expand)
			line = expand_variables(line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	child_heredoc_process(int fd, char *delimiter, int expand,
		t_shell *shell)
{
	write_heredoc_lines(fd, delimiter, expand, shell);
	close(fd);
	free(delimiter);
	_exit(0);
}

char	*handle_fork_error(int fd, char *delimiter, char *path)
{
	perror("fork");
	free(delimiter);
	free(path);
	close(fd);
	return (NULL);
}

t_heredoc_file	open_and_prepare_file(char *delimiter, char **clean_delimiter)
{
	t_heredoc_file	file;

	*clean_delimiter = remove_quote(delimiter);
	file.fd = open_heredoc_file(&file.path);
	if (file.fd < 0)
		free(*clean_delimiter);
	return (file);
}

char	*finalize_heredoc(pid_t pid, t_heredoc_file *path,
		struct sigaction *old, char *clean_delim)
{
	int	status;

	waitpid(pid, &status, 0);
	sigaction(SIGINT, old, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_ack_status = 1;
		unlink(path->path);
		return (NULL);
	}
	free(clean_delim);
	close(path->fd);
	return (path->path);
}
