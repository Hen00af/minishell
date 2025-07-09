/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:34:25 by shattori          #+#    #+#             */
/*   Updated: 2025/07/09 15:38:14 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

// ====== MAIN ======

// parser main

void	print_ast(t_ast *ast, int depth)
{
	if (!ast)
		return;
	for (int i = 0; i < depth; i++)
		printf("  ");
	switch (ast->type)
	{
		case NODE_COMMAND:
			printf("COMMAND:\n");
			for (int i = 0; ast->argv && ast->argv[i]; i++)
			{
				for (int j = 0; j <= depth; j++)
					printf("  ");
				printf("argv[%d] = %s\n", i, ast->argv[i]);
			}
			break;
		case NODE_HEREDOC:
			printf("HEREDOC: %s\n", ast->filename);
			print_ast(ast->left, depth + 1);
			break;
		case NODE_REDIR_OUT:
			printf("REDIR_OUT: %s\n", ast->filename);
			print_ast(ast->left, depth + 1);
			break;
		// 他のNODE_*も必要に応じて追加
		default:
			printf("UNKNOWN NODE TYPE\n");
	}
}

int	main(int argc, char **argv)
{
	t_token	*tokens;
	t_ast	*tree;

	if (argc != 2)
	{
		ft_fprintf(STDERROR_INT, "Usage: %s \"command string\"\n", argv[0]);
		return (1);
	}
	tokens = lexer(argv[1]);
	if (!tokens)
	{
		ft_fprintf(STDERROR_INT, "Tokenize error\n");
		return (1);
	}
	tree = start_parse(tokens);
	free(tokens);
	if (!tree)
	{
		ft_fprintf(STDERROR_INT, "Parse error\n");
		return (1);
	}
	print_ast(tree, 0);
	printf("parse end\n");
	return (0);
}
