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
