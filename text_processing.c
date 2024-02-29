#ifndef __TEXT_PROCESSING__
#define __TEXT_PROCESSING__

#include "shell.h"

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @character: The character to be checked.
 * @delimiter_set: A string containing delimiter characters.
 *
 * This function iterates through the given string
 * of delimiter characters and checks if the provided character
 * matches any of them. If a match is found, it returns 1,
 * indicating that the character is a delimiter.
 * If no match is found, it returns 0, indicating that
 * the character is not a delimiter.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char character, char *delimiter_set)
{
	while (*delimiter_set)
	{
		if (*delimiter_set++ == character)
			return (1);
	}
	return (0);
}

/**
 * strtow - Splits a string into words based on given delimiters.
 * @str: The string to split.
 * @delims: A string containing delimiter characters.
 *
 * This function splits the input string @str into words, using the characters
 * specified in @delims as delimiters. It dynamically allocates memory for the
 * array of words and each individual word. The resulting array of words is
 * terminated by a NULL pointer.
 *
 * Return: Upon success, returns a pointer to an array of strings (words)
 * or NULL on failure.
 */
char **strtow(char *input_string, char *delimiters)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (input_string == NULL || input_string[0] == '\0')
		return (NULL);

	if (!delimiters)
		delimiters = " ";

	for (i = 0; input_string[i] != '\0'; i++)
		if (!is_delimiter(input_string[i], delimiters) && (is_delimiter(input_string[i + 1], delimiters) || !input_string[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter(input_string[i], delimiters))
			i++;

		k = 0;
		while (!is_delimiter(input_string[i + k], delimiters) && input_string[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = input_string[i++];
		words[j][m] = 0;
	}

	words[j] = NULL;
	return (words);
}

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
 * n an array of strings.
 *
 * This function iterates through the elements of an array of strings
 * (arguments),
 * replacing placeholders of environment variables with their
 * corresponding values.
 * Placeholders are identified by the '$' symbol followed by
 * a sequence of characters.
 * If the placeholder matches "$?", it is replaced with the exit
 * status of the previous command.
 * If the placeholder matches "$$",
 * it is replaced with the process ID of the current process.
 * If the placeholder matches an environment variable,
 * it is replaced with the value of that variable.
 * If a placeholder does not match any known environment variable,
 * it is replaced with an empty string.
 *
 * @info:  A pointer to a structure containing information about
 * the environment and arguments.
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

#endif /* __TEXT_PROCESSING__ */
