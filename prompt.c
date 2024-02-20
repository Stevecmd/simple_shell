#ifndef _PROMPT_
#define _PROMPT_

#include <stdio.h>
#include <stdlib.h>

/**
 * shell_interactive - Entry point of simple shell interactive shell
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

/**
 * shell_none_interactive - Executes the shell in non-interactive mode.
 *
 * This function represents the behavior of the shell when it's not
 * in an interactive mode. It reads input from a stream, tokenizes the input
 * into arguments, executes the command, and frees allocated memory for the input
 * line and arguments.
 * 
 * Return: This function does not return a value.
 * Auth: Steve Murimi
 */

void shell_none_interactive(void)
{
 char *line;
 char **args;
 int status = -1;

 do {
  line = read_stream();
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