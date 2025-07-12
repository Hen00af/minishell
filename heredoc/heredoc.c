/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:34:59 by nando             #+#    #+#             */
/*   Updated: 2025/07/12 13:07:24 by nando            ###   ########.fr       */
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
	fd = open_heredoc_file(&path);
	if (fd < 0)
	{
		free(clean_delimiter);
		return (NULL);
	}
	write_heredoc_lines(fd, clean_delimiter, need_expand, shell);
	if (g_ack_status == 1)
	{
		unlink(path);
		free(path);
		path = NULL;
	}
	free(clean_delimiter);
	close(fd);
	return (path);
}

static int	handle_heredoc(t_tmp *ctx, t_command *cmd, t_redirection *redir,
		t_shell *shell)
{
	if (ctx->flag)
	{
		unlink(ctx->file);
		free(ctx->file);
		free(cmd->heredoc_filename);
	}
	ctx->file = run_heredoc(redir->filename, shell);
	if (!ctx->file)
		return (0);
	cmd->heredoc_filename = ft_strdup(ctx->file);
	ctx->flag = 1;
	return (1);
}

void	process_heredoc(t_command *cmd, t_shell *shell)
{
	t_list			*redir_list;
	t_redirection	*redir;
	t_tmp			ctx;

	ctx.file = NULL;
	ctx.flag = 0;
	if (!cmd || !cmd->redirections)
		return ;
	redir_list = cmd->redirections;
	while (redir_list)
	{
		redir = redir_list->content;
		if (redir->type == REDIR_HEREDOC)
		{
			if (!handle_heredoc(&ctx, cmd, redir, shell))
				return ;
		}
		redir_list = redir_list->next;
	}
	if (ctx.flag)
		free(ctx.file);
}
