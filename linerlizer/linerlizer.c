/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linerlizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:14:37 by shattori          #+#    #+#             */
/*   Updated: 2025/06/15 18:33:05 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./linerlizer.h"

// ====== AND/OR ======
t_andor	*linearize_andor(t_ast *ast)
{
	t_andor	*node;

	node = malloc(sizeof(t_andor));
	if (!node)
		return (NULL);
	node->type = (ast->type == NODE_AND) ? ANDOR_AND : ANDOR_OR;
	node->left = linearizer(ast->left);
	node->right = linearizer(ast->right);
	return (node);
}
t_redir_type	map_redir_type(t_node_type type)
{
	if (type == NODE_REDIR_IN)
		return (REDIR_IN);
	else if (type == NODE_REDIR_OUT)
		return (REDIR_OUT);
	else if (type == NODE_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (type == NODE_HEREDOC)
		return (REDIR_HEREDOC);
	else
	{
		ft_fprintf(2, "Unknown redirection type in map_redir_type\n");
		exit(1);
	}
}
// ====== SIMPLE_COMMAND (2段階化) ======
t_command	*linearize_simple_command_to_command(t_ast *ast)
{
	t_command		*cmd;
	t_command		*child;
	t_redirection	*redir;
	t_list			*redir_node;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = ast->argv;
	cmd->redirections = NULL;
	cmd->subshell_ast = NULL;
	// Redirection の再帰処理 (flattenする)
	if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
	{
		child = linearize_simple_command_to_command(ast->left);
		redir = malloc(sizeof(t_redirection));
		redir->type = map_redir_type(ast->type);
		redir->filename = ast->filename;
		redir_node = ft_lstnew(redir);
		ft_lstadd_back(&child->redirections, redir_node);
		free(cmd); // いま作ったcmdは不要
		return (child);
	}
	return (cmd);
}
t_andor	*linearize_simple_command(t_ast *ast)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	cmd = linearize_simple_command_to_command(ast);
	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = ft_lstnew(cmd);
	andor = malloc(sizeof(t_andor));
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	andor->left = NULL;
	andor->right = NULL;
	return (andor);
}
// ====== PIPELINE ======
void	flatten_pipeline(t_ast *node, t_pipeline *pipeline)
{
	t_command	*cmd;
	t_list		*new_node;

	if (node->type == NODE_PIPE)
	{
		flatten_pipeline(node->left, pipeline);
		flatten_pipeline(node->right, pipeline);
	}
	else
	{
		cmd = linearize_simple_command_to_command(node);
		new_node = ft_lstnew(cmd);
		ft_lstadd_back(&pipeline->commands, new_node);
	}
}
t_andor	*linearize_pipeline(t_ast *ast)
{
	t_pipeline	*pipeline;
	t_andor		*node;

	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = NULL;
	flatten_pipeline(ast, pipeline);
	node = malloc(sizeof(t_andor));
	node->type = ANDOR_PIPELINE;
	node->pipeline = pipeline;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
// ====== SUBSHELL ======
t_andor	*linearize_subshell(t_ast *ast)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	cmd = malloc(sizeof(t_command));
	pipeline = malloc(sizeof(t_pipeline));
	andor = malloc(sizeof(t_andor));
	cmd->subshell_ast = linearizer(ast->left);
	cmd->argv = NULL;
	cmd->redirections = NULL;
	pipeline->commands = ft_lstnew(cmd);
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	andor->left = NULL;
	andor->right = NULL;
	return (andor);
}
// ====== MAIN DISPATCH ======
t_andor	*linearizer(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->type == NODE_AND || ast->type == NODE_OR)
		return (linearize_andor(ast));
	if (ast->type == NODE_PIPE)
		return (linearize_pipeline(ast));
	if (ast->type == NODE_SUBSHELL)
		return (linearize_subshell(ast));
	return (linearize_simple_command(ast));
}
// ====== 簡易テスト用PRINT ======
void	print_linerlized_ast(t_andor *tree, int indent)
{
	if (!tree)
		return ;
	for (int i = 0; i < indent; i++)
		printf("  ");
	if (tree->type == ANDOR_AND)
		printf("AND\n");
	else if (tree->type == ANDOR_OR)
		printf("OR\n");
	else if (tree->type == ANDOR_PIPELINE)
		printf("PIPELINE\n");
	print_linerlized_ast(tree->left, indent + 1);
	print_linerlized_ast(tree->right, indent + 1);
}
// ====== MAIN ======
int	main(int ac, char **av)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;

	if (ac < 2)
		return (0);
	lex = lexer(av[1]);
	ast = start_parse(lex);
	linearized_ast = linearizer(ast);
	print_linerlized_ast(linearized_ast, 0);
	return (0);
}
