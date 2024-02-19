#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point of simple shell
 *
 * This function prompts the user with a "#cisfun$" symbol, reads input from stdin using getline,
 * and echoes the input back to stdout along with the prompt symbol until the user ends input.
 * Memory allocated for each input line is freed after processing.
 *
 * Return: Always 0 to indicate successful completion.
 */

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("#cisfun$ ");

    while ((read = getline(&line, &len, stdin)) != -1) {
        printf("%s", line);
        printf("#cisfun$ ");

        free(line);
        line = NULL;
        len = 0;
    }

    if (line != NULL) {
        free(line);
    }

    return 0;
}