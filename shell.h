#ifndef _SHELL_H_
#define _SHELL_H_

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
#define CMD_NORM0
#define CMD_OR1
#define CMD_AND2
#define CMD_CHAIN3

/* for convert_number() */
#define CONVERT_LOWERCASE1
#define CONVERT_UNSIGNED2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE".simple_shell_history"
#define HIST_MAX4096

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
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* daxx_loop.c */
int simple_shell(info_t *, char **);
int find_builtin_func(info_t *);
void find_command(info_t *);
void execute_command(info_t *);

/* daxx_parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *locate_path(info_t *, char *, char *);

/* shell_loop.c */
int shell_loop(char **);

/* daxx_errors.c */
void error_puts(char *);
int error_putchar(char);
int put_character_fd(char c, int fd);
int put_string_fd(char *str, int fd);

/* daxx_string.c */
int string_length(char *);
int string_compare(char *, char *);
char *starts_with(const char *, const char *);
char *string_concat(char *, char *);

/* daxx_string1.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void puts_string(char *);
int puts_character(char);

/* daxx_exits.c */
char *string_copy_n(char *, char *, int);
char *string_concat_n(char *, char *, int);
char *string_character(char *, char);

/* daxx_tokenizer.c */
char **split_string(char *, char *);
char **split_string2(char *, char);

/* daxx_realloc.c */
char *memory_set(char *, char, unsigned int);
void free_memory(char **);
void *realloc_memory(void *, unsigned int, unsigned int);

/* daxx_memory.c */
int buffer_free(void **);

/* daxx_atoi.c */
int shell_interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_int(char *);

/* daxx_errors1.c */
int error_string_to_int(char *);
void print_error_message(info_t *, char *);
int print_decimal(int, int);
char *number_conversion(long int, int, int);
void remove_comment(char *);

/* daxx_builtin.c */
int shell_exit(info_t *);
int shell_cd(info_t *);
int shell_help(info_t *);

/* daxx_builtin1.c */
int shell_history(info_t *);
int shell_alias(info_t *);

/* daxx_getline.c */
ssize_t read_input(info_t *);
int shell_getline(info_t *, char **, size_t *);
void signal_interrupt_handler(int);

/* daxx_getinfo.c */
void clear_info_data(info_t *);
void set_info_data(info_t *, char **);
void free_info_data(info_t *, int);

/* daxx_environ.c */
char *get_environment(info_t *, const char *);
int shell_env(info_t *);
int shell_setenv(info_t *);
int shell_unsetenv(info_t *);
int populate_environment_list(info_t *);

/* daxx_getenv.c */
char **get_environment_array(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* daxx_history.c */
char *get_history_filepath(info_t *info);
int write_history_data(info_t *info);
int read_history_data(info_t *info);
int build_history_list_data(info_t *info, char *buf, int linecount);
int renumber_history_list(info_t *info);

/* daxx_lists.c */
list_t *add_list_node(list_t **, const char *, int);
list_t *add_list_node_end(list_t **, const char *, int);
size_t print_list_string(const list_t *);
int delete_node_at(list_t **, unsigned int);
void free_list_data(list_t **);

/* daxx_lists1.c */
size_t list_length(const list_t *);
char **list_to_string_array(list_t *);
size_t print_list_content(const list_t *);
list_t *node_starting_with(list_t *, char *, char);
ssize_t get_node_position(list_t *, list_t *);

/* daxx_vars.c */
int is_chain_command(info_t *, char *, size_t *);
void check_chain_command(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_command(info_t *);
int replace_variables(info_t *);
int replace_string_content(char **, char *);

#endif
