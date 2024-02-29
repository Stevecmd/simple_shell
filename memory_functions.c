#ifndef __MEMORY_FUNCTIONS__
#define __MEMORY_FUNCTIONS__

#include "shell.h"

/**
 * custom_memset - Fills memory with a constant byte.
 *
 * This function fills the first n bytes of the
 * memory area pointed to by s with the constant byte b.
 *
 * @s: Pointer to the memory area to be filled.
 * @b: The constant byte to fill the memory area with.
 * @n: The number of bytes to be filled.
 *
 * Return: Pointer to the memory area s.
 */
char *custom_memset(char *dest, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		dest[i] = value;

	return (dest);
}

/**
 * deallocate_memory_block - Frees the memory block allocated by ptr.
 *
 * Checks if ptr is not NULL and if it points
 * to a valid memory block. If so, frees the
 * memory block and sets ptr to NULL to avoid
 * dangling pointers.
 *
 * @ptr: Pointer to the pointer to be freed.
 *
 * Return: 1 if the memory block is successfully freed, otherwise 0.
 */
int deallocate_memory_block(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * deallocate - Frees memory allocated to a pointer to pointer to char.
 * @pp: string of strings.
 *
 * This function takes a pointer to a pointer to char and
 * frees the memory allocated to both the array of char pointers
 * and the memory pointed to by each char pointer.
 *
 * This function frees memory allocated for an array of strings.
 * @pp: A pointer to a pointer to char, representing an array of strings.
 *
 * Return: void.
 *
 */
void deallocate(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	while (*pp)
		free(*pp++);

	free(a);
}

/**
 * _realloc - reallocates memory block with new size
 *
 * This function reallocates the memory block pointed to by ptr.
 * It resizes the memory block to new_size bytes.
 * If ptr is NULL, it behaves like malloc(new_size).
 * If new_size is 0 and ptr is not NULL, it behaves like free(ptr).
 * If new_size is the same as old_size, it returns ptr as is.
 * Otherwise, it copies the existing data to the new memory block
 * and frees the old memory block.
 *
 * @ptr: pointer to the previously allocated memory block
 * @old_size: size of the allocated space for ptr
 * @new_size: new size for the reallocation
 *
 * Return: pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

#endif /* __MEMORY_FUNCTIONS__ */
