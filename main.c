#include "./minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;
	t_env	*env;
	char	*cmd;
	char	*cwd;

	(void)ac;
	(void)av;
	init_signal();
	env = init_env(envp);
	while (1)
	{
		cwd = getcwd(NULL, 0);
		ft_printf("%s", cwd);
		cmd = readline("  >");
		if (!cmd)
		{
			ft_printf("exit\n");
			exit(0);
		}
		lex = lexer(cmd);
		ast = start_parse(lex);
		if (!ast)
			continue ;
		add_history(cmd);
		linearized_ast = linearizer(ast);
		expand_andor_arguments(linearized_ast, env);
		handle_heredoc(linearized_ast, env);
		executor(linearized_ast, env);
		free(cmd);
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
