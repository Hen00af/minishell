#include "../minishell.h"

typedef struct cmd {
    int argc;
    char **argv;
    int capa;
    int status;
    int pid;
    struct cmd *next;
}t_cmd;

void lexer(t_cmd cmd)
{
}

