#include "../expander.h"

// ====== MAIN ======
int	main(int ac, char **av, char **envp)
{
	t_token	*lex;
	t_ast	*ast;
	t_andor	*linearized_ast;
	t_shell	*shell;
	t_token	*next;

	if (ac < 2)
		return (0);
	shell = malloc(sizeof *shell);
	shell->env = init_env(envp);
	lex = lexer(av[1]);
	ast = start_parse(lex);
	free_tokens(lex);
	linearized_ast = linearizer(ast, shell);
	expand_andor_arguments(linearized_ast, shell);
	free_env_list(shell->env);
	free(shell);
	print_linerlized_ast(linearized_ast, 0);
	return (0);
}
