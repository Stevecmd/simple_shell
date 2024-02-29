#ifndef __ERROR_REPORTING__
#define __ERROR_REPORTING__

#include "shell.h"

/**
 * write_char_to_error_buffer - Writes a character to a
 * buffer for error output.
 *
 * This function writes a character to a buffer designated for error output.
 * It flushes the buffer if the character is a flush signal or if the buffer
 * is full.
 *
 * @character: The character to print
 *
 * Return: 1 on success, -1 on failure with errno set appropriately.
 */
int write_char_to_error_buffer(char character)
{
	static int buffer_index;
	static char error_buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(2, error_buffer, buffer_index);
		buffer_index = 0;
	}
	if (character != BUFFER_FLUSH)
		error_buffer[buffer_index++] = character;
	return (1);
}

/**
 * print_error_message - Prints a string character by
 * character using print_error_message.
 *
 * This function takes a string pointer as input and prints
 * each character of the string using the write_char_to_error_buffer function.
 * It iterates through the string until it encounters the null
 * terminator ('\0') indicating the end of the string.
 *
 * @str: A pointer to the string to be printed.
 *
 * Return: No return.
 */
void print_error_message(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write_char_to_error_buffer(str[i]);
		i++;
	}
}

/**
 * print_integer_to_fd - Prints an integer to a specified file descriptor.
 *
 * If the file descriptor is STDERR_FILENO, prints to standard error.
 * Handles negative numbers by printing a minus sign '-'.
 * Uses putchar-like function pointers for output.
 * Iterates through the digits of the input integer and prints each one.
 *
 * @num: The integer to be printed.
 * @fd: The file descriptor to which the integer is to be printed.
 *
 * Return: The number of characters printed.
 */
int print_integer_to_fd(int num, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current_digit;

	if (fd == STDERR_FILENO)
		output_char = write_char_to_error_buffer;

	if (num < 0)
	{
		absolute_value = -num;
		output_char('-');
		count++;
	}
	else
	{
		absolute_value = num;
	}

	current_digit = absolute_value;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			output_char('0' + current_digit / i);
			count++;
		}
		current_digit %= i;
	}
	output_char('0' + current_digit);
	count++;

	return (count);
}

/**
 * print_error_info - prints error information to standard error output.
 *
 * It constructs an error message consisting of the file name,
 * line count, program name, and the provided error string,
 * then prints it to standard error output.
 *
 * @error_info: Pointer to a structure containing information about the error.
 * @error_description: Pointer to a string containing the error description.
 *
 * Return: No return value.
 */
void print_error_info(info_t *error_info, char *error_description)
{
	print_error_message(error_info->file_name);
	print_error_message(": ");
	print_integer_to_fd(error_info->line_count, STDERR_FILENO);
	print_error_message(": ");
	print_error_message(error_info->argv[0]);
	print_error_message(": ");
	print_error_message(error_description);
}

#endif /* __ERROR_REPORTING__ */
