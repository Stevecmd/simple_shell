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
#include "shell_macros.h"

typedef struct built_in { char *type; int (*func)(info_t *); } built_in_table;

/* builtin_commands */
int change_directory(info_t *);
int print_command_history(info_t *);
int exit_program(info_t *);
char *strncat_exit(char *, char *, int);

/* alias */
int handle_alias_command(info_t *);
int define_alias(info_t *info, char *str);
char *extract_chars(char *, int, int);


/* utilities */
int print_environment_variable_alias(list_t *node);
int read_line_from_file_descriptor(info_t *info, char **ptr, size_t *length);
void reset_info_structure(info_t *);
int display_program_help(info_t *);
int is_interactive_mode(info_t *);

/* error handling */
void print_error_message(char *);

void remove_comments_from_string_buffer(char *buffer);
int convert_string_to_integer_with_error_handling(char *input_string);
int error_putfd(char c, int fd);
int error_putsfd(char *str, int fd);
char *convert_number_to_string(long int, int, int);

/* error reporting */
void print_error_info(info_t *, char *);
int print_integer_to_fd(int, int);

/* execute commands */
int find_builtin_command(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int print_environment_variables(info_t *);
int unset_environment_variables(info_t *);

/* execute environs*/
char *retrieve_environment_variable_value(info_t *, const char *);
int set_or_update_environment_variable(info_t *, char *, char *);
int remove_environment_variable(info_t *info, char *var);

/* execute processes */
ssize_t read_from_file_descriptor(info_t *file_info, char *buffer, size_t *bytes_read);
void fork_command(info_t *info);
void free_info(info_t *, int);
int populate_env_list(info_t *);
char **get_environ(info_t *);

/* command_execution */
int check_if_path_corresponds_to_known_command(info_t *command_info, char *command_path);
char *find_path(info_t *, char *, char *);
void find_cmd(info_t *);
void handle_sigint(__attribute__((unused)) int signal_number);
ssize_t read_input_buffer(info_t *info, char **buffer, size_t *length);

/* input_processing */
void set_info(info_t *info, char **command_line_arguments);
ssize_t get_input(info_t *);

/* text_processing */
int is_delimiter(char c, char *delimiter_set);
char **strtow(char *input_string, char *delimiters);
int compare_strings(char *string1, char *string2);
int replace_alias(info_t *);
int replace_vars(info_t *);

/* linked_list_printing */
size_t elements_printed(const list_t *head);
size_t print_linked_list_strings(const list_t *);

/* list_operations */
list_t *add_node_to_linked_list(list_t **, const char *, int);
list_t *add_node_to_end_of_linked_list(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
list_t *find_node_with_prefix_and_char(list_t *, char *, char);
ssize_t find_node_index(list_t *, list_t *);

/* linked list utility */
size_t list_length(const list_t *);
char **list_to_strings(list_t *);
void free_linked_list(list_t **);
void free_list(list_t **head_ptr);

/* main.c */







/* memory_functions */
char *custom_memset(char *dest, char value, unsigned int size);
int deallocate_memory_block(void **ptr);
void deallocate(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* string_replacement */
int replace_string(char **, char *);

/* shell_history */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* command_executor */
int run_shell(info_t *, char **);

/* character_operations */
int _isalpha(int character);
char *string_starts_with(const char *, const char *);
char *string_dupy(const char *);
int is_chain(info_t *, char *, size_t *);

/* string_conversion */
int _atoi(char *);
char *exit_strchr(char *, char);
char *exit_strncpy(char *, char *, int);

/* string_utilities.c */
int _putchar(char);
void _puts(char *);
int string_strlen(char *);


int write_char_to_error_buffer(char);
char *string_strcat(char *, char *);
char *string_cpy(char *, char *);

#endif
