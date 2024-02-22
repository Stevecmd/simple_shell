#ifndef _FORK_
#define _FORK_

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * forking - Demonstrates the usage of the fork system
 *				call to create a new process.
 *               The child process prints its own process ID
 *				(PID), while the parent process waits
 *                for the child process to finish and prints
 *				a message upon completion.
 *
 * Return: Always 0.
 */

int forking(void)
{
	pid_t my_pid;
	pid_t pid;

	my_pid = getpid();

	printf("Before fork:\n");
	pid = fork();
	printf("My pid is %u\n", my_pid);

	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	else if (pid == 0)
	{
		printf("After fork:\n");
		my_pid = getpid();
		printf("My pid is %u\n", my_pid);
	}
	else
	{

		int status;

		wait(&status); /* Ensuring parent waits for child to finish before exiting */

		if (WIFEXITED(status))
	{
		printf("Parent process finished\n");
	}
	}
		return (0);
	}

#endif /* _FORK_ */
