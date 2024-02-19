#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* Define error codes */
typedef enum {
    SUCCESS = 0,
    INVALID_PARAMETER,
    INVALID_INPUT,
    EXECUTION_ERROR,
    PERMISSION_DENIED,
    COMMAND_NOT_FOUND
} ErrorCode;

/* Log errors centrally with error code */
void handleError(ErrorCode code) {
    fprintf(stderr, "Error: %s\n", errorMessages[code]);
}

/* Utility function to validate command */
int isValidCommand(char *command) {
    return command && *command;
}

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Searches for and runs a built-in command
 * This function checks if the provided command matches 
 * any built-in commands. It iterates through the
 * builtintbl array, which maps command names to their
 * corresponding functions. If a match is found,
 * it increments the line count and calls the function.
 * 
 * @info: Pointer to info struct containing command details
 *
 * Return: Integer status code indicating if the built-in
 * was found and executed successfully, or what error occurred. 
 */

int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _help},
		{"history", _myhistory},
		{"setenv", _setenv},
		{"getenv", _getenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Searches the PATH environment variable to locate the command
 * This function takes the command provided in info->argv[0] and attempts
 * to find its full path by searching the directories listed in the PATH
 * variable. If a match is found, the full path is stored in info->path.
 * 
 * @info: Pointer to info_t struct containing command details
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!isDelim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Creates a child process to execute the given command.
 * @info: Pointer to info_t struct containing command details
 *
 * Return: void
 */
void fork_cmd(info_t *info) {

  pid_t child_pid;

  child_pid = fork();

  if (child_pid == -1) {
    handleError(EXECUTION_ERROR);
    return;
  }

  if (child_pid == 0) {

    if (execve(info->path, info->argv, environ) == -1) {

      free_info(info, 1);

      if (errno == EACCES) {
        handleError(PERMISSION_DENIED); 
        exit(126);
      }

      handleError(EXECUTION_ERROR);
      exit(1);

    }

  }

}