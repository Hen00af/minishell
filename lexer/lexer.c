#include "../minishell.h"

typedef struct cmd {
    int argc;
    char **argv;
    int capa;
    int status;
    int pid;
    struct cmd *next;
}t_cmd;

t_token *lexer(t_cmd cmd)
{
	t_token token_head;


	return (token_head);
}
