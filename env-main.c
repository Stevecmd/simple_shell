#ifndef _ENV_MAIN_
#define _ENV_MAIN_

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

#endif /* _ENV_MAIN_ */