/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:00:40 by nando             #+#    #+#             */
/*   Updated: 2025/07/30 10:22:27 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

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

char	*finalize_heredoc(pid_t pid, char *path, struct sigaction *old)
{
	int	status;

	waitpid(pid, &status, 0);
	sigaction(SIGINT, old, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_ack_status = 1;
		unlink(path);
		free(path);
		return (NULL);
	}
	return (path);
}
