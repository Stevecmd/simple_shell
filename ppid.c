#ifndef _PPID_
#define _PPID_

#include <unistd.h>
#include <stdlib.h>

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
	pid_t my_ppid = getppid();

	// Convert PPID to a string
	char ppid_buffer[20];
	int digits = 0;
	pid_t temp_ppid = my_ppid;
	// Count number of digits in my_ppid
	do {
		temp_ppid /= 10;
		digits++;
	} while (temp_ppid != 0);

	// Convert digits to string
	temp_ppid = my_ppid;
	for (int i = digits - 1; i >= 0; i--) {
		ppid_buffer[i] = (temp_ppid % 10) + '0';
		temp_ppid /= 10;
	}

	// Write PPID to STDOUT
	if (write(STDOUT_FILENO, ppid_buffer, digits) != digits) {
		// Error writing to STDOUT
		exit(EXIT_FAILURE);
	}

	return 0;
}

#endif /* _PPID_ */
