#ifndef _EXECUTE_ARGS_
#define _EXECUTE_ARGS_

#include "shell.h"
#include <string.h> // Include for strcmp function

/**
* execute_args - Determine whether a command is
*				a built-in or an external process.
*
* This function checks if the given command is a built-in command
* (such as "cd", "env", "help", "exit") or an external process.
* If the command is a built-in, it executes the corresponding function.
* If it's an external process, it forks a new process to execute it.
*
* @args: The command and its arguments.
*
* Return: 1 on success, 0 otherwise
*/

int execute_args(char **args)
{
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
int i = 0;

/* Check if args is NULL */
if (args == NULL)
{
	fprintf(stderr, "execute_args: Null argument\n");
	return (0);
}

/* Check if the command is empty */
if (args[0] == NULL)
{
	fprintf(stderr, "execute_args: Empty command\n");
	return (-1);
}

/* Find if the command is a builtin */
for (i = 0; i < num_builtins; i++)
{
	/* If there is a match, execute the builtin command */
	if (strcmp(args[0], builtin_func_list[i]) == 0)
	{
	return ((*builtin_func[i])(args));
	}
}
	/* If the command is not a builtin, execute it as an external process */
	return (new_process(args));
}

#endif /* _EXECUTE_ARGS_*/
