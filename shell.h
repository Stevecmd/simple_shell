#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Auth: Steve Murimi
 */

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/* Function declarations */

/* prompt.c */
// int get_prompt_choice(void);

/* shell_interactive.c */
void shell_interactive(void);

/* shell_none_interactive.c */
void shell_none_interactive(void);

/* execute_args.c*/
// int execute_args(char **args);

// /* env-environ */
// int environment(int ac, char **av, char **env);

// /* env-main */
// void print_environment(void);

// /* exec */
// int execute_command(void);

// /* fork.c */
// int forking(void);

// /* main.c */


// /* pid.c */
// int get_process_identifier(void);

// /* ppid.c */
// int get_parent_process_identifier(void);

// /* read_line.c */
// char *read_line(void);

// /* read_stream.c */
// char *read_stream(void);
// int handle_buffer_resize(char *line, int i, int *bufsize);

// /* split_line.c */
// char **split_line(char *line);

// /* stat.c */
// int shell_stat(int argc, char *argv[]);

// /* test_scripting */


// /* wait.c */
// int shell_wait(void);



#endif /* _SHELL_H_ */