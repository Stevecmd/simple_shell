#include "shell.h"

/**
 * _putfd - Writes a character to a file descriptor
 * @c: The character to write
 * @fd: The file descriptor to write to
 *
 * Return: 1 on success, -1 on error with errno set.
 */
int _putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putsfd - Prints a null-terminated string to a file descriptor.
 * 
 * This function prints the given null-terminated string to the provided file
 * descriptor. It iterates through each character of the string, writing them
 * to the file descriptor using _putfd().
 * 
 * @str: The string to print
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int _putsfd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += _putfd(*str++, fd);
    }
    return (i);
}

/**
 * print_d - Prints an integer in decimal format
 * 
 * This function takes an integer and prints its decimal
 * representation to the provided file descriptor.
 * It uses a divide-and-conquer approach to extract each digit from the number.
 * 
 * @input: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;
    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        count++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return (count);
}

/**
 * convert_number -  Converts a number to a string in a given base.
 * 
 * This function takes a number and base and converts it to a string
 * representation. It handles unsigned numbers as well as signed numbers
 * by checking flags.
 * 
 * @num: The number to convert
 * @base: The base to use for conversion
 * @flags: Flags to specify conversion options
 *
 * Return: A string containing the converted number
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';

    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do  {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}