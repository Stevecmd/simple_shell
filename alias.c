#ifndef _ALIAS_
#define __ALIAS__

#include "shell.h"

/**
 * remove_alias - Removes an alias from the information structure.
 *
 * This function takes in a pointer to an info_t structure and a string
 * representing an alias. It removes the specified alias from the
 * information structure.
 *
 * @info: A pointer to the info_t structure containing alias information.
 * @str: A pointer to the string representing the alias to be removed.
 *
 * Return: 1 if the specified alias is not found
 * or if the format is incorrect., 0 on success.
 *
 * Returns the result of delete_node_at_index() otherwise.
 */
int remove_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = exit_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		find_node_index(info->alias, find_node_with_prefix_and_char(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * handle_alias_command - Handles alias command functionality.
 * This function manages the alias command, allowing users
 * to set, print, or delete aliases. When called without
 * any arguments, it prints all existing aliases.
 * If given arguments, it either sets a new alias or prints
 * the alias associated with the specified command.
 *
 * @info: A pointer to a structure containing
 * information about the command and its arguments.
 *
 *  Return: Always returns 0 to indicate success.
 */
int handle_alias_command(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_environment_variable_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = exit_strchr(info->argv[i], '=');
		if (p)
			define_alias(info, info->argv[i]);
		else
			print_environment_variable_alias(find_node_with_prefix_and_char(info->alias, info->argv[i], '='));
	}

	return (0);
}

/**
 * define_alias - Sets an alias for a given command in the information structure.
 * An alias is a user-defined shorthand for a command.
 * @info: Pointer to the information structure containing aliases.
 * @str: Pointer to the string containing the alias definition.
 *
 * This function parses the input string to identify the alias name
 * and the command it represents. If an equal sign '=' is found in
 * the string, it separates the alias name from its corresponding command.
 * If no equal sign is found, the function assumes that the alias
 * is being unset.
 * If the alias already exists, it is first removed and
 * then replaced with the new definition.
 *
 * Return: returns 1 if an error occurs during parsing
 * or memory allocation, otherwise returns 0.
 */
int define_alias(info_t *info, char *str)
{
	char *p;

	p = exit_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_to_end_of_linked_list(&(info->alias), str, 0) == NULL);
}

/**
 * extract_chars - Copies characters from a given string
 * within a specified range.
 * This function takes a string 'pathstr' and extracts characters
 * from index 'start' to index 'stop' (exclusive), excluding any
 * ':' characters encountered in between.
 * The extracted characters are stored in a static buffer 'buf'.
 * It ensures that the copied string is null-terminated.
 *
 * @pathstr: The input string from which characters are copied.
 * @start: The starting index from which copying begins.
 * @stop: The stopping index (exclusive) until which copying occurs.
 *
 * Return: A pointer to the copied string stored in a static buffer 'buf'.
 */
char *extract_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

#endif /* __ALIAS__ */
