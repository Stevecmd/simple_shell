#ifndef _PROMPT_
#define _PROMPT_

#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point of simple shell
 *
 * This function prompts the user with a "#cisfun$" symbol, reads input from stdin using getline,
 * and echoes the input back to stdout along with the prompt symbol until the user ends input.
 * Memory allocated for each input line is freed after processing.
 *
 * Return: Always 0 to indicate successful completion.
 * Auth: Steve Murimi
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

#endif /* _PROMPT_ */