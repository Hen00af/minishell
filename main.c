#include "minishell.h"
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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
