#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "minishell.h"

#define REDIRECT_P(cmd) ((cmd)->argc == -1)
#define PID_BUILTIN -2
#define BUILTIN_P(cmd) ((cmd)->pid == PID_BUILTIN)

static void prompt(void);

int main(void)
{
    while(1)
        prompt();
    exit(0);
}

static void prompt(void)
{
    char *cmd;
    

    cmd = readline("minishell#");
    if(!cmd)
        exit(0);
    add_history(cmd);
    // tokens = lexer(cmd);
    // parser(tokens);
    // expander(tokens);
    // executor(tokens);
    // free_cmd(tokens);
    free(cmd);
}


