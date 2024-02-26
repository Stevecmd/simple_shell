#ifndef _STAT_
#define _STAT_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
* shell_stat - Retrieves file information using stat
* @argc: Number of arguments
* @argv: Array of arguments including the filename
*
* This function retrieves information about a file specified
* by the filename provided as the second argument in argv.
* It prints various attributes of the file, such as size, mode,
* device, inode, and number of links.
*
* Return: Always 0
*/

/*
 * File: stat.c
 * Auth: Steve Murimi
 */

int shell_stat(int argc, char *argv[])
{
    struct stat st;

    /* Check if the correct number of arguments is provided */
    if (argc != 2) {
        perror("Usage: stat <filename>");
        exit(EXIT_FAILURE);
    }

    /* Extract the filename from the arguments */
    const char *filename = argv[1];

    /* Retrieve file information using stat */
    if (stat(filename, &st) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    /* Print file attributes */
    write(STDOUT_FILENO, "File: ", 6);
    write(STDOUT_FILENO, filename, strlen(filename));
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}

#endif /* _STAT_ */
