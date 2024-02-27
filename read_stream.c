#ifndef _READ_STREAM_
#define _READ_STREAM_

#include "shell.h"

#define INITIAL_BUF_SIZE 1024
#define BUF_SIZE_INCREMENT 1024

/**
 * read_stream - Read a line from the stream.
 *
 * This function reads a line from the standard input stream (stdin).
 * It dynamically allocates memory for the line and adjusts the buffer size
 * as needed. The line is terminated by a null character ('\0') and returned
 * to the caller.
 *
 * Return: A pointer to the string containing the read line.
 */

/*
 * File: read_stream.c
 * Auth: Steve Murimi
 */

char *read_stream(void)
{
	int bufsize = INITIAL_BUF_SIZE;
	int i = 0;
	char *line = malloc(sizeof(char) * bufsize);

	if (line == NULL)
	{
		perror("Read_stream: Allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		char character = getchar();

		if (character == EOF || character == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		line[i] = character;
		i = handle_buffer_resize(line, i, &bufsize);
		i++;
	}
}

/**
 * handle_buffer_resize - Resize the buffer if needed.
 *
 * This function checks if the buffer is full and resizes it if needed.
 *
 * @line: Pointer to the buffer.
 * @i: Current index in the buffer.
 * @bufsize: Pointer to the buffer size.
 *
 * Return: Updated index value.
 */
int handle_buffer_resize(char *line, int i, int *bufsize)
{
	char *temp;

	if (i >= *bufsize - 1)
	{
		*bufsize += BUF_SIZE_INCREMENT;
		temp = realloc(line, *bufsize);
		if (temp == NULL)
		{
			perror("Read_stream: Reallocation error\n");
			free(line);
			exit(EXIT_FAILURE);
		}
		line = temp;
	}
	return (i);
}

#endif /* _READ_STREAM_ */
