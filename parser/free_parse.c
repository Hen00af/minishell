/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 07:13:47 by shattori          #+#    #+#             */
/*   Updated: 2025/08/01 16:15:52 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

void	free_ast(t_ast *ast)
{
	int	i;

	if (!ast)
		return ;
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	if (ast->argv)
	{
		i = 0;
		while (ast->argv[i])
		{
			if (ast->argv[i])
				free(ast->argv[i]);
			i++;
		}
		if (ast->argv)
			free(ast->argv);
	}
	if (ast->filename)
		free(ast->filename);
	free(ast);
}
