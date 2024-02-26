#ifndef _EXECUTE_ARGS_
#define _EXECUTE_ARGS_

#include "shell.h"
#include <string.h> // Include for strcmp function
#include "builtin.h"
#include "builtin.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
* execute_args - Determine whether a command is
*				a built-in or an external process.
*
* This function checks if the given command is a built-in command
* (such as "cd", "env", "help", "exit") or an external process.
* If the command is a built-in, it executes the corresponding function.
* If it's an external process, it forks a new process to execute it.
*
* @args: The command and its arguments.
*
* Return: 1 on success, 0 otherwise
*/

/*
 * File: execute_args.c
 * Auth: Steve Murimi
 */

int execute_args(char **args){
int i = 0;
int status;
pid_t pid;

/* Check if args is NULL */
if (args == NULL)
{
	perror("Execute_args: Null argument");
	return (0);
}

/* Check if the command is empty */
if (args[0] == NULL)
{
	perror("Execute_args: Empty command");
	return (-1);
}

/* Find if the command is a builtin */
for (i = 0; i < num_builtins; i++)
{
	/* If there is a match, execute the builtin command */
	if (strcmp(args[0], builtin_func_list[i]) == 0)
	{
	return ((*builtin_func[i])(args));
	}
}
	/* If the command is not a builtin, execute it as an external process */
	pid = fork();
	if (pid < 0) {
		perror("Execute_args: fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		// Child process
		if (execve(args[0], args, NULL) == -1) {
			perror("Execute_args: execve");
			_exit(EXIT_FAILURE);
		}
	} else {
		/* Parent process */
		do {
			if (waitpid(pid, &status, WUNTRACED) == -1) {
				perror("Execute_args: waitpid");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}
#endif /* _EXECUTE_ARGS_*/
