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


/* Declare functions */
char *get_location(char *command);
int create_error(char **args, int error_code);
void free_env(void);
void free_args(char **args, char **front);
void free_alias_list(void *aliases);
char **_copyenv(void);
int proc_file_commands(char *filename, int *exe_ret);

/* Declare environ variable */
extern char **environ;

/* Declare variables */
extern char *name;
extern int hist;
extern void *aliases;

/* Main function */
int main(int argc, char *argv[]);



#endif /* _SHELL_H_ */