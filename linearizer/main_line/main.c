#include "../linearizer.h"

void	print_redirections(t_list *redir_list, int indent)
{
	t_redirection	*redir;

	while (redir_list)
	{
		redir = (t_redirection *)redir_list->content;
		for (int i = 0; i < indent; i++)
			printf("  ");
		printf("REDIR: ");
		if (redir->type == REDIR_IN)
			printf("< ");
		else if (redir->type == REDIR_OUT)
			printf("> ");
		else if (redir->type == REDIR_APPEND)
			printf(">> ");
		else if (redir->type == REDIR_HEREDOC)
			printf("<< ");
		printf("%s\n", redir->filename);
		redir_list = redir_list->next;
	}
}

void	print_commands(t_pipeline *pipeline, int indent)
{
	t_list		*cmd_list;
	t_command	*cmd;

	cmd_list = pipeline->commands;
	while (cmd_list)
	{
		cmd = (t_command *)cmd_list->content;
		for (int i = 0; i < indent; i++)
			printf("  ");
		if (cmd->argv)
		{
			printf("COMMAND:");
			for (int i = 0; cmd->argv[i]; i++)
				printf(" %s", cmd->argv[i]);
			printf("\n");
		}
		else
		{
			printf("SUBSHELL:\n");
			print_linerlized_ast(cmd->subshell_ast, indent + 1);
		}
		if (cmd->redirections)
			print_redirections(cmd->redirections, indent + 1);
		cmd_list = cmd_list->next;
	}
}

void	print_linerlized_ast(t_andor *tree, int indent)
{
	if (!tree)
		return ;
	for (int i = 0; i < indent; i++)
		printf("  ");
	if (tree->type == ANDOR_AND)
	{
		printf("AND\n");
		if (tree->left)
			print_linerlized_ast(tree->left, indent + 1);
		if (tree->right)
			print_linerlized_ast(tree->right, indent + 1);
	}
	else if (tree->type == ANDOR_OR)
	{
		printf("OR\n");
		if (tree->left)
			print_linerlized_ast(tree->left, indent + 1);
		if (tree->right)
			print_linerlized_ast(tree->right, indent + 1);
	}
	else if (tree->type == ANDOR_PIPELINE)
	{
		printf("PIPELINE\n");
		print_commands(tree->pipeline, indent + 1);
	}
}

//// ====== MAIN ======
int	main(int ac, char **av, char **envp)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;
	t_shell	shell;

	if (ac < 2)
		return (0);
	shell.env = init_env(envp);
	lex = lexer(av[1]);
	ast = start_parse(lex);
	// print_ast(ast, 0);
	linearized_ast = linearizer(ast, &shell);
	print_linerlized_ast(linearized_ast, 0);
	return (0);
}
