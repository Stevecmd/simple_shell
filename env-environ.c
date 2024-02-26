#ifndef _ENV_ENVIRON_
#define _ENV_ENVIRON_

#include <unistd.h>

/**
* environment - prints the environment
*
* @ac: The number of command-line arguments.
* @av: An array of strings containing the command-line arguments.
* @env: An array of strings containing the environment variables.
*
* The program iterates through the array of
* environment variables, printing each one.
* 
* Return: Always 0.
*/

/*
 * File: env-environ.h
 * Auth: Steve Murimi
 */

int environment(char **env)
{
	unsigned int i = 0;
	char newline = '\n';

	while (env[i] != NULL)
	{
		size_t len = 0;
		while (env[i][len] != '\0') {
			len++;
		}
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, &newline, 1);
		i++;
	}
	return (0);
}

#endif /* _ENV_ENVIRON_ */