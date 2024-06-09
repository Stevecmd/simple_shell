#ifndef __TEXT_PROCESSING__
#define __TEXT_PROCESSING__

#include "shell.h"

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @character: The character to be checked.
 * @delimiter_set: A string containing delimiter characters.
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
 * counting_words - Counts the number of words in a string based on delimiters.
 * @input_string: The string to split.
 * @delimiters: A string containing delimiter characters.
 *
 * Return: The number of words found.
 */
int counting_words(char *input_string, char *delimiters)
{
	int i, numwords = 0;

	for (i = 0; input_string[i] != '\0'; i++)
	{
		if (!is_delimiter(input_string[i], delimiters) &&
			(is_delimiter(input_string[i + 1], delimiters) ||
			!input_string[i + 1]))
		{
			numwords++;
		}
	}

	return (numwords);
}

/**
 * allocate_words_array - Allocates memory for the array of words.
 * @numwords: The number of words.
 *
 * Return: A pointer to the allocated array of words or NULL on failure.
 */
char **allocate_words_array(int numwords)
{
	char **words = malloc((1 + numwords) * sizeof(char *));

	if (!words)
		return (NULL);

	return (words);
}

/**
 * allocate_and_fill_word - Allocates memory for a word and fills it.
 * @input_string: The input string.
 * @i: The starting index of the word.
 * @k: The length of the word.
 *
 * Return: A pointer to the allocated word or NULL on failure.
 */
char *allocate_and_fill_word(char *input_string, int i, int k)
{
	int m;
	char *word = malloc((k + 1) * sizeof(char));

	if (!word)
		return (NULL);

	for (m = 0; m < k; m++)
		word[m] = input_string[i + m];
	word[m] = '\0';

	return (word);
}

/**
 * fill_words_array - Fills the array of words by splitting the input string.
 * @input_string: The input string.
 * @delimiters: A string containing delimiter characters.
 * @words: The array of words to be filled.
 * @numwords: The number of words.
 *
 * Return: 0 on success, -1 on failure.
 */
int fill_words_array(
	char *input_string,
	char *delimiters,
	char **words,
	int numwords
)
{
	int i, j, k;

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimiter(input_string[i], delimiters))
			i++;

		k = 0;
		while (!is_delimiter(input_string[i + k], delimiters) &&
			   input_string[i + k])
			k++;

		words[j] = allocate_and_fill_word(input_string, i, k);
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (-1);
		}

		i += k;
	}

	words[j] = NULL;
	return (0);
}

#endif /* __TEXT_PROCESSING__ */
