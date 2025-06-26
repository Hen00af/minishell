#include "../expander.h"

// ====== MAIN ======
int	main(int ac, char **av, char **envp)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;
	t_env	*env;

	if (ac < 2)
		return (0);
	lex = lexer(av[1]);
	ast = start_parse(lex);
	// print_ast(ast, 0);
	linearized_ast = linearizer(ast);
	env = init_env(envp);
	expand_andor_arguments(linearized_ast, env);
	print_linerlized_ast(linearized_ast, 0);
	return (0);
}
