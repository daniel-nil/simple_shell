#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_ARGS 64
#define MAX_PATH 1024
#define DELIMITERS " \t\r\n\a"

extern char **environ;

typedef struct linkedList
{
	char *str;
	struct linkedList *next;
} LL;

typedef struct alias_node
{
	char *name;
	char *value;
	struct alias_node *next;
} alias_node;

/* cd_shell.c*/
LL *path_list();
void add_node(LL **head_ref, char *str);
void free_list(LL *head);
char *_getenv(const char *name);
char *find_executable(char *command, LL *path_list);

/* env1.c*/
int custom_putenv(char *str);
char *custom_strchr(const char *str, int c);
int custom_environSize(void);

/* env2.c*/
int custom_setenv(const char *name, const char *value, int overwrite);
int custom_unsetenv(const char *name);

/* error.c*/
void shell_setenv(char **args);
void shell_unsetenv(char **args);
void execute_exit(char **tokens);
void execute_env(char **env);

/* error.c*/
int is_empty_line(ssize_t len, char *buf);
int handle_empty_line(char *buf, char **lineptr);
void terminate_buffer(ssize_t len, char *buf);
char *allocate_buffer(size_t buf_size);

/* get_builtin.c*/
void execute_builtins(char **tokens, char **env);

/* get_line.c*/
ssize_t my_getline(char **lineptr, size_t *n, int fd);

/* split_shell.c*/
unsigned int is_delim(char c, char *delim);
char *my_strtok(char *srcString, char *delim);

/* cmd_exec.c*/
int file_input(int argc, char **argv);

/* cmd_exec2.c*/
void handle_semicolon(char *input);
int delim_tokenize(char *input, char **tokens, int max_tokens, char *delim);

/* get_help.c*/
char *read_input(void);
int getStringLength(const char *str);
void printString(char *str);
void writeStringToStderr(char *str);
int my_strcmp(const char *str1, const char *str2);

/*get_help2*/
char *concatenateStrings(char *str1, char *str2);
char *myStrcpy(char *dest, const char *src);
char *myStrcat(char *dest, const char *src);
int myStrncmp(const char *s1, const char *s2, size_t n);
char *my_strdup(const char *str);

/*get_help3*/
void *my_memcpy(void *dest, const void *src, size_t n);
void *my_realloc(void *ptr, size_t size);
int printenv(void);

/*main.c*/
char *command_checker(char **tokens);
void execute(char **tokens);
int tokenize(char *input, char **tokens, int max_tokens);


int execute_cd(char **tokens);
char *expand_buffer(char *buf, size_t buf_size);

#endif
