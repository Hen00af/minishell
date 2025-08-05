/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:34:59 by nando             #+#    #+#             */
/*   Updated: 2025/08/05 16:45:13 by nando            ###   ########.fr       */
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

char	*finalize_heredoc(pid_t pid, t_heredoc_file *h_file,
		struct sigaction *old, char *clean_delim)
{
	int	status;

	waitpid(pid, &status, 0);
	sigaction(SIGINT, old, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_ack_status = 1;
		unlink(h_file->path);
		close(h_file->fd);
		free(h_file->path);
		free(clean_delim);
		return (NULL);
	}
	free(clean_delim);
	close(h_file->fd);
	return (h_file->path);
}

char	*run_heredoc(char *delimiter, t_shell *shell)
{
	t_heredoc_file		h_file;
	char				*clean_delim;
	struct sigaction	old;
	pid_t				pid;
	int					is_quoted;

	sigaction(SIGINT, NULL, &old);
	g_ack_status = 0;
	is_quoted = is_include_quote(delimiter);
	h_file = open_and_prepare_file(delimiter, &clean_delim);
	if (h_file.fd < 0)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (handle_fork_error(h_file.fd, clean_delim, h_file.path));
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_heredoc_process(h_file.fd, clean_delim, !is_quoted, shell);
	}
	return (finalize_heredoc(pid, &h_file, &old, clean_delim));
}

int	handle_heredoc(t_tmp *ctx, t_command *cmd, t_redirection *redir,
		t_shell *shell)
{
	if (ctx->flag)
	{
		unlink(ctx->file);
		if (cmd->heredoc_filename)
		{
			free(cmd->heredoc_filename);
			cmd->heredoc_filename = NULL;
		}
	}
	ctx->file = run_heredoc(redir->filename, shell);
	if (!ctx->file)
	{
		shell->exit_status = 130;
		return (0);
	}
	free(redir->filename);
	redir->filename = NULL;
	cmd->heredoc_filename = ctx->file;
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
				if (ctx.flag && ctx.file)
					free(ctx.file);
				return ;
			}
		}
		redir_list = redir_list->next;
	}
}
