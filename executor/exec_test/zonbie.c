// zombie_test.c
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		printf("Child PID: %d exiting\n", getpid());
		_exit(0);
	}

	printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
	return (0);
}