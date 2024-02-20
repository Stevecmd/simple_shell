#ifndef _STAT_
#define _STAT_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(int argc, char *argv[]) {
    struct stat st;

    if (argc != 2) {
        perror("Usage: stat <filename>");
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];

    if (stat(filename, &st) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", st.st_size);
    printf("Mode: %o\n", st.st_mode);
    printf("Device: %ld\n", st.st_dev);
    printf("Inode: %ld\n", st.st_ino);
    printf("Links: %ld\n", st.st_nlink);

    return 0;
}

#endif /* _STAT_ */