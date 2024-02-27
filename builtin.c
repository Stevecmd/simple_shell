#ifndef BUILTIN_C
#define BUILTIN_C

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"

/*
 * File: builtin.c
 * Auth: Steve Murimi
 */

extern char **environ; /* Declare environmental variable */

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

int own_cd(char **args) {
	if (args[1] == NULL) {
		/* No directory specified, go to home directory */
		if (chdir(getenv("HOME")) != 0) {
			perror("cd");
		}
	} else {
		/* Change to the specified directory */
		if (chdir(args[1]) != 0) {
			perror("cd");
		}
	}
	return 1; /* Return 1 to continue shell loop */
}

int own_env(char **args) {
	char **env = environ;
	char newline = '\n';

	env = environ;

	while (*env != NULL) {
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, &newline, 1);
		env++;
	}

	(void)args;
	return 1;
}

int own_help(char **args) {

	char *help_msg = "Simple Shell Help\n"
					 "Available commands:\n"
					 "1. cd <directory>: Change the current directory\n"
					 "2. env: Display the environment variables\n"
					 "3. help: Display this help message\n"
					 "4. exit: Exit the shell\n";

	write(STDOUT_FILENO, help_msg, strlen(help_msg));

	(void)args;
	return 1;
}

int own_exit(char **args) {
	(void)args;
	exit(EXIT_SUCCESS);
}

#endif /* BUILTIN_C */