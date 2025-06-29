#include "./minishell.h"

char	*run_readline(void)
{
	char	*cwd;
	char	*prompt;
	char	*cmd;

	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin(cwd, " $ ");
	free(cwd);
	cmd = readline(prompt);
	free(prompt);
	if (!cmd)
	{
		ft_printf("exit\n");
		exit(0);
	}
	return (cmd);
}

t_andor	*make_linearized_ast(char *cmd)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;

	lex = lexer(cmd);
	ast = start_parse(lex);
	if (!ast)
		return (NULL);
	add_history(cmd);
	linearized_ast = linearizer(ast);
	return (linearized_ast);
}

void	expand_and_execute(t_andor *linearized_ast, t_shell *shell)
{
	expand_andor_arguments(linearized_ast, shell);
	handle_heredoc(linearized_ast, shell->env);
	executor(linearized_ast, shell);
}

int	prompt(t_shell *shell)
{
	char	*cmd;
	t_andor	*linearized_ast;

	cmd = run_readline();
	linearized_ast = make_linearized_ast(cmd);
	if (!linearized_ast)
	{
		free(cmd);
		return (0);
	}
	expand_and_execute(linearized_ast, shell);
	free(cmd);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_signal();
	shell.env = init_env(envp);
	shell.exit_status = 0;
	while (1)
	{
		if (g_ack_status == 1)
			shell.exit_status = 130;
		if (!prompt(&shell))
			continue ;
	}
	return (0);
}

// int	builtin_pwd(char **args, t_env *list_head)
// {
// 	char	*cwd;

// 	(void)args;
// 	(void)list_head;
// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		perror("pwd");
// 		return (NG);
// 	}
// 	printf("%s\n", cwd);
// 	free(cwd);
// 	return (OK);
// }
