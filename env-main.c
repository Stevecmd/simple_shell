#include <stdio.h>

/**
 * print_environment - prints the environment
 *
 * Return: Always 0.
 */
int print_environment(int ac, char **av, char **env)
{
    unsigned int i;

    i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}