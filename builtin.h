#ifndef BUILTIN_H
#define BUILTIN_H

/*
 * File: builtin.h
 * Auth: Steve Murimi
 */

int own_cd(char **args);
int own_env(void);
int own_help(void);
int own_exit(void);

extern char *builtin_func_list[];
extern int (*builtin_func[])(char **);
extern int num_builtins;

#endif /* BUILTIN_H */