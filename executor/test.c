#include <stdio.h>

int	main(void)
{
	char	*path;
	char	*args[] = {"cd", ".", NULL};
	char	*envp[] = {NULL};

	path = "/bin/ls";
	if (execve(path, args, envp) == -1)
	{
		perror("execve failed");
	}
	return (1);
}
