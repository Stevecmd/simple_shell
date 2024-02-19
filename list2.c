#include "shell.h"

/**
 * add_node_end - Adds a new node with given string and index to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: String to be stored in the new node.
 * @num: Index value to be assigned to the new node.
 *
 * Return: 1 on success, 0 on failure
 */
int add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return FAILURE;

    node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return FAILURE;
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return FAILURE;
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return SUCCESS;
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 *                  Each string is printed followed by a newline.
 *
 * @h: Pointer to the first node of the linked list.
 *
 * Return: The number of nodes printed.
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return i;
}

/**
 * delete_node_at_index - Deletes the node at the specified index in the linked list.
 * @head: Address of the pointer to the first node in the linked list.
 * @index: Index of the node to delete.
 * 
 * This function removes the node at the specified index in the linked list pointed to by head.
 * If the index is valid and the deletion is successful, the function returns 1.
 * If the index is invalid or the deletion fails, the function returns 0.
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return FAILURE;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return SUCCESS;
    }
    node = *head;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return SUCCESS;
        }
        i++;
        prev_node = node;
        node = node->next;
    }
    return FAILURE;
}

/**
 * free_list - Frees memory allocated for all nodes in a linked list.
 * @head_ptr: Address of pointer to the head node of the list.
 *
 * This function iterates through the linked list starting from the head node,
 * freeing memory allocated for each node and its associated string. It also
 * updates the head pointer to NULL after freeing all nodes.
 *
 * Return: void
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

/**
 * list_to_strings - Converts a linked list of strings into an array of strings.
 *                   Allocates memory for the array and copies each string from
 *                   the linked list into the array.
 * @head: Pointer to the first node of the linked list.
 *
 * Return: Pointer to the array of strings if successful, NULL otherwise.
 */
char **list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t len = list_len(head);
    size_t i;
    char **strs;
    char *str;

    if (!head || !len)
        return NULL;
    
    strs = malloc(sizeof(char *) * (len + 1));
    if (!strs)
        return NULL;
    
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return NULL;
        }
        
        str = _strcpy(str, node->str);
        strs[i] = str;
    }
    strs[i] = NULL;
    return strs;
}