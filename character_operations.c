#ifndef _CHARACTER_OPERATIONS_
#define _CHARACTER_OPERATIONS_

#include "shell.h"

/**
 * is_alpha - Checks if a character is an alphabetic character.
 *
 * This function takes a character as input and checks whether
 * it is an alphabetic character (either uppercase or lowercase).
 *
 * @character: The character to be checked.
 *
 * Return: 1 if @character is an alphabetic character, 0 otherwise.
 */
int is_alpha(int character)
{
	/* Return 1 to indicate that the character is alphabetic */
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
	{
		return (1);
	}
	else
	{
		/* Return 0 to indicate that the character is not alphabetic */
		return (0);
	}
}

/**
 * string_starts_with - checks if haystack starts with needle.
 *
 * This function checks if the string haystack starts with the
 * string needle. It iterates through both strings, comparing
 * characters, and returns a pointer to the character in haystack
 * immediately after the matched prefix if the prefix is found.
 * If haystack doesn't start with needle, it returns NULL.
 *
 * @haystack: The string to be checked.
 * @needle: The prefix to be compared.
 *
 * Return: A pointer to the character in haystack immediately
 * after the matched prefix if found, NULL otherwise.
 */
char *string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 *	string_dupy - duplicates a given string.
 *	This function takes a string as input and
 * creates a duplicate of it.
 * It calculates the length of the input string,
 * allocates memory for the duplicate string,
 * and then copies the characters from the input
 * string into the duplicate in reverse order.
 *	@str: Pointer to the string to be duplicated.
 *
 *	Return: Pointer to the duplicated string
 *	or NULL if memory allocation fails.
 */
char *string_dupy(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * is_chain - checks if the current position in the buffer indicates
 * the presence of a command chaining operator.
 * @info: pointer to information struct storing buffer format.
 * @buf: pointer to the buffer containing command line.
 * @pos: pointer to the current position in the buffer.
 * This function examines the character at the current position
 * in the buffer to determine if it represents a command chaining
 * operator such as '|', '||', '&&', or ';'. If such an operator
 * is found, it updates the buffer and information struct accordingly.
 *
 * Return: 1 if a command chaining operator is found, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *pos)
{
	size_t j = *pos;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->buf_format = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->buf_format = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->buf_format = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

#endif /* _CHARACTER_OPERATIONS_ */
