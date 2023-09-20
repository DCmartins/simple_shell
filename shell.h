#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

/* Used for reading and writing to buffers */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Utilized in command sequencing */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* Used with convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
/* Set to 1 if using system getline() */
#define USE_GETLINE 0

/* Set to 1 if using system strtok() */
#define USE_STRTOK 0

/* Define the history file name */
#define HIST_FILE ".my_shell_history"

/* Define the maximum history size */
#define HIST_MAX 4096

/* Declare the environment variable */
extern char **environ;

/**
 * Definition of a singly linked list node for strings.
 * @num: An integer field within the node.
 * @str: A character string stored in the node.
 * @next: A reference to the next node in the list.
 */

typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;
/**
 * allowing uniform prototype for function pointer struct
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @path: a string path for the current command
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
*/

typedef struct passinfo;
{
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
int err_num;
int linecount_flag;
int argc;
unsigned int line_count;
char *arg;
char **argv;
char *path
char *fname;

/* Reference to cmd: chain buffer used for memory management */
char **cmd_buf;
/* CMD_type: ||, &&, ; */
int cmd_buf_type;
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
                0, 0, 0}
/**
 * struct builtin - stores a builtin command and its associated function
 * @type: command flag
 * @func: function
 */
typedef struct builtin;
{
char *type;
int (*func)(info_t *);
}
builtin_table;

/* toem_parser.c */
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);

/* toem_shloop.c */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* loophsh.c */
int loophsh(char **);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_memory.c */
int bfree(void **);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
 
/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
 int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif                      
