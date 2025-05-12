#include <stdio.h>

void echo(char *str, char option)
{
    if (str)
        printf("%s", str);
    if (option == 'n')
        printf("\n");
    else
        printf("Error");
}

int main(int ac, char **av)
{
    if (ac > 1)
    {
        echo(av[1], NULL);
        echo(av[1], 'n');
    }
    return 0;
}
