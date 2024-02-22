Initially I set up the main file as the entry to the shell, from here you choose 
whether to use interactive shell or non interactive. 
main.c
```c
#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // For boolean type
#include <unistd.h>

#include "shell.h"

// Function to display the menu and get user's choice
void display_menu(void) {
    write(STDOUT_FILENO, "Choose shell mode:\n", 19);
    write(STDOUT_FILENO, "1. Interactive shell\n", 22);
    write(STDOUT_FILENO, "2. Non-interactive shell\n", 26);
    write(STDOUT_FILENO, "Enter your choice (1 or 2): ", 29);
}

// Function to read user's choice
int read_choice(void) {
    char buffer[2];
    int choice;
    ssize_t bytes_read;
    while ((bytes_read = read(STDIN_FILENO, buffer, 2)) > 0) {
        if (buffer[0] == '1' || buffer[0] == '2') {
            choice = buffer[0] - '0'; // Convert char to int
            return choice;
        } else {
            write(STDOUT_FILENO, "Invalid choice. Please enter 1 or 2.\n", 38);
        }
    }
    return -1; // Error reading choice
}

int main(void)
{
    int choice;
    bool valid_choice = false;

    do {
        display_menu();
        choice = read_choice();
        if (choice != -1) {
            valid_choice = true;
        }
    } while (!valid_choice);

    // Execute the selected shell mode
    if (choice == 1) {
        shell_interactive(); // Execute interactive shell
    } else {
        shell_none_interactive(); // Execute non-interactive shell
    }

    return 0;
}

#endif /* _MAIN_ */

```
shell_interactive.c
```c
#ifndef _SHELL_INTERACTIVE_
#define _SHELL_INTERACTIVE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "shell.h"

#define MAX_LINE 80 // Maximum length of command
#define MAX_ARGS 10 // Maximum number of arguments

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
    char *args[MAX_ARGS + 1]; // Additional slot for NULL terminator
    int should_run = 1;

    while (should_run) {
        printf("cisfun$ "); // Prompt symbol
        fflush(stdout); // Flush stdout to ensure prompt is displayed

        // Read input from user
        if (!fgets(line, sizeof(line), stdin)) {
            break; // Exit loop if fgets encounters EOF or error
        }

        // Tokenize input line into arguments
        char *token = strtok(line, " \t\n");
        int argc = 0;
        while (token && argc < MAX_ARGS) {
            args[argc++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[argc] = NULL; // Set the last argument to NULL as required by execvp

        if (argc == 0) {
            continue; // Skip empty lines
        }

        // Handle built-in commands
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0; // Exit the shell
        } else {
            // Fork a child process to execute the command
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
            } else if (pid == 0) {
                // Child process
                if (execvp(args[0], args) == -1) {
                    perror("execvp"); // Print error if execution fails
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                wait(NULL); // Wait for the child process to complete
            }
        }
    }
}

#endif /* _SHELL_INTERACTIVE_ */


```
shell_none_interactive.c
```c
#ifndef _SHELL_NONE_INTERACTIVE_
#define _SHELL_NONE_INTERACTIVE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024 // Maximum length of command
#define MAX_ARGS 128  // Maximum number of arguments

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
    char *args[MAX_ARGS + 1]; // Additional slot for NULL terminator

    // Read input from stdin until EOF
    while (fgets(line, sizeof(line), stdin)) {
        // Tokenize input line into arguments
        char *token = strtok(line, " \t\n");
        int argc = 0;
        while (token && argc < MAX_ARGS) {
            args[argc++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[argc] = NULL; // Set the last argument to NULL as required by execvp

        if (argc == 0) {
            continue; // Skip empty lines
        }

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("execvp"); // Print error if execution fails
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            wait(NULL); // Wait for the child process to complete
        }
    }
}
#endif /* _SHELL_NONE_INTERACTIVE_ */

```
shell.h
```c
#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Auth: Steve Murimi
 */

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/* Function declarations */
/* shell_interactive.c */
void shell_interactive(void);

/* shell_none_interactive.c */
void shell_none_interactive(void);
#endif /* _SHELL_H_ */
```

Compile: `gcc -Wall -Wextra -Werror -pedantic main.c shell_interactive.c shell_none_interactive.c -o shell`
Run: './shell'
You should be able to interact with the interactive and non-interactive shells

Allowed functions:
    access
    chdir 
    close 
    closedir 
    execve 
    exit 
    _exit 
    fflush 
    fork 
    free
    getcwd 
    getline 
    getpid 
    isatty 
    kill 
    malloc
    open 
    opendir 
    perror 
    read 
    readdir 
    signal 
    stat 
    lstat 
    fstat 
    strtok 
    wait 
    waitpid 
    wait3 
    wait4 
    write 
