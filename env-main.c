#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
extern char **environ;

int main(void) {
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }
    return 0;
}