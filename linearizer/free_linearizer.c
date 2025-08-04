/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linearizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 05:50:48 by nando             #+#    #+#             */
/*   Updated: 2025/08/04 21:41:00 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/07/25 06:54:37 by nando            ###   ########.fr       */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 05:50:48 by nando             #+#    #+#             */
/*   Updated: 2025/07/28 12:20:24 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linearizer.h"

void	free_redirections(t_list *redir_list)
{
	t_list			*next;
	t_redirection	*redir;

	while (redir_list)
	{
		next = redir_list->next;
		redir = redir_list->content;
		if (redir)
		{
			if (redir->filename)
				free(redir->filename);
			free(redir);
		}
		free(redir_list);
		redir_list = next;
	}
}

static void	free_command_list2(t_command *cmd)
{
	if (cmd->subshell_ast)
		free_andor_ast(cmd->subshell_ast);
	if (cmd->redirections)
		free_redirections(cmd->redirections);
	if (cmd->heredoc_filename)
		free(cmd->heredoc_filename);
	free(cmd);
}

static void	free_command_list(t_list *cmd_list)
{
	t_list		*next;
	t_command	*cmd;
	int			i;

	while (cmd_list)
	{
		next = cmd_list->next;
		cmd = cmd_list->content;
		if (cmd)
		{
			if (cmd->argv)
			{
				i = 0;
				while (cmd->argv[i])
				{
					free(cmd->argv[i]);
					i++;
				}
				free(cmd->argv);
			}
			free_command_list2(cmd);
		}
		free(cmd_list);
		cmd_list = next;
	}
}

void	free_command(void *ptr)
{
	t_command		*cmd;
	t_list			*node;
	t_list			*next;
	t_redirection	*redir;

	cmd = (t_command *)ptr;
	redir = NULL;
	next = NULL;
	if (!cmd)
		return ;
	if (cmd->argv)
		free_split(cmd->argv);
	if (cmd->redirections)
	{
		node = cmd->redirections;
		while (node)
			free_redirection_in_command(cmd, redir, node, next);
	}
	free(cmd->heredoc_filename);
	if (cmd->subshell_ast)
		free_andor_ast(cmd->subshell_ast);
	free(cmd);
}

void	free_andor_ast(t_andor *node)
{
	if (!node)
		return ;
	if (node->type == ANDOR_PIPELINE)
	{
		if (node->pipeline)
		{
			free_command_list(node->pipeline->commands);
			free(node->pipeline);
		}
	}
	else
	{
		free_andor_ast(node->left);
		free_andor_ast(node->right);
	}
	free(node);
}
