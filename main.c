#include "minishell.h"

static void	prompt(void);

int	main(void)
{
	while (1)
		prompt();
	exit(0);
}

static void	prompt(void)
{
	char	*cmd;

	cmd = readline("minishell#");
	if (!cmd)
		exit(0);
	add_history(cmd);
	// tokens = lexer(cmd);
	// parser(tokens);
	// expander(tokens);
	// executor(tokens);
	// free_cmd(tokens);
	free(cmd);
}
