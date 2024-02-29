#ifndef __STRING_UTILITIES__
#define __STRING_UTILITIES__

#include "shell.h"

/**
 * _putchar - writes a character to the output buffer.
 * If the buffer is full or if a flush character
 * is received, it flushes the buffer to stdout.
 * It maintains a static buffer to accumulate
 * characters before flushing.
 *
 * @character: The character to be written to the buffer.
 *
 * Return: On success, returns 1.
 *			On failure, returns -1.
 */
int _putchar(char character)
{
	static int buffer_index;
	static char error_buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(1, error_buffer, buffer_index);
		buffer_index = 0;
	}
	if (character != BUFFER_FLUSH)
		error_buffer[buffer_index++] = character;

	return (1);
}

/**
 *_puts - prints a string to stdout.
 *
 * This function prints each character of the
 * input string to the standard output until
 * the null terminator is encountered.
 *
 *@str: The string to be printed.
 *
 * Return: None.
 */
void _puts(char *str)
{
	int i;

	if (!str)
		return;

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}


/**
 * count_words - Counts the number of words in a string.
 *
 * This function counts the number of words in the input string
 * based on the provided delimiter.
 *
 * @str: The input string.
 * @delim: The delimiter character.
 *
 * Return: The number of words in the string.
 */
int count_words(char *str, char delim)
{
	int i, numwords = 0;

	if (str == NULL || str[0] == '\0')
		return (0);

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != delim && str[i + 1] == delim) ||
			(str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
		{
			numwords++;
		}
	}

	return (numwords);
}

/**
 * create_word_array - Creates an array of words from a string.
 *
 * This function takes a string and a delimiter character as input
 * and splits the string into individual words based on the delimiter.
 * It dynamically allocates memory for the array of words.
 *
 * @str: The string to be split.
 * @delim: The delimiter character.
 *
 * Return: An array of pointers to the individual words, or NULL if
 *         memory allocation fails or if the input string is empty.
 */
char **create_word_array(char *str, char delim)
{
	int i, j, k, m, numwords;
	char **words;

	numwords = count_words(str, delim);

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delim && str[i] != '\0')
			i++;

		k = 0;
		while (str[i + k] != delim && str[i + k] != '\0')
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
			words[j][m] = str[i++];

		words[j][m] = '\0';
	}

	words[j] = NULL;
	return (words);
}

/**
 * string_strlen - Calculates the length of a string.
 *
 * This function takes a string as input and counts
 * the number of characters in it until reaching
 * the null terminator. It returns the length of the string.
 *
 * @string: The input string to calculate its length.
 *
 * Return: The length of the string.
 */
int string_strlen(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}

#endif /* __STRING_UTILITIES__ */
