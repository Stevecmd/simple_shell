#ifndef _SHELL_INTERACTIVE_
#define _SHELL_INTERACTIVE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "shell.h"
#include "common.h"

#define MAX_LINE 80 /* Maximum length of command */
#define MAX_ARGS 10 /* Maximum number of arguments */

void shell_interactive(void);

/**
* shell_interactive - Entry point of simple shell interactive shell
*
* This function reads input from stdin using fgets,
* tokenizes the input into arguments,
* and executes the command until the user ends input.
*
* Return: Always 0 to indicate successful completion.
*
* File: shell_interactive.c
* Auth: Steve Murimi
*/

void shell_interactive(void) {
    char line[MAX_LINE];
    char *args[MAX_ARGS + 1]; /* Additional slot for NULL terminator */
    int should_run = 1;

    ssize_t read_result;
    /* Tokenize input line into arguments */
    char *token;
    int argc = 0;

    while (should_run) {
        write(STDOUT_FILENO, "cisfun$ ", 8); /* Prompt symbol */

        /* Read input from user */
        read_result = read(STDIN_FILENO, line, MAX_LINE);
        if (read_result < 0) {
            perror("read");
            break; /* Exit loop if encounters EOF or error */
        }


        argc = 0;
        token = strtok(line, " \t\n");
        while (token && argc < MAX_ARGS) {
            args[argc++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[argc] = NULL; /* Set the last argument to NULL as required by execvp */

        if (argc == 0) {
            continue; /* Skip empty lines */
        }

        /* Handle built-in commands */
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0; /* Exit the shell */
        } else {
            /* Fork a child process to execute the command */
            pid_t pid;

            pid = fork();
            if (pid < 0) {
                perror("fork");
            } else if (pid == 0) {
                /* Child process */
                if (execvp(args[0], args) == -1) {
                    perror("execvp"); /* Print error if execution fails */
                    exit(EXIT_FAILURE);
                }
            } else {
                /* Parent process */
                wait(NULL); /* Wait for the child process to complete */
            }
        }
    }
}

#endif /* _SHELL_INTERACTIVE_ */