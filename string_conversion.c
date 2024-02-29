#ifndef __STRING_CONVERSION__
#define __STRING_CONVERSION__

#include "shell.h"

/**
 * _atoi - converts a string to an integer.
 *
 * This function takes a string s as input and
 * converts it to an integer. It iterates through
 * the characters of the string, accumulating the
 * numerical value until a non-numeric character
 * is encountered. It handles negative numbers and
 * returns the corresponding integer value.
 *
 * @s: The input string to be converted.
 *
 * Return: The integer converted from the input string.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * exit_strchr - Searches for the first occurrence of a
 * character in a string.
 * Returns a pointer to the first occurrence of the character 'c'
 * in the string 's'. If the character is not found, returns NULL.
 * @s: The string to be searched.
 * @c: The character to search for.
 *
 * Return: A pointer to the first occurrence of the character 'c'
 * in the string 's', or NULL if the character is not found.
 */
char *exit_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * exit_strncpy - Safely copies a string from src to dest,
 * ensuring termination.
 *
 * It copies at most n characters from src to dest and ensures that
 * dest is null-terminated. If n is greater than the length of src,
 * the remaining characters in dest are filled with null bytes.
 *
 * @dest: The destination buffer where the string will be copied.
 * @src: The source string to be copied.
 * @n: The maximum number of characters to copy from src.
 *
 * Return: A pointer to dest, the destination buffer.
 */
char *exit_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * string_strcat - Concatenates two strings.
 * This function concatenates the string pointed to by src
 * to the end of the string pointed to by dest.
 *
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *string_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;

	return (ret);
}

/**
 * string_cpy - Copies a string from source to destination.
 *
 * This function copies the string from the source
 * to the destination. It ensures that the destination
 * string is not the same as the source string and that
 * the source string is not NULL. It iterates through
 * each character of the source string, copying it to
 * the destination string until it encounters the null
 * terminator, then adds a null terminator to the
 * destination string to terminate it.
 *
 * @dest: The destination string where the copied string will be stored.
 * @src: The source string which will be copied.
 *
 * Return: The pointer to the destination string.
 */
char *string_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;

	return (dest);
}

#endif /* __STRING_CONVERSION__ */
