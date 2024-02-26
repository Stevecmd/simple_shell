#ifndef _WAIT_
#define _WAIT_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
* shell_wait - fork & wait
*
* Return: Always 0.
*/

/*
 * File: wait.c
 * Auth: Steve Murimi
 */

int shell_wait(void)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		char *message = "Wait for me, wait for me\n";
		write(STDOUT_FILENO, message, strlen(message));
		sleep(3);
		_exit(0);
	}
	else
	{
		wait(&status);
		char *message = "Oh, it's all better now\n";
		write(STDOUT_FILENO, message, strlen(message));
	}
	return (0);
}

#endif /* _WAIT_ */