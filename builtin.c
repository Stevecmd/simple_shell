#ifndef _BUILTIN_
#define _BUILTIN_

#include "shell.h"

/**
 * get_builtin - Matches a command to a corresponding
 *               shell builtin function.
 * @command: The command string to match.
 *
 * Return: A pointer to the corresponding builtin function.
 *         NULL if no builtin is matched.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * shell_exit - Terminate the shell process with a specified exit status.
 * 
 * This function terminates the shell process, allowing the user to exit
 * with a specified exit status code. If no exit status is provided, it exits
 * with the default status code 0.
 * 
 * @args: An array containing the exit status code as a string.
 * @front: A double pointer to the shells command line arguments.
 * @command: The exit command passed by the user.
 * 
 * Return: This function does not return as it exits the program directly.
 */
int shell_exit(char **args, char **front)
{
    int i;
    unsigned int exit_status = 0;
    unsigned int max_int = 1 << (sizeof(int) * 8 - 1);

    if (args[0])
    {
        if (args[0][0] == '+')
            args[0]++;

        for (i = 0; args[0][i]; i++)
        {
            if (args[0][i] >= '0' && args[0][i] <= '9')
                exit_status = (exit_status * 10) + (args[0][i] - '0');
            else
                return (create_error(--args, 2));
        }
    }

    if (exit_status > max_int - 1)
        return (create_error(--args, 2));

    args -= 1;
    free_args(args, front);
    free_env();
    free_alias_list(aliases);
    exit(exit_status);
}

/**
 * shell_cd - Change the current working directory of the shell process.
 * This function changes the current working directory of the shell process
 * based on the provided arguments. If no arguments are provided, it changes
 * the directory to the user's home directory. If a hyphen ('-') is provided
 * as an argument, it changes the directory to the previous working directory.
 * Otherwise, it attempts to change the directory to the specified path.
 * 
 * @args: An array of arguments. If provided, the first argument should be
 *          the path to the target directory.
 * @front: A double pointer to the beginning of the args array.
 *
 * Return: If the specified path is not a directory or cannot be accessed - 2.
 *         If an error occurs during the directory change operation - -1.
 *         If the directory change operation is successful - 0.
 */
int shell_cd(char **args, char __attribute__((__unused__)) **front)
{
    char **dir_info, *new_line = "\n";
    char *old_pwd = NULL, *pwd = NULL;
    struct stat dir;

    old_pwd = getcwd(old_pwd, 0);
    if (!old_pwd)
        return (-1);

    if (args[0])
    {
        if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
        {
            if ((args[0][1] == '-' && args[0][2] == '\0') || args[0][1] == '\0')
            {
                if (_getenv("OLDPWD") != NULL)
                    (chdir(*_getenv("OLDPWD") + 7));
            }
            else
            {
                free(old_pwd);
                return (create_error(args, 2));
            }
        }
        else
        {
            if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) && ((dir.st_mode & S_IXUSR) != 0))
                chdir(args[0]);
            else
            {
                free(old_pwd);
                return (create_error(args, 2));
            }
        }
    }
    else
    {
        if (_getenv("HOME") != NULL)
            chdir(*(_getenv("HOME")) + 5);
    }

    pwd = getcwd(pwd, 0);
    if (!pwd)
        return (-1);

    dir_info = malloc(sizeof(char *) * 2);
    if (!dir_info)
        return (-1);

    dir_info[0] = "OLDPWD";
    dir_info[1] = old_pwd;
    if (shell_setenv(dir_info, dir_info) == -1)
        return (-1);

    dir_info[0] = "PWD";
    dir_info[1] = pwd;
    if (shell_setenv(dir_info, dir_info) == -1)
        return (-1);

    if (args[0] && args[0][0] == '-' && args[0][1] != '-')
    {
        write(STDOUT_FILENO, pwd, _strlen(pwd));
        write(STDOUT_FILENO, new_line, 1);
    }

    free(old_pwd);
    free(pwd);
    free(dir_info);
    return (0);
}


/**
 * shell_help - Displays information about shell built-in commands.
 * 
 * This function takes an array of arguments and displays information about
 * specific shell built-in commands based on the input argument. If no argument
 * is provided, it displays information about all available built-in commands.
 * 
 * @args: An array of arguments. If provided, the first argument specifies the
 *        built-in command for which help information is displayed.
 * @front: A pointer to the beginning of args (not used in this function).
 *
 * Return: If the specified built-in command is found and help information is
 *         displayed successfully - 0.
 *         If an error occurs or an unrecognized command is provided - -1.
 */
int shell_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

#endif /* _BUILTIN_ */