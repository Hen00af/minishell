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

int	prompt(t_env *env)
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
	expand_and_execute(linearized_ast, env);
	free(cmd);
	return (1);
}

void	expand_and_execute(t_andor *linearized_ast, t_env *env)
{
	expand_andor_arguments(linearized_ast, env);
	handle_heredoc(linearized_ast, env);
	executor(linearized_ast, env);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	init_signal();
	env = init_env(envp);
	while (1)
	{
		if (!prompt(env))
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
