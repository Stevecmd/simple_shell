#ifndef _ENV_MAIN_
#define _ENV_MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void print_environment(void)
{
	char **environ_ptr = environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

#endif /* _ENV_MAIN_ */
