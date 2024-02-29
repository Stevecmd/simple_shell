#ifndef __EXECUTE_PROCESSES__
#define __EXECUTE_PROCESSES__

#include "shell.h"

/**
 * read_from_file_descriptor - reads data from a file descriptor into a buffer
 * @file_info: a pointer to a structure containing information about the
 * file descriptor
 * @buffer: the buffer to store the read data
 * @bytes_read: a pointer to the size of data read
 *
 * This function reads data from the file descriptor specified in info
 * into the buffer buf. The amount of data read is stored in the variable
 * pointed to by i. If i is not zero, indicating that data has already
 * been read,
 * the function returns 0 without performing any read operation. Otherwise,
 * it attempts to read up to READ_BUF_SIZE bytes of data into buf from the
 * file descriptor. The actual number of bytes read is returned, and if
 * successful, the value is stored in i for future reference.
 *
 * Return: On success, the number of bytes read is returned.
 * On failure, -1 is returned and errno is set appropriately.
 */
ssize_t read_from_file_descriptor(
		info_t *file_info, char *buffer, size_t *bytes_read)
{
	ssize_t bytes_read_now = 0;

	if (*bytes_read)
		return (0);

	bytes_read_now = read(file_info->readfd, buffer, READ_BUF_SIZE);

	if (bytes_read_now >= 0)
		*bytes_read = bytes_read_now;

	return (bytes_read_now);
}

/**
 * fork_command - Forks a child process to execute a command.
 * @info: A pointer to the info_t structure containing command information.
 *
 * This function forks a child process to execute a command specified
 * in the info_t structure. If the fork fails, an error message is
 * printed, and the function returns. If the fork succeeds, the child
 * process executes the command using execve().
 * If execve() fails, the info_t structure is freed, and the
 * appropriate error code is returned.
 * The parent process waits for the child process to complete
 * execution and checks its exit status.
 * If the child process exits normally, the exit status is retrieved
 * and updated in the info_t structure.
 * If the exit status indicates a permission denied error (126),
 * an error message is printed.
 *
 * Return: None
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failed:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->cmd_status));
		if (WIFEXITED(info->cmd_status))
		{
			info->cmd_status = WEXITSTATUS(info->cmd_status);
			if (info->cmd_status == 126)
				print_error_info(info, "Permission denied\n");
		}
	}
}

/**
 * free_info - Frees memory allocated for info_t structure and its components.
 * @info: Pointer to the info_t structure to be deallocated.
 * @all: Flag indicating whether to deallocate all components.
 *
 * This function frees memory allocated for the info_t structure
 * and its components, such as argument vectors, environment variables,
 * history, and aliases.
 * If 'all' is set to true, it deallocates all components, including
 * command buffer and file descriptors. Otherwise,
 * it only deallocates argv and path.
*
 * Return: None.
 */
void free_info(info_t *info, int all)
{
	deallocate(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (info->command_buf == NULL)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		deallocate(info->environ);
			info->environ = NULL;
		deallocate_memory_block((void **) info->command_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(BUFFER_FLUSH);
	}
}

/**
 * populate_env_list - populates a linked list with environment variables.
 *
 * This function takes a pointer to an info_t structure as input and populates
 * the linked list pointed to by the 'env' member of the structure with the
 * environment variables of the current process. It iterates through the array
 * of environment variables until it encounters a NULL terminator, adding each
 * variable to the end of the linked list using the
 * add_node_to_end_of_linked_list
 * function.
 * @info: A pointer to an info_t structure where the environment variables
 * will be stored.
 *
 * Return: Always 0 indicating success.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_to_end_of_linked_list(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * get_environ - Retrieves the environment variables of the current process.
 * If the environment variables have not been previously retrieved
 * or if they have been modified, this function updates them.
 *
 * @info: A pointer to the structure containing information
 * about the environment.
 *
 * This function checks if the environment variables have been previously
 * retrieved or if they have been modified. If they haven't been retrieved
 * or if they have been changed, it converts the environment variables from
 * a linked list format to an array of strings format. It then returns
 * the array of environment variables.
 *
 * Return: A pointer to the array of environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->environ_changed)
	{
		info->environ = list_to_strings(info->env);
		info->environ_changed = 0;
	}

	return (info->environ);
}
#endif /* __EXECUTE_PROCESSES__ */
