/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linearizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:14:37 by shattori          #+#    #+#             */
/*   Updated: 2025/06/29 17:03:47 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./linearizer.h"

// ====== AND/OR ======
t_andor	*linearize_andor(t_ast *ast)
{
	t_andor	*node;

	node = malloc(sizeof(t_andor));
	if (!node)
		return (NULL);
	if (ast->type == NODE_AND)
		node->type = ANDOR_AND;
	else
		node->type = ANDOR_OR;
	node->left = linearizer(ast->left);
	node->right = linearizer(ast->right);
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

// ====== SIMPLE COMMAND ======
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
	if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_REDIR_APPEND || ast->type == NODE_HEREDOC)
	{
		child = linearize_simple_command_to_command(ast->left);
		redir = malloc(sizeof(t_redirection));
		redir->type = map_redir_type(ast->type);
		redir->filename = ast->filename;
		redir_node = ft_lstnew(redir);
		ft_lstadd_back(&child->redirections, redir_node);
		free(cmd);
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
	return (node);
}

// ====== SUBSHELL ======
t_andor	*linearize_subshell(t_ast *ast)
{
	t_command	*cmd;
	t_pipeline	*pipeline;
	t_andor		*andor;

	cmd = malloc(sizeof(t_command));
	cmd->argv = NULL;
	cmd->redirections = NULL;
	cmd->subshell_ast = linearizer(ast->left);
	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = ft_lstnew(cmd);
	andor = malloc(sizeof(t_andor));
	andor->type = ANDOR_PIPELINE;
	andor->pipeline = pipeline;
	return (andor);
}

// ====== DISPATCH ======
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

// void	print_redirections(t_list *redir_list, int indent)
// {
// 	t_redirection	*redir;

// 	while (redir_list)
// 	{
// 		redir = (t_redirection *)redir_list->content;
// 		for (int i = 0; i < indent; i++)
// 			printf("  ");
// 		printf("REDIR: ");
// 		if (redir->type == REDIR_IN)
// 			printf("< ");
// 		else if (redir->type == REDIR_OUT)
// 			printf("> ");
// 		else if (redir->type == REDIR_APPEND)
// 			printf(">> ");
// 		else if (redir->type == REDIR_HEREDOC)
// 			printf("<< ");
// 		printf("%s\n", redir->filename);
// 		redir_list = redir_list->next;
// 	}
// }

// void	print_commands(t_pipeline *pipeline, int indent)
// {
// 	t_list		*cmd_list;
// 	t_command	*cmd;

// 	cmd_list = pipeline->commands;
// 	while (cmd_list)
// 	{
// 		cmd = (t_command *)cmd_list->content;
// 		for (int i = 0; i < indent; i++)
// 			printf("  ");
// 		if (cmd->argv)
// 		{
// 			printf("COMMAND:");
// 			for (int i = 0; cmd->argv[i]; i++)
// 				printf(" %s", cmd->argv[i]);
// 			printf("\n");
// 		}
// 		else
// 		{
// 			printf("SUBSHELL:\n");
// 			print_linerlized_ast(cmd->subshell_ast, indent + 1);
// 		}
// 		if (cmd->redirections)
// 			print_redirections(cmd->redirections, indent + 1);
// 		cmd_list = cmd_list->next;
// 	}
// }

// void	print_linerlized_ast(t_andor *tree, int indent)
// {
// 	if (!tree)
// 		return ;
// 	for (int i = 0; i < indent; i++)
// 		printf("  ");
// 	if (tree->type == ANDOR_AND)
// 	{
// 		printf("AND\n");
// 		if (tree->left)
// 			print_linerlized_ast(tree->left, indent + 1);
// 		if (tree->right)
// 			print_linerlized_ast(tree->right, indent + 1);
// 	}
// 	else if (tree->type == ANDOR_OR)
// 	{
// 		printf("OR\n");
// 		if (tree->left)
// 			print_linerlized_ast(tree->left, indent + 1);
// 		if (tree->right)
// 			print_linerlized_ast(tree->right, indent + 1);
// 	}
// 	else if (tree->type == ANDOR_PIPELINE)
// 	{
// 		printf("PIPELINE\n");
// 		print_commands(tree->pipeline, indent + 1);
// 	}
// }
