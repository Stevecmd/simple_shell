#ifndef _ENV_MAIN_
#define _ENV_MAIN_

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
* print_environment - prints the unique identifier
*						(environment variables) of the current process.
* This function prints out the environment variables of
* the current process.
* It iterates through the array of environment
* variables, printing each one.
*
* Return: Always 0 - success.
*/

/*
 * File: env-main.c
 * Auth: Steve Murimi
 */


void print_environment(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		size_t len = strlen(environ[i]);

		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

#endif /* _ENV_MAIN_ */
