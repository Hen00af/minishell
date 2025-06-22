#include "../parser.h"

// ====== MAIN ======

// parser main

int	main(int argc, char **argv)
{
	t_token	*tokens;
	t_ast	*tree;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s \"command string\"\n", argv[0]);
		return (1);
	}
	tokens = lexer(argv[1]);
	if (!tokens)
	{
		fprintf(stderr, "Tokenize error\n");
		return (1);
	}
	tree = start_parse(tokens);
	free(tokens);
	if (!tree)
	{
		fprintf(stderr, "Parse error\n");
		return (1);
	}
	print_ast(tree, 0);
	return (0);
}
