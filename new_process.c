#ifndef _NEW_PROCESS_
#define _NEW_PROCESS_

#include "shell.h"

/**
* new_process - Create a new process to execute a command.
* @args: Array of strings containing the command and its arguments.
*
* Return: 1 on success, -1 on failure.
*/

/*
 * File: new_process.c
 * Auth: Steve Murimi
 */

int new_process(char **args)
{
	pid_t pid;
	int status;

	/* Fork a new process */
	pid = fork();

	if (pid == 0) {
		/* Child process */
		if (execvp(args[0], args) == -1)
		{
			/* Handle execvp error */
			perror("new_process: execvp");
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0) {
		/* Error forking */
		perror("new_process: fork");
		return -1;
	} else {
		/* Parent process */
		do {
		/* Wait for the child process to terminate */
			if (waitpid(pid, &status, WUNTRACED) == -1) {
				perror("new_process: waitpid");
				return -1;
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
return (0); /* Success */
}

#endif /* _NEW_PROCESS_ */