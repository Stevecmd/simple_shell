#ifndef _EXEC_
#define _EXEC_

#include <stdio.h>
#include <unistd.h>

/**
* execute_command - executes a command using execve
*
* Return: 0 on success, -1 on failure.
*/
int execute_command(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf("Before execve\n");
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error:");
	}
	printf("After execve\n");
	return (0);
}

#endif /* _EXEC_ */
