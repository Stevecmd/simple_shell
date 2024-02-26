#include "common.h"

/*
 * File: common.c
 * Auth: Steve Murimi
 */

/* Implement the display_menu function */
void display_menu(void) {
	write(STDOUT_FILENO, "Choose shell mode:\n", 19);
	write(STDOUT_FILENO, "1. Interactive shell\n", 22);
	write(STDOUT_FILENO, "2. Non-interactive shell\n", 26);
	write(STDOUT_FILENO, "Enter your choice (1 or 2): ", 29);
}

/* Implement the read_choice function */
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

void int_to_string(char *str, int num) {
	int i = 0;
	int temp = num;
	int len = 0;
	int j;

	/* Calculate the length of the integer */
	while (temp != 0) {
		temp /= 10;
		len++;
	}

	/* Handle the case when the number is negative */
	if (num < 0) {
		str[i++] = '-';
		num = -num;
	}

	/* Convert the integer to a string in reverse order */
	for (j = i + len - 1; j >= i; j--) {
		str[j] = (num % 10) + '0';
		num /= 10;
	}

	/* Null-terminate the string */
	str[i + len] = '\0';
}