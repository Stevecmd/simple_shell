#ifndef _SPLIT_LINES_
#define _SPLIT_LINES_

#include "shell.h"
#include <string.h>

/**
* split_line - Split a string into multiple tokens.
* @line: The string to be split.
*
* Return: A pointer to an array of tokens.
*         Returns NULL if memory allocation fails or if the input line is empty.
*/

/*
 * File: split_line.c
 * Auth: Steve Murimi
 */

#define TOK_DELIM " \t\n"

char **split_line(char *line)
{
	int bufsize = 64;            /* Initial size of the tokens array */
	int i = 0;                   /* Index for tokens array */
	char **tokens = malloc(bufsize * sizeof(char *));  /* Allocate memory for tokens array */
	char *token;                 /* Pointer to store each token */
	char **temp;                 /* Temporary pointer for realloc */

	/* Check if memory allocation for tokens array was successful */
	if (!tokens)
	{
		write(STDERR_FILENO, "split_line: allocation error for tokens\n", 40);
		_exit(EXIT_FAILURE);
	}

	/* Tokenize the input line using strtok */
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		/* Check if token is a comment (starts with '#'), and ignore it */
		if (token[0] == '#')
		{
			break;
		}

		/* Store token in tokens array */
		tokens[i] = token;
		i++;

		/* Check if tokens array needs to be resized */
		if (i >= bufsize)
		{
			bufsize += bufsize;   /* Double the buffer size */
			temp = realloc(tokens, bufsize * sizeof(char *));
			/* Check if memory reallocation was successful */
			if (!temp)
			{
				write(STDERR_FILENO, "split_line: reallocation error for tokens\n", 43);
				_exit(EXIT_FAILURE);
			}
			tokens = temp;
		}

		/* Get next token */
		token = strtok(NULL, TOK_DELIM);
	}

	tokens[i] = NULL;  /* Null-terminate the tokens array */
	return tokens;     /* Return the tokens array */
}

#endif /* _SPLIT_LINES_ */