#ifndef _SHELL_INTERACTIVE_
#define _SHELL_INTERACTIVE_
#include "shell.h"

/**
 * shell_interactive - If the interactive mode is enabled,
 *                     this function will be called to run the shell.
 *
 * Description: This function reads lines from stdin, tokenizes them,
 *              and executes the commands. It also handles the exit command.
 *              It will continue to run until the exit command is entered.
 *              It will also handle memory leaks.
 *
 * Return: void
 */
void shell_interactive(void)
{
 char *line;
 char **args;
 int status = -1;

 do {
  printf("cisfun$ ");
  line = read_line();
  args = split_line(line);
  status = execute_args(args);
  free(line);
  free(args);
  if (status >= 0)
  {
   exit(status);
  }
 } while (status == -1);
}

#endif /* _SHELL_INTERACTIVE_ */