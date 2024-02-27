#ifndef BUILTIN_C
#define BUILTIN_C

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"
#include "shell.h"

/*
 * File: builtin.c
 * Auth: Steve Murimi
 */

char *builtin_func_list[] = {
	"cd",
	"env",
	"help",
	"exit"
};

int (*builtin_func[])(char **) = {
	&own_cd,
	&own_env,
	&own_help,
	&own_exit
};
int num_builtins = sizeof(builtin_func_list) / sizeof(builtin_func_list[0]);

/**
 * own_cd - Change the current directory.
 * @args: A pointer to an array of strings containing command arguments.
 *		args[0] should be the command itself,
 *		and args[1] should be the directory path.
 *
 * Return: 1 to continue the shell loop.
 *
 */

int own_cd(char **args)
{
	if (args[1] == NULL)
	{
		/* No directory specified, go to home directory */
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
		}
	} else
	{
		/* Change to the specified directory */
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
	return (1); /* Return 1 to continue shell loop */
}

/**
 * own_env - Display the environment variables.
 * @args: A pointer to an array of strings containing command arguments.
 *         This function does not use the args parameter.
 *
 * Return: 1 to continue the shell loop.
 */

int own_env(char **args)
{
	char **env = environ;
	char newline = '\n';

	env = environ;

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, &newline, 1);
		env++;
	}

	(void)args;
	return (1);
}

/**
 * own_help - Display help information for the shell.
 * @args: A pointer to an array of strings containing command arguments.
 *		This function does not use the args parameter.
 *
 * Return: 1 to continue the shell loop.
 */

int own_help(char **args)
{

	char *help_msg = "Simple Shell Help\n"
					 "Available commands:\n"
					 "1. cd <directory>: Change the current directory\n"
					 "2. env: Display the environment variables\n"
					 "3. help: Display this help message\n"
					 "4. exit: Exit the shell\n";

	write(STDOUT_FILENO, help_msg, strlen(help_msg));

	(void)args;
	return (1);
}

/**
 * own_exit - Exit the shell.
 * @args: A pointer to an array of strings containing command arguments.
 *			This function does not use the args parameter.
 *
 * Return: This function does not return.
 */

int own_exit(char **args)
{
	(void)args;
	exit(EXIT_SUCCESS);
}

#endif /* BUILTIN_C */
