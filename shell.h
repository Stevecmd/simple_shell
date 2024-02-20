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

/* main.c */
void shell_interactive(void);
void shell_no_interactive(void);

/* env-environ */
int main(int ac, char **av, char **env);

/* env-main */
extern char **environ;
int main(void);

/* exec */
int main(void);

/* fork.c */
int main(void);

/* main.c */


/* pid.c */
int main(void);

/* ppid.c */
int main(void);

/* prompt.c */
int main(void);

/* stat.c */
int main(int argc, char *argv[]);

/* test_scripting */


/* wait.c */
int main(void);

/* builtin.c */
int (*get_builtin(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

#endif /* _SHELL_H_ */