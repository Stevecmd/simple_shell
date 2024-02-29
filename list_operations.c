#ifndef __LIST_OPERATIONS__
#define __LIST_OPERATIONS__

#include "shell.h"

/**
 * list_length - calculates the length of a linked list.
 * @head: A pointer to the head of the linked list.
 *
 * This function traverses the given linked list and counts
 * the number of elements it contains.
 * It starts from the head of the list and iterates through
 * each node until reaching the end (NULL), counting each node
 * encountered along the way.
 *
 * Return: The number of elements in the linked list.
 */
size_t list_length(const list_t *head)
{
	size_t length = 0;

	while (head)
	{
		head = head->next;
		length++;
	}
	return (length);
}

/**
 * list_to_strings - Converts a linked list of strings
 * into an array of strings.
 * @head: Pointer to the head of the linked list.
 *
 * This function takes the head of a linked list containing
 * strings and converts it into an array of strings.
 * It dynamically allocates memory for the array
 * and each string element, copying the content from the linked list nodes.
 * Memory is allocated for the array and each string individually.
 * If any memory allocation fails,
 * it frees the previously allocated memory and returns NULL.
 *
 * Return: Upon success, returns a pointer to the array of strings.
 * If the input linked list is empty or if memory allocation fails,
 * returns NULL.
 */
char **list_to_strings(list_t *head)
{
	list_t *current_node = head;
	size_t num_nodes = list_length(head), j;
	char **strs;
	char *str;
	size_t k;

	if (!head || !num_nodes)
		return (NULL);

	strs = malloc(sizeof(char *) * (num_nodes + 1));
	if (!strs)
		return (NULL);

	for (j = 0; current_node; current_node = current_node->next, j++)
	{
		str = malloc(string_strlen(current_node->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = string_cpy(str, current_node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}

/**
 * free_list - frees memory allocated for a linked list.
 * @head_ptr: Pointer to the pointer of the head of the list.
 *
 * This function takes a pointer to the head of a linked list
 * and frees all memory allocated for each node in the list.
 * It iterates through the list, freeing each node and its
 * associated string data, then sets the head pointer to NULL.
 *
 * Return: None
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

#endif /* __LIST_OPERATIONS__ */
