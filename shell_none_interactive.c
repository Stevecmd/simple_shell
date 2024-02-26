#ifndef _SHELL_NONE_INTERACTIVE_
#define _SHELL_NONE_INTERACTIVE_

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAX_LINE 1024 /* Maximum length of command */
#define MAX_ARGS 128  /* Maximum number of arguments */

void shell_none_interactive(void);

/**
* shell_none_interactive - Executes the shell in
*							non-interactive mode.
*
* This function represents the behavior
* of the shell when it's not
* in an interactive mode.
* It reads input from a stream, tokenizes the input
* into arguments, executes the command,
* and frees allocated memory for the input
* line and arguments.
*
* Return: This function does not return a value.
*
* File: shell_none_interactive.c
* Auth: Steve Murimi
*/

void shell_none_interactive(void)
{
    char line[MAX_LINE];
    char *args[MAX_ARGS + 1]; /* Additional slot for NULL terminator */
    pid_t pid;

    /* Read input from stdin until EOF */
    ssize_t bytes_read;
    while ((bytes_read = read(STDIN_FILENO, line, sizeof(line))) > 0) {
        /* Tokenize input line into arguments */
        char *token = strtok(line, " \t\n");
        int argc = 0;
        while (token && argc < MAX_ARGS) {
            args[argc++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[argc] = NULL; /* Set the last argument to NULL as required by execvp */

        if (argc == 0) {
            continue; /* Skip empty lines */
        }

        /* Fork a child process to execute the command */
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            if (execvp(args[0], args) == -1) {
                perror("execvp"); /* Print error if execution fails */
                exit(EXIT_FAILURE);
            }
            /* No need to free memory in child process */
        } else {
            /* Parent process */
            wait(NULL); /* Wait for the child process to complete */
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}
#endif /* _SHELL_NONE_INTERACTIVE_ */
