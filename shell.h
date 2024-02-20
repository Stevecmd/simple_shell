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
void shell_interactive(void);
void shell_none_interactive(void);

/* read_line.c */
char *read_line(void);

/* read_stream.c */
char *read_stream(void);

/* split_line.c */
char **split_line(char *line);

/* stat.c */
int main(int argc, char *argv[]);

/* test_scripting */


/* wait.c */
int main(void);



#endif /* _SHELL_H_ */