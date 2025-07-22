/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirectioin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:32:48 by shattori          #+#    #+#             */
/*   Updated: 2025/07/22 10:48:58 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	open_redirection_file_builtin(t_redirection *redir, char *last_tmpfile)
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
			return (-2);
		}
		return (open(last_tmpfile, O_RDONLY));
	}
	return (-1);
}

int	apply_redirection_builtin(int fd, int type)
{
	if (fd < 0)
	{
		if (fd == -2)
			return (1);
		perror("redirection");
		return (1);
	}
	if (type == REDIR_IN || type == REDIR_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections_builtin(t_command *cmd)
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
		fd = open_redirection_file_builtin(redir, last_tmpfile);
		if (apply_redirection_builtin(fd, redir->type))
			return (1);
		redir_list = redir_list->next;
	}
	return (0);
}
