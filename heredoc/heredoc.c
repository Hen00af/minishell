/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:34:59 by nando             #+#    #+#             */
/*   Updated: 2025/07/03 20:44:10 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*generate_tmpfile_path(void)
{
	static int	g_heredoc_count = 0;
	char		*heredoc_count_str;
	char		*path;
	char		*dest;
	size_t		idx;

	heredoc_count_str = ft_itoa(g_heredoc_count++);
	if (!heredoc_count_str || !(path = malloc(ft_strlen("/tmp/heredoc_")
				+ ft_strlen(heredoc_count_str) + ft_strlen(".tmp") + 1)))
	{
		free(heredoc_count_str);
		return (NULL);
	}
	dest = path;
	idx = 0;
	while ("/tmp/heredoc_"[idx])
		*dest++ = "/tmp/heredoc_"[idx++];
	idx = 0;
	while (heredoc_count_str[idx])
		*dest++ = heredoc_count_str[idx++];
	idx = 0;
	while (".tmp"[idx])
		*dest++ = ".tmp"[idx++];
	*dest = '\0';
	free(heredoc_count_str);
	return (path);
}

char	*run_heredoc(const char *delimiter, bool need_expand, t_shell *shell)
{
	char	*path;
	int		fd;
	char	*line;

	g_ack_status = 0;
	while (1)
	{
		path = generate_tmpfile_path();
		if (!path)
			return (NULL);
		fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd >= 0)
			break ;
		free(path);
	}
	while (1)
	{
		line = readline("> ");
		if (g_ack_status == 1)
		{
			free(line);
			unlink(path);
			free(path);
			path = NULL;
			break ;
		}
		if (!line)
			break ;
		if (strcmp(line, delimiter) == 0)
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
	close(fd);
	return (path);
}

char	*process_heredoc(t_list *redir_list, t_shell *shell)
{
	t_redirection	*redir;
	char			*tmpfile;
	bool			flag;

	if (!redir_list)
		return (NULL);
	tmpfile = NULL;
	flag = false;
	while (redir_list)
	{
		redir = (t_redirection *)redir_list->content;
		printf("redir->need_expand = %s\n",
			redir->need_expand ? "true" : "false");
		if (redir->type == REDIR_HEREDOC)
		{
			if (flag)
				unlink(tmpfile);
			tmpfile = run_heredoc(redir->filename, redir->need_expand, shell);
			if (!tmpfile)
				return (NULL);
			free(redir->filename);
			redir->filename = tmpfile;
			flag = true;
		}
		redir_list = redir_list->next;
	}
	return (redir->filename);
}
