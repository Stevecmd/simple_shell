#ifndef __INPUT_PROCESSING__
#define __INPUT_PROCESSING__

#include "shell.h"

/**
 * set_info -  sets information in the info_t structure.
 * @info: pointer to the info_t structure to be filled.
 * @command_line_arguments: pointer to an array of strings representing
 * command-line arguments.
 *
 * This function populates the fields of the info_t structure
 * with relevant information extracted from the command-line arguments.
 * It assigns the file name of the executable to info->executable_name .
 * If additional arguments are present (info->arg),
 * it parses them into separate tokens,
 * storing them in info->argv, and calculates the number of arguments
 * in info->argc. It also handles cases where the tokenization
 * fails or no arguments are present.
 * Lastly, it invokes functions to replace aliases
 * and variables within the arguments.
 *
 */
void set_info(info_t *info, char **command_line_arguments)
{
	int argument_count = 0;

	info->file_name = command_line_arguments[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_dupy(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (argument_count = 0; info->argv && info->argv[argument_count ]; argument_count ++)
			;
		info->argc = argument_count;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * get_input - reads input into a buffer and processes it
 *
 * @info: pointer to the info_t structure containing input information
 *
 * This function reads input into a buffer, processes it, and updates
 * the info_t structure accordingly. It handles dynamic resizing of
 * the buffer to accommodate input of varying lengths. It also checks
 * for specific patterns and formats within the input data.
 *
 * Return: On success, returns the length of the input string processed.
 */
ssize_t get_input(info_t *info)
{
	static char *input_buffer;
	static size_t buffer_index, processing_index, len;
	ssize_t read_bytes = 0;
	char **arg_ptr = &(info->arg), *processing_ptr;

	_putchar(BUFFER_FLUSH);
	read_bytes = read_input_buffer(info, &input_buffer, &len);
	if (read_bytes == -1)
		return (-1);
	if (len)
	{
		processing_index = buffer_index;
		processing_ptr = input_buffer + buffer_index;

		check_chain(info, input_buffer, &processing_index, buffer_index, len);
		while (processing_index < len)
		{
			if (is_chain(info, input_buffer, &processing_index))
				break;
			processing_index++;
		}

		buffer_index = processing_index + 1;
		if (buffer_index >= len)
		{
			buffer_index = len = 0;
			info->buf_format = CMD_NORM;
		}

		*arg_ptr = processing_ptr;
		return (string_strlen(processing_ptr));
	}

	*arg_ptr = input_buffer;
	return (read_bytes);
}
#endif /* __INPUT_PROCESSING__ */
