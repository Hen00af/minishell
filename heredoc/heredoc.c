/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:34:59 by nando             #+#    #+#             */
/*   Updated: 2025/07/04 19:18:47 by nando            ###   ########.fr       */
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

int	is_include_quote(char *delimiter)
{
	int	need_expand;
	int	len;

	len = ft_strlen(delimiter);
	if (delimiter[0] == '\"' && delimiter[len - 1] == '\"'
		|| delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		return (0);
	return (1);
}

char	*run_heredoc(char *delimiter, t_shell *shell)
{
	char	*path;
	int		fd;
	char	*line;
	char	*clean_delimiter;
	int		need_expand;

	g_ack_status = 0;
	need_expand = is_include_quote(delimiter);
	clean_delimiter = remove_quote(delimiter);
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
		if (strcmp(line, clean_delimiter) == 0)
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
	free(clean_delimiter);
	close(fd);
	return (path);
}

void	process_heredoc(t_command *cmd, t_shell *shell)
{
	t_list			*redir_list;
	t_redirection	*redir;
	char			*tmpfile;
	int				flag;

	if (!cmd || !cmd->redirections)
		return ;
	redir_list = cmd->redirections;
	tmpfile = NULL;
	flag = 0;
	while (redir_list)
	{
		redir = (t_redirection *)redir_list->content;
		if (redir->type == REDIR_HEREDOC)
		{
			printf("flag is %d\n", flag);
			if (flag == 1)
				unlink(tmpfile);
			tmpfile = run_heredoc(redir->filename, shell);
			if (!tmpfile)
				return ;
			free(redir->filename);
			cmd->heredoc_filename = ft_strdup(tmpfile);
			printf("heredoc_filename = %s\n", cmd->heredoc_filename);
			flag = 1;
		}
		redir_list = redir_list->next;
	}
}
