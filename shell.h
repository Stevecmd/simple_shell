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

#include "common.h"
#include "builtin.h"

/* Function declarations */

/* builtin.c */


/* builtin1.c */
void int_to_string(char *str, int num);

/* common.c */
/* void int_to_string(char *str, int num);*/

/* env-environ */
int environment(char **env);

/* env-main */
void print_environment(void);

/* exec */
int execute_command(void);

/* execute_args.c*/
int execute_args(char **args);
extern int num_builtins;

/* fork.c */
int forking(void);

/* main.c */
int main(void);

/* new_process */
int new_process(char **args);

/* pid.c */
int get_process_identifier(void);

/* ppid.c */
int get_parent_process_identifier(void);

/* prompt.c */
void display_menu(void);
int read_choice(void);

/* read_line.c */
char *read_line(void);

/* read_stream.c */
char *read_stream(void);
int handle_buffer_resize(char *line, int i, int *bufsize);

/* shell_interactive.c */
void shell_interactive(void);

/* shell_none_interactive.c */
void shell_none_interactive(void);

/* split_line.c */
char **split_line(char *line);

/* stat.c */
int shell_stat(int argc, char *argv[]);

/* test_scripting */


/* wait.c */
int shell_wait(void);

#endif /* _SHELL_H_ */