#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	if (ac >= 2 && atoi(av[1]) == 0)
		return (0);
	return (1);
}
