#ifndef _BUILTIN_COMMANDS_
#define _BUILTIN_COMMANDS_

#include "shell.h"

/**
 * change_directory - Change directory function
 * This function changes the current
 * working directory of the process.
 * If no argument is provided, it changes to the HOME directory.
 * @info: Pointer to info_t structure containing command information
 *
 *  Return: 0 on success, otherwise -1
 *	Auth: Steve Murimi
 */
int change_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = retrieve_environment_variable_value(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = retrieve_environment_variable_value(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compare_strings(info->argv[1], "-") == 0)
	{
		if (!retrieve_environment_variable_value(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(retrieve_environment_variable_value(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = retrieve_environment_variable_value(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error_info(info, "can't cd to ");
		print_error_message(info->argv[1]), write_char_to_error_buffer('\n');
	}
	else
	{
		print_error_info(info, "can't cd to ");
	}
	return (0);
}

/**
 * print_command_history - Prints the history of commands executed
 * @info: A pointer to the info_t struct containing history information.
 *
 * This function prints the history of commands executed by accessing
 * the linked list of command history stored in the info_t struct.
 * It calls the print_list function to iterate through and print each
 * command in the history list.
 *  Return: always returns 0
 */
int print_command_history(info_t *info)
{
	elements_printed(info->history);
	return (0);
}

/**
 * exit_program - Handles exiting the program with a specified exit status.
 *
 * This function takes an 'info' structure pointer as its argument,
 * which contains information about the current process,
 * including command-line arguments.
 * @info: Pointer to an 'info' structure containing process information.
 *
 * Return: -2 indicating that the program should exit with a specific status,
 */
int exit_program(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = convert_string_to_integer_with_error_handling(info->argv[1]);
		if (exitcheck == -1)
		{
			info->cmd_status = 2;
			print_error_info(info, "Illegal number: ");
			print_error_message(info->argv[1]);
			write_char_to_error_buffer('\n');
			return (1);
		}
		info->err_num = convert_string_to_integer_with_error_handling(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * strncat_exit - Concatenates at most n characters from the string src to the
 *  end of the string dest, and null-terminates the result.
 * @dest: Pointer to the destination string where the concatenation will occur.
 * @src: Pointer to the source string containing characters to be concatenated.
 * @n: Maximum number of characters to be concatenated from src.
 *
 * This function concatenates at most n characters from the string src to the
 * end of the string dest. It iterates through the destination string to find
 * its null terminator, then starts appending characters from the source string
 * until either it reaches the null terminator of src or n characters have been
 * appended, whichever comes first. If the total number of characters appended
 * is less than n, the resulting string is null-terminated. The original
 * destination string pointer is returned.
 * Return: Pointer to the resulting destination string after concatenation.
 */
char *strncat_exit(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}

	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
	{
		dest[i] = '\0';
	}

	return (s);
}

#endif /* _BUILTIN_COMMANDS_ */
