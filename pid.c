#ifndef _PID_
#define _PID_

#include <stdio.h>
#include <unistd.h>

/**
* get_process_identifier - Retrieves and prints the unique
*							identifier of the current process.
*
* Return: Always 0.
*
*/
int get_process_identifier(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("%u\n", my_pid);
	return (0);
}

#endif /* _PID_ */
