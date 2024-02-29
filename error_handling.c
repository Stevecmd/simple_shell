#ifndef __ERROR_HANDLING__
#define __ERROR_HANDLING__

#include "shell.h"

/**
 * remove_comments_from_string_buffer - Removes comments from a string buffer.
 * This function takes a string buffer as input and removes any
 * comments starting with '#' character, considering '#' is at the
 * beginning of the line or preceded by a space character.
 *
 * @buffer: Pointer to the string buffer.
 *
 * Return: Always 0 - Success;
 */
void remove_comments_from_string_buffer(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

/**
 * convert_string_to_integer_with_error_handling - Converts a string to
 * an integer with error handling
 * @input_string: The string to convert
 * This function takes a string @input_string and attempts to
 * convert it to an integer.
 * It iterates through each character in the string, multiplying the result
 * by 10 and adding the numerical value of the character. It handles both
 * positive and negative numbers. If the result exceeds the maximum value
 * for an integer, it returns -1 to indicate an error.
 *
 * Return: The converted integer if successful, or -1 if an error occurs.
 */
int convert_string_to_integer_with_error_handling(char *input_string)
{
	int index = 0;
	unsigned long int result = 0;

	if (*input_string == '+')
		input_string++;
	for (index = 0;  input_string[index] != '\0'; index++)
	{
		if (input_string[index] >= '0' && input_string[index] <= '9')
		{
			result *= 10;
			result += (input_string[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * error_putfd - writes characters to a file descriptor
 * with buffering support.
 *
 * This function writes characters to the specified file descriptor
 * with buffering support. It buffers characters in a static buffer
 * until either a buffer flush character (BUF_FLUSH) is encountered
 * or the buffer is full. Upon encountering a buffer flush character
 * or when the buffer is full, the buffered characters are written
 * to the file descriptor.
 *
 * @character: The character to be written to the file descriptor.
 * @fd: The file descriptor to which the characters are to be written.
 *
 * Return: On success, returns 1. If the buffer is flushed.
 */
int error_putfd(char character, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH  || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (character != BUFFER_FLUSH)
		buf[i++] = character;
	return (1);
}

/**
 *error_putsfd - Prints a string to a file descriptor with error handling.
 * @str: The string to be printed.
 * @fd: The file descriptor to which the string will be printed.
 *
 * Return: The total number of characters successfully
 * printed, or 0 if @str is NULL.
 */
int error_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += error_putfd(*str++, fd);
	}
	return (i);
}

/**
 * convert_number_to_string - Converts a long integer to a
 * string representation
 * in the specified base with optional formatting flags.
 * @number: The long integer to be converted.
 * @radix: The base to which @number should be converted
 * (e.g., 2 for binary, 10 for decimal, 16 for hexadecimal).
 * @conversion_flags: Optional formatting flags to control
 * the conversion process.
 *
 * This function takes a long integer and converts it into a string
 * representation according to the specified radix.
 * It supports bases from 2 to 16 inclusive. The function can
 * handle both signed and unsigned numbers.
 * Flags can be used to customize the conversion, such as choosing
 * lowercase or uppercase hexadecimal characters.
 * he result is stored in a static buffer and a pointer to the
 * resulting string is returned.
 * The buffer is statically allocated, so subsequent calls to this
 * function will overwrite the buffer.
 * If the number is negative and the CONVERSION_UNSIGNED flag is not set,
 * a sign character '-' is included in the output.
 *
 * Return: A pointer to the string representation of the converted number.
 */
char *convert_number_to_string(
		long int number,
		int radix,
		int conversion_flags)
{
	static char *digit_set;
	static char conversion_buffer[50];
	char is_negative = 0;
	char *result_ptr;
	unsigned long absolute_number = number;

	if (!(conversion_flags & CONVERSION_UNSIGNED) && number < 0)
	{
		absolute_number = -number;
		is_negative = '-';

	}
	digit_set = conversion_flags & CONVERT_LOWERCASE
		? "0123456789abcdef"
		: "0123456789ABCDEF";
	result_ptr = &conversion_buffer[49];
	*result_ptr = '\0';

	do	{
		*--result_ptr = digit_set[absolute_number % radix];
		absolute_number /= radix;
	} while (absolute_number != 0);

	if (is_negative)
		*--result_ptr = is_negative;
	return (result_ptr);
}

#endif /* __ERROR_HANDLING__ */
