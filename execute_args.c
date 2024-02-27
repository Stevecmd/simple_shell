#ifndef _EXECUTE_ARGS_
#define _EXECUTE_ARGS_

#include "shell.h"
#include <string.h>
#include "builtin.h"
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

int execute_args(char **args)
{
	if (args == NULL)
	{
		perror("Execute_args: Null argument");
		return (0);
	}

	if (args[0] == NULL)
	{
		perror("Execute_args: Empty command");
		return (-1);
	}

	return (execute_builtin(args) || execute_external(args));
}

/**
 * execute_builtin - Execute a built-in command.
 *
 * This function searches for the given
 * command in the list of built-in commands
 * and executes the corresponding function if found.
 *
 * @args: The command and its arguments.
 *
 * Return: 1 if the command is a built-in and
 * was executed successfully, 0 otherwise.
 */

int execute_builtin(char **args)
{
	int i;

	for (i = 0; i < num_builtins; i++)
	{
		if (strcmp(args[0], builtin_func_list[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}

	return (0);
}

/**
 * execute_external - Execute an external command.
 *
 * This function forks a new process to execute
 * an external command using execve,
 * and waits for the child process to finish.
 *
 * @args: The command and its arguments.
 *
 * Return: 0 on success.
 */

int execute_external(char **args)
{
	int status;
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Execute_args: fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Execute_args: execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("Execute_args: waitpid");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (0);
}
#endif /* _EXECUTE_ARGS_*/
