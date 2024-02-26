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
	char *message = "Wait for me, wait for me\n";
	char *message2 = "Oh, it's all better now\n";
	int len, delay;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		len = 0;
		while (message[len] != '\0')
			len++;
		
		write(STDOUT_FILENO, message, len);

		delay = 3;
		while (delay > 0)
		{
			getpid(); /* Simulate a delay */
			delay--;
		}

		_exit(0);

	}
	else
	{
		wait(&status);
		len = 0;
		while (message[len] != '\0')
			len++;
		write(STDOUT_FILENO, message2, len);
	}
	return (0);
}

#endif /* _WAIT_ */