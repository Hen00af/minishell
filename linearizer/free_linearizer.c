/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linearizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 05:50:48 by nando             #+#    #+#             */
/*   Updated: 2025/07/28 12:20:24 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linearizer.h"

static void	free_redirections(t_list *redir_list)
{
	t_list			*next;
	t_redirection	*redir;

	while (redir_list)
	{
		next = redir_list->next;
		redir = redir_list->content;
		free(redir);
		free(redir_list);
		redir_list = next;
	}
}

static void	free_command_list(t_list *cmd_list)
{
	t_list		*next;
	t_command	*cmd;

	while (cmd_list)
	{
		next = cmd_list->next;
		cmd = cmd_list->content;
		if (cmd->subshell_ast)
			free_andor_ast(cmd->subshell_ast);
		if (cmd->redirections)
			free_redirections(cmd->redirections);
		free(cmd);
		free(cmd_list);
		cmd_list = next;
	}
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
