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

/*
 * File: pid.c
 * Auth: Steve Murimi
 */

int get_process_identifier(void)
{
	pid_t my_pid;
	pid_t temp_pid;
	int digits = 0;
	int i;
	char pid_buffer[20];

	my_pid = getpid();
    
	/* Convert process ID to a string */
	temp_pid = my_pid;

	/* Count number of digits in my_pid */
	do {
		temp_pid /= 10;
		digits++;
	} while (temp_pid != 0);

	/* Convert digits to string */
	temp_pid = my_pid;
	for (i = digits - 1; i >= 0; i--) {
		pid_buffer[i] = (temp_pid % 10) + '0';
		temp_pid /= 10;
	}

	/* Write process ID to STDOUT */
	write(STDOUT_FILENO, pid_buffer, digits);
	write(STDOUT_FILENO, "\n", 1);

	return (0);
}
#endif /* _PID_ */