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
  printf("cisfun$ "); /* print prompt symbol */
  line = read_line(); /* read line from stdin */
  args = split_line(line); /* tokenize line */
  status = execute_args(args);
  /* avoid memory leaks */
  free(line);
  free(args);
  /* exit with status */
  if (status >= 0)
  {
   exit(status);
  }
 } while (status == -1);
}