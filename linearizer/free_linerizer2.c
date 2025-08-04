/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linerizer2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:31:42 by shattori          #+#    #+#             */
/*   Updated: 2025/08/04 18:40:29 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linearizer.h"

void	free_redirection_in_command(t_command *cmd, t_redirection *redir,
		t_list *node, t_list *next)
{
	node = cmd->redirections;
	while (node)
	{
		next = node->next;
		redir = node->content;
		if (redir)
		{
			free(redir->filename);
			free(redir);
		}
		free(node);
		node = next;
	}
}