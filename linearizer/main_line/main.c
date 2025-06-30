#include "../linearizer.h"

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
	// print_ast(ast, 0);
	linearized_ast = linearizer(ast);
	print_linerlized_ast(linearized_ast, 0);
	return (0);
}
