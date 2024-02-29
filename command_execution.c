#ifndef _COMMAND_EXECUTION_
#define _COMMAND_EXECUTION_

#include "shell.h"

/**
 * check_if_path_corresponds_to_known_command - checks if a given path corresponds to a known command.
 *
 * This function checks whether the provided path corresponds to a
 * known command in the system.
 * It utilizes the stat() function to obtain
 * information about the file specified by the path.
 * If the path is NULL or if stat() fails to retrieve
 * information about the file, it returns 0 indicating that the
 * command is not known.
 * If the file exists and is a regular file (i.e., st_mode & S_IFREG),
 * it returns 1,
 * indicating that the command is known. Otherwise, it returns 0.
 *
 * @command_info: A pointer to a structure containing additional information
 * (not used in this function).
 * @command_path: A string representing the path to the command to be checked.
 *
 * Return: 1 if the command is known, 0 otherwise.
 */
int check_if_path_corresponds_to_known_command(info_t *command_info, char *command_path)
{
	struct stat file_stat;

	(void)command_info;
	if (!command_path || stat(command_path, &file_stat))
		return (0);

	if (S_ISREG(file_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - Finds the full path of a command executable
 * in the given 'pathstr'.
 * @info: Pointer to information struct containing additional data.
 * @pathstr: String containing a list of directories separated by ':'.
 * @cmd: Command to find in the directories specified by 'pathstr'.
 *
 * This function searches for the executable file corresponding to
 * the given command within the directories listed in 'pathstr'.
 * It first checks if 'cmd' is a known command in the current environment. 
 * If 'cmd' starts with "./",
 * it checks if it's a known command directly.
 * Otherwise, it iterates through each directory in 'pathstr'
 * to construct the full path of the command and checks if
 * it's a known command.
 *
 * Return: If the command is found, returns a pointer to
 * the full path of the command.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_strlen(cmd) > 2) && string_starts_with(cmd, "./"))
	{
		if (check_if_path_corresponds_to_known_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = extract_chars(pathstr, curr_pos, i);
			if (!*path)
				string_strcat(path, cmd);
			else
			{
				string_strcat(path, "/");
				string_strcat(path, cmd);
			}
			if (check_if_path_corresponds_to_known_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * find_cmd - Finds and executes the specified command.
 * @info: Pointer to the structure containing command information.
 *
 * This function searches for the specified command in the system's
 * PATH environment variable and executes it if found.
 * It also handles cases where the command is not found.
 * If linecount_flag is set, it increments the line count.
 * It counts the number of arguments excluding delimiters.
 *
 * Return: None.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;

	if (!k)
		return;

	path = find_path(info, retrieve_environment_variable_value(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((is_interactive_mode(info) || retrieve_environment_variable_value(info, "PATH=") ||
		     info->argv[0][0] == '/') && check_if_path_corresponds_to_known_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->cmd_status = 127;
			print_error_info(info, "not found\n");
		}
	}
}

/**
 * handle_sigint -  Signal handler function for SIGINT (Ctrl+C).
 *
 * This function handles the SIGINT signal, which is generated when
 * the user presses Ctrl+C. It prints a newline character followed
 * by the prompt symbol "$ " to indicate the program is ready for
 * a new command. Additionally, it flushes the output buffer
 * to ensure prompt visibility.
 *
 * @signal_number: Unused parameter representing the signal number (SIGINT).
 *
 * Return: void.
 */
void handle_sigint(__attribute__((unused))int signal_number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

/**
 * read_input_buffer - Reads input from the standard input stream and processes it.
 * @info: A pointer to the info_t structure containing various information.
 * @buffer: A pointer to a pointer to the input buffer.
 * @length: A pointer to the size of the input buffer.
 *
 * Return: Upon success, returns the number of characters read,
 * excluding the trailing newline character. If an error occurs,
 * returns -1.
 */
ssize_t read_input_buffer(info_t *info, char **buffer, size_t *length)
{
	ssize_t read_bytes = 0;
	size_t new_length = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);
		#if USE_GETLINE
		read_bytes = getline(buffer, &new_length, stdin);
		#else
		read_bytes = read_line_from_file_descriptor(info, buffer, &new_length);
		#endif
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments_from_string_buffer(*buffer);
			build_history_list(info, *buffer, info->history_count++);
			{
				*length = read_bytes ;
				info->command_buf = buffer;
			}
		}
	}
	return (read_bytes);
}

#endif /* _COMMAND_EXECUTION_ */
