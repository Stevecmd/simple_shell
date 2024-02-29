#ifndef __LINKED_LIST_PRINTING__
#define __LINKED_LIST_PRINTING__

#include "shell.h"

/**
 * elements_printed - Prints the elements of a linked list.
 * @head: A pointer to the head of the linked list.
 *
 * This function iterates through a linked list, printing each element
 * along with its corresponding numerical value. Each element is printed
 * in the format "<number>: <string>\n".
 * If a string is NULL, it prints "(nil)"instead.
 * The function utilizes another function _puts to print strings and
 * _putchar to print individual characters.
 *
 * Return: The number of elements printed.
 */

size_t elements_printed(const list_t *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(convert_number_to_string(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		index++;
	}
	return (index);
}

/**
 * print_linked_list_strings - Prints the strings stored in a linked list.
 * @head: A pointer to the head of the linked list.
 *
 * This function traverses the provided linked list
 * and prints the strings stored in each node.
 * If a node's string is NULL, it prints "(nil)" instead.
 * After printing each string, a newline character is appended.
 *
 * Return: The number of nodes in the linked list.
 */
size_t print_linked_list_strings(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

#endif /* __LINKED_LIST_PRINTING__ */
