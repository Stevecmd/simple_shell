#ifndef _PROMPT_
#define _PROMPT_

#include <unistd.h>
#include "common.h"

/*
 * File: prompt.c
 * Auth: Steve Murimi
 */

/* Function to display the menu and get user's choice */
void display_menu(void) {
    write(STDOUT_FILENO, "Choose shell mode:\n", 19);
    write(STDOUT_FILENO, "1. Interactive shell\n", 22);
    write(STDOUT_FILENO, "2. Non-interactive shell\n", 26);
    write(STDOUT_FILENO, "Enter your choice (1 or 2): ", 29);
}

/* Function to read user's choice */
int read_choice(void) {
    char buffer[2];
    int choice;
    ssize_t bytes_read;
    while ((bytes_read = read(STDIN_FILENO, buffer, 2)) > 0) {
        if (buffer[0] == '1' || buffer[0] == '2') {
            choice = buffer[0] - '0'; /* Convert char to int */
            return choice;
        } else {
            write(STDOUT_FILENO, "Invalid choice. Please enter 1 or 2.\n", 38);
        }
    }
    return -1; /* Error reading choice */
}

#endif /* _PROMPT_ */