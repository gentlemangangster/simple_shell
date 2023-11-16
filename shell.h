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
#define HIST_MAX	4097

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @strng: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *strng;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int tmsh(info_t *, char **);
int builtin_fnd(info_t *);
void fnd_cmd(info_t *);
void frk_cmd(info_t *);

/* toem_parser.c */
int dtm_if_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputstrg(char *);
int _eputstrgchar(char);
int _putdf(char c, int fd);
int _putsdf(char *str, int fd);

/* toem_string.c */
int _strlent(char *);
int _strgcmp(char *, char *);
char *begin_with(const char *, const char *);
char *_strgcat(char *, char *);

/* toem_string1.c */
char *_strgcpy(char *, char *);
char *_strngdup(const char *);
void _putts(char *);
int _sendchar(char);

/* toem_exits.c */
char *_strngcpy(char *, char *, int);
char *_strngcat(char *, char *, int);
char *_strngchr(char *, char);

/* toem_tokenizer.c */
char **strngtow(char *, char *);
char **strngtow2(char *, char);

/* toem_realloc.c */
char *_memoryset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delimt(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void generate_error(info_t *, char *);
int print_d(int, int);
char *change_number(long int, int, int);
void remv_comments(char *); 

/* toem_builtin.c */
int _shelexit(info_t *);
int _tmcd(info_t *);
int _tmhlp(info_t *);

/* toem_builtin1.c */
int _tmhistory(info_t *);
int _tmalias(info_t *);

/*toem_getline.c */
ssize_t get_inpts(info_t *);
int _getline(info_t *, char **, size_t *);
void signintHandler(int);

/* toem_getinfo.c */
void discard_info(info_t *);
void ini_info(info_t *, char **);
void free_dlinfo(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _tmenv(info_t *);
int _tmsetenv(info_t *);
int _tmunsetenv(info_t *);
int addto_env_list(info_t *);

/* toem_getenv.c */
char **gt_enviromt(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *history_get_file(info_t *dl_info);
int wrt_history(info_t *dl_info);
int rd_history(info_t *dl_info);
int build_list_history(info_t *dl_info, char *buff, int linecount);
int renumber_history(info_t *dl_info);

/* toem_lists.c */
list_t *new_node(list_t **, const char *, int);
list_t *add_end_node(list_t **, const char *, int);
size_t strng_list_print(const list_t *);
int delete_nodes(list_t **, unsigned int);
void free_lst(list_t **);

/* toem_lists1.c */
size_t list_lent(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_edex(list_t *, list_t *);

/* toem_vars.c */
int te_chain(info_t *, char *, size_t *);
void chck_chain(info_t *, char *, size_t *, size_t, size_t);
int re_place_alias(info_t *);
int re_place_vars(info_t *);
int re_place_string(char **, char *);

#endif
