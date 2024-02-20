#ifndef _READ_LINE_
#define _READ_LINE_

#include "shell.h"

/**
 * read_line - Reads a line of input from standard input (stdin).
 * 
 * This function dynamically allocates memory to store the input line.
 * If an error occurs during input or memory allocation, appropriate error handling
 * is performed before the program exits.
 *
 * Return: A pointer to the string containing the input line.
 *          Returns NULL if an error occurs or if end-of-file (EOF) is reached.
 */
char *read_line(void)
{
 char *line = NULL;
 size_t bufsize = 0;

 if (getline(&line, &bufsize, stdin) == -1)
 {
  if (feof(stdin))
  {
   free(line);
   exit(EXIT_SUCCESS);
  }
  else
  {
   free(line);
   perror("error while reading the line from stdin");
   exit(EXIT_FAILURE);
  }
 }
 return (line);
}

#endif /* _READ_LINE_ */