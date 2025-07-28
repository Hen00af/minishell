/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 06:40:50 by shattori          #+#    #+#             */
/*   Updated: 2025/07/25 06:41:31 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
			free(node->argv[i++]);
		free(node->argv);
	}
	if (node->filename)
		free(node->filename);
	free(node);
}
