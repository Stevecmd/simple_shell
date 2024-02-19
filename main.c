#include "shell.h"

/**
 * main - The main entry point of the shell program.
 * @ac: The number of arguments passed to the program.
 * @av: An array of strings containing the arguments.
 *
 * This function serves as the main entry point for the shell program.
 * It initializes the 'info' structure, sets the file descriptor 'fd' to 2,
 * and checks if the program is executed with a command-line argument.
 * If a file argument is provided, it attempts to open the file for reading.
 * If the file cannot be opened due to permissions or non-existence, it prints
 * an error message and exits with the appropriate exit code. Otherwise,
 * it sets 'readfd' in the 'info' structure to the file descriptor.
 * Then, it populates the environment list, reads the command history,
 * and invokes the shell processing function 'hsh' to start the shell.
 *
 * Return: 0 on success, 1 on error.
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}