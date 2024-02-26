#ifndef BUILTIN_H
#define BUILTIN_H

int own_cd(char **args);
int own_env(char **args);
int own_help(char **args);
int own_exit(char **args);

extern char *builtin_func_list[];
extern int (*builtin_func[])(char **);
extern int num_builtins;

#endif /* BUILTIN_H */