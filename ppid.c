#ifndef _PPID_
#define _PPID_

#include <stdio.h>
#include <unistd.h>

/**
* get_parent_process_identifier - Retrieves the parent process ID (PPID).
*
* This function retrieves the process ID (PID) of the parent process
* in the current process's execution environment. It then prints the
* obtained PPID to the standard output.
*
* Return: Always 0 Success.
*/
int get_parent_process_identifier(void)
{
	pid_t my_ppid;

	my_ppid = getppid();
	printf("%u\n", my_ppid);
	return (0);
}

#endif /* _PPID_ */
