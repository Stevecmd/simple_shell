#ifndef _ENV_ENVIRON_
#define _ENV_ENVIRON_

#include <stdio.h>

/**
* environment - prints the environment
*
* @ac: The number of command-line arguments.
* @av: An array of strings containing the command-line arguments.
* @env: An array of strings containing the environment variables.
*
* Return: Always 0.
*/
int environment(int ac, char **av, char **env)
{
	unsigned int i;

	i = 0;
	while (env[i] != NULL)
{
	printf("%s\n", env[i]);
	i++;
}
	return (0);
}

#endif /* _ENV_ENVIRON_ */
