#ifndef __SHELL_HISTORY__
#define __SHELL_HISTORY__

#include "shell.h"

/**
 * get_history_file - Retrieves the path to the history file.
 * @info: Pointer to the info_t structure containing environment
 * information.
 *
 * This function constructs the path to the history
 * file using the HOME environment variable.
 * It concatenates the HOME directory path with
 * the predefined history file name.
 * The resulting path is returned as a string.
 *
 * Return: A pointer to a dynamically allocated string
 * representing the path to the history file.
 * NULL is returned if the HOME environment variable
 * is not set or if memory allocation fails.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = retrieve_environment_variable_value(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (
		string_strlen(dir) +
		string_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	string_cpy(buf, dir);
	string_strcat(buf, "/");
	string_strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * write_history - Writes the history information to a file.
 * Saves history entries to a specified file.
 * Opens or creates the file, truncates it,
 * and writes each history entry followed by
 * a newline character. Finally, closes the file.
 *
 * @info: Pointer to the structure containing history info.
 *
 * Return: Upon successful completion, it returns 1 to indicate success.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		error_putsfd(node->str, fd);
		error_putfd('\n', fd);
	}
	error_putfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads the history from a file and populates
 * the history list in the info structure.
 * This function reads the history from a file specified by
 * the info structure, populating the history list.
 * It opens the file, reads its contents, parses them, and
 * builds a history list accordingly.
 *
 * @info: A pointer to the info_t structure holding
 * information about the history file and list.
 *
 * Return: The number of history entries read and added to
 * the history list.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->history_count = linecount;
	while (info->history_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->history_count);
}

/**
 * build_history_list - Builds a linked list of historical command entries.
 * It adds a new node at the end of the list containing
 * the provided command buffer and line count information.
 *
 * This function builds a linked list to store historical command entries.
 * If the history list exists, the new node is added at the end of the list.
 * If the history list is empty, the new node becomes the first node.
 *
 * @info: Pointer to the structure holding command history information.
 * @buf: Pointer to the buffer containing the command.
 * @linecount: Number of lines in the command.
 *
 * Return: Always returns 0 to indicate success.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_to_end_of_linked_list(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumber the history entries.
 * Updates the numbering of history
 * entries in the given info structure.
 * It traverses through the linked list
 * of history entries, assigning a
 * sequential number to each entry.
 *
 * @info: Pointer to the info structure containing
 * the history entries to be renumbered.
 *
 * Return: Number of history entries after renumbering.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_count = i);
}

#endif /* __SHELL_HISTORY__ */
