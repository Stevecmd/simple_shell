#ifndef __COMMAND_EXECUTOR__
#define __COMMAND_EXECUTOR__

#include "shell.h"

/**
 * run_shell - Executes commands provided by the user.
 * It handles both built-in commands and external commands.
 * The function continuously prompts the user for input,
 * parses it, and executes the corresponding command.
 *
 * This function runs a loop until either an error occurs
 * in reading input or the user exits the shell.
 * Within each iteration, it clears the info structure,
 * prompts the user if in interactive mode, reads input,
 * sets up the info structure, identifies built-in commands or external commands,
 * and executes them accordingly. After each iteration, it frees the
 * allocated memory. It also handles the writing
 * of command history and exits the shell appropriately
 * based on the execution status.
 *
 * @info: Pointer to the info_t structure containing
 * command-related information.
 * @command_line_arguments: Array of strings representing command-line arguments.
 *
 * Return: The exit status of the last executed command or built-in function.
 */
int run_shell(info_t *info, char **command_line_arguments)
{
	ssize_t read_status = 0;
	int built_in_return_status = 0;

	while (read_status != -1 && built_in_return_status != -2)
	{
		reset_info_structure(info);
		if (is_interactive_mode(info))
			_puts("$ ");
		write_char_to_error_buffer(BUFFER_FLUSH);
		read_status = get_input(info);
		if (read_status != -1)
		{
			set_info(info, command_line_arguments);
			built_in_return_status = find_builtin_command(info);
			if (built_in_return_status == -1)
				find_cmd(info);
		}
		else if (is_interactive_mode(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive_mode(info) && info->cmd_status)
		exit(info->cmd_status);
	if (built_in_return_status == -2)
	{
		if (info->err_num == -1)
			exit(info->cmd_status);
		exit(info->err_num);
	}
	return (built_in_return_status);
}

#endif /* __COMMAND_EXECUTOR__ */
