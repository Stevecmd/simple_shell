#ifndef __MAIN__
#define __MAIN__

#include "shell.h"

/**
 * main - This is the entry point for the program.
 * Parses command line arguments, initializes info_t structure,
 * and executes specified command.
 *
 * @ac: Number of command line arguments.
 * @av: Array of command line arguments.
 *
 * Return: 0 on success, otherwise exit failure.
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
				print_error_message(av[0]);
				print_error_message(": 0: Can't open ");
				print_error_message(av[1]);
				write_char_to_error_buffer('\n');
				write_char_to_error_buffer(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	run_shell(info, av);
	return (EXIT_SUCCESS);
}

#endif /* __MAIN__ */
