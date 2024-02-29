#ifndef __EXECUTE_COMMANDS__
#define __EXECUTE_COMMANDS__

#include "shell.h"

/**
 * find_builtin_command - Finds if a command is a built-in and returns
 * its corresponding function. Checks if the given command matches
 * any built-in command from the built-in table.
 *
 * @command_info: Pointer to the structure containing information about
 * the command and its arguments.
 *
 * Return: The function pointer to the corresponding built-in
 * function if the command is built-in, otherwise returns -1
 * indicating the command is not built-in.
 */
int find_builtin_command(info_t *command_info)
{
	int index, builtin_return = -1;
	built_in_table builtin_table[] = {
		{"exit", exit_program},
		{"env", print_environment_variables},
		{"help", display_program_help},
		{"history", print_command_history},
		{"unsetenv", unset_environment_variables},
		{"cd", change_directory},
		{"alias", handle_alias_command},
		{NULL, NULL}
	};

	for (index = 0; builtin_table[index].type; index++)
		if (compare_strings(command_info->argv[0], builtin_table[index].type) == 0)
		{
			command_info->line_count++;
			builtin_return = builtin_table[index].func(command_info);
			break;
		}
	return (builtin_return);
}

/**
 * adjust_buffer_position_for_chain - checks the chain of commands and updates buffer position.
 *
 * @command_info: pointer to structure holding command information.
 * @buffer: pointer to buffer to be updated.
 * @current_position: pointer to current position in buffer.
 * @index: index for the current buffer position.
 * @buffer_length: length of the buffer.
 * This function checks the chain of commands based on the buffer format
 * specified in the command information structure.
 * If the buffer format is CMD_AND and the command status is true,
 * it terminates the buffer at the current index.
 * If the buffer format is CMD_OR and the command status is false,
 * it terminates the buffer at the current index.
 * It updates the buffer position accordingly.
 *
 * Return: No return.
 */
void check_chain(info_t *command_info, char *buffer, size_t *current_position, size_t index, size_t buffer_length)
{
	size_t updated_position = *current_position;

	if (command_info->buf_format == CMD_AND)
	{
		if (command_info->cmd_status)
		{
			buffer[index] = '\0';
			updated_position = buffer_length;
		}
	}

	if (command_info->buf_format == CMD_OR)
	{
		if (!command_info->cmd_status)
		{
			buffer[index] = '\0';
			updated_position = buffer_length;
		}
	}
	*current_position = updated_position;
}

/**
 * print_environment_variables- prints the environment variables
 * stored in the provided info structure.
 * This function takes a pointer to a structure info which contains
 * information about the environment variables.
 * It calls the print_linked_list_strings function to print out the
 * list of environment variables stored in the env member of the
 * info structure.
 *
 * @environment_info:  A pointer to the structure containing environment
 * variable information.
 *
 * Return: Always returns 0 indicating success.
 */
int print_environment_variables(info_t *environment_info)
{
	print_linked_list_strings(environment_info->env);
	return (0);
}

/**
 * unset_environment_variables - Unsets environment variables specified
 * in the provided arguments.
 * @info: A pointer to a structure containing information about
 * the environment variables.
 * This function unsets environment variables based on the arguments provided.
 * If the number of arguments is insufficient,
 * it displays an error message and returns 1.
 * Otherwise, it iterates through the arguments,
 * calling remove_environment_variable for each one.
 *
 *  Return: 0 on success, 1 if there are too few arguments.
 */
int unset_environment_variables(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		print_error_message("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		remove_environment_variable(info, info->argv[i]);

	return (0);
}

#endif /* __EXECUTE_COMMANDS__ */
