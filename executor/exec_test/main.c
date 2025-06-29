#include "../executor.h"

int	main(int ac, char **av, char **envp)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;
	t_env	*env;
	char	*cmd;

	(void)ac;
	(void)av;
	init_signal();
	env = init_env(envp);
	while (1)
	{
		cmd = readline("minishell# ");
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
		//printf("linerized\n");
		expand_andor_arguments(linearized_ast, env);
		//printf("expanded\n");
		executor(linearized_ast, env);
		free(cmd);
	}
	return (0);
}
