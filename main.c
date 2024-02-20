#ifndef _MAIN_
#define _MAIN_

#include "shell.h"

/**
 * main - function that checks if our shell is called
 *        From here it runs the interactive or 
 *        Non-interactive shell depending on the input.
 * 
 * Description: If the shell is called from the command line
 *              the shell will run in interactive mode.
 *              If the shell is called from within another shell
 *              the shell will run in non-interactive mode.
 * 
 * Author: Steve Murimi
 * 
 * Return: 0 on success
 */
int main(void)
{
 if (isatty(STDIN_FILENO) == 1)
 {
  shell_interactive();
 }
 else
 {
  shell_no_interactive();
 }
 return (0);
}

#endif /* _MAIN_ */