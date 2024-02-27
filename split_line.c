#ifndef _SPLIT_LINES_
#define _SPLIT_LINES_

#include "shell.h"
#include <string.h>
#define TOK_DELIM " \t\n"

/**
 * handle_allocation_error - Helper function to
 *							handle memory allocation errors.
 */

static void handle_allocation_error(void)
{
	perror("split_line: allocation error for tokens");
	exit(EXIT_FAILURE);
}

/**
 * handle_reallocation_error - Helper function to handle reallocation errors.
 */

static void handle_reallocation_error(void)
{
	perror("split_line: reallocation error for tokens");
	exit(EXIT_FAILURE);
}

/**
 * tokenize_line - Helper function to tokenize the input line.
 * @line: The string to be tokenized.
 *
 * Return: A pointer to an array of tokens.
 */

static char **tokenize_line(char *line)
{
	int bufsize = 64;
	int i = 0;
	char *token;
	char **tokens = malloc(bufsize * sizeof(char *));
	char **temp;

	if (!tokens)
	{
		handle_allocation_error();
	}

	token = strtok(line, TOK_DELIM);

	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
		}
		tokens[i++] = token;


		if (i >= bufsize)
		{
			bufsize += bufsize;
			temp = realloc(tokens, bufsize * sizeof(char *));

			if (!temp)
				handle_reallocation_error();

			tokens = temp;
		}
		token = strtok(NULL, TOK_DELIM);
	}

	tokens[i] = NULL;
	return (tokens);
}

/**
* split_line - Split a string into multiple tokens.
* @line: The string to be split.
*
* Return: A pointer to an array of tokens.
*         Returns NULL if memory allocation
*			fails or if the input line is empty.
*/

/*
 * File: split_line.c
 * Auth: Steve Murimi
 */

char **split_line(char *line)

{
	char **tokens = tokenize_line(line);

	return (tokens);

}

#endif /* _SPLIT_LINES_ */
