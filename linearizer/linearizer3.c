/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:30:05 by shattori          #+#    #+#             */
/*   Updated: 2025/08/01 15:19:34 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./linearizer.h"

// ====== AND/OR ======
t_andor	*linearize_andor(t_ast *ast, t_shell *shell)
{
	t_andor	*node;

	node = ft_calloc(1, sizeof(t_andor));
	if (!node)
		return (NULL);
	if (ast->type == NODE_AND)
		node->type = ANDOR_AND;
	else
		node->type = ANDOR_OR;
	node->left = linearizer(ast->left, shell);
	node->right = linearizer(ast->right, shell);
	return (node);
}

t_redir_type	map_redir_type(t_node_type type)
{
	if (type == NODE_REDIR_IN)
		return (REDIR_IN);
	if (type == NODE_REDIR_OUT)
		return (REDIR_OUT);
	if (type == NODE_REDIR_APPEND)
		return (REDIR_APPEND);
	if (type == NODE_HEREDOC)
		return (REDIR_HEREDOC);
	ft_fprintf(STDERROR_INT, "Unknown redirection type!\n");
	exit(1);
}
