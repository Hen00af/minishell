#include "parser.h"

static t_ast	*create_ast_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*parse_pipeline(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command_or_subshell(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == TOK_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_command_or_subshell(cur);
		if (!right)
		{
			fprintf(stderr, "Syntax error after pipe\n");
			return (NULL);
		}
		left = create_ast_node(NODE_PIPE, left, right);
	}
	return (left);
}

t_ast	*parse_subshell(t_token **cur)
{
	t_ast	*inner;
	t_ast	*node;

	if (!*cur || (*cur)->type != TOK_LPAREN)
	{
		fprintf(stderr, "Syntax error: expected '('\n");
		return (NULL);
	}
	*cur = (*cur)->next;
	inner = parse_and_or(cur);
	if (!inner)
		return (NULL);
	if (!*cur || (*cur)->type != TOK_RPAREN)
	{
		fprintf(stderr, "Syntax error: expected ')' but got '%s'\n",
			(*cur) ? (*cur)->text : "end of input");
		return (NULL);
	}
	*cur = (*cur)->next;
	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = inner;
	return (node);
}

t_ast	*parse_command_or_subshell(t_token **cur)
{
	if ((*cur)->type == TOK_LPAREN)
		return (parse_subshell(cur));
	return (parse_command(cur));
}

static int	is_redirection_token(t_token *tok)
{
	if (!tok)
		return (0);
	return (tok->type == TOK_REDIR_IN || tok->type == TOK_REDIR_OUT
		|| tok->type == TOK_REDIR_APPEND || tok->type == TOK_HEREDOC);
}

static t_ast	*parse_redirection(t_token **cur, t_ast *cmd)
{
	t_node_type	type;
	t_ast		*redir;

	switch ((*cur)->type)
	{
	case TOK_REDIR_IN:
		type = NODE_REDIR_IN;
		break ;
	case TOK_REDIR_OUT:
		type = NODE_REDIR_OUT;
		break ;
	case TOK_REDIR_APPEND:
		type = NODE_REDIR_APPEND;
		break ;
	case TOK_HEREDOC:
		type = NODE_HEREDOC;
		break ;
	default:
		fprintf(stderr, "Unexpected token in redirection\n");
		return (NULL);
	}
	*cur = (*cur)->next;
	if (!*cur || (*cur)->type != TOK_WORD)
	{
		fprintf(stderr, "Expected filename after redirection\n");
		return (NULL);
	}
	redir = calloc(1, sizeof(t_ast));
	redir->type = type;
	redir->filename = ft_strdup((*cur)->text);
	redir->left = cmd;
	redir->right = NULL;
	*cur = (*cur)->next;
	return (redir);
}

static t_ast	*parse_simple_command(t_token **cur)
{
	t_token	*tok;
	int		argc;
	t_ast	*cmd;
	int		i;

	tok = *cur;
	argc = 0;
	while (tok && tok->type == TOK_WORD)
	{
		argc++;
		tok = tok->next;
	}
	if (argc == 0)
		return (NULL);
	cmd = calloc(1, sizeof(t_ast));
	cmd->type = NODE_COMMAND;
	cmd->argv = calloc(argc + 1, sizeof(char *));
	i = 0;
	while (i < argc)
	{
		cmd->argv[i] = ft_strdup((*cur)->text);
		*cur = (*cur)->next;
		i++;
	}
	cmd->argv[argc] = NULL;
	return (cmd);
}

t_ast	*parse_command(t_token **cur)
{
	t_ast	*cmd;

	cmd = parse_simple_command(cur);
	if (!cmd)
		return (NULL);
	while (*cur && is_redirection_token(*cur))
	{
		cmd = parse_redirection(cur, cmd);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

static t_ast	*parse_and_or(t_token **cur)
{
	t_ast		*left;
	t_node_type	op_type;
	t_ast		*right;

	left = parse_pipeline(cur);
	if (!left)
		return (NULL);
	while (*cur && ((*cur)->type == TOK_AND || (*cur)->type == TOK_OR))
	{
		if ((*cur)->type == TOK_AND)
			op_type = NODE_AND;
		else
			op_type = NODE_OR;
		*cur = (*cur)->next;
		right = parse_pipeline(cur);
		if (!right)
		{
			fprintf(stderr, "Syntax error after && or ||\n");
			return (NULL);
		}
		left = create_ast_node(op_type, left, right);
	}
	return (left);
}


void	print_ast(t_ast *node, int indent)
{
	if (!node)
		return ;
	for (int i = 0; i < indent; i++)
		printf("  ");
	switch (node->type)
	{
	case NODE_COMMAND:
		printf("COMMAND:");
		for (int i = 0; node->argv && node->argv[i]; i++)
			printf(" %s", node->argv[i]);
		printf("\n");
		break ;
	case NODE_PIPE:
		printf("PIPE\n");
		break ;
	case NODE_AND:
		printf("AND\n");
		break ;
	case NODE_OR:
		printf("OR\n");
		break ;
	case NODE_SUBSHELL:
		printf("SUBSHELL\n");
		break ;
	case NODE_REDIR_IN:
		printf("REDIR_IN → %s\n", node->filename);
		break ;
	case NODE_REDIR_OUT:
		printf("REDIR_OUT → %s\n", node->filename);
		break ;
	case NODE_REDIR_APPEND:
		printf("REDIR_APPEND → %s\n", node->filename);
		break ;
	case NODE_HEREDOC:
		printf("HEREDOC → %s\n", node->filename);
		break ;
	}
	if (node->left)
		print_ast(node->left, indent + 1);
	if (node->right)
		print_ast(node->right, indent + 1);
}

t_ast	*start_parse(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	return (parse_and_or(&cur));
}

// void	print_exec_order(t_ast *node)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_COMMAND)
// 	{
// 		for (int i = 0; node->argv && node->argv[i]; i++)
// 			printf("%s ", node->argv[i]);
// 		printf("\n");
// 		return ;
// 	}
// 	// リダイレクトノードなら中身のコマンドを先に処理
// 	if (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
// 		|| node->type == NODE_REDIR_APPEND || node->type == NODE_HEREDOC)
// 	{
// 		print_exec_order(node->left); // COMMAND ノードが left に入ってる
// 		return ;
// 	}
// 	// サブシェルの場合も中の構文を処理
// 	if (node->type == NODE_SUBSHELL)
// 	{
// 		print_exec_order(node->left);
// 		return ;
// 	}
// 	// AND, OR, PIPE など：左右を処理順に従って
// 	print_exec_order(node->left);
// 	print_exec_order(node->right);
// }

// // parser main

// int	main(int argc, char **argv)
// {
// 	t_token	*tokens;
// 	t_ast	*tree;

// 	if (argc != 2)
// 	{
// 		fprintf(stderr, "Usage: %s \"command string\"\n", argv[0]);
// 		return (1);
// 	}
// 	tokens = lexer(argv[1]);
// 	if (!tokens)
// 	{
// 		fprintf(stderr, "Tokenize error\n");
// 		return (1);
// 	}
// 	tree = start_parse(tokens);
// 	free(tokens);
// 	if (!tree)
// 	{
// 		fprintf(stderr, "Parse error\n");
// 		return (1);
// 	}
// 	// print_ast(tree, 0);
// 	print_exec_order(tree);
// 	return (0);
// }
