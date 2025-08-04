/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:00:40 by nando             #+#    #+#             */
/*   Updated: 2025/08/04 17:13:23 by nando            ###   ########.fr       */
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

char	*handle_fork_error(int fd, char *delimiter, char *path)
{
	perror("fork");
	free(delimiter);
	free(path);
	close(fd);
	return (NULL);
}

int	open_heredoc_file(char **path)
{
	char	*tmp_path;
	int		fd;

	tmp_path = generate_tmpfile_path();
	if (!tmp_path)
		return (-1);
	while (1)
	{
		fd = open(tmp_path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd >= 0)
			break ;
		free(tmp_path);
		tmp_path = generate_tmpfile_path();
		if (!tmp_path)
			return (-1);
	}
	*path = tmp_path;
	return (fd);
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
