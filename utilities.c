#ifndef __UTILITIES__
#define __UTILITIES__

#include "shell.h"

/**
 * print_environment_variable_alias - Prints an environment variable alias.
 * This function takes a node from a linked list
 * containing environment variable strings and
 * prints out the alias part of the variable.
 *
 * @node: A pointer to the node containing the environment
 * variable string.
 *
 * Return: 0 on success, 1 if the node is NULL.
 */
int print_environment_variable_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = exit_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * read_line_from_file_descriptor -  reads a line from a file descriptor and
 * stores it into a buffer.
 * @info: A pointer to a structure holding file descriptor information.
 * @ptr: A pointer to a pointer to the buffer where the line will be stored.
 * @length: A pointer to the size of the buffer.
 *
 * Return: On success, the number of characters read
 * including the newline character; on failure, -1.
 */
int read_line_from_file_descriptor(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_from_file_descriptor(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = exit_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strncat_exit(new_p, buf + i, k - i);
	else
		exit_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * reset_info_structure -  Clears the information stored in a
 * structure of type info_t.
 * This function resets all the fields of the provided info_t
 * structure to NULL or zero.
 * It is typically used to clean up memory or reset state before
 * reusing the structure.
 * @info: A pointer to the info_t structure whose fields need to be cleared.
 */
void reset_info_structure(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}



/**
 * display_program_help - Displays help information for a program.
 * @info:  A pointer to a structure containing program information.
 * This function is responsible for displaying help information
 * for the program. It currently prints a message indicating
 * that the help call works but the function itself is not yet implemented.
 *
 * @info: A pointer to a structure containing program information,
 * which may include command-line arguments and other details.
 *
 *  Return: Always returns 0 indicating success.
 */
int display_program_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * is_interactive_mode - Checks if the program is running in an interactive mode.
 * An interactive mode is determined by verifying whether the
 * standard input (stdin) is associated with a terminal (tty),
 * and if the file descriptor for reading (readfd) in the
 * provided information structure (info) is less than or equal
 * to 2, which typically corresponds to the standard input, output,
 * and error streams.
 *
 * @info: Pointer to a structure containing information relevant to the
 * current execution context.
 *
 * Return: Returns 1 if the program is running interactively;
 * otherwise, returns 0 to indicate non-interactive mode.
 */
int is_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

#endif /* __UTILITIES__ */
