#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

typedef enum {
    SUCCESS = 0,
    INVALID_PARAMETER,
    FILE_STAT_ERROR
} ErrorCode;

void handleError(ErrorCode code) {
    const char *errorMessages[] = {
        "Success",
        "Invalid parameter",
        "File stat error"
    };
    fprintf(stderr, "Error: %s\n", errorMessages[code]);
}

/**
 * is_cmd - Checks if a file path points to an executable command
 * 
 * This function determines if the given file path refers to a file
 * that has executable permissions, indicating it is a command.
 * 
 * @info: Pointer to info struct containing command details
 * @path: File path to check
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_cmd(info_t *info, char *path) {
    if (!info || !path) {
        handleError(INVALID_PARAMETER);
        return 0;
    }

    struct stat st;
    if (stat(path, &st) != 0) {
        handleError(FILE_STAT_ERROR);
        return 0;
    }

    return (st.st_mode & S_IFREG) ? 1 : 0;
}

/**
 * dup_chars - Duplicates a substring from a string
 * 
 * This function duplicates a substring from the given path string. It
 * copies characters from index start to stop-1 into a static buffer,
 * terminating it with a null character.
 * 
 * @pathstr: The string to duplicate from
 * @start: The index of the first character to copy
 * @stop: The index after the last character to copy
 *
 * Return: A pointer to the null-terminated buffer 
 * containing the duplicate substring.
 * Returns NULL if any parameters are invalid. 
 */
char *dup_chars(char *pathstr, int start, int stop) {
    static char buf[1024];
    int i = 0, k = 0;

    if (!pathstr || start < 0 || stop < 0) {
        handleError(INVALID_PARAMETER);
        return NULL;
    }

    for (k = 0, i = start; i < stop; i++) {
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    }
    buf[k] = '\0';
    return buf;
}

/**
 * find_path - Searches the PATH environment variable
 * to locate the full path of a command.
 * @info: Pointer to info struct containing command details
 * @pathstr: String containing directories in PATH
 * @cmd: Command to search for
 *
 * Return: Full path of command if found, NULL otherwise
 */
char *find_path(info_t *info, char *pathstr, char *cmd) {
    if (!info || !pathstr || !cmd) {
        handleError(INVALID_PARAMETER);
        return NULL;
    }

    if ((_strlen(cmd) > 2) && starts_with(cmd, "./")) {
        if (is_cmd(info, cmd))
            return cmd;
    }

    int i = 0, curr_pos = 0;
    char *path;

    while (1) {
        if (!pathstr[i] || pathstr[i] == ':') {
            path = dup_chars(pathstr, curr_pos, i);
            if (!*path)
                _strcat(path, cmd);
            else {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (is_cmd(info, path))
                return path;
            if (!pathstr[i])
                break;
            curr_pos = i;
        }
        i++;
    }
    return NULL;
}