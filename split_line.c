#include "shell.h"

/**
 * split_line - Split a string into multiple tokens.
 * @line: The string to be split.
 *
 * Return: A pointer to an array of tokens.
 *         Returns NULL if memory allocation fails or if the input line is empty.
 */
char **split_line(char *line)
{
    int bufsize = 64;            /* Initial size of the tokens array */
    int i = 0;                   /* Index for tokens array */
    char **tokens = malloc(bufsize * sizeof(char *));  /* Allocate memory for tokens array */
    char *token;                 /* Pointer to store each token */

    /* Check if memory allocation for tokens array was successful */
    if (!tokens) {
        fprintf(stderr, "split_line: allocation error for tokens\n");
        exit(EXIT_FAILURE);
    }

    /* Tokenize the input line using strtok */
    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        /* Check if token is a comment (starts with '#'), and ignore it */
        if (token[0] == '#') {
            break;
        }

        /* Store token in tokens array */
        tokens[i] = token;
        i++;

        /* Check if tokens array needs to be resized */
        if (i >= bufsize) {
            bufsize += bufsize;   /* Double the buffer size */
            tokens = realloc(tokens, bufsize * sizeof(char *));  /* Resize tokens array */
            /* Check if memory reallocation was successful */
            if (!tokens) {
                fprintf(stderr, "split_line: reallocation error for tokens\n");
                exit(EXIT_FAILURE);
            }
        }

        /* Get next token */
        token = strtok(NULL, TOK_DELIM);
    }

    tokens[i] = NULL;  /* Null-terminate the tokens array */
    return tokens;     /* Return the tokens array */
}
