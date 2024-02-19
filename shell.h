#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - Main data structure passed between functions,
 *		This structure contains all the information needed to 
 * 		execute commands.
 *@arg: Command line entered by the user
 *@argv: Null-terminated array of tokens from splitting @arg
 *@path: Path of the command being executed 
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()'s
 *@linecount_flag: if on, count this line of input
 *@fname: the filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last executed command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the file descriptor from which to read line input
 *@histcount: Line number of current command in history
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer: Buffer to store multiple commands for chaining */
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - Stores information about built-in commands
 *@type: Name of the built-in command
 *@func: pointer to call for this command
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*_atoi.c */
const char* errorMessages[] = { 
    "No error", 
    "Parameter error", 
    "Invalid input error", 
    "Invalid string error", 
    "Runtime error"
};
void handleError(ErrorCode code, const char* func);
int interactive(info_t* info);
int isDelim(char c, char *delim);
int _isalpha(int char);
int _atoi(char *str);

/*builtin.c */
int _myexit(info_t *commandInfo) ;
int _mycd(info_t *commandInfo);
int _help(info_t* commandInfo);

/*builtin2.c */
int _myhistory(info_t *);
int _myalias(info_t *);
int print_alias(list_t *node);
int set_alias(info_t *info, char *str);
int unset_alias(info_t *info, char *str);

/*shell_loop.c */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/*parser.c */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);

/*errors.c */
void _eputs(char *str);
int _eputchar(char c);
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
void remove_comments(char *buf);

/*errors2.c */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);

/*string.c */
int _strlen(char *s);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/*string2.c */
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

/*exits.c */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/*tokenizeration.c */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

/*realloc.c */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*memory.c */
int free(void **ptr);

/*getLine.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/*getinfo.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/*environ.c */
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

/*getenv.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/*history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/*lists.c */
int add_node(list_t **head, const char *str, int num);
size_t list_len(const list_t *h);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
size_t get_node_index(list_t *head, list_t *node);

/*list2.c */
int add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
char **list_to_strings(list_t *head);

/*vars.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

#endif /* SHELL_H */