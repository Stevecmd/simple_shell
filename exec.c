#ifndef _EXEC_
#define _EXEC_

#include <stdlib.h> // For EXIT_FAILURE
#include <unistd.h>

/**
* execute_command - executes a command using execve.
* This function attempts to execute a command
* using the execve system call.
* 
* The command to be executed is "/bin/ls" with arguments "-l" and "/usr/".
*
* Return: 0 on success, -1 on failure.
*/
int execute_command(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	write(STDOUT_FILENO, "Before we use execve\n", 22);
	if (execve(argv[0], argv, NULL) == -1)
	{
		char *error_message = "Error: Unable to execute command\n";
		write(STDERR_FILENO, error_message, strlen(error_message));
		exit(EXIT_FAILURE);
	}
	// This line will not be executed if execve is successful
	write(STDOUT_FILENO, "After we use execve\n", 21);
	return (0);
}

#endif /* _EXEC_ */
