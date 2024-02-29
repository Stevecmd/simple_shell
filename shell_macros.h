#ifndef SHELL_MACROS_H
#define SHELL_MACROS_H

#define READ_BUF_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERSION_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct singly_linked_list - Singly linked list node structure
 * @num: Node number
 * @str: String data
 * @next: Pointer to the next node
 *
 * Description: Node structure for a singly linked list.
 */

typedef struct singly_linked_list
{
	int num;
	char *str;
	struct singly_linked_list *next;
} list_t;

/**
 * struct ExecutionInfo - Structure for execution information
 * @arg: Command argument
 * @argv: Array of command arguments
 * @path: Path to the command
 * @file_name: Name of the executable file
 * @environ: Environment variables
 * @command_buf: Command buffer
 * @env: Environment list
 * @history: Command history list
 * @alias: Alias list
 * @argc: Argument count
 * @err_num: Error number
 * @linecount_flag: Line count flag
 * @environ_changed: Flag indicating environment change
 * @cmd_status: Command status
 * @buf_format: Buffer format
 * @readfd: Read file descriptor
 * @history_count: History count
 * @line_count: Line count
 *
 * This structure holds information related to command execution.
 */

typedef struct ExecutionInfo
{
	char *arg, **argv, *path, *file_name, **environ, **command_buf;
	list_t *env, *history, *alias;
	int argc, err_num, linecount_flag, environ_changed,
		cmd_status, buf_format, readfd, history_count;
	unsigned int line_count;
} info_t;

#define INFO_INIT { NULL }

#endif /* SHELL_MACROS_H */
