/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:34:25 by shattori          #+#    #+#             */
/*   Updated: 2025/06/22 20:38:12 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

// ====== MAIN ======

// parser main

void	print_ast(t_ast *node, int indent)
{
	if (!node)
		return ;
	for (int i = 0; i < indent; i++)
		printf("  ");
	switch (node->type)
	{
	case NODE_COMMAND:
		ft_printf("COMMAND:");
		for (int i = 0; node->argv && node->argv[i]; i++)
			ft_printf(" %s", node->argv[i]);
		ft_printf("\n");
		break ;
	case NODE_PIPE:
		ft_printf("PIPE\n");
		break ;
	case NODE_AND:
		ft_printf("AND\n");
		break ;
	case NODE_OR:
		ft_printf("OR\n");
		break ;
	case NODE_SUBSHELL:
		ft_printf("SUBSHELL\n");
		break ;
	case NODE_REDIR_IN:
		ft_printf("REDIR_IN → %s\n", node->filename);
		break ;
	case NODE_REDIR_OUT:
		ft_printf("REDIR_OUT → %s\n", node->filename);
		break ;
	case NODE_REDIR_APPEND:
		ft_printf("REDIR_APPEND → %s\n", node->filename);
		break ;
	case NODE_HEREDOC:
		ft_printf("HEREDOC → %s\n", node->filename);
		break ;
	}
	if (node->left)
		print_ast(node->left, indent + 1);
	if (node->right)
		print_ast(node->right, indent + 1);
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
