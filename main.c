#ifndef _MAIN_
#define _MAIN_

#include <stdbool.h> /* For boolean type */

#include "shell.h"

/**
* main - This is the main entry point of the program.
*
* Return: 1 on success, 0 on failure.
*/
/*
 * File: main.c
 * Auth: Steve Murimi
 */

int main(void)
{
	int choice;
	bool valid_choice = false;

	do {
		display_menu();
		choice = read_choice();
		if (choice != -1)
		{
			valid_choice = true;
		}
	} while (!valid_choice);

	/* Execute the selected shell mode */
	if (choice == 1)
	{
		shell_interactive(); /* Execute interactive shell */
	} else
	{
		shell_none_interactive(); /* Execute non-interactive shell */
	}
	return (0);
}

#endif /* _MAIN_ */
