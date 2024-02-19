#ifndef _PID_
#define _PID_

#include <stdio.h>
#include <unistd.h>

/**
 * main - Process identifier
 *
 * Return: Always 0.
 * 
 */
int main(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("%u\n", my_pid);
	return (0);
}

#endif /* _PID_ */