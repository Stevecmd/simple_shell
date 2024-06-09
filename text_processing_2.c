#ifndef __TEXT_PROCESSING_2__
#define __TEXT_PROCESSING_2__

#include "shell.h"

/**
 * compare_strings - compares two strings character by character
 * @string1: pointer to the first string
 * @string2: pointer to the second string
 *
 * This function compares two strings character by character until a
 * difference is found or one of the strings ends. It returns an
 * integer less than, equal to, or greater than zero if the first
 * string is found to be less than, equal to, or greater than the
 * second string, respectively.
 *
 * Return: An integer less than, equal to, or greater than zero if the
 *			first string is found to be less than, equal to, or greater.
 *			than the second string, respectively.
 */
int compare_strings(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);

		string1++;
		string2++;
	}

	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * replace_alias - Replaces an alias in the command with its
 * corresponding value.
 *
 * This function searches for an alias in the list of aliases stored in 'info',
 * matching the command name stored in 'info->argv[0]'. If found, it replaces
 * 'info->argv[0]' with the corresponding value of the alias.
 * It iterates up to 10 times to allow for nested aliases.
 *
 * @info: A pointer to the info_t structure containing command information.
 *
 * Return: 1 if the alias replacement is successful, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_with_prefix_and_char(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);

		p = exit_strchr(node->str, '=');
		if (!p)
			return (0);

		p = string_dupy(p + 1);
		if (!p)
			return (0);

		info->argv[0] = p;
	}

	return (1);
}

/**
 * replace_vars - Replaces environment variable placeholders
 * in an array of strings.
 *
 * This function iterates through the elements of an array of strings
 * (arguments), replacing placeholders of environment variables with their
 * corresponding values.
 *
 * @info:  A pointer to a structure containing information
 * about the environment and arguments.
 *
 * Return: Always 0 indicating success.
 */
int replace_vars(info_t *info)
{
	int i;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!compare_strings(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				string_dupy(convert_number_to_string(info->cmd_status, 10, 0)));
			continue;
		}

		if (!compare_strings(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				string_dupy(convert_number_to_string(getpid(), 10, 0)));
			continue;
		}

		node = find_node_with_prefix_and_char(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				string_dupy(exit_strchr(node->str, '=') + 1));
			continue;
		}

		replace_string(&info->argv[i], string_dupy(""));
	}

	return (0);
}

/**
 * strtow - Splits a string into words based on given delimiters.
 * @input_string: The string to split.
 * @delimiters: A string containing delimiter characters.
 *
 * Return: Upon success, returns a pointer to an array of strings (words)
 * or NULL on failure.
 */
char **strtow(char *input_string, char *delimiters)
{
	int numwords;
	char **words;

	if (input_string == NULL || input_string[0] == '\0')
		return (NULL);

	if (!delimiters)
		delimiters = " ";

	numwords = counting_words(input_string, delimiters);
	if (numwords == 0)
		return (NULL);

	words = allocate_words_array(numwords);
	if (!words)
		return (NULL);

	if (fill_words_array(input_string, delimiters, words, numwords) == -1)
		return (NULL);

	return (words);
}

#endif /* __TEXT_PROCESSING_2__ */
