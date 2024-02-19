#include "shell.h"

#define SUCCESS 1
#define FAILURE 0

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: String to be stored in the new node.
 * @num: Index or numeric value associated with the new node.
 *
 * Return: 1 on success, 0 on failure
 */
int add_node(list_t **head, const char *str, int num)
{
    list_t *new_head;

    if (!head)
        return FAILURE;
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return FAILURE;
    _memset((void *)new_head, 0, sizeof(list_t));
    new_head->num = num;
    if (str)
    {
        new_head->str = _strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return FAILURE;
        }
    }
    new_head->next = *head;
    *head = new_head;
    return SUCCESS;
}



/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node of the list.
 *
 * Return: The size of the list.
 */
size_t list_len(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return i;
}

/**
 * print_list - Prints all elements of a list_t linked list.
 *
 * @h: Pointer to the first node of the linked list.
 *
 * Return: The number of nodes printed.
 */
size_t print_list(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return i;
}

/**
 * node_starts_with - Finds a node whose string starts with a specified prefix.
 * @node: Pointer to the head of the linked list.
 * @prefix: The prefix to match.
 * @c: The next character after the prefix to match.
 *
 * This function iterates through the linked list starting from the given node
 * and searches for a node whose string starts with the specified prefix. If
 * the next character after the prefix matches the provided character, the node
 * is considered a match.
 *
 * Return: A pointer to the matching node if found, otherwise returns NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the head of the linked list.
 * @node: Pointer to the node whose index is to be found.
 *
 * This function traverses the linked list starting from the head node
 * and searches for the specified node. If the node is found, its index
 * (position) in the linked list is returned. If the node is not found,
 * the function returns FAILURE.
 *
 * Return: Index of the node if found, FAILURE if the node is not found.
 */
size_t get_node_index(list_t *head, list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return i;
        head = head->next;
        i++;
    }
    return FAILURE;
}