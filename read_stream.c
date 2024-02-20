#ifndef _READ_STREAM_
#define _READ_STREAM_

#include "shell.h"

/**
 * read_stream - Read a line from the stream.
 *
 * This function reads a line from the standard input stream (stdin).
 * It dynamically allocates memory for the line and adjusts the buffer size
 * as needed. The line is terminated by a null character ('\0') and returned
 * to the caller.
 *
 * Return: A pointer to the string containing the read line.
 */
char *read_stream(void)
{
    int bufsize = 1024;
    int i = 0;
    int character;
    char *line = malloc(sizeof(char) * bufsize);

    /* Check if memory allocation was successful */
    if (line == NULL) {
        fprintf(stderr, "read_stream: Allocation error\n");
        exit(EXIT_FAILURE);
    }

    /* Read characters from stream until newline or end of file */
    while (1) {
        character = getchar();

        /* Check for end of file */
        if (character == EOF) {
            free(line);
            exit(EXIT_SUCCESS);
        }
        /* Check for newline */
        else if (character == '\n') {
            line[i] = '\0';
            return line;
        }
        else {
            /* Store the character in the line buffer */
            line[i] = character;
        }

        i++;

        /* Check if buffer size needs to be increased */
        if (i >= bufsize) {
            bufsize += 1024;
            line = realloc(line, bufsize);
            /* Check if reallocation was successful */
            if (line == NULL) {
                fprintf(stderr, "read_stream: Reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


#endif /* __READ_STREAM__ */