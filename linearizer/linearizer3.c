/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 09:30:05 by shattori          #+#    #+#             */
/*   Updated: 2025/08/04 09:05:34 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./linearizer.h"

t_andor	*linearize_andor(t_ast *ast, t_shell *shell)
{
	t_andor	*node;

	printf("linearize_andor: \n");
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
	printf("map_redir_type: \n");
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
