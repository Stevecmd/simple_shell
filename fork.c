#ifndef _FORK_
#define _FORK_

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Declaration of int_to_string function */
void int_to_string(char *str, int num);

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

 /*
 * File: fork.c
 * Auth: Steve Murimi
 */

int forking(void)
{
	pid_t my_pid;
	pid_t pid;

	my_pid = getpid();

	write(STDOUT_FILENO, "Before fork:\n", 13);
	pid = fork();
	write(STDOUT_FILENO, "After fork:\n", 12);
	char my_pid_str[20];
	int_to_string(my_pid_str, my_pid);
	write(STDOUT_FILENO, "My pid is ", 10);
	write(STDOUT_FILENO, my_pid_str, strlen(my_pid_str));
	write(STDOUT_FILENO, "\n", 1);	

	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}

	else if (pid == 0)
	{
		write(STDOUT_FILENO, "After fork:\n", 13);
		my_pid = getpid();
		int_to_string(my_pid_str, my_pid);
		write(STDOUT_FILENO, "My pid is ", 10);
		write(STDOUT_FILENO, my_pid_str, strlen(my_pid_str));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{

		int status;

		wait(&status); /* Ensuring parent waits for child to finish before exiting */

		if (WIFEXITED(status))
	{
		write(STDOUT_FILENO, "The parent process has finished\n", 25);
	}
	}
		return (0);
	}

#endif /* _FORK_ */
