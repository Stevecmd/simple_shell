#ifndef BUILTIN_1_C
#define BUILTIN_1_C

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*
 * File: builtin1.c
 * Auth: Steve Murimi
 */

/* Custom function to convert an integer to a string */
void int_to_string(char *str, int num)
{
	int i = 0;
	int start = 0, end = i - 1;

	/* Calculate the digits and store them in reverse order */
	while (num != 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	str[i] = '\0';

	/* Reverse the string */
	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

#endif /* BUILTIN_1_C */
