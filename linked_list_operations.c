#ifndef __LINEKD_LIST_OPERATIONS__
#define __LINEKD_LIST_OPERATIONS__

#include "shell.h"

/**
 * add_node_to_linked_list - Adds a new node to the beginning of a linked list.
 * @head: A pointer to the pointer to the head of the linked list.
 * @str: The string to be stored in the new node.
 * @num: The integer value to be stored in the new node.
 *
 * This function adds a new node to the beginning of a linked list.
 * It allocates memory for the new node, initializes its members,
 * and assigns the provided string and integer values to the new node.
 * If the string parameter is NULL, it does not assign a string value
 * to the node.
 * It then updates the head pointer to point to the new node.
 *
 * Return: On success, returns a pointer to the newly created node.
 */
list_t *add_node_to_linked_list(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	custom_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = string_dupy(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * add_node_to_end_of_linked_list - Adds a new node at the end of a linked list.
 * @head: Pointer to the pointer to the head of the list.
 * @str: String to be stored in the new node.
 * @num: Integer value to be stored in the new node.
 *
 * This function creates a new node with the provided string
 * and integer values and appends it at the end of the linked
 * list pointed to by head. If head is NULL, the function returns NULL.
 * Memory allocation for the new node is handled dynamically using malloc.
 * If memory allocation fails, the function returns NULL.
 * If str is not NULL, a duplicate of str is stored in the
 * new node using string_dupy function.
 * If string_dupy fails, the function frees the
 * allocated memory for the new node and returns NULL.
 * If the list is not empty (node != NULL),
 * the function traverses the list to find the last node
 * and then appends the new node to it.
 * If the list is empty (node == NULL), the new node becomes the head.
 *
 * Return: On success, returns a pointer to the newly added node.
 * If head is NULL or memory allocation fails, returns NULL.
 */
list_t *add_node_to_end_of_linked_list(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	custom_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = string_dupy(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * delete_node_at_index - Deletes a node at a specified index in a linked list.
 * @head: A pointer to a pointer to the head of the linked list.
 * @index: The index of the node to delete.
 *
 * This function deletes the node at the specified index in a linked list.
 * It takes a pointer to the head of the list and the index of the
 * node to delete.
 * If the index is 0, it deletes the head node.
 *
 * Return: 1 if the deletion is successful, 0 otherwise.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current_node, *previous_node;
	unsigned int current_index = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}

	current_node = *head;
	while (current_node)
	{
		if (current_index == index)
		{
			previous_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		current_index++;
		previous_node = current_node;
		current_node = current_node->next;
	}
	return (0);
}

/**
 * find_node_with_prefix_and_char -  Finds a node in a linked list whose string
 * starts with a given prefix followed by a specific character.
 *
 * This function traverses a linked list of strings and checks
 * if any of the strings in the nodes start with a specified prefix
 * followed by a specific character. If such a string is found,
 * the corresponding head containing that string is returned.
 *
 * @head: Pointer to the head of the linked list.
 * @prefix: The prefix to search for at the beginning of the strings.
 * @c: The character that should follow the prefix in the matched strings.
 *
 * Return: pointer to the matching head, or NULL if not found.
 */
list_t *find_node_with_prefix_and_char(list_t *head, char *prefix, char c)
{
	char *substring_start = NULL;

	while (head)
	{
		substring_start = string_starts_with(head->str, prefix);
		if (substring_start && ((c == -1) || (*substring_start == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * find_node_index - retrieves the index of a given node within a linked list.
 *
 * This function takes a pointer to the head of a linked list and
 * a pointer to a node within that list.
 * It traverses the list until it finds the specified node and returns
 * its index (position) within the list.
 *
 * @head: Pointer to the head of the linked list.
 * @node: Pointer to the node whose index is to be retrieved.
 *
 * Return: On success, returns the index of the node within the list.
 * If the node is not found within the list, it returns -1
 * to indicate failure.
 */
ssize_t find_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

#endif /* __LINEKD_LIST_OPERATIONS__ */
