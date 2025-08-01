/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:34:59 by nando             #+#    #+#             */
/*   Updated: 2025/07/31 22:40:59 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

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
	t_heredoc_file		file;
	char				*clean_delim;
	struct sigaction	old;
	pid_t				pid;
	int					is_quoted;

	sigaction(SIGINT, NULL, &old);
	g_ack_status = 0;
	is_quoted = is_include_quote(delimiter);
	file = open_and_prepare_file(delimiter, &clean_delim);
	if (file.fd < 0)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (handle_fork_error(file.fd, clean_delim, file.path));
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_heredoc_process(file.fd, clean_delim, !is_quoted, shell);
	}
	return (finalize_heredoc(pid, &file, &old, clean_delim));
}

int	handle_heredoc(t_tmp *ctx, t_command *cmd, t_redirection *redir,
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
			{
				if (ctx.flag)
					free(ctx.file);
				return ;
			}
		}
		redir_list = redir_list->next;
	}
	if (ctx.flag)
		free(ctx.file);
}
