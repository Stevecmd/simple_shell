#ifndef _ENV_MAIN_
#define _ENV_MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
* print_environment - Retrieves and prints the unique
*						identifier of the current process.
* This function retrieves the process identifier (PID) of the current process
* using getpid() function and prints it to the standard output.
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
