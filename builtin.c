#ifndef BUILTIN_C
#define BUILTIN_C

#include <stdio.h>
#include <string.h>
#include "builtin.h"

/*
 * File: builtin.c
 * Auth: Steve Murimi
 */

char *builtin_func_list[] = {
    "cd",
    "env",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &own_cd,
    &own_env,
    &own_help,
    &own_exit
};

int num_builtins = sizeof(builtin_func_list) / sizeof(builtin_func_list[0]);

#endif /* BUILTIN_C */