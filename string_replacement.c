#ifndef __STRING_REPLACEMENT__
#define __STRING_REPLACEMENT__

#include "shell.h"

/**
 * replace_string - Replaces a string with a new one.
 *
 * Frees the memory of the old string and
 * updates it with the new string.
 *
 * @old: Pointer to the old string.
 * @new: Pointer to the new string.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

#endif /* __STRING_REPLACEMENT__ */
