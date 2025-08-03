/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:51:48 by shattori          #+#    #+#             */
/*   Updated: 2025/07/31 21:15:48 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	open_redirection_file(t_redirection *redir, char *last_tmpfile)
{
	if (redir->type == REDIR_IN)
		return (open(redir->filename, O_RDONLY));
	else if (redir->type == REDIR_OUT)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == REDIR_APPEND)
		return (open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else if (redir->type == REDIR_HEREDOC)
	{
		if (!last_tmpfile)
		{
			ft_fprintf(2, "heredoc error: heredoc filename is NULL\n");
			exit(1);
		}
		return (open(last_tmpfile, O_RDONLY));
	}
	return (-1);
}

static void	apply_redirection(int fd, int type)
{
	if (fd < 0)
	{
		perror("redirection");
		exit(1);
	}
	if (type == REDIR_IN || type == REDIR_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_command *cmd)
{
	t_list			*redir_list;
	t_redirection	*redir;
	int				fd;
	char			*last_tmpfile;

	redir_list = cmd->redirections;
	last_tmpfile = cmd->heredoc_filename;
	while (redir_list)
	{
		redir = redir_list->content;
		fd = open_redirection_file(redir, last_tmpfile);
		apply_redirection(fd, redir->type);
		redir_list = redir_list->next;
	}
	// heredocファイルを削除
	if (cmd->heredoc_filename)
	{
		unlink(cmd->heredoc_filename);
	}
}
