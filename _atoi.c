#include "shell.h"
#include <stdio.h>
#include <unistd.h>

typedef enum { 
    SUCCESS, 
    PARAM_ERROR, 
    INPUT_ERROR, 
    STRING_ERROR, 
    RUNTIME_ERROR
} ErrorCode;

const char* errorMessages[] = { 
    "No error", 
    "Parameter error", 
    "Invalid input error", 
    "Invalid string error", 
    "Runtime error"
};

void handleError(
    ErrorCode code,
    const char* func
) {
    printf("Error in %s: %s\n", func, errorMessages[code]);
    exit(code);
}

/**
 * interactive - check if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t* info)
{
    if (!info) {
        handleError(PARAM_ERROR, "interactive");
        return 0;
    }

    if (isatty(STDIN_FILENO) && info->readfd <= 2)
        return 1;
    else
        return 0;
}

/**
 * isDelim - checks if character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 * Return: 1 if alphabetic, 0 if not
 */
int isDelim(char c, char *delim)
{
    // Validate parameters
    if (!delim) {
        handleError(PARAM_ERROR, "isDelim");
        return 0;
    }

    while (*delim) {
        if (*delim++ == c)
            return 1;
    }
    return 0;
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    else
        return 0;
}

/**
 * _atoi - converts string to integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *str)
{
    if (!str) {
        handleError(PARAM_ERROR, "_atoi");
        return 0;
    }

    int i, sign = 1, flag = 0;
    unsigned int result = 0;

    for (i = 0; str[i] != '\0' && flag != 2; i++) {
        if (str[i] == '-')
            sign *= -1;

        if (str[i] >= '0' && str[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (str[i] - '0');
        } else if (flag == 1)
            flag = 2;
    }

    int output = result;
    if (sign == -1)
        output = -output;

    return output;
}