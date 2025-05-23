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
	t_token	*token_head;

	cmd = readline("minishell#");
	if (!cmd)
		exit(0);
	add_history(cmd);
	// token_head = lexer(cmd);
	// parser(token_head);
	// expander(tokens);
	// executor(tokens);
	// free_cmd(tokens);
	free(cmd);
}
