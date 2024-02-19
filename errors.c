#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: Prints a null-terminated string to stderr
 *
 * This function prints the given null-terminated string to stderr.
 * It iterates through the string characters until it reaches the null terminator.
 * 
 * Return: Nothing, it prints the string directly to stderr.
 */
void _eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * _eputchar - Writes a character to stderr.
 * 
 * This function writes the given character to the
 * standard error stream (stderr). It uses a static
 * buffer to batch writes for efficiency.
 * 
 * @c: The character to write
 *
 * Return: 1 on success, -1 on error with errno set.
 */
int _eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}



/**
 * _erratoi - Converts a string to an integer
 * 
 * This function takes a string and attempts to convert it to an integer.
 * It iterates through the string, converting characters between '0' and '9'
 * to their integer values. If non-digit characters are encountered,
 * it returns an error.
 * 
 * @s: The string to convert
 * Return: The integer value if successful, 0 if no digits found, or -1 on error.
 */
int _erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0;  s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * print_error - Prints an error message
 * 
 * This function prints an error message including the filename,
 * line number, command name, and error type. It concatenates
 * these details into a string and uses helper functions like
 * _eputs() to output to stderr.
 * 
 * @info: Pointer to info struct containing execution context
 * @estr: Error type string
 * Return: Nothing, prints directly to stderr.
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * remove_comments - Removes comments from a string
 * 
 * This function takes a string as input and removes comments from it by
 * replacing the first '#' character with a string terminator '\0'. This
 * effectively removes comments while preserving the rest of the string.
 * 
 * @buf: Pointer to the input string
 *
 * Return: Always 0 to indicate success;
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}